package simulator.model;

import java.util.Map;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.HashMap;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class PhysicsSimulator implements Observable<SimulatorObserver> {

	private double _dt;
	private ForceLaws _fl;
	private Map<String,BodiesGroup> _groups;
	//
	private List<String> _gIds;
	//
	private double _actual_t;
	private List<SimulatorObserver> _observerList;
	private Map<String, BodiesGroup> _groupsRO;
	
	
	public PhysicsSimulator(ForceLaws fl, double dt) {
		if(dt < 0 || fl == null) {
			throw new IllegalArgumentException("Invalid arguments to create the PhysicsSimulator");
		}
		this._dt = dt;
		this._fl = fl;
		_groups = new HashMap<>();
		_groupsRO = Collections.unmodifiableMap(_groups);
		_gIds = new ArrayList<>();
		_observerList = new ArrayList<>();
		_actual_t = 0;
	}
	
	public void advance() {
		for(Map.Entry<String, BodiesGroup> entry : _groups.entrySet()) {
			entry.getValue().advance(_dt);
		}
		_actual_t += _dt;				//Se actualiza el tiempo total actual
		//envía una notificación onAdvance a todos los observadores
		for(SimulatorObserver o: _observerList) {
			o.onAdvance(_groupsRO, _actual_t);
		}
	}
	
	public void addGroup(String id) {
		 if (_groups.containsKey(id)) {
	         throw new IllegalArgumentException("There is already a group with the id");
	      }
	      BodiesGroup group = new BodiesGroup(id, _fl);	//Nuevo grupo
	      _groups.put(id, group);
	      _gIds.add(id);
	      //addGroup envía una notificación onGroupAdded a todos los observadores.
	      for(SimulatorObserver o: _observerList) {
	    	  o.onGroupAdded(_groupsRO, group);
	      }
	}
	
	public void addBody(Body b) {
		if (!_groups.containsKey(b.getgId())) {		//Si el grupo del cuerpo no existe, excepcion
	         throw new IllegalArgumentException("The bodies group does not exist");
	    }
		_groups.get(b.getgId()).addBody(b);
		//envía una notificación onBodyAdded a todos los observadores.
		for(SimulatorObserver o: _observerList) {
			o.onBodyAdded(_groupsRO, b);
		}
	}
	
	public void setForceLaws(String id, ForceLaws f) {
		 if(!_groups.containsKey(id)) {				//Si no existe el grupo
	         throw new IllegalArgumentException("The bodies group does not exist");
	     }
	     _groups.get(id).setForceLaws(f);
	     //envía una notificación onDeltaTimeChanged a todos los observadores
	     for(SimulatorObserver o: _observerList) {
	    	 o.onForceLawsChanged(_groupsRO.get(id));
	     }
	
	}
	
	public JSONObject getState() {
		JSONArray json_aux= new JSONArray();
		for(int i = 0; i < _gIds.size(); i++) {
			json_aux.put(_groups.get(_gIds.get(i)).getState())  ;	//Array de JSONObject de los grupos de bodies
		}
		
		JSONObject json = new JSONObject();
		json.put("time", _actual_t);					//Formato del JSONObject del simulador
		json.put("groups", json_aux);
		
		return json;
	}
	
	public String toString() {
		return getState().toString();
	}
	
	public void reset() {
		_groups.clear();
		_gIds.clear();
		_actual_t = 0;
		//envía una notificación onReset a todos los observadores
		for(SimulatorObserver o: _observerList) {
			o.onReset(_groupsRO, _actual_t, _dt);
		}
	}
	
	public void setDeltaTime(double dt) {
		if(dt <= 0) {
			throw new IllegalArgumentException("Delta time is not valid");
		}
		this._dt = dt;
		//envía una notificación onDeltaTimeChanged a todos los observadores
		for(SimulatorObserver o: _observerList) {
			o.onDeltaTimeChanged(dt);
		}
	}

	@Override
	public void addObserver(SimulatorObserver o) {
		if(!_observerList.contains(o)) {
			_observerList.add(o);
		}
		/*envía una notificación onRegister solo al observador que se 
		acaba de registrar, para pasarle el estado actual del simulador*/
		o.onRegister(_groupsRO, _actual_t, _dt);
	}

	@Override
	public void removeObserver(SimulatorObserver o) {
		if(_observerList.contains(o)) {
			_observerList.remove(o);
		}
	}
	
}
