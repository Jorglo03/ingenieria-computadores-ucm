package tp1.p2.logic;

//import static tp1.p2.view.Messages.error;

import java.util.ArrayDeque;
import java.util.Deque;
//import java.util.List;
import java.util.Random;

import tp1.p2.control.Command;
import tp1.p2.control.exceptions.GameException;
import tp1.p2.control.exceptions.NotCatchablePositionException;
import tp1.p2.control.exceptions.NotEnoughCoinsException;
import tp1.p2.control.exceptions.RecordException;
import tp1.p2.control.Level;
import tp1.p2.logic.actions.AddGameItemAction;
import tp1.p2.logic.actions.GameAction;
import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.logic.gameobjects.Sun;
import tp1.p2.view.Messages;

public class Game implements GameStatus, GameWorld {

	private long seed;

	private Level level;

	private int cycle;
	
	private int suncoins;
	
	private int score;
	
	private int score_saved;
	
	private Random rand;
	
	private GameObjectContainer container;

	private ZombiesManager zombiesManager;
	
	private SunsManager sunsManager;
	
	private Record record;
	
	private boolean playerQuits = false;
	private boolean allZombiesDied = false;
	private boolean isPlayerDied = false;
	
	private Deque<GameAction> actions;

	public Game(long seed, Level level) throws GameException {
		this.seed = seed;
		this.level = level;
		this.container = new GameObjectContainer();
		reset();
	}

	/**
	 * Resets the game.
	 */
	@Override
	public void reset() throws GameException {
		reset(this.level, this.seed);
	}

	/**
	 * Resets the game with the provided level and seed.
	 * 
	 * @param level {@link Level} Used to initialize the game.
	 * @param seed Random seed Used to initialize the game.
	 */
	@Override
	public void reset(Level level, long seed) throws GameException {
		this.level = level;
		this.seed = seed;
		container.clear();
		rand = new Random(seed);
		zombiesManager = new ZombiesManager(this,level,rand);
		sunsManager = new SunsManager(this, rand);
		record = new Record(level.name());
		score_saved = record.load();
		this.suncoins = 50;
		this.cycle = 0;
		this.score = 0;
		this.actions = new ArrayDeque<>();
	}


	/**
	 * Executes the game actions and update the game objects in the board.
	 * 
	 */
	@Override
	public void update() throws GameException {

		// 1. Execute pending actions
		executePendingActions();

		// 2. Execute game Actions
		zombiesManager.update();
		sunsManager.update();

		// 3. Game object updates
		container.update();


		// 4. & 5. Remove dead and execute pending actions
		boolean deadRemoved = true;
		while (deadRemoved || areTherePendingActions()) {
			// 4. Remove dead
			deadRemoved = this.container.removeDead();

			// 5. execute pending actions
			executePendingActions();
		}

		this.cycle++;

		// 6. Notify commands that a new cycle started
		Command.newCycle();

		// 7. Update record
		record.update(score);
	}

	private void executePendingActions() {
		while (!this.actions.isEmpty()) {
			GameAction action = this.actions.removeLast();
			action.execute(this);
		}
	}

	private boolean areTherePendingActions() {
		return this.actions.size() > 0;
	}

	public boolean isFinished() {		//Si ha terminado el juego ganando zombies o player
		isPlayerDied = container.objectInLimit();
		allZombiesDied = zombiesManager.allZombiesDied();
		if(allZombiesDied) {
			try {
				record.save();
			} catch (RecordException e) {}
		}
		
		return isPlayerDied || allZombiesDied;
	}

	public boolean execute(Command command) throws GameException {		//Se ejecuta el comando
		return command.execute(this);
	}
	
	@Override
	public void tryToCatchObject(int col, int row) throws GameException {
		if(!container.catchObjects(col, row)){
			throw new NotCatchablePositionException(Messages.NO_CATCHABLE_IN_POSITION.formatted(col, row));
		}
	}

	@Override
	public boolean addItem(GameObject object) {		//Se aniade un objeto el container
		container.add(object);
		object.onEnter();
		return true;
	}

	@Override
	public void addSun() {		//Se aniade un sun en una casilla aleatoria mediante los Game Actions
		Sun sun;
		int col = rand.nextInt(GameWorld.NUM_COLS);
		int row = rand.nextInt(GameWorld.NUM_ROWS);
		sun = new Sun(this, col, row) ;
		sun.update();
		addGameActions(new AddGameItemAction(sun));
	}
	
	@Override
	public void playerQuits() {						//Se va a salir el jugador
		playerQuits = true;
	}

	@Override
	public boolean isFullyOcuppied(int col, int row) {
		return this.container.isFullyOccupied(col, row);
	}

	@Override
	public int getCycle() {
		return cycle;
	}

	@Override
	public int getSuncoins() {
		return suncoins;
	}

	@Override
	public int getScore() {
		return score;
	}
	@Override
	public int getRemainingZombies() {
		return zombiesManager.getRemainingZombies();
	}

	@Override
	public String positionToString(int col, int row) {
		return container.positionToString(col, row);
	}

	@Override
	public int getGeneratedSuns() {
		return sunsManager.getGeneratedSuns();
	}

	@Override
	public int getCaughtSuns() {
		return sunsManager.getCatchedSuns();
	}

	@Override
	public boolean isPlayerQuits() {
		return playerQuits;
	}

	@Override
	public boolean isPlayerDied() {
		return isPlayerDied;
	}

	@Override
	public boolean allZombiesDied() {
		return allZombiesDied;
	}

	@Override
	public GameItem getGameItemInPosition(int col, int row) {
		return container.getGameItemInPosition(col,row);
	}

	@Override
	public boolean isPositionEmpty(int col, int row) {
		return container.isPositionEmpty(col, row);
	}

	@Override
	public void operacionRemainingZombies(boolean operacion) {
		zombiesManager.operacionRemainingZombies(operacion);
	}

	@Override
	public void operacionZombiesAlived(boolean operacion) {
		zombiesManager.operacionZombiesAlived(operacion);
	}

	@Override
	public void tryToBuy(int cost) throws GameException{		//Se comprueba si tenemos coins suficientes
		if(suncoins >= cost)
			buy(cost);
		else
			throw new NotEnoughCoinsException(Messages.NOT_ENOUGH_COINS);
	}
	
	private void buy(int cost) {				//Se disminuyen las coins
		suncoins -= cost;
	}

	@Override
	public void addCoins(int coins) {		//Se aniaden las coins
		this.suncoins += coins;
	}

	@Override
	public void addGameActions(GameAction action) {		//Se aniade un GameAction a "actions"
		actions.addLast(action);
	}

	@Override
	public void addScore(int score) {
		this.score += score;
	}

	@Override
	public void ifDeath(int col, int row, int score) {
		if(!isFullyOcuppied(col, row)) {
			addScore(score);
		}
	}

	@Override
	public boolean getUpdateRecord() {
		return this.score > score_saved;
	}
	
	@Override
	public boolean getUpdate_eqRecord() {
		return score_saved == score;
	}
	
	@Override
	public String getRecordCommand() {		//Mensaje para el comando ShowRecordCommand
		StringBuilder str = new StringBuilder();
		str.append(Messages.CURRENT_RECORD.formatted(level.name(), score_saved));
		return str.toString();
	}

	@Override
	public String getResetMessage() {		//Mensaje al resetear
		StringBuilder str = new StringBuilder();
		str.append(String.format(Messages.CONFIGURED_LEVEL, level.name()) + Messages.LINE_SEPARATOR);
		str.append((String.format(Messages.CONFIGURED_SEED, seed)));
		return str.toString();
	}
	
}
