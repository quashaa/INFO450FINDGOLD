//Program that allows user to play Goldfinder (Minesweeper-like game)
#include <iostream>
#include <time.h>
using namespace std;

const int ROW = 10;
const int COL = 19;

int playGame(char gameBoard[ROW][COL]);
char setGameBoard(char gameBoard[ROW][COL]);
bool isBomb(char gameBoard[ROW][COL], int row, int col);
bool isGold(char gameBoard[ROW][COL], int row, int col);

int main()
{
	int r, c;
	char answer;

	cout << "*** ***************** ***" << endl;
	cout << "***                   ***" << endl;
	cout << "***    WELCOME TO     ***" << endl;
	cout << "***   GOLD FINDER!!!  ***" << endl;
	cout << "***                   ***" << endl;
	cout << "*** ***************** ***" << endl;
	cout << endl;

	system("pause");
	system("CLS");

	cout << "*** **************************** ***" << endl;
	cout << "***   Please Read Instructions   ***" << endl;
	cout << "***       Before Playing!        ***" << endl;
	cout << "*** ---------------------------- ***" << endl;
	cout << "***        INSTRUCIONS:          ***" << endl;
	cout << "***      You have 5 guesses      ***" << endl;
	cout << "***  There are 5 pieces of gold  ***" << endl;
	cout << "***        There is 1 bomb       ***" << endl;
	cout << "***                              ***" << endl;
	cout << "***     If you find a bomb,      ***" << endl;
	cout << "***        GAME OVER!!!          ***" << endl;
	cout << "***                              ***" << endl;
	cout << "*** If you find a piece of gold, ***" << endl;
	cout << "***  you get an extra guess!!!   ***" << endl;
	cout << "***                              ***" << endl;
	cout << "***         GOOD LUCK!!!         ***" << endl;
	cout << "*** **************************** ***" << endl;
	cout << endl;
	
	do {
		// Creates and resets hidden game board for subsequent plays
		char gameBoard[ROW][COL] =
		{
			{' ',' ',' ',' ','1',' ','2',' ','3',' ','4',' ','5',' ','6',' ','7',' ','8'},
			{' ',' ',' ','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_','_'},
			{'1',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
			{'2',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
			{'3',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
			{'4',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
			{'5',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
			{'6',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
			{'7',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
			{'8',' ','|',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
		};

		//Displays hidden game board
		for (r = 0; r < ROW; r++)
		{
			for (c = 0; c < COL; c++)
			{
				cout << gameBoard[r][c];
			}

			cout << endl;
		}

		playGame(gameBoard);

		cout << "\nWould you like to play again? (enter Y to continue)" << endl;
		cin >> answer;
		cout << endl;

	} while (answer == 'Y' || answer == 'y');


	cout << "**** Good Bye!!! ****" << endl;
	cout << endl;
	system("pause");
	return 0;
}

//Allows user to play a game of Gold Finder
int playGame(char gameBoard[ROW][COL])
{
	const int maxPoints = 5;
	int row = 0, col = 0;
	int guesses = 5;
	int points = maxPoints;

	setGameBoard(gameBoard);

	//This loop continues while guesses are > 0
	do
	{
		int coordMin = 1;
		int  coordMax = 8;

		//Validates input from the user
		do 
		{

			cout << "\nPlease enter an x coordinate: ";
			cin >> col;
			cout << "Please enter a y coordinate: ";
			cin >> row;

			if ((row < coordMin || row > coordMax) || (col < coordMin || col > coordMax))
				cout << "(Coordinates can only be a number 1 - 8)" << endl;

		} while ((row < coordMin || row > coordMax) || (col < coordMin || col > coordMax));

		//Calibrates users choice to match the 2D Array & decrements guesses
		col += col + 2;
		row += 1;
		guesses--;
		
		//Adds a point and extra guess is there is gold found while changing the value from 'G' to 'F'
		//Breaks loop if max gold found
		if (isGold(gameBoard, row, col) == true)
		{
			guesses++;
			points++;

			gameBoard[row][col] = 'F';

			if (points == maxPoints)
				break;

			cout << "You found GOLD!!! You have " << guesses << " guess(es) remaining" << endl;

		}

		//Breaks loop if Bomb is found
		else if (isBomb(gameBoard, row, col) == true)
		{
			cout << "YOU LOSE!!! You found a BOMB! GAME OVER!!!" << endl;
			break;
		}

		//Default response is no Gold or Bomb
		else
			cout << "TOO BAD, SO SAD! NO GOLD! You have " << guesses << " guess(es) remaining." << endl;

	} while (guesses > 0);

	//Special output if all 5 pieces of Gold are found
	if (points == 5)
	{
		cout << "\n*** ************************ ***" << endl;
		cout << "***                          ***" << endl;
		cout << "***  CONGRATS!!! YOU WIN!!!  ***"<< endl;
		cout << "***   You scored " << points << " points!   ***" << endl;
		cout << "***    Here is your board!   ***" << endl;
		cout << "***                          ***" << endl;
		cout << "*** ************************ ***" << endl;
		cout << endl;

	}

	//Default output at end of game
	else
	{
		cout << "\nTry Again! You scored " << points << " points!" << endl;
		cout << "(Here is your board)" << endl;
		cout << endl;
	}

	//Prints board at the end of game
	for (row = 0; row < ROW; row++)
	{
		for (col = 0; col < COL; col++)
		{
			cout << gameBoard[row][col];
		}

		cout << endl;
	}

	return 0;
}

//Initializes game board with Gold & Bomb
char setGameBoard(char gameBoard[ROW][COL])
{
	int row, col;
	srand(time(NULL));

	//Clears board
	for (row = 2; row < ROW; row++)
	{
		for (col = 4; col < COL; col++)
		{
			gameBoard[row][col] = ' ';
		}

	}

	int i;

	//Places Gold
	for (i = 0; i < 5; i++)
	{
		row = rand() % 9;
		row += 1;
		col = rand() % 9;
		col += col + 2;

		if (row == 1)
			row += 1;

		if (col == 2)
			col += 2;

		gameBoard[row][col] = 'G';

	}

	//Places Bomb
	for (i = 0; i < 1; i++)
	{
		row = rand() % 9;
		row += 1;
		col = rand() % 9;
		col += col + 2;

		if (row == 1)
			row += 1;

		if (col == 2)
			col += 2;

		gameBoard[row][col] = 'B';

	}
	
	return gameBoard[ROW][COL];
}

//Checks if guess was the Bomb
bool isBomb(char gameBoard[ROW][COL], int row, int col)
{
	if (gameBoard[row][col] == ' ' || gameBoard[row][col] == 'G')
		return false;

	if (gameBoard[row][col] == 'B')
		return true;
}

//Checks if guess was Gold
bool isGold(char gameBoard[ROW][COL], int row, int col)
{
	if (gameBoard[row][col] == ' ' || gameBoard[row][col] == 'B')
		return false;

	if (gameBoard[row][col] == 'G')
		return true;
}
