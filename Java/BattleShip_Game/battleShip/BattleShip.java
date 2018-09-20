package battleShip;

import java.util.Random;
import java.util.Scanner;

public class BattleShip {
	public static void main(String[] args) {
		int boardSize = 20;
		int[] board = new int[boardSize];
		Random rand = new Random();
		
		// num of ships are between 3 to 8
		System.out.println((int)(boardSize / 4));
		int numOfShips = rand.nextInt((int)(boardSize / 4) - 2) + 3;
		
		System.out.println("There are " + numOfShips + " on this board.");
		
		// make an array that stores shipPos and shipSize
		int[] shipPos = new int[numOfShips];
		int[] shipSize = new int[numOfShips];
		
		// Fill the board with ships
		for (int i = 0; i < numOfShips; i++) {
			shipPos[i] = rand.nextInt(boardSize-1);
			shipSize[i] = rand.nextInt(4) + 1;
			
			while (cantFit(board, shipPos[i], shipSize[i])) {
				shipPos[i] = rand.nextInt(19);
				shipSize[i] = rand.nextInt(5) + 1;
			}
			
			for (int j = 0; j < shipSize[i]; j++) {
				board[shipPos[i] + j] = shipSize[i];
			}
		}
		
		// For testing puposes
//		System.out.println("***** POS **********");
//		for (int i = 0; i < shipPos.length; i++) {
//			System.out.print(shipPos[i] + " ");
//		}
//		System.out.println();
//		
//		System.out.println("***** Size **********");
//		for (int i = 0; i < shipSize.length; i++) {
//			System.out.print(shipSize[i] + " ");
//		}
//		System.out.println();
//		
//		System.out.println("***** Board **********");
//		for (int i = 0; i < board.length; i++) {
//			System.out.print(board[i] + " ");
//		}
//		System.out.println();
		
		Scanner scn = new Scanner(System.in);
		// While board has ships, take input from the user
		while (boardHasShips(board) == true) {
			int hit = scn.nextInt();
			// isHit contains the size of Ship that is hit
			int isHit = board[hit];
			board[hit] = 0;
			if (isHit >= 1) {
				System.out.println("Hit!");
				// if hit, find the ship that was hit
				int ship = -1;
				for (int i = 0; i < numOfShips; i++) {
					if (hit >= shipPos[i] && hit < shipPos[i] + shipSize[i]) {
						ship = i;
						break;
					}
				}
				
				boolean shipPresent = false;
				for (int i = shipPos[ship]; i < shipPos[ship] + shipSize[ship]; i++) {
					if (board[i] >= 1) {
						shipPresent = true;
						break;
					}
				}
				if (!shipPresent) {
					System.out.println("You sunk the ship of size " + isHit + ".");
				}
				

				System.out.println();
			}
			else {
				System.out.println("Missed the ship!");
			}
		}
		
		// Game ends
		System.out.println("You have sunken all ships.");
		
	}
	
	public static boolean cantFit(int[] board, int pos, int size) {		
		if (pos + size > board.length) {
			return true;
		}
		for (int i = 0; i < size; i++) {
			if (board[pos + i] >= 1) {
				return true;
			}
		}
		return false;
	}
	
	public static boolean boardHasShips(int[] board) {
		for (int i = 0; i < board.length; i++) {
			if (board[i] >= 1) {
				return true;
			}
		}
		return false;
	}
}
