package tp1.p2.control.commands;

import tp1.p2.control.Command;
import tp1.p2.control.exceptions.CommandParseException;
import tp1.p2.control.exceptions.GameException;
import tp1.p2.control.exceptions.InvalidPositionException;
import tp1.p2.logic.GameWorld;
import tp1.p2.logic.gameobjects.Zombie;
import tp1.p2.logic.gameobjects.ZombieFactory;
import tp1.p2.view.Messages;

public class AddZombieCommand extends Command {

	private int zombieIdx;

	private int col;

	private int row;

	public AddZombieCommand() {

	}

	private AddZombieCommand(int zombieIdx, int col, int row) {
		this.zombieIdx = zombieIdx;
		this.col = col;
		this.row = row;
	}

	@Override
	protected String getName() {
		return Messages.COMMAND_ADD_ZOMBIE_NAME;
	}

	@Override
	protected String getShortcut() {
		return Messages.COMMAND_ADD_ZOMBIE_SHORTCUT;
	}

	@Override
	public String getDetails() {
		return Messages.COMMAND_ADD_ZOMBIE_DETAILS;
	}

	@Override
	public String getHelp() {
		return Messages.COMMAND_ADD_ZOMBIE_HELP;
	}

	@Override
	public boolean execute(GameWorld game) throws GameException {
		Zombie zombie;
		if(!game.isFullyOcuppied(col, row)) {		//Si esta vacia
			zombie = ZombieFactory.spawnZombie(zombieIdx, game, col, row);
			game.addItem(zombie);					//Aniade el item
			game.operacionRemainingZombies(true);	//Restablece el remaining zombies
			game.update();							//Update
			return true;
		}
		else {
			throw new InvalidPositionException(Messages.INVALID_POSITION.formatted(col,row));
		}
	}

	@Override
	public Command create(String[] parameters) throws GameException {
		Command command = null;
		
		if(parameters.length >= 3) {
			if(parameters.length == 3) {
				try {	//Excepcion por si no se introduce un indice (numero) para el zombie
					zombieIdx = Integer.parseInt(parameters[0]);
					try {			//Excepcion por si no se introducen dos numeros para col y row
						col = Integer.parseInt(parameters[1]);
						row = Integer.parseInt(parameters[2]);
					}catch(NumberFormatException nfe) {
						throw new CommandParseException(Messages.INVALID_POSITION.formatted(parameters[1],parameters[2]), nfe);
					}
				}catch(NumberFormatException nfe) {
					throw new CommandParseException(Messages.INVALID_COMMAND);
				}	
	
				if(ZombieFactory.isValidZombie(zombieIdx)) {
					if((col >= 0 && col <= GameWorld.NUM_COLS) && (row >= 0 && row < GameWorld.NUM_ROWS)) {
						command = new AddZombieCommand(zombieIdx, col, row);	//Se crea un nuevo objeto completo
					}
					else {
						throw new CommandParseException(Messages.INVALID_POSITION.formatted(parameters[1],parameters[2]));
					}
				}	
				else {
					throw new CommandParseException(Messages.INVALID_GAME_OBJECT);
				}
			}
			else {
				throw new CommandParseException(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER);
			}
		}
		else {
			throw new CommandParseException(Messages.COMMAND_PARAMETERS_MISSING);
		}
		
		return command;
	}

}
