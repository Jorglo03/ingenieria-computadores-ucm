package tp1.p2.logic.actions;

import tp1.p2.logic.GameItem;
import tp1.p2.logic.GameWorld;

public class ExplosionAction implements GameAction {

	private int col;

	private int row;

	private int damage;
	
	public ExplosionAction(int col, int row, int damage) {
		this.col = col;
		this.row = row;
		this.damage = damage;
	}

	@Override
	public void execute(GameWorld game) {	//Hace "damage" a las plantas de las 8 posiciones que rodean una
		GameItem item;
		for(int i = col-1; i <= col + 1; i++) {
			for(int j = row - 1; j <= row + 1; j++) {
				if(!(i == col && j == row)) {
					item = game.getGameItemInPosition(i, j);
					if(item != null) {
						item.receiveZombieAttack(damage);		
					}
				}
			}
		}
	}
}
