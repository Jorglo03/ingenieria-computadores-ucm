package simulator.model;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;

import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;

class NewtonUniversalGravitationTest {

	@Test
	void basic_behaviour() {
		Body b1 = new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);
		Body b2 = new StationaryBody("earth", "milkyway", new Vector2D(3.0, 4.0), 20.0);
		Body b3 = new MovingBody("earth", "milkyway", new Vector2D(1.0, 3.0), new Vector2D(3.4, 1.2), 30.0);
		Body b4 = new MovingBody("earth", "milkyway", new Vector2D(4.0, 9.0), new Vector2D(3.4, 1.2), 40.0);

		List<Body> bs = new ArrayList<>();
		bs.add(b1);
		bs.add(b2);
		bs.add(b3);
		bs.add(b4);

		ForceLaws fl = new NewtonUniversalGravitation(10);
		fl.apply(bs);

		assertEquals(new Vector2D(-861.0410635498471, 1490.998893284755), b1.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-1191.8546412035175, -592.710060018094), b2.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(2253.2297597797087, -285.48993957989404), b3.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-200.3340550263439, -612.7988936867671), b4.getForce(),
				"MovingBody.getForce returned a wrong value");
	}

	@Test
	void errors_handling() {

		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class, () -> new NewtonUniversalGravitation(0), "G cannot be 0");

		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class, () -> new NewtonUniversalGravitation(-1), "G cannot be negative");

	}

}
