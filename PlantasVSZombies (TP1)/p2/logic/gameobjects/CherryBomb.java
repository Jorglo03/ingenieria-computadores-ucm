package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class CherryBomb extends Plant{

	public static final int COOLDOWN = 2;
	public static final int COST = 50;
	public static final int DAMAGE = 10;
	public static final int ENDURANCE = 2;
	public static final int EXTRA_SCORE_EXPLOSION = 10;
	
	public CherryBomb(GameWorld game, int col, int row) {
		super(game, col, row);
		vida = ENDURANCE;
		ciclos = -1;
	}

	public CherryBomb() {
	}

	@Override
	public int getCost() {
		return COST;
	}

	@Override
	public Plant copy(GameWorld game, int col, int row) {
		return new CherryBomb(game, col, row);
	}

	@Override
	public String getName() {
		return Messages.CHERRY_BOMB_NAME;
	}

	@Override
	protected String getSymbol() {
		if(ciclos == 1) 
			return Messages.CHERRY_BOMB_SYMBOL.toUpperCase();
		else {
			return Messages.CHERRY_BOMB_SYMBOL;
		}
	}

	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.CHERRY_BOMB_NAME_SHORTCUT, COST, DAMAGE, ENDURANCE);
	}

	@Override
	public void onEnter() {
	}

	@Override
	public void onExit() {
	}

	@Override
	public void update() {
		GameItem item;

		ciclos++;
		if(ciclos >= COOLDOWN && isAlive()) {		//Si pasan los ciclos necesarios, explota
			for(int i = col-1; i <= col+1; i++) {
				for(int j = row-1; j <= row + 1; j++) {
					if(!(i == col && j == row)) {
						item = game.getGameItemInPosition(i, j);
						if(item != null ) {  
							if(item.receivePlantAttack(DAMAGE)) {
								game.ifDeath(i, j, EXTRA_SCORE_EXPLOSION);	//Suma score por la explosion
							}
						}
					}
				}
			}
			vida = 0;
		}
	}
}
