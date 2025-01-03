package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class Peashooter extends Plant {

	public static final int COST = 50;
	public static final int DAMAGE = 1;
	public static final int ENDURANCE = 3;

	
	public Peashooter(GameWorld game, int col, int row) {
		super(game,col,row);
		vida = ENDURANCE;
		ciclos = 0;
	}
	
	public Peashooter() {
	}
	
	@Override
	public String getName() {
		return Messages.PEASHOOTER_NAME;
	}
	
	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.PEASHOOTER_NAME_SHORTCUT, COST, DAMAGE, ENDURANCE);
	}
	
	@Override
	protected String getSymbol() {
		return Messages.PEASHOOTER_SYMBOL;
	}

	@Override
	public void update() {
		int i = col+1;
		GameItem item;
		boolean impacto = false;
		
		if(isAlive()) {	//Hace danio al primer zombie que encuentre en su fila
			while(i < GameWorld.NUM_COLS && !impacto) {
				item = game.getGameItemInPosition(i, row);
				if(item != null ) {  
					if(item.receivePlantAttack(DAMAGE))
						impacto = true;
				}
				i++;
			}
		}
	}
	
	
	
	@Override
	public Plant copy(GameWorld game, int col, int row) {
		return new Peashooter(game, col, row);
	}

	@Override
	public int getCost() {
		return COST;
	}

	@Override
	public void onEnter() {
	}

	@Override
	public void onExit() {
	}
}