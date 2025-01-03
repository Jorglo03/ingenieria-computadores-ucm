package simulator.factories;

import static org.junit.Assert.assertTrue;
import org.json.JSONObject;
import org.junit.jupiter.api.Test;

import simulator.model.ForceLaws;

class NoForceBuilderTest {

	@Test
	void basic_behaviour() {
		Builder<ForceLaws> fb = new NoForceBuilder();

		assertTrue("Info must include the type tag",fb.getInfo().getString("type").equals(fb.getTypeTag()));
		assertTrue("Descreption cannot be empty",fb.getInfo().getString("desc").trim().length() > 0);

		ForceLaws fl = fb.createInstance(new JSONObject("{}"));
		assertTrue(fl instanceof ForceLaws);
	}

	@Test
	void errors_handling() {
	}
}
