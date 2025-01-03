package simulator.factories;

import org.json.JSONArray;
import org.json.JSONObject;

import simulator.misc.Vector2D;
import simulator.model.ForceLaws;
import simulator.model.MovingTowardsFixedPoint;

public class MovingTowardsFixedPointBuilder extends Builder<ForceLaws>{

	public MovingTowardsFixedPointBuilder() {
		super("mtfp","Moving Towards Fixed Point");
	}

	@Override
	protected ForceLaws createInstance(JSONObject data) {
		double g;
		Vector2D c; 
		
		if(data.has("g")) {		//Si tiene el valor se lee
			g =  data.getDouble("g");
		}else {
			g = 9.81;			//Valor por defecto
		}
		if(data.has("c")){		//Si tiene el valor se lee
			JSONArray coordinates1 = data.getJSONArray("c");
			c =  new Vector2D(coordinates1.getDouble(0),coordinates1.getDouble(1));
		}else {
			c = new Vector2D();	//Valor por defecto, un vector (0,0)
		}
		return new MovingTowardsFixedPoint(c, g);
	}

	@Override
	protected void fillInData(JSONObject data) {
		data.put("c", "A 2D vector, e.g., [1e14,1.4e10]");
		data.put("g", "Acceletation towards the fixpoint, e.g, 9.8");
	}

}
