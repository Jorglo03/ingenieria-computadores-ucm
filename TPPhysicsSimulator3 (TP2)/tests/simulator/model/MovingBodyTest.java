package simulator.model;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;

class MovingBodyTest {

	@Test
	void basic_behaviour() {
		Body b = new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);

		// check getters
		assertEquals("earth", b.getId(), "MovingBody.getId returned a wrong value");
		assertEquals("milkyway", b.getgId(), "MovingBody.getgId returned a wrong value");
		assertEquals(new Vector2D(2.0, 2.0), b.getPosition(), "MovingBody.getPosition returned a wrong value");
		assertEquals(new Vector2D(3.4, 1.2), b.getVelocity(), "MovingBody.getVelocity returned a wrong value");
		assertEquals(new Vector2D(), b.getForce(), "MovingBody.getForce returned a wrong value");
		assertEquals(10.0, b.getMass(), "MovingBody.getMass returned a wrong value");

		// check addForce
		b.addForce(new Vector2D(1.1, 2.3));
		assertEquals(new Vector2D(1.1, 2.3), b.getForce(),
				"MovingBody.getForce returned a wrong value after calling addForce");
		b.addForce(new Vector2D(4.9, 2.7));
		assertEquals(new Vector2D(6.0, 5.0), b.getForce(),
				"MovingBody.getForce returned a wrong value after calling addForce");

		// check advance
		b.advance(1.0);
		assertEquals(new Vector2D(5.7, 3.45), b.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling advance");
		assertEquals(new Vector2D(4.0, 1.7), b.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling advance");

		// check getState
		JSONObject bs1 = new JSONObject("{\"p\":[5.7,3.45],\"v\":[4,1.7],\"f\":[6,5],\"id\":\"earth\",\"m\":10}\n");
		JSONObject bs2 = new JSONObject(b.getState().toString());
		assertTrue("MovingBody.getState retuned a wrong value", bs1.similar(bs2));

		// check resetForce
		b.resetForce();
		assertEquals(new Vector2D(), b.getForce(),
				"MovingBody.getForce returned a wrong value after calling resetForce");
		b.addForce(new Vector2D(1.5, 2.5));
		assertEquals(new Vector2D(1.5, 2.5), b.getForce(),
				"MovingBody.getForce returned a wrong value after calling addForce");

		// check advance again
		b.advance(2.0);
		assertEquals(new Vector2D(14.0, 7.35), b.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling advance");
		assertEquals(new Vector2D(4.3, 2.2), b.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling advance");
		bs1 = new JSONObject("{\"p\":[14,7.35],\"v\":[4.3,2.2],\"f\":[1.5,2.5],\"id\":\"earth\",\"m\":10}\n");
		bs2 = new JSONObject(b.getState().toString());
		assertTrue("MovingBody.getState retuned a wrong value", bs1.similar(bs2));
		assertTrue("MovingBody.toString retuned a wrong value", bs1.toString().equals(b.toString()));
		
	}

	@Test
	void errors_handling() {

		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0),
				"Id cannot be empty");

		// id must include at least one char that is no white space
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody(" 	", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0),
				"Id must have at least one char that is not white space");

		// gid cannot be empty
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("earth", "", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0),
				"Id cannot be empty");

		// gid must include at least one char that is no white space
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("eart", " 	", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0),
				"gId must have at least one char that is not white space");

		// id cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody(null, "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0),
				"Id cannot be null");

		// gid cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("earth", null, new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0),
				"gId cannot be null");

		// position cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("earth", "milkyway", null, new Vector2D(3.4, 1.2), 10.0),
				"position vector cannot be null");

		// velocity cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), null, 10.0),
				"velocity vector cannot be null");

		// mass must be positive
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), -10.0),
				"mass cannot be negative");
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 0.0),
				"mass cannot be zero");

	}

}
