#include <iostream>
#include <string>
#include "Ship.h"
#include "gameLogic.h"
#include <iomanip>
#include <cstring>
using namespace std;

//ship sizes 
const int CARRIER_H = 5;
const int BATTLESHIP_H = 4;
const int DESTROYER_H = 3;
const int SUB_H = 2;


// =======================================================================================
// MAIN
// =======================================================================================
int main()
{

	bool win = false;
	bool game = false;
	string name;


	ship player[4];
	ship computer[4];
	char p_board[10][10];
	char c_board[10][10];
	char g_board[10][10];

	Game mygame;

	mygame.setDefault(p_board, game);
	mygame.setDefault(c_board, game);
	mygame.setDefault(g_board, game);

	//used to test computer is properly placing its ships 
	/*mygame.setComp(computer, c_board);
	mygame.printBoard(c_board, player, computer);*/

	game = true;
	
	//game introduction 
	cout << "**********Welcome to Battleship!**********" << endl;

	int count = 0;
	char direction;
	int row = 0;
	int col = 0;
	int health = 0;
	bool isSetUpComplete = false;
	int setUpCount = 0;

	do
	{
		//sets the user's current ship's name and health
		if (count == 0)
		{
			cout << "Please enter your carrier's name: ";
			health = CARRIER_H;
		}
		if (count == 1)
		{
			cout << "Please enter your battleship's name: ";
			health = BATTLESHIP_H;
		}
		if (count == 2)
		{
			cout << "Please enter your destroyer's name: ";
			health = DESTROYER_H;
		}
		if (count == 3)
		{
			cout << "Please enter your submarine's name: ";
			health = SUB_H;
		}

		if (count > 0)
		{
			cin.ignore();
		}

		getline(cin, name);
		player[count].setName(name);
		player[count].setHealth(health);
		player[count].setSize();

		//set's the current ship's orinetation 
		cout << "Do you want " << player[count].getName() << " to be oriented vertical or horizontal? Press v or h: ";
		cin >> direction;

		direction = tolower(direction);
		
		//fix!!!!!!!!!!!!!!!!!!!!!
		//validates direction input
		while ((direction != 'v' && direction != 'h') || cin.fail())
		{
			if (cin.fail())
			{
				cin.clear();
			}
			cout << "Please enter a v or an h ";
			cin >> direction;
		}
		

		//instructs user to put the proper range of coordinates for their current ship
		mygame.validateDirection(direction, row, col, health);
		player[count].setDirection(direction);
		mygame.validatePostion(direction, row, col, health, player, count);

		count++;
		
		//prints the current board

		mygame.setBoard(player, p_board, count);
		mygame.printBoard(p_board, player, computer, isSetUpComplete, setUpCount);
		setUpCount++;

	} while (count != 4);
	

	//sets names for computer ships and health 
	mygame.setComp(computer, c_board);
	isSetUpComplete = true;
	//mygame.printBoard(p_board, player, computer, isSetUpComplete, setUpCount);

// ====================================================================================
// BEGIN GAME LOOP
// ====================================================================================
	while (win != true)
	{
		//prints current state of the board as seen by the player
		//this top one is to test
		mygame.printBoard(c_board, player, computer, isSetUpComplete, setUpCount);
		mygame.printBoard(g_board, player, computer, isSetUpComplete, setUpCount);

		cout << endl;

		//user's turn and checks game state after the player move
		mygame.userTurn(computer, g_board);
		win = mygame.checkWin(computer);
		if(win)
		{
			cout << "Congrats! You have won the game!" << endl;
			return 0;
		}
		
		mygame.computerTurn(player, p_board);
		win = mygame.checkWin(player);
		
		if (win)
		{
			cout << "Computer has defeated you" << endl;
			cout << "GAME OVER" << endl;
			return 0;
		}
	}
// =====================================================================================
// END GAME LOOP
// =====================================================================================
}
// ====================================================================================
// ====================================================================================
// END MAIN
// ====================================================================================
// ====================================================================================




