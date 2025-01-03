package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class Sporty extends Zombie{

	public static final int SPEED = 1;
	public static final int ENDURANCE = 2;
	
	public Sporty(GameWorld game, int col, int row) {
		super(game,col,row);
		vida = ENDURANCE;
		ciclos = -1;
	}
	
	public Sporty() {
	}

	@Override
	public String getName() {
		return Messages.SPORTY_ZOMBIE_NAME;
	}
	
	@Override
	protected String getSymbol() {
		return Messages.SPORTY_ZOMBIE_SYMBOL;
	}

	@Override
	public String getDescription() {
		return Messages.zombieDescription(Messages.SPORTY_ZOMBIE_NAME, SPEED, DAMAGE, ENDURANCE);
	}

	@Override
	public Zombie copy(GameWorld game, int col, int row) {
		return new Sporty(game, col, row);
	}
	
	@Override
	public int getSpeed() {
		return SPEED;
	}
}
