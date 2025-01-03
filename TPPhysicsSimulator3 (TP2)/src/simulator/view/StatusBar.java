package simulator.view;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.util.Map;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.SwingUtilities;

import simulator.control.Controller;
import simulator.model.BodiesGroup;
import simulator.model.Body;
import simulator.model.SimulatorObserver;

class StatusBar extends JPanel implements SimulatorObserver {

	private JLabel _currentTime;
	private JLabel _groupsNumber;
	private JLabel _threadsNumber;
	private final JLabel _TIME = new JLabel("Time: ");
	private final JLabel _GROUPS = new JLabel("Groups: ");
	private final JLabel _THREADS = new JLabel("Threads: ");

	StatusBar(Controller ctrl) {
		initGUI();
		//Registrar this como observador
		ctrl.addObserver(this);
	}

	private void initGUI() {
		this.setLayout(new FlowLayout(FlowLayout.LEFT));
		this.setBorder(BorderFactory.createBevelBorder(1));

		//Crear una etiqueta de tiempo y añadirla al panel junto con el separador
		this.add(_TIME);
		_currentTime = new JLabel();
		_currentTime.setPreferredSize(new Dimension(125,20));
		this.add(_currentTime);
		
		//1er separador
		JSeparator s1 = new JSeparator(JSeparator.VERTICAL);
		s1.setPreferredSize(new Dimension(10, 20));
		this.add(s1);
		
		//Crear la etiqueta de número de grupos y añadirla al panel junto con el separador
		this.add(_GROUPS);
		_groupsNumber = new JLabel();
		_groupsNumber.setPreferredSize(new Dimension(125,20));
		this.add(_groupsNumber);
		
		//2o separador
		JSeparator s2 = new JSeparator(JSeparator.VERTICAL);
		s2.setPreferredSize(new Dimension(10, 20));
		this.add(s2);
		
		this.add(_THREADS);
		_threadsNumber = new JLabel();
		_threadsNumber.setPreferredSize(new Dimension(125,20));
		this.add(_threadsNumber);
		
		//Glue
		this.add(Box.createHorizontalGlue());
	}

	@Override
	public void onAdvance(Map<String, BodiesGroup> groups, double time) {
		SwingUtilities.invokeLater(()->{
			_currentTime.setText(Double.toString(time));
			_threadsNumber.setText(Integer.toString(Thread.activeCount()));
		});
	}
	@Override
	public void onReset(Map<String, BodiesGroup> groups, double time, double dt) {
		_currentTime.setText(Double.toString(0.0));
		_groupsNumber.setText(Integer.toString(groups.size()));
		_threadsNumber.setText(Integer.toString(Thread.activeCount()));
	}
	@Override
	public void onRegister(Map<String, BodiesGroup> groups, double time, double dt) {
		onReset(groups,time,dt);
	}
	@Override
	public void onGroupAdded(Map<String, BodiesGroup> groups, BodiesGroup g) {
		_groupsNumber.setText(Integer.toString(groups.size()));
	}
	@Override
	public void onBodyAdded(Map<String, BodiesGroup> groups, Body b) {
		//Implementacion vacia
	}
	@Override
	public void onDeltaTimeChanged(double dt) {
		//Implementacion vacia
	}
	@Override
	public void onForceLawsChanged(BodiesGroup g) {
		//Implementacion vacia
	}
}