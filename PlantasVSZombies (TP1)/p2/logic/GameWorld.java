package tp1.p2.logic;

import tp1.p2.control.Level;
import tp1.p2.logic.actions.GameAction;
import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.control.exceptions.GameException;

public interface GameWorld {

	public static final int NUM_ROWS = 4;

	public static final int NUM_COLS = 8;

	void addSun();
	
	boolean addItem(GameObject object);
	
	void update() throws GameException;

	void reset() throws GameException;

	void reset(Level level, long seed) throws GameException;
	
	//void checkValidPlantPosition(int col, int row) throws GameException;

	//void checkValidZombiePosition(int col, int row) throws GameException;

	void playerQuits();

	GameItem getGameItemInPosition(int i, int row);

	boolean isPositionEmpty(int i, int row);

	void operacionRemainingZombies(boolean operacion);

	void operacionZombiesAlived(boolean operacion);

	void tryToBuy(int cost) throws GameException;

	boolean isFullyOcuppied(int col, int row);

	void addCoins(int coins);

	void addGameActions(GameAction action);

	void tryToCatchObject(int col, int row) throws GameException;
	
	void addScore(int score);

	void ifDeath(int col, int row, int score);
	
	String getRecordCommand();
	
	String getResetMessage();
}