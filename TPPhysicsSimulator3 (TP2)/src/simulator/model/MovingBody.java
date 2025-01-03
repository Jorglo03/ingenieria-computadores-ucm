package simulator.model;

import simulator.misc.Vector2D;

public class MovingBody extends Body{

	public MovingBody(String id, String gid, Vector2D p, Vector2D v, double m) {
		super(id, gid, p, v, m);
	}

	@Override
	void advance(double dt) {
		Vector2D a;
		if(m == 0) {
			a = new Vector2D();
		}
		else {
			a = f.scale(1/m);		//a(V2D) = f(V2D)/m
		}
		p = p.plus(v.scale(dt).plus(a.scale(Math.pow(dt, 2)/2)));	//p(V2D) = p(V2D) + v(V2D)*t + 1/2 * a(V2D) * t^2
		v = v.plus(a.scale(dt));	//v(V2D) = v(V2D) + a(V2D) * t
	}

}
