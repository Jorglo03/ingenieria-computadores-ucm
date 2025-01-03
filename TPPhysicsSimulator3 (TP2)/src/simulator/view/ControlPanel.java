package simulator.view;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.io.File;
import java.io.FileInputStream;
import java.util.Map;

import javax.swing.Box;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSpinner;
import javax.swing.JTextField;
import javax.swing.JToolBar;
import javax.swing.SpinnerNumberModel;
import javax.swing.SwingUtilities;
import javax.swing.SwingWorker;

import simulator.control.Controller;
import simulator.model.BodiesGroup;
import simulator.model.Body;
import simulator.model.SimulatorObserver;

class ControlPanel extends JPanel implements SimulatorObserver {

	private Controller _ctrl;
	private JToolBar _toolBar;
	private JFileChooser _fc;
	private boolean _stopped = true; //utilizado en los botones de run/stop
	private JButton _quitButton;
	private JButton _gravityButton;
	private JButton _loadButton;
	private JButton _runSimulation;
	private JButton _stopSimulation;
	private JButton _openViewer;
	private JSpinner _steps;
	private JLabel _stepsName;
	private JLabel _delayName;
	private JLabel _simType;
	private JComboBox<String> _simTypeComboBox;
	private JSpinner _delay;
	private JTextField _deltaTime;
	private JLabel _deltaTimeName;
	private ForceLawsDialog _fld;
	private double _defaultDt;

	private String[] simTypes = {"THREAD", "PRACTICA 2", "SWING WORKER"};
	private volatile Thread _thread;
	private SwingWorker<Void,Void> _swingWorker;


	ControlPanel(Controller ctrl) {
		_ctrl = ctrl;
		initGUI();
		//registrar this como observador
		_ctrl.addObserver(this);
	}

	private void initGUI() {
		setLayout(new BorderLayout());
		_toolBar = new JToolBar();
		add(_toolBar, BorderLayout.PAGE_START);

		// crear los diferentes botones/atributos y añadirlos a _toolBar.
		// Todos ellos han de tener su correspondiente tooltip. Puedes utilizar
		// _toolBar.addSeparator() para añadir la línea de separación vertical
		// entre las componentes que lo necesiten
		// Quit Button
		_fc = new JFileChooser("resources/examples/input");

		_loadButton = new JButton(new ImageIcon("resources/icons/open.png"));
		_loadButton.setToolTipText("Load an input file into the simulator");
		_loadButton.addActionListener((e) ->  {
			int val = _fc.showOpenDialog(Utils.getWindow(this));

			if(val == JFileChooser.APPROVE_OPTION) {
				File file = _fc.getSelectedFile();
				try {
					_ctrl.reset();
					_ctrl.loadData(new FileInputStream(file));
				}catch(Exception ex){
					Utils.showErrorMsg(ex.getMessage());
				}
			}
		});
		_toolBar.add(_loadButton);
		_toolBar.addSeparator();



		_gravityButton = new JButton(new ImageIcon("resources/icons/physics.png"));
		_gravityButton.setToolTipText("Select force laws for groups");
		_gravityButton.addActionListener((e) -> {

			if(_fld == null) {
				_fld = new ForceLawsDialog(Utils.getWindow(this), _ctrl);
			}
			_fld.open();

		});
		_toolBar.add(_gravityButton);

		_openViewer = new JButton(new ImageIcon("resources/icons/viewer.png"));
		_openViewer.setToolTipText("Open viewer window");

		_openViewer.addActionListener((e) -> {
			new ViewerWindow((JFrame) Utils.getWindow(this), _ctrl);
		});

		_toolBar.add(_openViewer);
		_toolBar.addSeparator();


		_runSimulation = new JButton(new ImageIcon("resources/icons/run.png"));
		_runSimulation.setToolTipText("Run the simulator");
		_runSimulation.addActionListener(e -> {
			switch(_simTypeComboBox.getSelectedItem().toString()) {

			case "THREAD":
				if (_thread == null) {
					// deshabilita los componentes
					toggleComponents(false);
					_stopSimulation.setEnabled(true);

					// crea un nuevo hilo para ejecutar run_sim_threads
					_thread = new Thread(() -> {
						run_sim_threads((int) _steps.getValue(), (int) _delay.getValue());

						// habilita los componentes
						toggleComponents(true);
						_thread = null;
					});
					_thread.start();
				}
				break;

			case "PRACTICA 2":
				toggleComponents(false);
				_stopped = false;
				try {
					double number = Double.parseDouble(_deltaTime.getText());
					_deltaTime.setText(String.valueOf(number));

					_ctrl.setDeltaTime(number);
					ControlPanel.this.run_sim_practica2((int) _steps.getValue());
				}catch(NumberFormatException nfe) {
					Utils.showErrorMsg("Incorrect delta time");
					toggleComponents(true);
				}
				break;

			case "SWING WORKER":
				if (_swingWorker == null) {
	                // deshabilita los componentes
	                toggleComponents(false);

	                // crea un nuevo SwingWorker para ejecutar run_sim_threads
	                _swingWorker = new SwingWorker<Void, Void>() {
	                    @Override
	                    protected Void doInBackground() throws Exception {
	                        run_sim_swingWorker((int) _steps.getValue(), (int) _delay.getValue());
	                        return null;
	                    }

	                    @Override
	                    protected void done() {
	                        // habilita los componentes
	                        toggleComponents(true);
	                        _swingWorker = null;
	                    }
	                };
	                _swingWorker.execute();
	            }
	            break;
			}


		});
		_toolBar.add(_runSimulation);

		_stopSimulation = new JButton(new ImageIcon("resources/icons/stop.png"));
		_stopSimulation.setToolTipText("Stop the simulator");
		_stopSimulation.addActionListener((e) -> {
			_stopped = true;
			if (_thread != null) {
				_thread.interrupt(); // Interrumpe el hilo para parar la ejecucion
			}
			if (_swingWorker != null && !_swingWorker.isDone()) { // comprueba si el SwingWorker está en ejecución
		        _swingWorker.cancel(true); // cancela la ejecución del SwingWorker
		    }
		});
		_toolBar.add(_stopSimulation);

		_toolBar.addSeparator();


		Font font = new Font("SansSerif", Font.BOLD, 14);
		_delay = new JSpinner(new SpinnerNumberModel(50,0,1000,1));
		_delay.setMaximumSize(new Dimension(200, 35));
		_delay.setToolTipText("Delay");
		_delay.setFont(font);

		_delayName = new JLabel("Delay:");
		_toolBar.add(_delayName);
		_toolBar.add(_delay);

		_simType = new JLabel(" Mode:");


		
		_simTypeComboBox = new JComboBox<>(simTypes);
		_simTypeComboBox.setMaximumSize(new Dimension(250, 25));
		_simTypeComboBox.setToolTipText("Simulation type");
		_toolBar.add(_simType);
		_toolBar.add(_simTypeComboBox);

		_toolBar.addSeparator();

		_steps = new JSpinner(new SpinnerNumberModel(10000,1,10000,100));
		_steps.setMaximumSize(new Dimension(200, 35));
		_steps.setToolTipText("Simulation steps to run: 1-10000");
		_steps.setFont(font);

		_stepsName = new JLabel("Steps:");
		_toolBar.add(_stepsName);
		_toolBar.add(_steps);

		_deltaTime = new JTextField(8);
		_deltaTime.setFont(font);
		_deltaTime.setMaximumSize(new Dimension(200, 35));
		_deltaTime.setToolTipText("Real time (seconds) corresponding to a step");
		_deltaTimeName = new JLabel(" Delta-Time:");
		_toolBar.add(_deltaTimeName);
		_toolBar.add(_deltaTime);



		_toolBar.add(Box.createGlue()); // this aligns the button to the right
		_toolBar.addSeparator();
		_quitButton = new JButton();
		_quitButton.setToolTipText("Quit");
		_quitButton.setIcon(new ImageIcon("resources/icons/exit.png"));
		_quitButton.addActionListener((e) -> Utils.quit(this));
		_toolBar.add(_quitButton);
	}

	private void toggleComponents(boolean state) {
		_loadButton.setEnabled(state);
		_gravityButton.setEnabled(state);
		_runSimulation.setEnabled(state);
		_openViewer.setEnabled(state);
		_steps.setEnabled(state);
		_deltaTime.setEnabled(state);
		_quitButton.setEnabled(state);
		_delay.setEnabled(state);
		_simTypeComboBox.setEnabled(state);
	}

	@Override
	public void onAdvance(Map<String, BodiesGroup> groups, double time) {	
	}

	@Override
	public void onReset(Map<String, BodiesGroup> groups, double time, double dt) {
		_deltaTime.setText(Double.toString(_defaultDt));
		_steps.setValue(Integer.parseInt("10000"));
	}

	@Override
	public void onRegister(Map<String, BodiesGroup> groups, double time, double dt) {
		_defaultDt = dt;
		_deltaTime.setText(Double.toString(dt));
	}

	@Override
	public void onGroupAdded(Map<String, BodiesGroup> groups, BodiesGroup g) {
	}

	@Override
	public void onBodyAdded(Map<String, BodiesGroup> groups, Body b) {
	}

	@Override
	public void onDeltaTimeChanged(double dt) {
		_deltaTime.setText(Double.toString(dt));
	}

	@Override
	public void onForceLawsChanged(BodiesGroup g) {
	}

	private void run_sim_threads(int n, int delay) {

		while (n > 0 && !Thread.interrupted()) {
			try {
				_ctrl.run(1);
			}  catch (Exception e) {
				SwingUtilities.invokeLater(() -> {
					Utils.showErrorMsg(e.getMessage());
					toggleComponents(true);
				});
				return;
			}
			try {
				Thread.sleep(delay);
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt(); 
				return;
			}
			n--;
		}

		// habilita los componentes
		toggleComponents(true);
	}

	private void run_sim_practica2(int n) {

		if (n > 0 && !_stopped) {
			try {
				_ctrl.run(1);
			} catch (Exception e) {

				// llamar a Utils.showErrorMsg con el mensaje de error que corresponda
				Utils.showErrorMsg(e.getMessage());
				// habilita los componentes
				toggleComponents(true);

				_stopped = true;
				return;
			}
			SwingUtilities.invokeLater(() -> run_sim_practica2(n - 1));
		} else {
			// habilita los componentes
			toggleComponents(true);

			_stopped = true;
		}
	}


	private void run_sim_swingWorker(int n, int delay) {
		while (n > 0 && !_swingWorker.isCancelled()) {
	        try {
	            _ctrl.run(1);
	        } catch (Exception e) {
	            SwingUtilities.invokeLater(() -> {
	                Utils.showErrorMsg(e.getMessage());
	                toggleComponents(true);
	            });
	            return;
	        }

	        try {
	            Thread.sleep(delay);
	        } catch (InterruptedException e) {
	            _swingWorker.cancel(true);
	            return;
	        }

	        n--;
	    }

	    // habilita los componentes
	    toggleComponents(true);
	}
}

