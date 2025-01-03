package simulator.view;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.swing.table.AbstractTableModel;

import org.json.JSONObject;

import simulator.control.Controller;
import simulator.model.BodiesGroup;
import simulator.model.Body;
import simulator.model.SimulatorObserver;

class GroupsTableModel extends AbstractTableModel implements SimulatorObserver {
	String[] _header = { "Id", "Force Laws", "Bodies" };
	List<BodiesGroup> _groups;
	
	
	GroupsTableModel(Controller ctrl) {
		_groups = new ArrayList<>();
		//registrar this como observador;
		ctrl.addObserver(this);
	}

	@Override
	public int getRowCount() {
		if(_groups == null) return 0;
		return _groups.size();
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
        String value = null;
        switch(columnIndex){
        case 0:
            value = _groups.get(rowIndex).getId();
            break;
        case 1:
            value = _groups.get(rowIndex).getForceLawsInfo();
            break;
        case 2:
        	value = "";   
            for(Body b:_groups.get(rowIndex)) {
                JSONObject jo = new JSONObject (b.toString());
                value += jo.getString("id") + " ";
            }
            break;
        }
        return value;
    }

	@Override
	public void onAdvance(Map<String, BodiesGroup> groups, double time) {
	}

	@Override
	public void onReset(Map<String, BodiesGroup> groups, double time, double dt) {
		_groups.clear();
		fireTableDataChanged();
	}

	@Override
	public void onRegister(Map<String, BodiesGroup> groups, double time, double dt) {
		_groups.clear();
        _groups.addAll(groups.values());     
        fireTableStructureChanged();
	}

	@Override
	public void onGroupAdded(Map<String, BodiesGroup> groups, BodiesGroup g) {		
		_groups.add(g);
		fireTableStructureChanged();	
	}

	@Override
	public void onBodyAdded(Map<String, BodiesGroup> groups, Body b) {
        fireTableStructureChanged();
	}

	@Override
	public void onDeltaTimeChanged(double dt) {
	}

	@Override
	public void onForceLawsChanged(BodiesGroup g) {
		fireTableDataChanged();
	}

}
