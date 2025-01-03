package simulator.model;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;

class StationaryBodyTest {

	@Test
	void basic_behaviour() {
		Body b = new StationaryBody("earth", "milkyway", new Vector2D(2.0, 2.0), 10.0);

		// check getters
		assertEquals("earth", b.getId(), "StationaryBody.getId returned a wrong value");
		assertEquals("milkyway", b.getgId(), "StationaryBody.getgId returned a wrong value");
		assertEquals(new Vector2D(2.0, 2.0), b.getPosition(), "StationaryBody.getPosition returned a wrong value");
		assertEquals(new Vector2D(), b.getVelocity(), "StationaryBody.getVelocity returned a wrong value");
		assertEquals(new Vector2D(), b.getForce(), "StationaryBody.getForce returned a wrong value");
		assertEquals(10.0, b.getMass(), "StationaryBody.getMass returned a wrong value");

		// check addForce
		b.addForce(new Vector2D(1.1, 2.3));
		assertEquals(new Vector2D(1.1, 2.3), b.getForce(),
				"StationaryBody.getForce returned a wrong value after calling addForce");
		b.addForce(new Vector2D(4.9, 2.7));
		assertEquals(new Vector2D(6.0, 5.0), b.getForce(),
				"StationaryBody.getForce returned a wrong value after calling addForce");

		// check advance
		b.advance(1.0);
		assertEquals(new Vector2D(2.0, 2.0), b.getPosition(),
				"StationaryBody.getPosition returned a wrong value after calling advance");
		assertEquals(new Vector2D(), b.getVelocity(),
				"StationaryBody.getVelocity returned a wrong value after calling advance");

		// check getState
		JSONObject bs1 = new JSONObject("{\"p\":[2,2],\"v\":[0,0],\"f\":[6,5],\"id\":\"earth\",\"m\":10}\n");
		JSONObject bs2 = new JSONObject(b.getState().toString());
		assertTrue("StationaryBody.getState retuned a wrong value", bs1.similar(bs2));

		// check resetForce
		b.resetForce();
		assertEquals(new Vector2D(), b.getForce(),
				"StationaryBody.getForce returned a wrong value after calling resetForce");
		b.addForce(new Vector2D(1.5, 2.5));
		assertEquals(new Vector2D(1.5, 2.5), b.getForce(),
				"StationaryBody.getForce returned a wrong value after calling addForce");

		// check advance again
		b.advance(2.0);
		assertEquals(new Vector2D(2.0, 2.0), b.getPosition(),
				"StationaryBody.getPosition returned a wrong value after calling advance");
		assertEquals(new Vector2D(), b.getVelocity(),
				"StationaryBody.getVelocity returned a wrong value after calling advance");
		bs1 = new JSONObject("{\"p\":[2,2],\"v\":[0,0],\"f\":[1.5,2.5],\"id\":\"earth\",\"m\":10}\n");
		bs2 = new JSONObject(b.getState().toString());
		assertTrue("StationaryBody.getState retuned a wrong value", bs1.similar(bs2));
		assertTrue("MovingBody.toString retuned a wrong value", bs1.toString().equals(b.toString()));
	}

	@Test
	void errors_handling() {

		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody("", "milkyway", new Vector2D(2.0, 2.0), 10.0));

		// id must include at least one char that is no white space
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody(" 	", "milkyway", new Vector2D(2.0, 2.0), 10.0));

		// gid cannot be empty
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody("earth", "", new Vector2D(2.0, 2.0), 10.0));

		// gid must include at least one char that is not a white space
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody("eart", " 	", new Vector2D(2.0, 2.0), 10.0));

		// id cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody(null, "milkyway", new Vector2D(2.0, 2.0), 10.0));

		// gid cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody("earth", null, new Vector2D(2.0, 2.0), 10.0));

		// position cannot be null
		assertThrowsExactly(IllegalArgumentException.class, () -> new StationaryBody("earth", "milkyway", null, 10.0));

		// mass must be positive cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody("earth", "milkyway", new Vector2D(2.0, 2.0), -10.0));
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new StationaryBody("earth", "milkyway", new Vector2D(2.0, 2.0), 0.0));

	}

}
