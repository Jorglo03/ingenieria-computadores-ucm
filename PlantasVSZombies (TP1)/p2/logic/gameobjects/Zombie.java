package tp1.p2.logic.gameobjects;

import tp1.p2.view.Messages;
import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameWorld;

public class Zombie extends GameObject{

	public static final int DAMAGE = 1;
	public static final int ENDURANCE = 5;
	public static final int SPEED = 2;
	public static final int ZOMBIES_SCORE_ADD = 10;
	
	public Zombie(GameWorld game, int col, int row) {
		super(game,col,row);
		vida = ENDURANCE;
		ciclos = -1;
	}
	
	public Zombie() {
	}

	@Override
	public boolean receiveZombieAttack(int damage) {
		return false;
	}

	@Override
	public boolean receivePlantAttack(int damage) {
		boolean hit = false;
		if(isAlive()) {
			vida -= damage;
			hit = true;
		}
		return hit;
	}

	@Override
	public String getName() {
		return Messages.ZOMBIE_NAME;
	}
	
	@Override
	protected String getSymbol() {
		return Messages.ZOMBIE_SYMBOL;
	}

	@Override
	public String getDescription() {
		return Messages.zombieDescription(Messages.ZOMBIE_NAME, SPEED, DAMAGE, ENDURANCE);
	}

	@Override
	public void update() {
		GameItem item;
		ciclos++;
		if(isAlive()) {
			if(ciclos >= getSpeed()) {
				ciclos = 0;
				if(!game.isFullyOcuppied(col-1, row)) {	//Si puede, avanza
					col--;
				}
			}
		}
		item = game.getGameItemInPosition(col-1, row);		
		if(item != null ) {  
			item.receiveZombieAttack(DAMAGE);	//Ataca a la siguiente casilla si hay un objeto
		}
	}

	@Override
	public void onEnter() {
		game.operacionRemainingZombies(false);	//Se resta
		game.operacionZombiesAlived(true); //Se suma
	}

	@Override
	public void onExit() {
		game.operacionZombiesAlived(false);	//Se resta
		game.addScore(ZOMBIES_SCORE_ADD);
	}

	public Zombie copy(GameWorld game, int col, int row) {
		return new Zombie(game, col, row);
	}

	@Override
	public boolean isAlive() {
		return vida>0;
	}

	@Override
	public boolean catchObject() {
		return false;
	}
	
	public int getSpeed() {
		return SPEED;
	}
	
	public boolean fillPosition() {
		return true;
	}
}
