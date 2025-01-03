package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class WallNut extends Plant{

	public static final int COST = 50;
	public static final int ENDURANCE = 10;
	public static final int DAMAGE = 0;
	
	public WallNut(GameWorld game, int col, int row) {
		super(game, col, row);
		vida = ENDURANCE;
	}
	
	public WallNut() {
	}

	@Override
	public int getCost() {
		return COST;
	}

	@Override
	public Plant copy(GameWorld game, int col, int row) {
		return new WallNut(game, col, row);
	}

	@Override
	public String getName() {
		return Messages.WALL_NUT_NAME;
	}

	@Override
	protected String getSymbol() {
		return Messages.WALL_NUT_SYMBOL;
	}

	@Override
	public String getDescription() {
		return Messages.plantDescription(Messages.WALL_NUT_NAME_SHORTCUT, COST, DAMAGE, ENDURANCE);
	}

	@Override
	public void update() {
	}

	@Override
	public void onEnter() {
	}

	@Override
	public void onExit() {
	}

}
