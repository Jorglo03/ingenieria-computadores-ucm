package simulator.factories;

import org.json.JSONObject;

import simulator.model.ForceLaws;
import simulator.model.NewtonUniversalGravitation;

public class NewtonUniversalGravitationBuilder extends Builder<ForceLaws> {
	
	public NewtonUniversalGravitationBuilder() {
		super("nlug", "Newton Universal Gravitation");
	}

	@Override
	protected ForceLaws createInstance(JSONObject data) {	//Si tiene valor se lee, sino, se toma el valor por defecto
		//return new NewtonUniversalGravitation(data.optDouble("G", 6.67E-11));
		return data.has("G") ? new NewtonUniversalGravitation(data.getDouble("G")) : new NewtonUniversalGravitation(6.67E-11);
	}

	@Override
	protected void fillInData(JSONObject data) {
		data.put("G", "Gravitational constant, e.g, 6.67E-11");
	}
	
	
	 
}
