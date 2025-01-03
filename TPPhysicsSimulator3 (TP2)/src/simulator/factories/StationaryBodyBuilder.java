package simulator.factories;

import org.json.JSONArray;
import org.json.JSONObject;

import simulator.misc.Vector2D;
import simulator.model.Body;
import simulator.model.StationaryBody;


public class StationaryBodyBuilder extends Builder<Body>{

	public StationaryBodyBuilder() {
		super("st_body","Stationary Body");
	}

	@Override
	protected Body createInstance(JSONObject data) {
		if(!data.has("id") || !data.has("gid") ||!data.has("p") || !data.has("m")) {
			throw new IllegalArgumentException("Attributes missing to create the body");	//Si no tiene alguno de los parametros
		}
		
		JSONArray coordinates1 = data.getJSONArray("p");
		if(coordinates1.length() != 2) {			//Si es un array con dos valores(coordenadas)
        	throw new IllegalArgumentException("Error reading the coordinates of the body position vector");
        }
	    Vector2D p = new Vector2D(coordinates1.getDouble(0),coordinates1.getDouble(1)); //Nuevo vector con los valores
	    
		return new StationaryBody(data.getString("id"), data.getString("gid"), p, data.getDouble("m"));
	}

	@Override
	protected void fillInData(JSONObject data) {
		//Implementacion vacia por ser un body
	}
	
}
