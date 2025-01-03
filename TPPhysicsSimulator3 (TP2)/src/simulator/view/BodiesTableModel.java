package simulator.view;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import javax.swing.SwingUtilities;
import javax.swing.table.AbstractTableModel;

import simulator.control.Controller;
import simulator.model.BodiesGroup;
import simulator.model.Body;
import simulator.model.SimulatorObserver;

class BodiesTableModel extends AbstractTableModel implements SimulatorObserver {
	String[] _header = { "Id", "gId", "Mass", "Velocity", "Position", "Force" };
	List<Body> _bodies;

	BodiesTableModel(Controller ctrl) {
		_bodies = new ArrayList<>();
		//registrar this como observer
		ctrl.addObserver(this);
	}

	@Override
	public int getRowCount() {
		if (_bodies == null) return 0;
		else return _bodies.size();
	}
	@Override
	public int getColumnCount() {
		return _header.length;
	}

	@Override
	public String getColumnName(int col) {
		return _header[col];
	}

	@Override
	public Object getValueAt(int rowIndex, int columnIndex) {
		Object value = null;
		switch(columnIndex){
		case 0:
			value = _bodies.get(rowIndex).getId();
			break;
		case 1:
			value = _bodies.get(rowIndex).getgId();
			break;
		case 2: 
			value = _bodies.get(rowIndex).getMass();
			break;
		case 3:
			value = _bodies.get(rowIndex).getVelocity();
			break;
		case 4:
			value = _bodies.get(rowIndex).getPosition();
			break;
		case 5: 
			value = _bodies.get(rowIndex).getForce();
			break;
		}
		return value;	
	}

	@Override
	public void onAdvance(Map<String, BodiesGroup> groups, double time) {
		SwingUtilities.invokeLater(()->{
			fireTableDataChanged();
		});
	}
	@Override
	public void onReset(Map<String, BodiesGroup> groups, double time, double dt) {
		_bodies.clear();
		fireTableDataChanged();
	}
	@Override
	public void onRegister(Map<String, BodiesGroup> groups, double time, double dt) {
		_bodies.clear();
		for (BodiesGroup g : groups.values()) {
			for(Body b : g) {
				_bodies.add(b);
			}
		}
		fireTableStructureChanged();
	}
	@Override
	public void onGroupAdded(Map<String, BodiesGroup> groups, BodiesGroup g) {
		for (Body b : g) {           // Iterar sobre los cuerpos del nuevo grupo y agregarlos a la lista de cuerpos
			_bodies.add(b);
		}
		fireTableStructureChanged();
	}
	@Override
	public void onBodyAdded(Map<String, BodiesGroup> groups, Body b) {
		_bodies.add(b);
		fireTableStructureChanged();
	}
	@Override
	public void onDeltaTimeChanged(double dt) {

	}
	@Override
	public void onForceLawsChanged(BodiesGroup g) {

	}
}