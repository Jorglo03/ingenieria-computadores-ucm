package simulator.model;

import java.util.List;

import simulator.misc.Vector2D;

public class NewtonUniversalGravitation implements ForceLaws{

	private double _G;
	
	public NewtonUniversalGravitation(double G) {
		if(G <= 0) {
			throw new IllegalArgumentException("Invalid NewtonUniversalGravitation");
		}
		this._G = G;
	}
	
	@Override
	public void apply(List<Body> bs) {
        double fuerza = 0;
        Vector2D d, F = null;
        
        for(Body b1: bs) {
        	Vector2D Ft = new Vector2D();
            for(Body b2: bs) {
                if(b1 != b2) {
                    if(b2.getPosition().distanceTo(b1.getPosition()) > 0)
                        fuerza = (b1.getMass()*(_G*b2.getMass()))/Math.pow(b2.getPosition().distanceTo(b1.getPosition()), 2);
                    	//f = G * (m1 * m2)/(|p2(V2D)-p2(V2D)|^2)
                    else if (b2.getPosition().distanceTo(b1.getPosition()) == 0)
                        fuerza = 0;
                    d = (b2.getPosition().minus(b1.getPosition())).direction();	//d(direccion) = p2(V2D)-p1(V2D)
                    F = d.scale(fuerza);					//F(V2D) = d(V2D) * f
                    Ft = Ft.plus(F);						//FT(V2D) = FT(V2D) + F(V2D)
                }
            }
            b1.addForce(Ft);
        }
    }
	
	public String toString() {
		return "Newton’s Universal Gravitation with G="+_G;
	}
}
