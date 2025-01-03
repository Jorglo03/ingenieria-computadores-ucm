package simulator.model;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;

import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;

class MovingTowardsFixedPointTest {

	@Test
	void basic_behaviour() {
		Body b1 = new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);
		Body b2 = new MovingBody("earth", "milkyway", new Vector2D(3.0, 4.0), new Vector2D(3.4, 1.2), 20.0);
		Body b3 = new MovingBody("earth", "milkyway", new Vector2D(1.0, 3.0), new Vector2D(3.4, 1.2), 30.0);
		Body b4 = new MovingBody("earth", "milkyway", new Vector2D(4.0, 9.0), new Vector2D(3.4, 1.2), 40.0);

		List<Body> bs = new ArrayList<>();
		bs.add(b1);
		bs.add(b2);
		bs.add(b3);
		bs.add(b4);

		ForceLaws fl = new MovingTowardsFixedPoint(new Vector2D(), 9.8);
		fl.apply(bs);

		assertEquals(new Vector2D(-69.29646455628165, -69.29646455628165), b1.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-117.60000000000002, -156.8), b2.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-92.97096320895035, -278.91288962685104), b3.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-159.20627869295149, -358.2141270591408), b4.getForce(),
				"MovingBody.getForce returned a wrong value");
	}

	@Test
	void errors_handling() {

		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class, () -> new MovingTowardsFixedPoint(new Vector2D(), 0),
				"g cannot be 0");

		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class, () -> new MovingTowardsFixedPoint(new Vector2D(), -1.0),
				"g cannot be 0");

		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class, () -> new MovingTowardsFixedPoint(null, 8.8),
				"c cannot be 0");

	}

}
