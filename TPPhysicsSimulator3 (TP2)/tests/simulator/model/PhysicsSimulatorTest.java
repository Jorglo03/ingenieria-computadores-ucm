package simulator.model;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;

class PhysicsSimulatorTest {


	@Test
	void basic_behaviour() {
		Body b1 = new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);
		Body b2 = new StationaryBody("star", "milkyway", new Vector2D(3.0, 4.0), 20.0);
		Body b3 = new MovingBody("moon", "milkyway", new Vector2D(1.0, 3.0), new Vector2D(3.4, 1.2), 30.0);
		Body b4 = new MovingBody("mars", "milkyway", new Vector2D(4.0, 9.0), new Vector2D(3.4, 1.2), 40.0);

		Body b5 = new MovingBody("B10", "Andromeda", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);
		Body b6 = new StationaryBody("B23", "Andromeda", new Vector2D(3.0, 4.0), 20.0);
		Body b7 = new MovingBody("B09", "Andromeda", new Vector2D(1.0, 3.0), new Vector2D(3.4, 1.2), 30.0);
		Body b8 = new MovingBody("B11", "Andromeda", new Vector2D(4.0, 9.0), new Vector2D(3.4, 1.2), 40.0);

		PhysicsSimulator fs = new PhysicsSimulator(new NewtonUniversalGravitation(10), 2.0);

		fs.addGroup("milkyway");
		fs.addGroup("Andromeda");

		fs.addBody(b1);
		fs.addBody(b2);
		fs.addBody(b3);
		fs.addBody(b4);
		fs.addBody(b5);
		fs.addBody(b6);
		fs.addBody(b7);
		fs.addBody(b8);

		fs.advance();

		assertEquals(new Vector2D(-861.0410635498471, 1490.998893284755), b1.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-163.4082127099694, 302.599778656951), b1.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-168.8082127099694, 299.399778656951), b1.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(10.0, b1.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(-1191.8546412035175, -592.710060018094), b2.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(3.0, 4.0), b2.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(0.0, 0.0), b2.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(20.0, b2.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(2253.2297597797087, -285.48993957989404), b3.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(158.01531731864725, -13.632662638659603), b3.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(153.61531731864724, -17.832662638659603), b3.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(30.0, b3.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(-200.3340550263439, -612.7988936867671), b4.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(0.7832972486828043, -19.239944684338358), b4.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-6.616702751317195, -29.439944684338357), b4.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(40.0, b4.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(-861.0410635498471, 1490.998893284755), b5.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-163.4082127099694, 302.599778656951), b5.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-168.8082127099694, 299.399778656951), b5.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(10.0, b5.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(-1191.8546412035175, -592.710060018094), b6.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(3.0, 4.0), b6.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(0.0, 0.0), b6.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(20.0, b6.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(2253.2297597797087, -285.48993957989404), b7.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(158.01531731864725, -13.632662638659603), b7.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(153.61531731864724, -17.832662638659603), b7.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(30.0, b7.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(-200.3340550263439, -612.7988936867671), b8.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(0.7832972486828043, -19.239944684338358), b8.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-6.616702751317195, -29.439944684338357), b8.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(40.0, b8.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		JSONObject fs1 = new JSONObject(
				"{\"groups\":[{\"bodies\":[{\"p\":[-163.4082127099694,302.599778656951],\"v\":[-168.8082127099694,299.399778656951],\"f\":[-861.0410635498471,1490.998893284755],\"id\":\"earth\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[-1191.8546412035175,-592.710060018094],\"id\":\"star\",\"m\":20},{\"p\":[158.01531731864725,-13.632662638659603],\"v\":[153.61531731864724,-17.832662638659603],\"f\":[2253.2297597797087,-285.48993957989404],\"id\":\"moon\",\"m\":30},{\"p\":[0.7832972486828043,-19.239944684338358],\"v\":[-6.616702751317195,-29.439944684338357],\"f\":[-200.3340550263439,-612.7988936867671],\"id\":\"mars\",\"m\":40}],\"id\":\"milkyway\"},{\"bodies\":[{\"p\":[-163.4082127099694,302.599778656951],\"v\":[-168.8082127099694,299.399778656951],\"f\":[-861.0410635498471,1490.998893284755],\"id\":\"B10\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[-1191.8546412035175,-592.710060018094],\"id\":\"B23\",\"m\":20},{\"p\":[158.01531731864725,-13.632662638659603],\"v\":[153.61531731864724,-17.832662638659603],\"f\":[2253.2297597797087,-285.48993957989404],\"id\":\"B09\",\"m\":30},{\"p\":[0.7832972486828043,-19.239944684338358],\"v\":[-6.616702751317195,-29.439944684338357],\"f\":[-200.3340550263439,-612.7988936867671],\"id\":\"B11\",\"m\":40}],\"id\":\"Andromeda\"}],\"time\":2}\n");
		JSONObject fs2 = new JSONObject(fs.getState().toString());
		assertTrue("PhysicsSimulator.getState retuned a wrong value", fs1.similar(fs2));

		assertTrue("PhysicsSimulator.toString retuned a wrong value", fs1.toString().equals(fs.toString()));

		fs.setForceLaws("milkyway", new NoForce());

		fs.advance();

		assertEquals(new Vector2D(0.0, 0.0), b1.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-501.0246381299082, 901.399335970853), b1.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-168.8082127099694, 299.399778656951), b1.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(10.0, b1.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(0.0, 0.0), b2.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(3.0, 4.0), b2.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(0.0, 0.0), b2.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(20.0, b2.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(0.0, 0.0), b3.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(465.24595195594173, -49.29798791597881), b3.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(153.61531731864724, -17.832662638659603), b3.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(30.0, b3.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(0.0, 0.0), b4.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-12.450108253951587, -78.11983405301507), b4.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-6.616702751317195, -29.439944684338357), b4.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(40.0, b4.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(0.03277511898375951, -0.05259404234645533), b5.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-501.0180831061115, 901.3888171623837), b5.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-168.80165768617266, 299.38925984848174), b5.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(10.0, b5.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(-1.1571835219319688, -14.625250007758806), b6.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(3.0, 4.0), b6.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(0.0, 0.0), b6.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(20.0, b6.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(-0.7399148415595445, 0.020930085883389123), b7.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(465.19662429983777, -49.29659257691991), b7.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(153.56598966254327, -17.83126729960071), b7.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(30.0, b7.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		assertEquals(new Vector2D(1.864323244507754, 14.656913964221872), b8.getForce(),
				"getForce returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-12.356892091726198, -77.38698835480398), b8.getPosition(),
				"getPosition returned a wrong value after calling (sim) advance");
		assertEquals(new Vector2D(-6.5234865890918075, -28.707098986127264), b8.getVelocity(),
				"getVelocity returned a wrong value after calling (sim) advance");
		assertEquals(40.0, b8.getMass(), "MovingBody.getMass returned a wrong value after calling (sim) advance");

		fs1 = new JSONObject(
				"{\"groups\":[{\"bodies\":[{\"p\":[-501.0246381299082,901.399335970853],\"v\":[-168.8082127099694,299.399778656951],\"f\":[0,0],\"id\":\"earth\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[0,0],\"id\":\"star\",\"m\":20},{\"p\":[465.24595195594173,-49.29798791597881],\"v\":[153.61531731864724,-17.832662638659603],\"f\":[0,0],\"id\":\"moon\",\"m\":30},{\"p\":[-12.450108253951587,-78.11983405301507],\"v\":[-6.616702751317195,-29.439944684338357],\"f\":[0,0],\"id\":\"mars\",\"m\":40}],\"id\":\"milkyway\"},{\"bodies\":[{\"p\":[-501.0180831061115,901.3888171623837],\"v\":[-168.80165768617266,299.38925984848174],\"f\":[0.03277511898375951,-0.05259404234645533],\"id\":\"B10\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[-1.1571835219319688,-14.625250007758806],\"id\":\"B23\",\"m\":20},{\"p\":[465.19662429983777,-49.29659257691991],\"v\":[153.56598966254327,-17.83126729960071],\"f\":[-0.7399148415595445,0.020930085883389123],\"id\":\"B09\",\"m\":30},{\"p\":[-12.356892091726198,-77.38698835480398],\"v\":[-6.5234865890918075,-28.707098986127264],\"f\":[1.864323244507754,14.656913964221872],\"id\":\"B11\",\"m\":40}],\"id\":\"Andromeda\"}],\"time\":4}\n");
		fs2 = new JSONObject(fs.getState().toString());
		assertTrue("PhysicsSimulator.getState retuned a wrong value", fs1.similar(fs2));
		assertTrue("PhysicsSimulator.toString retuned a wrong value", fs1.toString().equals(fs.toString()));

	}

	@Test
	void errors_handling() {
		// force laws cannot be null
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new PhysicsSimulator(null, 2.0), "Force laws cannot be null");

		// delta-time must be positive
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new PhysicsSimulator(null, 0.0), "Delta-time must be positive");
		
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new PhysicsSimulator(null, -1.0), "Delta-time must be positive");

		PhysicsSimulator fs = new PhysicsSimulator(new NewtonUniversalGravitation(10), 2.0);

		fs.addGroup("milkyway");
		
		// cannot add a group twice
		assertThrowsExactly(IllegalArgumentException.class,
				() -> fs.addGroup("milkyway"), "Cannot add a group twice");

		// group must exists 
		assertThrowsExactly(IllegalArgumentException.class,
				() -> fs.addBody(new MovingBody("B10", "Andromeda", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0)), "Group must exists");

	}

}
