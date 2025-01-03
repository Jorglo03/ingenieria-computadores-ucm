package simulator.model;

import static org.junit.Assert.assertTrue;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrowsExactly;

import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.misc.Vector2D;

class BodiesGroupTest {

	@Test
	void basic_behaviour() {
		Body b1 = new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);
		Body b2 = new StationaryBody("star", "milkyway", new Vector2D(3.0, 4.0), 20.0);
		Body b3 = new MovingBody("moon", "milkyway", new Vector2D(1.0, 3.0), new Vector2D(3.4, 1.2), 30.0);
		Body b4 = new MovingBody("mars", "milkyway", new Vector2D(4.0, 9.0), new Vector2D(3.4, 1.2), 40.0);

		BodiesGroup g = new BodiesGroup("milkyway", new NewtonUniversalGravitation(10.0));

		assertEquals("milkyway", g.getId(), "ID should be as the one passed to the constructor");

		g.addBody(b1);
		g.addBody(b2);
		g.addBody(b3);
		g.addBody(b4);

		g.advance(1.0);

		assertEquals(new Vector2D(-861.0410635498471, 1490.998893284755), b1.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-37.652053177492355, 77.74994466423776), b1.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-82.7041063549847, 150.2998893284755), b1.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(10.0, b1.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(-1191.8546412035175, -592.710060018094), b2.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(3, 4), b2.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(0, 0), b2.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(20.0, b2.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(2253.2297597797087, -285.48993957989404), b3.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(41.95382932966181, -0.5581656596649003), b3.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(78.50765865932362, -8.316331319329802), b3.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(30.0, b3.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(-200.3340550263439, -612.7988936867671), b4.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(4.895824312170701, 2.540013828915411), b4.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-1.6083513756585979, -14.119972342169179), b4.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(40.0, b4.getMass(), "MovingBody.getMass returned a wrong value");

		JSONObject gs1 = new JSONObject(
				"{\"bodies\":[{\"p\":[-37.652053177492355,77.74994466423776],\"v\":[-82.7041063549847,150.2998893284755],\"f\":[-861.0410635498471,1490.998893284755],\"id\":\"earth\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[-1191.8546412035175,-592.710060018094],\"id\":\"star\",\"m\":20},{\"p\":[41.95382932966181,-0.5581656596649003],\"v\":[78.50765865932362,-8.316331319329802],\"f\":[2253.2297597797087,-285.48993957989404],\"id\":\"moon\",\"m\":30},{\"p\":[4.895824312170701,2.540013828915411],\"v\":[-1.6083513756585979,-14.119972342169179],\"f\":[-200.3340550263439,-612.7988936867671],\"id\":\"mars\",\"m\":40}],\"id\":\"milkyway\"}\n");
		JSONObject gs2 = new JSONObject(g.getState().toString());
		assertTrue("BodiesGroup.getState retuned a wrong value", gs1.similar(gs2));

		assertTrue("BodiesGroup.toString retuned a wrong value", gs1.toString().equals(g.toString()));

		g.advance(2.0);

		assertEquals(new Vector2D(0.5714319251598272, -0.881966076543702), b1.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-202.9459795024298, 378.17333010588004), b1.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-82.58981996995274, 150.12349611316677), b1.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(10.0, b1.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(1110.7292129027492, -852.7071148541891), b2.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(3, 4), b2.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(0, 0), b2.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(20.0, b2.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(-12.693086225549997, 1.345011462893863), b3.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(198.12294089993904, -17.101160867464912), b3.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(77.66145291095363, -8.226663888470211), b3.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(30.0, b3.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(-1098.6075586023592, 852.2440694678389), b4.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-53.25125636926445, 16.912272617969002), b4.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-56.53872930577656, 28.492231131222773), b4.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(40.0, b4.getMass(), "MovingBody.getMass returned a wrong value");

		gs1 = new JSONObject(
				"{\"bodies\":[{\"p\":[-202.9459795024298,378.17333010588004],\"v\":[-82.58981996995274,150.12349611316677],\"f\":[0.5714319251598272,-0.881966076543702],\"id\":\"earth\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[1110.7292129027492,-852.7071148541891],\"id\":\"star\",\"m\":20},{\"p\":[198.12294089993904,-17.101160867464912],\"v\":[77.66145291095363,-8.226663888470211],\"f\":[-12.693086225549997,1.345011462893863],\"id\":\"moon\",\"m\":30},{\"p\":[-53.25125636926445,16.912272617969002],\"v\":[-56.53872930577656,28.492231131222773],\"f\":[-1098.6075586023592,852.2440694678389],\"id\":\"mars\",\"m\":40}],\"id\":\"milkyway\"}\n");
		gs2 = new JSONObject(g.getState().toString());
		assertTrue("BodiesGroup.getState retuned a wrong value", gs1.similar(gs2));
		assertTrue("BodiesGroup.toString retuned a wrong value", gs1.toString().equals(g.toString()));

		g.setForceLaws(new NoForce());

		g.advance(2.0);

		assertEquals(new Vector2D(), b1.getForce(), "MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-368.1256194423353, 678.4203223322136), b1.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-82.58981996995274, 150.12349611316677), b1.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(10.0, b1.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(), b2.getForce(), "MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(3, 4), b2.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(0, 0), b2.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(20.0, b2.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(), b3.getForce(), "MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(353.4458467218463, -33.55448864440534), b3.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(77.66145291095363, -8.226663888470211), b3.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(30.0, b3.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(), b4.getForce(), "MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-166.32871498081758, 73.89673488041456), b4.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-56.53872930577656, 28.492231131222773), b4.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(40.0, b4.getMass(), "MovingBody.getMass returned a wrong value");

		gs1 = new JSONObject(
				"{\"bodies\":[{\"p\":[-368.1256194423353,678.4203223322136],\"v\":[-82.58981996995274,150.12349611316677],\"f\":[0,0],\"id\":\"earth\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[0,0],\"id\":\"star\",\"m\":20},{\"p\":[353.4458467218463,-33.55448864440534],\"v\":[77.66145291095363,-8.226663888470211],\"f\":[0,0],\"id\":\"moon\",\"m\":30},{\"p\":[-166.32871498081758,73.89673488041456],\"v\":[-56.53872930577656,28.492231131222773],\"f\":[0,0],\"id\":\"mars\",\"m\":40}],\"id\":\"milkyway\"}\n");
		gs2 = new JSONObject(g.getState().toString());
		assertTrue("BodiesGroup.getState retuned a wrong value", gs1.similar(gs2));
		assertTrue("BodiesGroup.toString retuned a wrong value", gs1.toString().equals(g.toString()));

		g.setForceLaws(new MovingTowardsFixedPoint(new Vector2D(), 9.8));

		g.advance(2.0);

		assertEquals(new Vector2D(46.73934077335248, -86.13613657503123), b1.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-523.9573912275703, 961.4400872435408), b1.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-73.24195181528225, 132.89626879816052), b1.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(10.0, b1.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(-117.60000000000002, -156.8), b2.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(3, 4), b2.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(0, 0), b2.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(20.0, b2.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(-292.6840201241436, 27.786046209741638), b3.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(489.2564845354773, -48.15541334069632), b3.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(58.14918490267739, -6.374260807820769), b3.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(30.0, b3.getMass(), "MovingBody.getMass returned a wrong value");
		assertEquals(new Vector2D(358.2358166275974, -159.15746820416064), b4.getForce(),
				"MovingBody.getForce returned a wrong value");
		assertEquals(new Vector2D(-261.49438276099085, 122.92332373265208), b4.getPosition(),
				"MovingBody.getPosition returned a wrong value after calling (group) advance");
		assertEquals(new Vector2D(-38.626938474396695, 20.534357721014743), b4.getVelocity(),
				"MovingBody.getVelocity returned a wrong value after calling (group) advance");
		assertEquals(40.0, b4.getMass(), "MovingBody.getMass returned a wrong value");

		gs1 = new JSONObject(
				"{\"bodies\":[{\"p\":[-523.9573912275703,961.4400872435408],\"v\":[-73.24195181528225,132.89626879816052],\"f\":[46.73934077335248,-86.13613657503123],\"id\":\"earth\",\"m\":10},{\"p\":[3,4],\"v\":[0,0],\"f\":[-117.60000000000002,-156.8],\"id\":\"star\",\"m\":20},{\"p\":[489.2564845354773,-48.15541334069632],\"v\":[58.14918490267739,-6.374260807820769],\"f\":[-292.6840201241436,27.786046209741638],\"id\":\"moon\",\"m\":30},{\"p\":[-261.49438276099085,122.92332373265208],\"v\":[-38.626938474396695,20.534357721014743],\"f\":[358.2358166275974,-159.15746820416064],\"id\":\"mars\",\"m\":40}],\"id\":\"milkyway\"}\n");
		gs2 = new JSONObject(g.getState().toString());
		assertTrue("BodiesGroup.getState retuned a wrong value", gs1.similar(gs2));
		assertTrue("BodiesGroup.toString retuned a wrong value", gs1.toString().equals(g.toString()));

	}

	@Test
	void errors_handling() {
		// id cannot be empty
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new BodiesGroup("", new NewtonUniversalGravitation(10.0)), "Id cannot be empty");

		// id must include at least one char that is no white space
		assertThrowsExactly(IllegalArgumentException.class,
				() -> new BodiesGroup("  ", new NewtonUniversalGravitation(10.0)),
				"Id must have at least one char that is not white space");

		// gid cannot be empty
		assertThrowsExactly(IllegalArgumentException.class, () -> new BodiesGroup("milkyway", null),
				"Force laws cannot be null");

		Body b1 = new MovingBody("earth", "milkyway", new Vector2D(2.0, 2.0), new Vector2D(3.4, 1.2), 10.0);
		Body b2 = new StationaryBody("earth", "milkyway", new Vector2D(3.0, 4.0), 20.0);

		BodiesGroup g = new BodiesGroup("milkyway", new NewtonUniversalGravitation(10.0));

		// bodies in the same group must have different ids
		assertThrowsExactly(IllegalArgumentException.class, () -> {
			g.addBody(b1);
			g.addBody(b2);
		}, "Bodies in a group must have different ids");

		// bodies cannot be null
		assertThrowsExactly(IllegalArgumentException.class, () -> g.addBody(null),
				"Bodies in a group must have different ids");

		// force laws cannot be null
		assertThrowsExactly(IllegalArgumentException.class, () -> g.setForceLaws(null),
				"Bodies in a group must have different ids");

		// Delta time must be positive
		assertThrowsExactly(IllegalArgumentException.class, () -> g.advance(0),
				"Delta time must be positive");

		// Delta time must be positive
		assertThrowsExactly(IllegalArgumentException.class, () -> g.advance(-1.0),
				"Delta time must be positive");

	}

}
