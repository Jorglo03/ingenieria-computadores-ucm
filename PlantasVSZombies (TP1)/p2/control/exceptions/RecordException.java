package tp1.p2.control.exceptions;

public class RecordException extends GameException{

	private static final long serialVersionUID = 1L;

	public RecordException(String message) {
		super(message);
	}

	public RecordException(Throwable cause) {
		super(cause);
	}

	public RecordException(String message, Throwable cause) {
		super(message, cause);
	}

	/*public RecordException() {
		super();
	}

	public RecordException(String message, Throwable cause, boolean enableSupression, boolean writableStackTrace){
		super(message,cause,enableSupression,writableStackTrace);
	}*/
}
