package simulator.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;

public class BodiesGroup implements Iterable<Body>{

	private String _id;
	private ForceLaws _fl;
	private List<Body> _bodies;
	List<Body> _bodiesRO;
	
	public BodiesGroup(String id, ForceLaws fl) {
		if(id == null || fl == null || id.trim().length() == 0) {
			throw new IllegalArgumentException("Invalid bodies group");
		}
		this._id = id;
		this._fl = fl;
		_bodies = new ArrayList<>();
		_bodiesRO = Collections.unmodifiableList(_bodies);

	}
	
	public String getId() {
		return _id;
	}
	
	void setForceLaws(ForceLaws fl) {
		if(fl == null) {
			throw new IllegalArgumentException("Force law is null");
		}
		this._fl = fl;
	}
	
	void addBody(Body b) {
		if(b == null) {
			throw new IllegalArgumentException("Empty body");
		}
		if(this._bodies.contains(b)) {
			throw new IllegalArgumentException("The group already contains the body");//Comprueba que no haya un planeta con ese id en el grupo
		}
//		for(Body b1: _bodies) {
//			if(b1.getId().equals(b.getId())) {		
//				throw new IllegalArgumentException();
//			}
//		}
		_bodies.add(b);
		
	}
	
	void advance(double dt) {
		if(dt <= 0) {
			throw new IllegalArgumentException("Delta time is not valid");
		}
		
		for(Body b: _bodies) {
			b.resetForce();		//Resetea las fuerzas de los bodies
		}
		_fl.apply(_bodies);		//Aplica las fuerzas a los bodies
		for(Body b: _bodies) {			
			b.advance(dt);		//Metodo advance de los bodies
		}
	}
	
	public JSONObject getState() {
		
		JSONArray json_aux = new JSONArray();
		for(int i = 0; i < _bodies.size(); i++) {
			json_aux.put(_bodies.get(i).getState()) ;		//Array de JSONObject bodies
		}
		
		JSONObject json = new JSONObject();
		json.put("id", _id);								//Formato de JSONObject del grupo de bodies
		json.put("bodies", json_aux);
		
		return json;
	}
	
	public String toString() {
		return getState().toString();
	}
	
	public String getForceLawsInfo() {
		return  _fl.toString();
	}

	@Override
	public Iterator<Body> iterator() {
		return _bodiesRO.iterator();
	}
}
