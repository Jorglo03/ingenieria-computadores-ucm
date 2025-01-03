package tp1.p2.control.commands;

import tp1.p2.control.Command;
import tp1.p2.control.exceptions.CommandExecuteException;
import tp1.p2.control.exceptions.CommandParseException;
import tp1.p2.control.exceptions.GameException;
import tp1.p2.control.exceptions.InvalidPositionException;
import tp1.p2.control.exceptions.NotCatchablePositionException;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class CatchCommand extends Command {

	private static boolean caughtSunThisCycle = false;

	private int col;

	private int row;

	public CatchCommand() {
		caughtSunThisCycle = false;
	}
	
	@Override
	protected void newCycleStarted() {
		caughtSunThisCycle = false;
	}

	private CatchCommand(int col, int row) {
		this.col = col;
		this.row = row;
	}

	@Override
	protected String getName() {
		return Messages.COMMAND_CATCH_NAME;
	}

	@Override
	protected String getShortcut() {
		return Messages.COMMAND_CATCH_SHORTCUT;
	}

	@Override
	public String getDetails() {
		return Messages.COMMAND_CATCH_DETAILS;
	}

	@Override
	public String getHelp() {
		return Messages.COMMAND_CATCH_HELP;
	}

	@Override
	public boolean execute(GameWorld game) throws GameException {
		
		if(!caughtSunThisCycle) {		//Si no se ha cogido un objeto en ese ciclo
			game.tryToCatchObject(col, row);		//Se intenta coger el objeto
			caughtSunThisCycle = true;
			if(!caughtSunThisCycle) {		//Si no hay un objeto capturable en esa posicion
				throw new NotCatchablePositionException(String.format(Messages.NO_CATCHABLE_IN_POSITION, col, row));
			}
		}else {
			throw new CommandExecuteException(Messages.SUN_ALREADY_CAUGHT);
		}
		
		return true;
	}

	@Override
	public Command create(String[] parameters) throws GameException {
		Command command = null;
		
		if(parameters.length >= 2) {
			if(parameters.length == 2) {
				try {		//Excepcion por si no se introducen dos numeros para col y row
					col = Integer.parseInt(parameters[0]);
					row = Integer.parseInt(parameters[1]);
				}catch(NumberFormatException nfe){
					throw new CommandParseException(Messages.INVALID_POSITION.formatted(parameters[0],parameters[1]), nfe);
				}
				if((col >= 0 && col < GameWorld.NUM_COLS) && (row >= 0 && row < GameWorld.NUM_ROWS)) {
					command = new CatchCommand(col, row);	//Se crea un nuevo objeto completo
				}
				else {
					throw new InvalidPositionException(Messages.INVALID_POSITION.formatted(parameters[0],parameters[1]));
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
