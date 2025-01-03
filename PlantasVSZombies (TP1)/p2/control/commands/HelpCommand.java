package tp1.p2.control.commands;

import tp1.p2.control.Command;
import tp1.p2.control.exceptions.GameException;
import tp1.p2.logic.GameWorld;
import tp1.p2.view.Messages;

public class HelpCommand extends Command {

	@Override
	protected String getName() {
		return Messages.COMMAND_HELP_NAME;
	}

	@Override
	protected String getShortcut() {
		return Messages.COMMAND_HELP_SHORTCUT;
	}

	@Override
	public String getDetails() {
		return Messages.COMMAND_HELP_DETAILS;
	}

	@Override
	public String getHelp() {
		return Messages.COMMAND_HELP_HELP;
	}

	@Override
	public boolean execute(GameWorld game) throws GameException {
		StringBuilder buffer = new StringBuilder(Messages.HELP_AVAILABLE_COMMANDS);

		for (Command command : Command.getAvailableCommands()) {	//Lista de commands
			/* @formatter:off */
			buffer.append(Messages.LINE_SEPARATOR);
			buffer.append(command.getDetails());
			buffer.append(Messages.HELP_DETAILS_COMMAND_HELP_SEPARATOR + command.getHelp());
			/* @formatter:on */
		}

		System.out.println(buffer.toString());

		return false;
	}

}
