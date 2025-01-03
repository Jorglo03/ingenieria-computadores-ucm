package tp1.p2.logic;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;

import tp1.p2.control.exceptions.RecordException;
import tp1.p2.view.Messages;

public class Record {

	public static final int LONGITUD = 2;
	
	private String level;						//Nivel que estamos evaluando
	private int current_score;					//Score actual
	
	public Record(String level) {
		this.level = level;
		current_score = 0;
	}
	
	public int load() throws RecordException{
		String[] texto = new String[LONGITUD];
		boolean encontrada = false;
		Scanner scanner = null;
		
		try {
			scanner = new Scanner (new File(Messages.RECORD_FILENAME));						
			try {
				while(scanner.hasNext() && !encontrada) {
					texto = scanner.next().split(":");		//Se lee la linea separando level de score
					if(texto[0].equals(this.level)) {		//Se busca el score del level
						try {
							this.current_score = Integer.parseInt(texto[1]);	
							encontrada = true;
						}catch(NumberFormatException nfe) {
							throw new RecordException(Messages.RECORD_READ_ERROR, nfe);
						}catch(ArrayIndexOutOfBoundsException aioobe){
							throw new RecordException(Messages.RECORD_READ_ERROR, aioobe);
						}
					}
				}						
			}catch(NullPointerException npe) {	
				throw new RecordException(Messages.RECORD_READ_ERROR, npe);
			}	
		}catch(FileNotFoundException fnfe) {			
			throw new RecordException(Messages.RECORD_READ_ERROR, fnfe);			
		}finally {
			if(scanner != null)
				scanner.close();
		}
		
		return current_score;
	}
	
	public void save() throws RecordException{	
		String[] texto = new String[LONGITUD];
		StringBuilder str = new StringBuilder();
		PrintWriter write = null;
		Scanner scanner = null;
		
		try {
			scanner = new Scanner (new File(Messages.RECORD_FILENAME));				
			while(scanner.hasNext()) {
				texto = scanner.nextLine().split(":");	//Se lee la linea separando level de score
				if(!texto[0].equals(level)) {			//Se escriben todos los niveles, menos el que evaluamos
					str.append(texto[0] + ":" + texto[1] + Messages.LINE_SEPARATOR);					
				}												
			}
			str.append(level + ":" + this.current_score + Messages.LINE_SEPARATOR);
			
			write = new PrintWriter(Messages.RECORD_FILENAME);
			write.print(str.toString());
		}catch(FileNotFoundException fnfe) {			
			throw new RecordException(Messages.RECORD_WRITE_ERROR, fnfe);
		}finally {
			if(write != null)
				write.close();
			if(scanner != null)
				scanner.close();
		}	
	}
	
	public void update(int score) {
		if(score > this.current_score) {
			current_score = score;		//Se actualiza current_score
		}
	}
	
}
