package simulator.view;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Frame;
import java.util.List;
import java.util.Map;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.DefaultComboBoxModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableModel;

import org.json.JSONObject;

import simulator.control.Controller;
import simulator.model.BodiesGroup;
import simulator.model.Body;
import simulator.model.SimulatorObserver;

class ForceLawsDialog extends JDialog implements SimulatorObserver {

	private DefaultComboBoxModel<String> _lawsModel;
	private DefaultComboBoxModel<String> _groupsModel;
	private DefaultTableModel _dataTableModel;
	private Controller _ctrl;
	private List<JSONObject> _forceLawsInfo;
	private String[] _headers = { "Key", "Value", "Description" };
	private int _selectedLawsIndex;

	private boolean _status = false;


	ForceLawsDialog(Frame parent, Controller ctrl) {
		super(parent, true);
		_ctrl = ctrl;        
		initGUI();
		// Registrar como observador        
		_ctrl.addObserver(this);          
	}

	private void initGUI() {
		setTitle("Force Laws Selection");
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		setContentPane(mainPanel);

		// _forceLawsInfo se usará para establecer la información en la tabla
		_forceLawsInfo = _ctrl.getForceLawsInfo();  

		
		
		Font font = new Font("SansSerif", Font.PLAIN, 14);
		JLabel label1 =  new JLabel();
		label1.setFont(font);
		label1.setText("<html>Select a force law and provide values for the parameters in the<b> Value Column </b>(default values are used for parameters with no value).</html>");
		label1.setAlignmentX(Component.CENTER_ALIGNMENT);
		
		mainPanel.add(label1);
		mainPanel.add(Box.createRigidArea(new Dimension(700, 20)));
		
		//crear un JTable que use _dataTableModel, y añadirla al panel

		_dataTableModel = new DefaultTableModel() {
			@Override
			public boolean isCellEditable(int row, int column) {
				// hacer editable solo la columna 1
				return column == 1;
			}
		};

		_dataTableModel.setColumnIdentifiers(_headers);	
		JTable _dataTable = new JTable(_dataTableModel);
		JScrollPane scrollPane = new JScrollPane(_dataTable);
		scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);

		mainPanel.add(scrollPane);		

		JPanel panel_aux = new JPanel();
		JPanel panel_aux2 = new JPanel();

		_lawsModel = new DefaultComboBoxModel<>();

		// añadir la descripción de todas las leyes de fuerza a _lawsModel
		for(JSONObject json: _forceLawsInfo) {
			_lawsModel.addElement(json.getString("desc"));
		}

		// crear un combobox que use _lawsModel y añadirlo al panel
		JLabel label2 = new JLabel("Force Law: ");
		JComboBox<String> combobox1 = new JComboBox<>(_lawsModel);	
		combobox1.setSelectedIndex(-1);
		combobox1.addActionListener((e)->{
			
			_dataTableModel.setRowCount(0);
			_selectedLawsIndex = combobox1.getSelectedIndex();			
			JSONObject info = _forceLawsInfo.get(_selectedLawsIndex);
			JSONObject data = info.getJSONObject("data");				
			String [] s_aux = new String[_headers.length];
			for(String str: data.keySet()) {
				s_aux[0] = str;
				s_aux[1] = null;
				s_aux[2] = data.getString(str);
				_dataTableModel.addRow(s_aux);
			}		

		});
		
		combobox1.setSelectedIndex(0);
		_groupsModel = new DefaultComboBoxModel<>();		

		// crear un combobox que use _groupsModel y añadirlo al panel
		JLabel label3 = new JLabel("Group: ");
		JComboBox<String> combobox2 = new JComboBox<>(_groupsModel);

		// crear los botones OK y Cancel y añadirlos al panel
		JButton ok = new JButton("OK");
		ok.addActionListener((e) -> {
			StringBuilder s = new StringBuilder();
			s.append('{');
			try {
				String v = "";
				for (int row = 0; row < _dataTableModel.getRowCount(); row++) {
					
					String k = _dataTableModel.getValueAt(row, 0).toString();
					
					if(_dataTableModel.getValueAt(row, 1) != null) {
						v = _dataTableModel.getValueAt(row, 1).toString();
					}
					else {
						v = "";
					}
					
					if (!v.isEmpty()) {
						s.append('"');
						s.append(k);
						s.append('"');
						s.append(':');
						s.append(v);
						s.append(',');
					}
				}
				if (s.length() > 1)
					s.deleteCharAt(s.length() - 1);
				s.append('}');
				
				JSONObject ok_json = new JSONObject(s.toString());
				// new JSONObject(getJSON());
				JSONObject ok_json2 = new JSONObject();
				ok_json2.put("data", ok_json);
				ok_json2.put("type", _forceLawsInfo.get(_selectedLawsIndex).getString("type"));
				_ctrl.setForcesLaws((String) combobox2.getSelectedItem(), ok_json2);
				_status = true;
				setVisible(false);
			}
			catch(Exception ex) {
				Utils.showErrorMsg("Enter the data in the indicated format");
			}
		});
		
		JButton cancel = new JButton("Cancel");
		cancel.addActionListener((e) -> {
			_status = false;
			setVisible(false);
		});

		panel_aux.setPreferredSize(new Dimension(700, 160));
		
		panel_aux.add(Box.createRigidArea(new Dimension(700, 20)));
		panel_aux.add(label2, BorderLayout.CENTER);
		panel_aux.add(combobox1, BorderLayout.CENTER);

		panel_aux.add(label3, BorderLayout.CENTER);
		panel_aux.add(combobox2, BorderLayout.CENTER);

		panel_aux2.add(cancel);
		panel_aux2.add(ok);

		mainPanel.add(panel_aux);
		mainPanel.add(panel_aux2);

		setPreferredSize(new Dimension(700, 400));
		pack();
		setResizable(false);
		setVisible(false);
	}

	public boolean open() {
		if (_groupsModel.getSize() == 0) {
			Utils.showErrorMsg("Choose an input file");
			return _status;
		}

			// Establecer la posición de la ventana de diálogo de tal manera que se
			// abra en el centro de la ventana principal
		setLocationRelativeTo(getParent());
		pack();
		setVisible(true);
		return _status;
	}

	@Override
	public void onAdvance(Map<String, BodiesGroup> groups, double time) {
	}

	@Override
	public void onReset(Map<String, BodiesGroup> groups, double time, double dt) {
		// Actualizar la lista de grupos de _groupsModel
		_groupsModel.removeAllElements();
	}

	@Override
	public void onRegister(Map<String, BodiesGroup> groups, double time, double dt) {
		// Actualizar la lista de grupos de _groupsModel
		_groupsModel.removeAllElements();
		for (String groupId : groups.keySet()) {
			_groupsModel.addElement(groupId);
		}
	}

	@Override
	public void onGroupAdded(Map<String, BodiesGroup> groups, BodiesGroup g) {
		// Actualizar la lista de grupos de _groupsModel
		_groupsModel.addElement(g.getId());
	}

	@Override
	public void onBodyAdded(Map<String, BodiesGroup> groups, Body b) {
	}

	@Override
	public void onDeltaTimeChanged(double dt) {
	}

	@Override
	public void onForceLawsChanged(BodiesGroup g) {
	}
}