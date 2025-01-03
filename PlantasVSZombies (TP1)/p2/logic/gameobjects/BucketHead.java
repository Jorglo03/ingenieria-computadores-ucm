package tp1.p2.logic.gameobjects;

import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class BucketHead extends Zombie{

	public static final int SPEED = 4;
	public static final int ENDURANCE = 8;
	
	public BucketHead(GameWorld game, int col, int row) {
		super(game,col,row);
		vida = ENDURANCE;
		ciclos = -1;
	}
	
	public BucketHead() {
	}

	@Override
	public String getName() {
		return Messages.BUCKET_HEAD_ZOMBIE_NAME;
	}
	
	@Override
	protected String getSymbol() {
		return Messages.BUCKET_HEAD_ZOMBIE_SYMBOL;
	}

	@Override
	public String getDescription() {
		return Messages.zombieDescription(Messages.BUCKET_HEAD_ZOMBIE_NAME, SPEED, DAMAGE, ENDURANCE);
	}

	@Override
	public Zombie copy(GameWorld game, int col, int row) {
		return new BucketHead(game, col, row);
	}
	
	@Override
	public int getSpeed() {
		return SPEED;
	}
}
