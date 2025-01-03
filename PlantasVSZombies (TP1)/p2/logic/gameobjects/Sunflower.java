package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;


public class Sunflower extends Plant {
	
	public static final int COST = 20;
	public static final int DAMAGE = 0;
	public static final int ENDURANCE = 1;
	public static final int TIME_TO_GENERATE = 3;


	public Sunflower(GameWorld game, int col, int row) {
		super(game,col,row);
		vida = ENDURANCE;
		ciclos = -1;
	}

	public Sunflower() {
	}
	
	@Override
	public String getName() {
		return Messages.SUNFLOWER_NAME;
	}
	
	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.SUNFLOWER_NAME_SHORTCUT, COST, DAMAGE, ENDURANCE);
	}
	
	@Override
	protected String getSymbol() {
		return Messages.SUNFLOWER_SYMBOL;
	}
	
	@Override
	public Plant copy(GameWorld game, int col, int row) {
		return new Sunflower(game, col, row);
	}

	@Override
	public int getCost() {
		return COST;
	}

	@Override
	public void update() {
		ciclos++;
		if(ciclos == TIME_TO_GENERATE && isAlive()) {
			game.addSun();		//Genera un sun
			ciclos = 0;
		}
	}

	@Override
	public void onEnter() {
	}

	@Override
	public void onExit() {
	}

}
