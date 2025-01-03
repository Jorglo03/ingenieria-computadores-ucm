package tp1.p2.control.exceptions;

public class NotEnoughCoinsException extends CommandExecuteException{

	private static final long serialVersionUID = 1L;

	public NotEnoughCoinsException(String message) {
		super(message);
	}

	public NotEnoughCoinsException(Throwable cause) {
		super(cause);
	}

	public NotEnoughCoinsException(String message, Throwable cause) {
		super(message, cause);
	}

	/*public NotEnoughCoinsException() {
		super();
	}
	
	public NotEnoughCoinsException(String message, Throwable cause, boolean enableSupression, boolean writableStackTrace){
		super(message,cause,enableSupression,writableStackTrace);
	}*/
}
