package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;

public abstract class Plant extends GameObject {

	public Plant(GameWorld game, int col, int row) {
		super(game,col,row);
	}

	public Plant() {
	}

	@Override
	public boolean isAlive() {
		return vida > 0;
	}

	@Override
	public boolean receivePlantAttack(int damage) {
		return false;
	}
	
	@Override
	public boolean receiveZombieAttack(int damage) {	//Recibe el danio del zombie
		boolean hit = false;		
		if(isAlive()) {
			vida -= damage;
			hit = true;
		}
		return hit;
	}
	
	abstract public int getCost();
	abstract public Plant copy(GameWorld game, int col, int row);


	@Override
	public boolean catchObject() {
		return false;
	}
	
	public boolean fillPosition() {
		return true;
	}
}
