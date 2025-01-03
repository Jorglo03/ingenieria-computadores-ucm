package simulator.model;

import java.util.Objects;

import org.json.JSONObject;

import simulator.misc.Vector2D;

public abstract class Body {
	protected String id;
	protected String gid;
	protected Vector2D v;
	protected Vector2D f;
	protected Vector2D p;
	protected double m;
	
	public Body(String id, String gid , Vector2D p, Vector2D v, double m) {
		if(m <= 0 || id == null || gid == null || v == null || p == null || id.trim().length() == 0 || gid.trim().length() == 0) {	
			throw new IllegalArgumentException("Invalid body");
		}
		resetForce();
		this.id = id;
		this.gid = gid;
		this.p = p;
		this.v = v;
		this.m = m;
	}
	
	public String getId() {
		return this.id;
	}
	
	public String getgId() {
		return this.gid;
	}
	
	public Vector2D getVelocity() {
		return this.v;
	}
	
	public Vector2D getForce() {
		return this.f;
	}
	
	public Vector2D getPosition() {
		return this.p;
	}
	
	public double getMass() {
		return m;
	}
	
	void addForce(Vector2D f) {
		this.f = this.f.plus(f);
	}
	
	void resetForce() {
		this.f = new Vector2D();
	}
	
	abstract void advance(double dt);
	
	public JSONObject getState() {
		JSONObject json = new JSONObject();
		json.put("id", id);						//Formato de JSONObject de cada body
		json.put("m", m);
		json.put("p", p.asJSONArray());
		json.put("v", v.asJSONArray());
		json.put("f", f.asJSONArray());
		
		return json;
	}
	
	public String toString() {
		return getState().toString();
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (obj == null)
			return false;
		Body other = (Body) obj;
		return Objects.equals(id, other.id);
	}
}
