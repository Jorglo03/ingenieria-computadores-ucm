package simulator.model;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;

class NoForceTest {

	@Test
	void basic_behaviour() {
		Body b1 = new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);
		Body b2 = new StationaryBody("earth", "milkyway", new Vector2D(2.0, 2.0), 10.0);

		List<Body> bs = new ArrayList<>();
		bs.add(b1);
		bs.add(b2);

		ForceLaws fl = new NoForce();
		fl.apply(bs);
		
		assertEquals(new Vector2D(), b1.getForce(), "MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(), b2.getForce(), "MovingBody.getForce returned a wrong value");
	}

}
