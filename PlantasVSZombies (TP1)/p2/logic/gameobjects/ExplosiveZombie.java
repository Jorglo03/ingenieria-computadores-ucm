package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.logic.actions.ExplosionAction;
import tp1.p2.view.Messages;

public class ExplosiveZombie extends Zombie{
	
	public static final int EXPLOSIVE_DAMAGE = 3;
	
	public ExplosiveZombie(GameWorld game, int col, int row) {
		super(game,col,row);
		ciclos = -1;
	}
	
	public ExplosiveZombie() {
	}

	@Override
	public String getName() {
		return Messages.EXPLOSIVE_ZOMBIE_NAME;
	}
	
	@Override
	protected String getSymbol() {
		return Messages.EXPLOSIVE_ZOMBIE_SYMBOL;
	}

	@Override
	public String getDescription() {
		return Messages.zombieDescription(Messages.EXPLOSIVE_ZOMBIE_NAME, SPEED, DAMAGE, ENDURANCE);
	}

	@Override
	public Zombie copy(GameWorld game, int col, int row) {
		return new ExplosiveZombie(game, col, row);
	}
	
	@Override
	public void onExit() {
		game.operacionZombiesAlived(false);		//Se resta
		game.addScore(ZOMBIES_SCORE_ADD);		//Añade el score del zombie por morir
		game.addGameActions(new ExplosionAction(col, row, EXPLOSIVE_DAMAGE));	//Aniade un GameAction de explosion
	}

}
