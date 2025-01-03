package tp1.p2.control.commands;

import tp1.p2.view.Messages;

public class AddPlantCheatCommand extends AddPlantCommand{

	private AddPlantCheatCommand(boolean consumeCoins) {
		super(consumeCoins);
	}
	
	public AddPlantCheatCommand() {
		this(false);
	}

	@Override
	protected String getName() {
		return Messages.COMMAND_CHEAT_PLANT_NAME;
	}

	@Override
	protected String getShortcut() {
		return Messages.COMMAND_CHEAT_PLANT_SHORTCUT;
	}

	@Override
	public String getDetails() {
		return Messages.COMMAND_CHEAT_PLANT_DETAILS;
	}

	@Override
	public String getHelp() {
		return Messages.COMMAND_CHEAT_PLANT_HELP;
	}
}

