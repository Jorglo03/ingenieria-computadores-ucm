package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class Sun extends GameObject{

	public static final int GENERATE_SUNS = 10;
	
	// Remember that a Sun is updated the very same cycle is added to the container
	public static final int SUN_COOLDOWN = 10 + 1;
	
	public static int catchedSuns = 0;

	public static int generatedSuns = 0;
	
	public Sun(GameWorld game, int col, int row) {
		super(game,col,row);
		vida = SUN_COOLDOWN;
	}
	
	@Override
	public String getName() {
		return null;
	}
	
	@Override
	protected String getSymbol() {
		return Messages.SUN_SYMBOL;
	}

	@Override
	public String getDescription() {
		return Messages.SUN_DESCRIPTION;
	}

	@Override
	public void onEnter() {
		generatedSuns++;
	}

	@Override
	public void onExit() {
	}

	@Override
	public boolean catchObject() {
		game.addCoins(GENERATE_SUNS);	//Se coge el sol, aniadiendo los coins necesarios
		catchedSuns++;
		vida = 0;
		return true;
	}

	@Override
	public boolean receiveZombieAttack(int damage) {
		return false;
	}

	@Override
	public boolean receivePlantAttack(int damage) {
		return false;
	}

	@Override
	public boolean isAlive() {
		return vida > 0;
	}

	@Override
	public void update() {
		if(isAlive())
			vida--;
	}

	@Override
	public boolean fillPosition() {
		return false;
	}
}
