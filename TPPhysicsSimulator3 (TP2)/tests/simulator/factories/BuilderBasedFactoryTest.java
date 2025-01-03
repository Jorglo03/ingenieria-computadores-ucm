package simulator.factories;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;
import simulator.model.Body;
import simulator.model.ForceLaws;
import simulator.model.MovingBody;
import simulator.model.MovingTowardsFixedPoint;
import simulator.model.NewtonUniversalGravitation;
import simulator.model.NoForce;
import simulator.model.StationaryBody;

class BuilderBasedFactoryTest {

	@Test
	void basic_behaviour_1() {

		Builder<Body> b1 = new MovingBodyBuilder();
		Builder<Body> b2 = new StationaryBodyBuilder();
		List<Builder<Body>> l = new ArrayList<>();
		l.add(b1);
		l.add(b2);

		BuilderBasedFactory<Body> fb = new BuilderBasedFactory<>(l);

		assertTrue("Must have two builders", fb.getInfo().size() == 2);

		assertTrue("Type tag of info is like that of builder", fb.getInfo().get(0).getString("type").equals(b1.getTypeTag()));
		assertTrue("Type tag of info is like that of builder", fb.getInfo().get(1).getString("type").equals(b2.getTypeTag()));

		String s = "{ \"type\": \"mv_body\","+ "\"data\": {\n" + "\"id\" : \"b1\",\n" + "	\"gid\": \"g1\",\n" + " \"p\"  : [0.0e00,  4.5e10],\n"
				+ "	\"v\"  : [1.0e04, 0.0e00],\n" + "	\"m\" : 1.5e30\n" + "}}\n";

		Body b = fb.createInstance(new JSONObject(s));

		assertTrue("Should be a Moving body", b instanceof MovingBody);
		
		assertEquals(new Vector2D(0.0, 0.0), b.getForce(), "getForce returned a wrong value");
		assertEquals(new Vector2D(0.0, 4.5E10), b.getPosition(), "getPosition returned a wrong value");
		assertEquals(new Vector2D(10000.0, 0.0), b.getVelocity(), "getVelocity returned a wrong value");
		assertEquals(1.5E30, b.getMass(), "MovingBody.getMass returned a wrong");

		
		s = "{ \"type\": \"st_body\","+ "\"data\": {\n" + "\"id\" : \"b1\",\n" + "	\"gid\": \"g1\",\n" + " \"p\"  : [0.0e00,  4.5e10],\n"
				+  "	\"m\" : 1.5e30\n" + "}}\n";
		
		b = fb.createInstance(new JSONObject(s));

		assertTrue("Should be a Stationary", b instanceof StationaryBody);
		
		assertEquals(new Vector2D(0.0, 0.0), b.getForce(), "getForce returned a wrong value");
		assertEquals(new Vector2D(0.0, 4.5E10), b.getPosition(), "getPosition returned a wrong value");
		assertEquals(1.5E30, b.getMass(), "MovingBody.getMass returned a wrong");

	}

	@Test
	void basic_behaviour_2() {

		Builder<ForceLaws> f1 = new NoForceBuilder();
		Builder<ForceLaws> f2 = new NewtonUniversalGravitationBuilder();
		Builder<ForceLaws> f3 = new MovingTowardsFixedPointBuilder();

		List<Builder<ForceLaws>> l = new ArrayList<>();
		l.add(f1);
		l.add(f2);

		BuilderBasedFactory<ForceLaws> fb = new BuilderBasedFactory<>(l);
		fb.addBuilder(f3);
		
		assertTrue("Must have 3 builders", fb.getInfo().size() == 3);

		assertTrue("Type tag of info is like that of builder", fb.getInfo().get(0).getString("type").equals(f1.getTypeTag()));
		assertTrue("Type tag of info is like that of builder", fb.getInfo().get(1).getString("type").equals(f2.getTypeTag()));
		assertTrue("Type tag of info is like that of builder", fb.getInfo().get(2).getString("type").equals(f3.getTypeTag()));


		ForceLaws fl = null;
		
		fl = fb.createInstance(new JSONObject("{ \"type\": \"nlug\"}"));
		assertTrue("Should be Newton universal laws", fl instanceof NewtonUniversalGravitation);

		fl = fb.createInstance(new JSONObject("{ \"type\": \"mtfp\"}"));
		assertTrue("Should be a Moving towards a fixed point", fl instanceof MovingTowardsFixedPoint);

		fl = fb.createInstance(new JSONObject("{ \"type\": \"nf\"}"));
		assertTrue("Should be a No Force", fl instanceof NoForce);
		
	}

	@Test
	void errors_handling() {
		Builder<ForceLaws> f1 = new NoForceBuilder();
		Builder<ForceLaws> f2 = new NewtonUniversalGravitationBuilder();
		Builder<ForceLaws> f3 = new MovingTowardsFixedPointBuilder();

		List<Builder<ForceLaws>> l = new ArrayList<>();
		l.add(f1);
		l.add(f2);
		l.add(f3);

		BuilderBasedFactory<ForceLaws> fb = new BuilderBasedFactory<>(l);

		// must have id
		assertThrows(Exception.class, () -> {
			fb.createInstance(new JSONObject("{}\n"));
		}, "Should throw an exception if no 'type' is given");

		// must have id
		assertThrowsExactly(IllegalArgumentException.class, () -> {
			fb.createInstance(new JSONObject("{\"type\": \"bla\" }\n"));
		}, "Should throw IllegalArgumentException if no correspoing builder found");

	}

}
