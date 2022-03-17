#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;
// global variables
const int NUM_ROWS = 10;
const int NUM_COLS = 10;
string temp = "";
// lets store ship info in 3 parallel arrays
string shipNames[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"};
char shipSymbols[] = {'c', 'b', 'r', 's', 'd'};
int shipSizes[] = {5, 4, 3, 3, 2};
ofstream outputFile;
bool playerWins = false;
int isShipShot = 0;
bool player1Turn = false;
bool player2Turn = false;
bool gameEnd = false;
bool player1Lost = false;
bool player2Lost = false;
bool player1CSunk = false, player2CSunk = false;
bool player1BSunk = false, player2BSunk = false;
bool player1RSunk = false, player2RSunk = false;
bool player1SSunk = false, player2SSunk = false;
bool player1DSunk = false, player2DSunk = false;
int playerChoice = 0;
int player1Row = 0, player1Col = 0, player2Row = 0, player2Col = 0;
int player1TotalHits = 0, player2TotalHits = 0, player1TotalMisses = 0, player2TotalMisses = 0, player1TotalShots = 0, player2TotalShots = 0;
// function prototypes
void welcomeScreen();
void selectWhoStartsFirst(bool&, bool&);
void initializeBoard(char[NUM_ROWS][NUM_COLS], int, int);
void displayBoard(char[NUM_ROWS][NUM_COLS], int, int);
void displayOpponentBoard(char[NUM_ROWS][NUM_COLS], int, int);
void manuallyPlaceShipsOnBoard(char[NUM_ROWS][NUM_COLS], string[5], char[5], int[5]);
void randomlyPlaceShipsOnBoard(char[NUM_ROWS][NUM_COLS], string[5], char[5], int[5]);
int checkShot(char[][NUM_COLS], int, int);
bool isLoser(char[][NUM_COLS], int, int, bool&, bool&);
void updateBoard(char[NUM_ROWS][NUM_COLS], int, int, int);
void outputCurrentMove(ofstream&, int, int, int, bool, bool);
void checkIfSunkShip(char[NUM_ROWS][NUM_COLS], ofstream&, int, int, bool&, bool&, bool&, bool&, bool&);
void outputStats(ofstream&, double, double, double, double, double, double);

int main() {
	
	srand(time(0));
	
	char p1SolutionGrid[NUM_ROWS][NUM_COLS];
	char p2SolutionGrid[NUM_ROWS][NUM_COLS];
	
	outputFile.open("battleship.log");
	
	welcomeScreen();
	
	initializeBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
	initializeBoard(p2SolutionGrid, NUM_ROWS, NUM_COLS);
	
	cout << "Please select from the following menu:\n1. Enter positions of ships manually.\n2. Allow the program to randomly select positions of ships." << endl << endl;
	cin >> playerChoice;
	cout << endl;
	
	if (playerChoice == 1) {
		manuallyPlaceShipsOnBoard(p1SolutionGrid, shipNames, shipSymbols, shipSizes);
	}
	else {
		randomlyPlaceShipsOnBoard(p1SolutionGrid, shipNames, shipSymbols, shipSizes);
	}
	
	randomlyPlaceShipsOnBoard(p2SolutionGrid, shipNames, shipSymbols, shipSizes);
	
	selectWhoStartsFirst(player1Turn, player2Turn);
	
	while (gameEnd == false) {
		while (player1Turn == true && player2Turn == false && player1Lost == false) {
			cout << "Player1's Board:" << endl << endl;
			displayBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << endl;
			cout << "Player2's Board:" << endl << endl;
			displayOpponentBoard(p2SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << endl;
			
			cout << "Enter a target: ";
			cin >> player1Row >> player1Col;
			
			isShipShot = checkShot(p2SolutionGrid, player1Row, player1Col);
			
			while (isShipShot == -1) {
				cout << "Invalid target! Please enter a new coordinate: ";
				cin >> player1Row >> player2Col;
				isShipShot = checkShot(p2SolutionGrid, player1Row, player1Col);
			}
			
			if (isShipShot == 1) {
				player1TotalHits++;
			}
			else if (isShipShot == 0) {
				player1TotalMisses++;
			}
			
			outputCurrentMove(outputFile, player1Row, player1Col, isShipShot, player1Turn, player2Turn);
			
			while (isShipShot == -1) {
				cin >> player1Row >> player1Col;
				isShipShot = checkShot(p2SolutionGrid, player1Row, player1Col);
			}
			player1TotalShots++;
			updateBoard(p2SolutionGrid, player1Row, player1Col, isShipShot);
			isLoser(p1SolutionGrid, NUM_ROWS, NUM_COLS, player1Lost, gameEnd);
			checkIfSunkShip(p2SolutionGrid, outputFile, NUM_ROWS, NUM_COLS, player2CSunk, player2BSunk, player2RSunk, player2SSunk, player2DSunk);
			
			player2Turn = true;
			player1Turn = false;
		
		cout << "Hit enter to continue!" << endl << endl;
		getline(cin, temp);	
		}
		
		while (player2Turn == true && player1Turn == false && player2Lost == false) {
			cout << "Player1's Board:" << endl << endl;
			displayBoard(p1SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << endl;
			cout << "Player2's Board:" << endl << endl;
			displayOpponentBoard(p2SolutionGrid, NUM_ROWS, NUM_COLS);
			cout << endl;
			
			player2Row = rand() % 10;
			player2Col = rand() % 10;
			
			cout << "Player2 selects: " << player2Row << " " << player2Col << endl << endl;
			
			isShipShot = checkShot(p1SolutionGrid, player2Row, player2Col);
		
			
			if (isShipShot == 1) {
				player2TotalHits++;
			}
			else if (isShipShot == 0) {
				player2TotalMisses++;
			}
			
			outputCurrentMove(outputFile, player2Row, player2Col, isShipShot, player1Turn, player2Turn);
			
			while (isShipShot == -1) {
				player2Row = rand() % 10;
				player2Col = rand() % 10;
				isShipShot = checkShot(p1SolutionGrid, player2Row, player2Col);
			}
			player2TotalShots++;
			updateBoard(p1SolutionGrid, player2Row, player2Col, isShipShot);
			isLoser(p2SolutionGrid, NUM_ROWS, NUM_COLS, player2Lost, gameEnd);
			checkIfSunkShip(p1SolutionGrid, outputFile, NUM_ROWS, NUM_COLS, player1CSunk, player1BSunk, player1RSunk, player1SSunk, player1DSunk);
			
			player1Turn = true;
			player2Turn = false;
		
		cout << "Hit enter to continue!" << endl << endl;
		getline(cin, temp);	
		}
	}
	
	if (player1Lost == true) {
		cout << "Player2 won the game!" << endl << endl;
		outputFile << "Player 2 won the game!" << endl;
		
	}
	
	if (player2Lost == true) {
		cout << "Player1 won the game!" << endl << endl;
		outputFile << "Player 1 won the game!" << endl;
		
	}
	
	outputStats(outputFile, player1TotalHits, player2TotalHits, player1TotalMisses, player2TotalMisses, player1TotalShots, player2TotalShots);
	
	cout << "Statistics outputted to logfile successfully!" << endl;
	
	outputFile.close();
	
	return 0;
}

// function definitions
void welcomeScreen() {
 	cout << "***** Welcome to Battleship! *****\n\nRules of the Game:\n1. This is a two player game.\n2. Player1 is you and Player2 is the computer. \n3. The goal is to sink all of your opponent's ships.\n4. Each player places ships on the grid.\n5. Each player take turns firing shots by inputing grid coordinates.\n6. The other player indicates if it is a hit or miss.\n7. When a ship is sunk, the player must tell opponent when a ship sinks.\n8. The player to sink all the opponent's ships wins." << endl << endl;
	cout << "Hit enter to start the game!" << endl << endl;
	getline(cin, temp);
	
	system("clear");
}

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

void updateBoard(char playerGrid[NUM_ROWS][NUM_COLS], int rowPlacement, int colPlacement, int isShipShot) {
	if (isShipShot == 1) {
		playerGrid[rowPlacement][colPlacement] = '*';
	}
	else if (isShipShot == 0) {
		playerGrid[rowPlacement][colPlacement] = 'm';
	}
}

void outputCurrentMove(ofstream& outputFile, int rowPlacement, int colPlacement, int isShipShot, bool player1Turn, bool Player2Turn) {
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
		
