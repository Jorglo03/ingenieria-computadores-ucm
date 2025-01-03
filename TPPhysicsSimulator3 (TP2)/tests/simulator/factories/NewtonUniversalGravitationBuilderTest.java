package simulator.factories;

import static org.junit.Assert.assertTrue;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.model.ForceLaws;
import simulator.model.NewtonUniversalGravitation;

class NewtonUniversalGravitationBuilderTest {

	@Test
	void basic_behaviour() {
		Builder<ForceLaws> fb = new NewtonUniversalGravitationBuilder();

		assertTrue("Info must include the type tag",fb.getInfo().getString("type").equals(fb.getTypeTag()));
		assertTrue("Descreption cannot be empty",fb.getInfo().getString("desc").trim().length() > 0);

		ForceLaws fl = fb.createInstance(new JSONObject("{}"));
		assertTrue(fl instanceof NewtonUniversalGravitation);
		fl = fb.createInstance(new JSONObject("{ \"G\": 10e10}"));
		assertTrue(fl instanceof NewtonUniversalGravitation);

	}

	@Test
	void errors_handling() {
	}
}
