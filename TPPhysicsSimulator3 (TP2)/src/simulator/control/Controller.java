package simulator.control;

import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.util.List;

import org.json.JSONArray;
import org.json.JSONObject;
import org.json.JSONTokener;

import simulator.factories.Factory;
import simulator.model.Body;
import simulator.model.ForceLaws;
import simulator.model.PhysicsSimulator;
import simulator.model.SimulatorObserver;

public class Controller {
	
	private PhysicsSimulator _simulator;
	private Factory<Body> _fb;
	private Factory<ForceLaws> _fl;

	public Controller(PhysicsSimulator simulator, Factory<Body> fb, Factory<ForceLaws> fl) {
		this._simulator = simulator;
		this._fb = fb;
		this._fl = fl;
	}
	
	public void loadData(InputStream in) {
		JSONObject jsonInput = new JSONObject(new JSONTokener(in));
				
		//1-Llama a addGroup del simulador para cada g(i)

		JSONArray groups = jsonInput.getJSONArray("groups");
		for(int i = 0;i<groups.length();i++) {
			_simulator.addGroup(groups.getString(i));
		}
		
		/*for(Object obj: groups ) {				Otra manera
			_simulator.addGroup((String)obj);
		}*/
		
		/*2-Llama a setForceLaws del simulador para cada l(i) (después de convertir l(i) a un objeto de tipo ForceLaws
		    usando la factoría)
		*/
		if(jsonInput.has("laws")) {	
			JSONArray forceLaws = jsonInput.getJSONArray("laws");
			for (int i = 0; i < forceLaws.length(); i++)
				_simulator.setForceLaws(forceLaws.getJSONObject(i).getString("id"),_fl.createInstance(forceLaws.getJSONObject(i).getJSONObject("laws")));
		}
		
		//3-Llama a addBody para cada bb(i) (después de convertir bb(i) a un objeto Body usando la factoría).
		
		JSONArray bodies = jsonInput.getJSONArray("bodies");
		for (int i = 0; i < bodies.length(); i++)
			 _simulator.addBody(_fb.createInstance(bodies.getJSONObject(i)));
		
	}
	
	public void run(int n, OutputStream out) {
		
		PrintStream p = new PrintStream(out);	
		p.print("{\n");								//saltos de linea con "\n"
		p.print("\"states\": [\n");
		p.print(_simulator.getState() + "\n,");
		
		for(int i = 0; i < n; i++) {
			_simulator.advance();
			p.print(_simulator.getState() + "\n");	//Imprime el JSONObject correspondiente al tiempo que se lleve
			if(i < n-1)
				p.print(",");
		}
		
		p.print("]\n");
		p.print("}\n");
	}
	
	public void reset() {
		_simulator.reset();
	}
	
	public void setDeltaTime(double dt) {
		_simulator.setDeltaTime(dt);
	}
	
	public void addObserver(SimulatorObserver o) {
		_simulator.addObserver(o);
	}
	
	public void removeObserver(SimulatorObserver o) {
		_simulator.removeObserver(o);
	}
	
	public List<JSONObject> getForceLawsInfo(){
		return _fl.getInfo();
	}
	
	public void setForcesLaws(String gId, JSONObject info) {
	    //Modifica la ley de fuerza actual del grupo pasado por el gId
	    _simulator.setForceLaws(gId, _fl.createInstance(info));
	}
	
	public void run(int n) {
		for(int i=0; i<n; i++)
			_simulator.advance();
	}
}
