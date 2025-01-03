package tp1.p2.control.commands;

import tp1.p2.control.Command;
//import tp1.p2.control.exceptions.CommandExecuteException;
import tp1.p2.control.exceptions.CommandParseException;
import tp1.p2.control.exceptions.GameException;
import tp1.p2.control.exceptions.InvalidPositionException;
import tp1.p2.logic.GameWorld;
import tp1.p2.logic.gameobjects.Plant;
import tp1.p2.logic.gameobjects.PlantFactory;
import tp1.p2.view.Messages;

public class AddPlantCommand extends Command implements Cloneable {

	private int col;

	private int row;

	private String plantName;

	private boolean consumeCoins;

	public AddPlantCommand() {
		this(true);
	}

	public AddPlantCommand(boolean consumeCoins) {
		this.consumeCoins = consumeCoins;
	}

	@Override
	protected String getName() {
		return Messages.COMMAND_ADD_NAME;
	}

	@Override
	protected String getShortcut() {
		return Messages.COMMAND_ADD_SHORTCUT;
	}

	@Override
	public String getDetails() {
		return Messages.COMMAND_ADD_DETAILS;
	}

	@Override
	public String getHelp() {
		return Messages.COMMAND_ADD_HELP;
	}

	@Override
	public boolean execute(GameWorld game) throws GameException {
		Plant plant;
		if(!game.isFullyOcuppied(col, row)) {		//Si esta vacia
			plant = PlantFactory.spawnPlant(plantName, game, col, row);
			if(consumeCoins) {						//Si consume monedas (AddPlantCommand)
				game.tryToBuy(plant.getCost()); 
				game.addItem(plant);				//Aniade el item
			}										//Si no consume monedas (AddPlantCheatCommand)
			else {
				game.addItem(plant);
			}
			game.update();						//Update
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
				try {		//Excepcion por si no se introducen dos numeros para col y row
					col = Integer.parseInt(parameters[1]);
					row = Integer.parseInt(parameters[2]);
					if(PlantFactory.isValidPlant(parameters[0])) {		//Nombre valido de la planta
						plantName = parameters[0];
						if(((col >= 0 && col < GameWorld.NUM_COLS) && (row >= 0 && row < GameWorld.NUM_ROWS))) {
							command = this;			//Devuelve este objeto
						} else {
							throw new InvalidPositionException(Messages.INVALID_POSITION.formatted(parameters[1],parameters[2]));	
						}
					}
					else {
						throw new CommandParseException(Messages.INVALID_GAME_OBJECT);
					}
				}catch(NumberFormatException nfe) {
					throw new CommandParseException(Messages.INVALID_POSITION.formatted(parameters[1],parameters[2]), nfe);
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