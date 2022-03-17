#include "Battleship.h"
// main function
int main() {
	
	srand(time(0));
	
	// lets store ship info in 3 parallel arrays
	string shipNames[] = {"carrier", "battleship", "cruiser", "submarine", "destroyer"};
	char shipSymbols[] = {'c', 'b', 'r', 's', 'd'};
	int shipSizes[] = {5, 4, 3, 3, 2};
	
	string temp = "";
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
