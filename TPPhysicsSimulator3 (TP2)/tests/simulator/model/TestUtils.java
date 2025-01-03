package simulator.model;

import simulator.misc.Vector2D;

public class TestUtils {
	public static void pp(Body b, String n) {
		Vector2D v = b.getVelocity();
		double vx = v.getX();
		double vy = v.getY();

		Vector2D p = b.getPosition();
		double px = p.getX();
		double py = p.getY();

		Vector2D f = b.getForce();
		double fx = f.getX();
		double fy = f.getY();

		double m = b.getMass();

		System.out.println("assertEquals(new Vector2D(" + fx + "," + fy + ")," + n + ".getForce(),\n"
				+ "\"getForce returned a wrong value\");\n" +

				"assertEquals(new Vector2D(" + px + "," + py + ")," + n + ".getPosition(),\n"
				+ "\"getPosition returned a wrong value\");\n" +

				"assertEquals(new Vector2D(" + vx + "," + vy + "), " + n + ".getVelocity(),\n"
				+ "\"getVelocity returned a wrong value\");\n" + "assertEquals(" + m + ", " + n
				+ ".getMass(), \"MovingBody.getMass returned a wrong\");\n" + " ");
	}

}
