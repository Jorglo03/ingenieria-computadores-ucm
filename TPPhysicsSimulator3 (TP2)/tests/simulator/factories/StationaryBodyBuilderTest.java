package simulator.factories;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;
import simulator.model.Body;
import simulator.model.StationaryBody;

class StationaryBodyBuilderTest {

	@Test
	void basic_behaviour() {

		String s = "{\n" + "\"id\" : \"b1\",\n" + "	\"gid\": \"g1\",\n" + " \"p\"  : [0.0e00,  4.5e10],\n"
				+ "	\"m\" : 1.5e30\n" + "}\n";

		JSONObject jo = new JSONObject(s);

		Builder<Body> bb = new StationaryBodyBuilder();

		assertTrue("Info must include the type tag",bb.getInfo().getString("type").equals(bb.getTypeTag()));
		assertTrue("Descreption cannot be empty",bb.getInfo().getString("desc").trim().length() > 0);

		
		Body b = bb.createInstance(jo);

		assertTrue(b instanceof StationaryBody);

		assertEquals(new Vector2D(0.0, 0.0), b.getForce(), "getForce returned a wrong value");
		assertEquals(new Vector2D(0.0, 4.5E10), b.getPosition(), "getPosition returned a wrong value");
		assertEquals(new Vector2D(), b.getVelocity(), "getVelocity returned a wrong value");
		assertEquals(1.5E30, b.getMass(), "MovingBody.getMass returned a wrong");
	}

	@Test
	void errors_handling() {

		Builder<Body> bb = new StationaryBodyBuilder();

		// must have id
		assertThrowsExactly(IllegalArgumentException.class, () -> {
			String s = "{\n" + "	\"gid\": \"g1\",\n" + " \"p\"  : [0.0e00,  4.5e10],\n" + "	\"m\" : 1.5e30\n"
					+ "}\n";
			JSONObject jo = new JSONObject(s);
			bb.createInstance(jo);
		}, "Must have id");

		// must have gid
		assertThrowsExactly(IllegalArgumentException.class, () -> {
			String s = "{\n" + "\"id\" : \"b1\",\n" + " \"p\"  : [0.0e00,  4.5e10],\n" + "	\"m\" : 1.5e30\n" + "}\n";
			JSONObject jo = new JSONObject(s);
			bb.createInstance(jo);
		}, "Must have gid");

		// must have p
		assertThrowsExactly(IllegalArgumentException.class, () -> {
			String s = "{\n" + "\"id\" : \"b1\",\n" + "	\"gid\": \"g1\",\n" + "	\"m\" : 1.5e30\n" + "}\n";
			JSONObject jo = new JSONObject(s);
			bb.createInstance(jo);
		}, "Must have p");

		// must have m
		assertThrowsExactly(IllegalArgumentException.class, () -> {
			String s = "{\n" + "\"id\" : \"b1\",\n" + "	\"gid\": \"g1\",\n" + " \"p\"  : [0.0e00,  4.5e10],\n" + "}\n";
			JSONObject jo = new JSONObject(s);
			bb.createInstance(jo);
		}, "ddd");

		// p must be 2D
		assertThrowsExactly(IllegalArgumentException.class, () -> {
			String s = "{\n" + "\"id\" : \"b1\",\n" + "	\"gid\": \"g1\",\n" + " \"p\"  : [0,0.0e00,  4.5e10],\n"
					+ "	\"m\" : 1.5e30\n" + "}\n";
			JSONObject jo = new JSONObject(s);
			bb.createInstance(jo);
		}, "p must be 2D");

	}

}
