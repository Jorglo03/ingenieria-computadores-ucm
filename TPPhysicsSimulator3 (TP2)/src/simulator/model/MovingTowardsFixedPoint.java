package simulator.model;

import java.util.List;

import simulator.misc.Vector2D;

public class MovingTowardsFixedPoint implements ForceLaws{

	private Vector2D _c;
	private double _g;
	
	public MovingTowardsFixedPoint(Vector2D c, double g) {
		if(c == null || g <= 0) {
			throw new IllegalArgumentException("Invalid MovingTowardsFixedPoint");
		}
		this._c = c;
		this._g = g;
	}
	
	@Override
	public void apply(List<Body> bs) {
		Vector2D d;
		for(Body b: bs) {
			d = (_c.minus(b.getPosition())).direction();	//d(direccion) = c(V2D) - p(V2D)
			b.addForce(d.scale(b.getMass()*_g));			//d(V2D) * m(V2D) * g		
		}
	}
	
	@Override
	public String toString() {
		return "Moving towards "+_c+" with constant acceleration "+_g;
	}
}
