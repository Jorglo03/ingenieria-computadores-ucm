package tp1.p2.control.commands;

import tp1.p2.control.Command;
import tp1.p2.control.Level;
import tp1.p2.control.exceptions.CommandParseException;
import tp1.p2.control.exceptions.GameException;
import tp1.p2.control.exceptions.InvalidPositionException;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class ResetCommand extends Command {

	private Level level;

	private long seed;

	public ResetCommand() {
	}

	public ResetCommand(Level level, long seed) {
		this.level = level;
		this.seed = seed;
	}

	@Override
	protected String getName() {
		return Messages.COMMAND_RESET_NAME;
	}

	@Override
	protected String getShortcut() {
		return Messages.COMMAND_RESET_SHORTCUT;
	}

	@Override
	public String getDetails() {
		return Messages.COMMAND_RESET_DETAILS;
	}

	@Override
	public String getHelp() {
		return Messages.COMMAND_RESET_HELP;
	}

	@Override
	public boolean execute(GameWorld game) throws GameException {

		if(level==null) {
			System.out.println(game.getResetMessage());
			game.reset();
		}
		else {
			System.out.println(String.format(Messages.CONFIGURED_LEVEL, level.name()));
			System.out.println(String.format(Messages.CONFIGURED_SEED, seed));
			game.reset(level, seed);
		}
		return true;
	}

	@Override
	public Command create(String[] parameters) throws GameException {
		Command command = null;
		
		if(parameters.length == 2) {		//Con parametros
			try {
				Level level = Level.valueOfIgnoreCase(parameters[0]);	//Si se ha introducido un level correcto
				if(level == null) {	
					throw new InvalidPositionException(Messages.INVALID_COMMAND.formatted(parameters[0], parameters[1]));
				}
				else {
					long seed = Long.parseLong(parameters[1]);	//Se convierte la seed a Long
					command = new ResetCommand(level, seed);	//Se crea un nuevo objeto completo
				}
			}catch(NumberFormatException nfe) {
				throw new InvalidPositionException(Messages.INVALID_COMMAND.formatted(parameters[0], parameters[1]), nfe);
			}
		}
		else if(parameters.length == 0) {		//Sin parametros
			command = this;						//Se devuelve este objeto
		}
		else {
			throw new CommandParseException(Messages.COMMAND_INCORRECT_PARAMETER_NUMBER);
		}

		return command;
	}

}
