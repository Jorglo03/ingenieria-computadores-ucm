package tp1.p2.control.exceptions;

public class InvalidPositionException extends GameException{

	private static final long serialVersionUID = 1L;

	public InvalidPositionException(String message) {
		super(message);
	}

	public InvalidPositionException(Throwable cause) {
		super(cause);
	}

	public InvalidPositionException(String message, Throwable cause) {
		super(message, cause);
	}

	/*public InvalidPositionException() {
		super();
	}
	
	public InvalidPositionException(String message, Throwable cause, boolean enableSupression, boolean writableStackTrace){
		super(message,cause,enableSupression,writableStackTrace);
	}*/
}
