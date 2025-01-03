package simulator.model;

import java.util.List;

public class NoForce implements ForceLaws{

	@Override
	public void apply(List<Body> bs) {	//No hay fuerza
	}

	public String toString() {
		return "No Force";
	}
}
