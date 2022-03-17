#include "Battleship.h"
// function definitions
 /*************************************************************
 * Function: displayGuessMessage()
 * Date Created: 04/01/19
 * Date Last Modified: 04/01/19          
 * Description: This function displays messages throughout 
 *				game.
 * Input parameters: The booleans for if a letter matches and 
 *				if it was not already guessed, the letter that 
 *				was guessed, and number of remaining guesses.
 * Returns: nothing
 * Pre: The booleans for if a letter matches and if it was not 
 * 				already guessed, the letter that was guessed, 
 *				and number of remaining guesses had to have 
 *            	been scanned in by the user.
 * Post: A message is displayed.
 *************************************************************/
void welcomeScreen() {
	string temp = "";
 	cout << "***** Welcome to Battleship! *****\n\nRules of the Game:\n1. This is a two player game.\n2. Player1 is you and Player2 is the computer. \n3. The goal is to sink all of your opponent's ships.\n4. Each player places ships on the grid.\n5. Each player take turns firing shots by inputing grid coordinates.\n6. The other player indicates if it is a hit or miss.\n7. When a ship is sunk, the player must tell opponent when a ship sinks.\n8. The player to sink all the opponent's ships wins." << endl << endl;
	cout << "Hit enter to start the game!" << endl << endl;
	getline(cin, temp);
	
	system("clear");
}
 /*************************************************************
 * Function: selectWhoStartsFirst()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function selects who goes first.
 * Input parameters: Booleans of player's turn.
 * Returns: nothing
 * Pre: The booleans for player's turn had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void selectWhoStartsFirst(bool& player1Turn, bool& player2Turn) {
	int firstPlayerTurn = 0;

	firstPlayerTurn = rand() % 2 + 1;
	
	if (firstPlayerTurn == 1) {
		player1Turn = true;
		player2Turn = false;
		cout << "Player1 has been randomly selected to go first." << endl << endl;
	}
	else if (firstPlayerTurn == 2) {
		player2Turn = true;
		player1Turn = false;
		cout << "Player2 has been randomly selected to go first." << endl << endl;
	}
}
/*************************************************************
 * Function: initializeBoard()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function initializes the board.
 * Input parameters: Player's grid, rows, cols.
 * Returns: nothing
 * Pre: The player's grid, rows, cols had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void initializeBoard(char playerGrid[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i, j;
	
	// outer loop iterates over each row
	for (i = 0; i < rows; i++) {
		// inner loop iterates over int in playerGrid[i] (row)
		for (j = 0; j < cols; j++) {
			playerGrid[i][j] = '-';
		}
	}
}
/*************************************************************
 * Function: displayBoard()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function displays the board.
 * Input parameters: Player's grid, rows, cols.
 * Returns: nothing
 * Pre: The player's grid, rows, cols had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void displayBoard(char playerGrid[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i, j;
	
	cout << "   ";
	
	for (j = 0; j < cols; j++) {
			cout << j << " ";
	}
	cout << endl;
	
	for (i = 0; i < rows; i++) {
		cout << i << "  ";
		for (j = 0; j < cols; j++) {
			cout << playerGrid[i][j] << " ";
		}
		cout << endl;
	}
}
/*************************************************************
 * Function: displayOpponentBoard()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function displays the board.
 * Input parameters: Player's grid, rows, cols.
 * Returns: nothing
 * Pre: The player's grid, rows, cols had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void displayOpponentBoard(char playerGrid[NUM_ROWS][NUM_COLS], int rows, int cols) {
	int i, j;
	
	cout << "   ";
	
	for (j = 0; j < cols; j++) {
			cout << j << " ";
	}
	cout << endl;
	
	for (i = 0; i < rows; i++) {
		cout << i << "  ";
		for (j = 0; j < cols; j++) {
			if (playerGrid[i][j] == '*') {
				cout << "*" << " ";
			}
			else if (playerGrid[i][j] == 'm') {
				cout << "m" << " ";
			}
			else {
				cout << "-" << " ";
			}
		}
		cout << endl;
	}
}
/*************************************************************
 * Function: manuallyPlaceShipsOnBoard()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function randomly places ships on board.
 * Input parameters: Player's grid, ship names, symbols, and sizes.
 * Returns: nothing
 * Pre: The player's grid, ship names, symbols, and sizes had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void manuallyPlaceShipsOnBoard(char p1SolutionGrid[NUM_ROWS][NUM_COLS], string shipNames[5], char shipSymbols[5], int shipSizes[5]) {

	int numOfShips = 0;
	int rowPlacement = 0;
	int colPlacement = 0;
	int lastInputRow, lastInputCol = 0;
	
	while (numOfShips < 5) {
		cout << "Please enter the cells to place the " << shipNames[numOfShips] << " across:" << endl;
		int i = 0;
		while (i < shipSizes[numOfShips]) {
			cin >> rowPlacement >> colPlacement;
			
			if (i == 0) {
				lastInputRow = rowPlacement;
				lastInputCol = colPlacement;
			}
			
			if (!(rowPlacement > lastInputRow + 1) && !(rowPlacement < lastInputRow - 1) && !(colPlacement > lastInputCol + 1) && !(colPlacement < lastInputCol - 1)  && (rowPlacement <= 9) && (colPlacement <= 9) && (rowPlacement >= 0) && (colPlacement >= 0) && (p1SolutionGrid[rowPlacement][colPlacement] == '-')) {
				p1SolutionGrid[rowPlacement][colPlacement] = shipSymbols[numOfShips];
				lastInputRow = rowPlacement;
				lastInputCol = colPlacement;
				i++;
			}
			else {
				cout << "Invalid cell input." << endl << endl << "Enter different cells for your ships: ";
				cin.clear();
				cin.ignore(1000, '\n');
			}
		}
		cout << endl;
		displayBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
		cout << endl;
		numOfShips++;
	}
}	
/*************************************************************
 * Function: randomlyPlaceShipsOnBoard()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function randomly places ships on board.
 * Input parameters: Player's grid, ship names, symbols, and sizes.
 * Returns: nothing
 * Pre: The player's grid, ship names, symbols, and sizes had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void randomlyPlaceShipsOnBoard(char playerGrid[NUM_ROWS][NUM_COLS], string shipNames[5], char shipSymbols[5], int shipSizes[5]) {
	
	int positionPlacement = 0;
	int numOfShips = 0;
	int rowPlacement = 0;
	int colPlacement = 0;
	int lastInputRow, lastInputCol = 0;
	bool invalidPlacement = false;
	
	while (numOfShips < 5) {
		int i = 0, x = 0, y = 0;
		positionPlacement = rand() % 2;
		rowPlacement = rand() % (11 - shipSizes[numOfShips]);
		colPlacement = rand() % (11 - shipSizes[numOfShips]);
		
		while (i < shipSizes[numOfShips]) {
			if (positionPlacement == 0 && playerGrid[rowPlacement][colPlacement] == '-') {
				playerGrid[rowPlacement][colPlacement]  = shipSymbols[numOfShips];
				rowPlacement++;
				i++;
			}
			else if (positionPlacement == 1 && playerGrid[rowPlacement][colPlacement] == '-') {
				playerGrid[rowPlacement][colPlacement]  = shipSymbols[numOfShips];
				colPlacement++;
				i++;
			}
			else if(playerGrid[rowPlacement][colPlacement] != '-') {
				positionPlacement = rand() % 2;
				rowPlacement = rand() % (11 - shipSizes[numOfShips]);
				colPlacement = rand() % (11 - shipSizes[numOfShips]);
				invalidPlacement = true;
				i = 0;
			}
			
			while (invalidPlacement == true) {
				if (playerGrid[x][y] != shipSymbols[numOfShips]) {
					if (x >= 9) {
						x = 0;
						y++;
					}
					else {
						x++;
					}
				}
				else if(playerGrid[x][y] == shipSymbols[numOfShips]) {
					playerGrid[x][y] = '-';
					x = 0;
					y = 0;
				}
				if (x >= 9 && y >= 10) {
					invalidPlacement = false;
				}
			}
				
		}
		numOfShips++;
	}
}
/*************************************************************
 * Function: checkShot()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function checks if you hit or missed.
 * Input parameters: Player's grid, row , and col.
 * Returns: If ship was shot.
 * Pre: The player's grid, row , and col had to have 
 *            	been scanned in by the user.
 * Post: If ship was shot.
 *************************************************************/
int checkShot(char playerGrid[][NUM_COLS], int rowPlacement, int colPlacement) {
	int isShipShot = 0;
	if (playerGrid[rowPlacement][colPlacement] != '-') {
		cout << "Righty on! " << rowPlacement << "," << colPlacement << " is a hit. Bullseye!" << endl << endl;
		isShipShot = 1;
	}
	if (playerGrid[rowPlacement][colPlacement] == '*' || playerGrid[rowPlacement][colPlacement] == 'm') {
		cout << "You've aready selected that coordinate. Pick another target." << endl;
		isShipShot = -1;
	}
	if (playerGrid[rowPlacement][colPlacement] == '-') {
		cout << "Rough. " << rowPlacement << "," << colPlacement << " is a miss. Better luck next time!" << endl << endl;
		isShipShot = 0;
	}
	return isShipShot;
}
/*************************************************************
 * Function: isLoser()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function determines if player lost.
 * Input parameters: Player's grid, rows, cols, bool for player lost and game end.
 * Returns: nothing
 * Pre: The player's grid, rows, cols, bool for player lost and game endhad to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
bool isLoser(char playerGrid[][NUM_COLS], int rows, int cols, bool& playerLost, bool& gameEnd) {
	int i = 0, j = 0, k = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if(playerGrid[i][j] == '*' || playerGrid[i][j] == '-' || playerGrid[i][j] == 'm') {
				k++;
			}
		}
	}
	if (k == 100) {
		playerLost = true;
		gameEnd = true;
	}
}
/*************************************************************
 * Function: updateBoard()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function updates the board.
 * Input parameters: Player's grid row, col, ship shot.
 * Returns: nothing
 * Pre: The player's grid row, col, ship shot had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void updateBoard(char playerGrid[NUM_ROWS][NUM_COLS], int rowPlacement, int colPlacement, int isShipShot) {
	if (isShipShot == 1) {
		playerGrid[rowPlacement][colPlacement] = '*';
	}
	else if (isShipShot == 0) {
		playerGrid[rowPlacement][colPlacement] = 'm';
	}
}
/*************************************************************
 * Function: outputCurrentMove()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function writes data to file.
 * Input parameters: Output file, row, col, ship shot, players' turn.
 * Returns: nothing
 * Pre: The booleans for player's turn had to have 
 *            	been scanned in by the user.
 * Post: noting.
 *************************************************************/
void outputCurrentMove(ofstream& outputFile, int rowPlacement, int colPlacement, int isShipShot, bool player1Turn, bool player2Turn) {
	if (isShipShot == 1 && player1Turn == true) {
		outputFile << "Player 1 targeted " << rowPlacement << "," << colPlacement << " and landed a hit!" << endl;
	}
	if (isShipShot == 0 && player1Turn == true) {
		outputFile << "Player 1 targeted " << rowPlacement << "," << colPlacement << " and missed the target!" << endl;
	}
	if (isShipShot == 1 && player2Turn == true) {
		outputFile << "Player 2 targeted " << rowPlacement << "," << colPlacement << " and landed a hit!" << endl;
	}
	if (isShipShot == 0 && player2Turn == true) {
		outputFile << "Player 2 targeted " << rowPlacement << "," << colPlacement << " and missed the target!" << endl;
	}
}
/*************************************************************
 * Function: checkIfSunkShip()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function checks if ships are sunk.
 * Input parameters: Player's grid, output file, rows, cols,
 				and boolean for sunk ships.
 * Returns: nothing
 * Pre: The player's grid, output file, rows, cols, and boolean
 *				for sunk ships had to have been scanned in by
 *            	the user.
 * Post: noting
 *************************************************************/
void checkIfSunkShip(char playerGrid[NUM_ROWS][NUM_COLS], ofstream& outputFile, int rows, int cols, bool& cSunk, bool& bSunk, bool& rSunk, bool& sSunk, bool& dSunk) {
	int a = 0, b = 0, c = 0, d = 0, e = 0, i = 0, j = 0;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (playerGrid[i][j] == 'c') {
				a++;
			}
			else if (playerGrid[i][j] == 'b') {
				b++;
			}
			else if (playerGrid[i][j] == 'r') {
				c++;
			}
			else if (playerGrid[i][j] == 's') {
				d++;
			}
			else if (playerGrid[i][j] == 'd') {
				e++;
			}
		}
	}
	if (a == 0 && cSunk == false) {
		cout << "The carrier ship was sunk!" << endl;
		outputFile << "The carrier ship was sunk!" << endl;
		cSunk = true;
	}
	else if (b == 0 && bSunk == false) {
		cout << "The battleship was sunk!" << endl;
		outputFile << "The battleship was sunk!" << endl;
		bSunk = true;
	}
	else if (c == 0 && rSunk == false) {
		cout << "The crusier ship was sunk!" << endl;
		outputFile << "The crusier ship was sunk!" << endl;
		rSunk = true;
	}
	else if (d == 0 && sSunk == false) {
		cout << "The submarine was sunk!" << endl;
		outputFile << "The submarine was sunk!" << endl;
		sSunk = true;
	}
	else if (e == 0 && dSunk == false) {
		cout << "The destroyer ship was sunk!" << endl;
		outputFile << "The destroyer ship was sunk!" << endl;
		dSunk = true;
	}
}
/*************************************************************
 * Function: outputStats()
 * Date Created: 04/17/19
 * Date Last Modified: 04/18/19          
 * Description: This function writes stats to file.
 * Input parameters: Players' hits, misses, and shots.
 * Returns: nothing
 * Pre: The players' hits, misses, and shots had to have 
 *            	been scanned in by the user.
 * Post: noting
 *************************************************************/
void outputStats(ofstream& outputFile, double player1TotalHits, double player2TotalHits, double player1TotalMisses, double player2TotalMisses, double player1TotalShots, double player2TotalShots) {
	double player1HitMissRatio = 0.0;
	double player2HitMissRatio = 0.0;
	
	player1HitMissRatio = (player1TotalHits/player1TotalMisses) * 100.0;
	player2HitMissRatio = (player2TotalHits/player2TotalMisses) * 100.0;
	
	outputFile << endl;
	outputFile << "*** Player1 Stats ***" << endl;
	outputFile << "Number Hits: " << player1TotalHits << endl;
	outputFile << "Number Misses: " << player1TotalMisses << endl;
	outputFile << "Total Shots: " << player1TotalShots << endl;
	outputFile << "Hit/Miss Ratio: " << player1HitMissRatio << "%" << endl << endl;
	
	outputFile << "*** Player2 Stats ***" << endl;
	outputFile << "Number Hits: " << player2TotalHits << endl;
	outputFile << "Number Misses: " << player2TotalMisses << endl;
	outputFile << "Total Shots: " << player2TotalShots << endl;
	outputFile << "Hit/Miss Ratio: " << player2HitMissRatio << "%" << endl << endl;
}
		
