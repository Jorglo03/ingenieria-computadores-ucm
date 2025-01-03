package simulator.factories;

import org.json.JSONArray;
import org.json.JSONObject;

import simulator.misc.Vector2D;
import simulator.model.Body;
import simulator.model.MovingBody;


public class MovingBodyBuilder extends Builder<Body>{

	public MovingBodyBuilder() {
		super("mv_body", "Moving Body");
	}

	@Override
	protected Body createInstance(JSONObject data) {
		if(!data.has("id") || !data.has("gid") ||!data.has("p") || !data.has("v") || !data.has("m")) {
			throw new IllegalArgumentException("Attributes missing to create the body");		//Si no tiene alguno de los parametros
		}
		
        JSONArray coordinates1 = data.getJSONArray("p");
        if(coordinates1.length() != 2) {		//Si es un array con dos valores(coordenadas)
        	throw new IllegalArgumentException("Error reading the coordinates of the body position vector");
        }
        Vector2D p = new Vector2D (coordinates1.getDouble(0),coordinates1.getDouble(1));	//Nuevo vector con los valores
        
        coordinates1 = data.getJSONArray("v");
        if(coordinates1.length() != 2) {		//Si es un array con dos valores(coordenadas)
        	throw new IllegalArgumentException("Error reading the coordinates of the body position vector");
        }
        Vector2D v = new Vector2D(coordinates1.getDouble(0),coordinates1.getDouble(1)); //Nuevo vector con los valores
        
		return new MovingBody(data.getString("id"), data.getString("gid"), p, v, data.getDouble("m"));
	}

	@Override
	protected void fillInData(JSONObject data) {
		//Implementacion vacia por ser un body
	}

}
