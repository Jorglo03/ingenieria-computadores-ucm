package tp1.p2.logic;

import java.util.ArrayList;
import java.util.List;

import tp1.p2.logic.gameobjects.GameObject;
import tp1.p2.view.Messages;

public class GameObjectContainer {

	private List<GameObject> gameObjects;

	public GameObjectContainer() {
		gameObjects = new ArrayList<>();
	}

	public String positionToString(int col, int row) {
		StringBuilder buffer = new StringBuilder();
		boolean sunPainted = false;
		boolean sunAboutToPaint = false;

		for (GameObject g : gameObjects) {
			if(g.isAlive() && g.getCol() == col && g.getRow() == row) {
				String objectText = g.toString();
				sunAboutToPaint = objectText.indexOf(Messages.SUN_SYMBOL) >= 0;
				if (sunAboutToPaint) {
					if (!sunPainted) {
						buffer.append(objectText);
						sunPainted = true;
					}
				} else {
					buffer.append(objectText);
				}
			}
		}

		return buffer.toString();
	}

	public boolean removeDead() {		//Se eliminan todos los objetos muertos del ArrayList
		boolean remove = false;
		List<GameObject> gameObjects1;
		gameObjects1 = new ArrayList<>();
		
		for(GameObject object: gameObjects) {
			if(object.isAlive()) {
				gameObjects1.add(object);
			}
			else {
				object.onExit();
				remove = true;
			}
		}
		gameObjects = gameObjects1;

		return remove;
	}

	public void add(GameObject object) {		//Se aniade un nuevo objeto
		gameObjects.add(object);
	}

	public boolean isPositionEmpty(int col, int row) {		//Se comprueba si la posicion dada esta vacia
		boolean empty = true;
		for(GameObject object: gameObjects) {
			if(object.isInPosition(col, row) && object.isAlive())
				empty = false;
		}
		return empty;
	}

	public GameItem getGameItemInPosition(int col , int row) {	//Se devuelve un item en la posicion dada
		GameItem gameItem = null;
		for(GameObject object: gameObjects) {
			if(object.isInPosition(col, row) && object.isAlive() && object.fillPosition())
				gameItem = object;
		}
		
		return gameItem;
	}

	public void update() {							//Se hace el update de todos los objetos vivos
		for(GameObject g: gameObjects) {
			if(g.isAlive()) {
				g.update();
			}
		}
	}

	public boolean isFullyOccupied(int col, int row) {		//Se comprueba si la posicion dada esta llena
		int i=0;
		boolean fullyOcuppied = false;

		while (i<gameObjects.size() && !fullyOcuppied) {
			GameObject g = gameObjects.get(i);
			if (g.isAlive() && g.isInPosition(col, row)) {
				fullyOcuppied = g.fillPosition();
			}
			i++;
		}

		return fullyOcuppied;
	}

	public void clear() {				//Se eliminan todos los objetos del ArrayList
		gameObjects.clear();
	}

	public boolean objectInLimit() {	//Se comprueba si hay un objeto en la columna -1
		boolean inLimit = false;
		for(GameObject object: gameObjects) {
			if(object.getCol() == -1) {
				inLimit = true;
			}
		}
		return inLimit;
	}

	public boolean catchObjects(int col, int row){	//Se intenta coger el objeto de la posicion dada
		boolean catchObjects = false;
		for(GameObject object: gameObjects) {
			if(object.isInPosition(col, row) && object.isAlive() && object.catchObject()) {
				catchObjects = true;
			}
		}
		return catchObjects;
	}
}
