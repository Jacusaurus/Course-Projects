#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <windows.h>
/*
Name: Jacob Wood & Jonathan Loyd
Lab: Final
Section: Jacob Wood: 02			Jonathan Loyd: 01
Date: 4/24/2019
Description: This program pits two AIs against each other for ten games and displays the winner and final score.  Jacob is O's and Jon is X's.
*/

using namespace std; //974

void who_starts(class Game* TicTacToe);
bool jon_chooses(class Tile * Jon_choice);
bool jacob_chooses(class Tile * choice);
void check_if_jon_won(class Game * TicTacToe, class Gameboard * Board1, class Gameboard * Board2, class Gameboard * Board3);
void check_if_jacob_won(class Game * TicTacToe, class Gameboard * Board1, class Gameboard * Board2, class Gameboard * Board3);
void jon_starts(class Game* TicTacToe);
void jacob_starts(class Game* TicTacToe);
int jascore;
int joscore;
int num_games;
//prototypes for functions to be used later

class Tile {
private:
	int location; //"location" deprecated
	bool isoccupied;
	//private variables of Tile class

public:
	string allegiance;
	Tile() {
		isoccupied = false;
	} //default constructor
	bool get_occupation() {
		return isoccupied;
	} //function passing private variable by reference giving access to private variable "isoccupied"
	void set_occupation() {
		isoccupied = true;
	} //function used to change value of private variable
	Tile(int);
	//constructor prototype
};
//class declaration for "Tile" class

Tile::Tile(int locat) {
	location = locat;
	isoccupied = false;
} //definition of constuctor for Tile class

class Gameboard {
public:
	bool middle_tile_taken = false;
	//definitions for public variables of "Gameboard"
	char board_rep[9][3][6]; //array of array of array of characters used to store the values needed to print the correct shapes on the board
	class Tile Tiles[9] = {
		Tile(1), Tile(2), Tile(3), Tile(4), Tile(5), Tile(6), Tile(7), Tile(8), Tile(9)
	}; //creates an array of class instances of "Tile" under the name "Tiles"
	void cp_turn();
	bool check_not_full();
	void display_board();
	void update_allegiance();
	void print_row(int first, int second, int third);
	//function prototypes used by the class
	~Gameboard() {}; //destructor
}; //class declaration for class "Gameboard"

class Game {
public:
	int winner;
	bool gameover = false;
	class Gameboard Board1;
	class Gameboard Board2;
	class Gameboard Board3;
	void win_status(int);
	void check_if_tie();
	void jacob_ai();
	void jon_ai();
}; //class declaration for class "Game"

void Gameboard::display_board() {
	update_allegiance(); //calls function "update_allegiance
	//lines used to  print the board with ASCII art and print each row with the "print_row" function:
	cout << "-------------------" << endl;
	print_row(0, 1, 2);
	cout << "|#################|" << endl;
	print_row(3, 4, 5);
	cout << "|#################|" << endl;
	print_row(6, 7, 8);
	cout << "-------------------" << endl;
} //function definition for function used to display the TicTacToe board 

class Competition : public Game {
public:
	int jacob_score = 0;
	int jon_score = 0;
};

void jon_starts(class Game* TicTacToe) {
	TicTacToe->Board1.display_board();
	TicTacToe->Board2.display_board();
	TicTacToe->Board3.display_board();
	//calls the function to display each gameboard
	class Gameboard* Board1 = &(TicTacToe->Board1);
	class Gameboard* Board2 = &(TicTacToe->Board2);
	class Gameboard* Board3 = &(TicTacToe->Board3);
	//creates pointers to "Gameboard" class instances
	while (TicTacToe->gameover == false) {
		if (TicTacToe->gameover == false) {
			TicTacToe->jon_ai();
			TicTacToe->Board1.display_board();
			TicTacToe->Board2.display_board();
			TicTacToe->Board3.display_board();
			check_if_jacob_won(TicTacToe, Board1, Board2, Board3);
			TicTacToe->check_if_tie();
		} if (TicTacToe->gameover == false) {
			TicTacToe->jacob_ai();
			TicTacToe->Board1.display_board();
			TicTacToe->Board2.display_board();
			TicTacToe->Board3.display_board();
			check_if_jon_won(TicTacToe, Board1, Board2, Board3);
		}
	} //repeating functions that execute while "gameover" is false, executing the Jon's turn, cp's turn, and updating the board
} //definition for function that executes the code necessary for the Jacob to go first

void Game::jacob_ai() {
	int i = 0; //sets index equal to zero
	Tile * tileList[27] = {
		&(Board2.Tiles[4]), &(Board1.Tiles[4]), &(Board3.Tiles[4]), &(Board1.Tiles[2]), &(Board1.Tiles[6]), &(Board2.Tiles[2]),
		&(Board2.Tiles[6]), &(Board3.Tiles[2]), &(Board3.Tiles[6]), &(Board1.Tiles[0]), &(Board1.Tiles[1]), &(Board2.Tiles[1]),
		&(Board2.Tiles[0]), &(Board3.Tiles[0]), &(Board3.Tiles[1]), &(Board1.Tiles[8]), &(Board3.Tiles[8]),
		&(Board2.Tiles[8]), &(Board1.Tiles[3]), &(Board2.Tiles[5]), &(Board3.Tiles[7]), &(Board3.Tiles[3]), &(Board2.Tiles[7]),
		&(Board1.Tiles[7]), &(Board1.Tiles[5]), &(Board2.Tiles[3]), &(Board3.Tiles[5])
	}; //creates an array of pointers to "class" instances
	class Tile *tile_selection = tileList[i]; //sets "tile_selection" pointer to the first entry in tileList
	bool move_success = false;
	cout << "Jacob thinking..." << endl;
	_sleep(3000); //gives false compute time for opponent
	while (move_success == false) { //while move is not successful
		if (!tile_selection->get_occupation()) { //if the tile is unoccupied
			move_success = jacob_chooses(tile_selection); //set "move_success" equal to return value of "jacob_chooses" and executes the function
		} else {
			tile_selection = tileList[i++]; //otherwise increment i and set "tile_selection" equal to tileList entry
		}
	}
} //declaration of "jacob_ai"

void Game::jon_ai() {
	int i = rand() % 27; //sets index equal to zero
	Tile * tileList[27] = {
		&(Board2.Tiles[4]), &(Board1.Tiles[4]), &(Board3.Tiles[4]), &(Board1.Tiles[2]), &(Board1.Tiles[6]), &(Board2.Tiles[2]),
		&(Board2.Tiles[6]), &(Board3.Tiles[2]), &(Board3.Tiles[6]), &(Board1.Tiles[0]), &(Board1.Tiles[1]), &(Board2.Tiles[1]),
		&(Board2.Tiles[0]), &(Board3.Tiles[0]), &(Board3.Tiles[1]), &(Board1.Tiles[8]), &(Board3.Tiles[8]),
		&(Board2.Tiles[8]), &(Board1.Tiles[3]), &(Board2.Tiles[5]), &(Board3.Tiles[7]), &(Board3.Tiles[3]), &(Board2.Tiles[7]),
		&(Board1.Tiles[7]), &(Board1.Tiles[5]), &(Board2.Tiles[3]), &(Board3.Tiles[5])
	}; //creates an array of pointers to "class" instances
	class Tile *tile_selection = tileList[i]; //sets "tile_selection" pointer to the first entry in tileList
	bool move_success = false;
	cout << "Jon thinking..." << endl;
	_sleep(3000); //gives false compute time for opponent
	while (move_success == false) { //while move is not successful
		if (!tile_selection->get_occupation()) { //if the tile is unoccupied
			move_success = jon_chooses(tile_selection); //set "move_success" equal to return value of "jacob_chooses" and executes the function
		} else {
			i = rand() % 27;
			tile_selection = tileList[i]; //otherwise increment i and set "tile_selection" equal to tileList entry
		}
	}
} //declaration of "jon_ai"

void jacob_starts(class Game* TicTacToe) {
	TicTacToe->Board1.display_board();
	TicTacToe->Board2.display_board();
	TicTacToe->Board3.display_board();
	//calls the function to display each gameboard
	class Gameboard* Board1 = &(TicTacToe->Board1);
	class Gameboard* Board2 = &(TicTacToe->Board2);
	class Gameboard* Board3 = &(TicTacToe->Board3);
	//creates pointers to "Gameboard" class instances
	while (TicTacToe->gameover == false) {
		if (TicTacToe->gameover == false) {
			TicTacToe->jacob_ai();
			TicTacToe->Board1.display_board();
			TicTacToe->Board2.display_board();
			TicTacToe->Board3.display_board();
			check_if_jacob_won(TicTacToe, Board1, Board2, Board3);
			TicTacToe->check_if_tie();
		} if (TicTacToe->gameover == false) {
			TicTacToe->jon_ai();
			TicTacToe->Board1.display_board();
			TicTacToe->Board2.display_board();
			TicTacToe->Board3.display_board();
			check_if_jon_won(TicTacToe, Board1, Board2, Board3);
		}
	} //repeating functions that execute while "gameover" is false, executing the Jon's turn, cp's turn, and updating the board
} //definition for function that executes the code necessary for the Jacob to go first


void who_starts(class Game* TicTacToe) {
	int starter = rand() % 2;
	if (starter == 0) {
		jon_starts(TicTacToe);
	} else {
		jacob_starts(TicTacToe);
	}
} //definition for function that decides whether the Jon or the Jacob goes first

bool jon_chooses(class Tile *choice) {
	if (choice->get_occupation() == false) {
		choice->allegiance = "Jon";
		choice->set_occupation();
		return true; //if the tile is unoccupied, set allegiance to "Jacob", set occupation, and return true
	} else {
		return false;
	} //otherwise, return false
} //function definition for executing the Jacob's turn

bool jacob_chooses(class Tile *choice) {
	if (choice->get_occupation() == false) {
		choice->allegiance = "Jacob";
		choice->set_occupation();
		return true; //if the tile is unoccupied, set allegiance to "Jacob", set occupation, and return true
	} else {
		return false;
	} //otherwise, return false
} //function definition for executing the Jacob's turn

void Game::win_status(int dub) {
	if (dub == 1) {
		cout << "Jon won this round" << endl;
		joscore++;
	} else if (dub == 2) {
		cout << "Jacob won this round" << endl;
		jascore++;
	} else if (dub == 3) {
		cout << "It's a CATS game! (why is it called that?)";
	} else {
		cout << "ERROR";
		exit(1);
	} //gives appropriate message for who won, tie, or an error if something weird happened
	gameover = true; //sets "gameover" as "true"
	_sleep(5000); //pauses execution for five seconds
	//exit(0); //exits program with "success" status
} //executes the proper message to be displayed


void Game::check_if_tie()
{
	if (Board1.Tiles[0].get_occupation() && Board1.Tiles[1].get_occupation() && Board1.Tiles[2].get_occupation() &&
		Board1.Tiles[3].get_occupation() && Board1.Tiles[4].get_occupation() && Board1.Tiles[5].get_occupation() &&
		Board1.Tiles[6].get_occupation() && Board1.Tiles[7].get_occupation() && Board1.Tiles[8].get_occupation() &&
		Board2.Tiles[0].get_occupation() && Board2.Tiles[1].get_occupation() && Board2.Tiles[2].get_occupation() &&
		Board2.Tiles[3].get_occupation() && Board2.Tiles[4].get_occupation() && Board2.Tiles[5].get_occupation() &&
		Board2.Tiles[6].get_occupation() && Board2.Tiles[7].get_occupation() && Board2.Tiles[8].get_occupation() &&
		Board3.Tiles[0].get_occupation() && Board3.Tiles[1].get_occupation() && Board3.Tiles[2].get_occupation() &&
		Board3.Tiles[3].get_occupation() && Board3.Tiles[4].get_occupation() && Board3.Tiles[5].get_occupation() &&
		Board3.Tiles[6].get_occupation() && Board3.Tiles[7].get_occupation() && Board3.Tiles[8].get_occupation()) {
		winner = 3;
		win_status(3);
	}
} //function checks all tiles to see if they are occupied and if they are it executes "win_status" with "3" as the parameter


void Gameboard::cp_turn() {
	bool move_success = false;
	int rand_int;
	//defines local variables used in function
	Tile *tile_selection = &Tiles[4]; //creates temporary class instance pointer and initializes it to point to the fifth element in the "Tiles" array
	cout << "Opponent thinking..." << endl; //prints "Opponent thinking..."
	_sleep(3000); //creates a false loading or "thinking" time of three seconds to make the game flow smoother and not print immediately after Jon's turn
	if (middle_tile_taken == false) {
		move_success = jacob_chooses(tile_selection);
		middle_tile_taken = true; //if middle tile is not taken, Jacob takes middle tile and sets "middle_tile_taken" to true
	} else while (move_success == false) {
		rand_int = rand() % 8; //assign rand_int to the remainder of the quotient of a random number divided by eight
		switch (rand_int) {
		case 0:
			tile_selection = &Tiles[0];
			cout << "1" << endl;
			break;
		case 1:
			tile_selection = &Tiles[1];
			cout << "2" << endl;
			break;
		case 2:
			tile_selection = &Tiles[2];
			cout << "3" << endl;
			break;
		case 3:
			tile_selection = &Tiles[3];
			cout << "4" << endl;
			break;
		case 4:
			tile_selection = &Tiles[5];
			cout << "6" << endl;
			break;
		case 5:
			tile_selection = &Tiles[6];
			cout << "7" << endl;
			break;
		case 6:
			tile_selection = &Tiles[7];
			cout << "8" << endl;
			break;
		case 7:
			tile_selection = &Tiles[8];
			cout << "9" << endl;
			break;
		} //switch that sets "tile_selection" to reference the correct instance in the array, the "hard" way (could have used "rand_int" as index)
		move_success = jacob_chooses(tile_selection); //sets "move_success" equal to return status of "jacob_chooses" function, so loop will be broken if the turn is successful
	}
}

bool check_three_in_row(class Tile *check1, class Tile *check2, class Tile *check3, string faction) {
	if ((check1->allegiance == faction) && (check2->allegiance == faction) && (check3->allegiance == faction)) {
		return true;
	} else {
		return false;
	}
} //function for checking if three tiles in a row, column, or diagonally all have the same allegiance

void Gameboard::update_allegiance() {
	const char Jon_space[3][6] = { " X X ", "  X  ", " X X " }; //array of character arrays containing the characters needed to print each line of the "X" symbol
	const char cp_space[3][6] = { "  OO ", " O  O", "  OO " }; //array of character arrays containing the characters needed to print each line of the "O" sybmol
	const char empty_space[3][6] = { "     ", "     ", "     " }; //array of character arrays containing empty spaces needed to print a blank cell
	char temp[6]; //creates temporary character array
	//goes through each "Tile" and assigns each character array in "board_rep" with an appropriate value:
	for (int i = 0; i < 9; i++) {
		for (int k = 0; k < 3; k++) {
			if (Tiles[i].allegiance == "Jon") {
				strcpy(temp, Jon_space[k]);
				strcpy(board_rep[i][k], temp);
			} else if (Tiles[i].allegiance == "Jacob") {
				strcpy(temp, cp_space[k]);
				strcpy(board_rep[i][k], temp);
			} else {
				strcpy(temp, empty_space[k]);
				strcpy(board_rep[i][k], temp);
			}
		}
	}
}

void Gameboard::print_row(int first, int second, int third) {
	for (int k = 0; k < 3; k++) {
		cout << '|';
		cout << board_rep[first][k] << '#';
		cout << board_rep[second][k] << '#';
		cout << board_rep[third][k] << '|' << endl;
	} //prints a row using the "board_rep" array
} //function for printing a row on a board

void check_if_jon_won(class Game* TicTacToe, class Gameboard* Board1, class Gameboard* Board2, class Gameboard* Board3) {
#pragma region TilePointers
	Tile* B1T1 = &(Board1->Tiles[0]);
	Tile* B1T2 = &(Board1->Tiles[1]);
	Tile* B1T3 = &(Board1->Tiles[2]);
	Tile* B1T4 = &(Board1->Tiles[3]);
	Tile* B1T5 = &(Board1->Tiles[4]);
	Tile* B1T6 = &(Board1->Tiles[5]);
	Tile* B1T7 = &(Board1->Tiles[6]);
	Tile* B1T8 = &(Board1->Tiles[7]);
	Tile* B1T9 = &(Board1->Tiles[8]);
	Tile* B2T1 = &(Board2->Tiles[0]);
	Tile* B2T2 = &(Board2->Tiles[1]);
	Tile* B2T3 = &(Board2->Tiles[2]);
	Tile* B2T4 = &(Board2->Tiles[3]);
	Tile* B2T5 = &(Board2->Tiles[4]);
	Tile* B2T6 = &(Board2->Tiles[5]);
	Tile* B2T7 = &(Board2->Tiles[6]);
	Tile* B2T8 = &(Board2->Tiles[7]);
	Tile* B2T9 = &(Board2->Tiles[8]);
	Tile* B3T1 = &(Board3->Tiles[0]);
	Tile* B3T2 = &(Board3->Tiles[1]);
	Tile* B3T3 = &(Board3->Tiles[2]);
	Tile* B3T4 = &(Board3->Tiles[3]);
	Tile* B3T5 = &(Board3->Tiles[4]);
	Tile* B3T6 = &(Board3->Tiles[5]);
	Tile* B3T7 = &(Board3->Tiles[6]);
	Tile* B3T8 = &(Board3->Tiles[7]);
	Tile* B3T9 = &(Board3->Tiles[8]);
#pragma endregion
	//region containing pointers to all tiles
	string faction = "Jon"; //creates temporary string with value "Jon"
	//checks if "three in a row" has been achieved by the Jon.  If so, prints the corresponding numbers and executes win_status(1).  If not, prints "Not yet":
	//			FIRST BOARD:
#pragma region FirstBoardCheck
	if (check_three_in_row(B1T1, B1T2, B1T3, faction)) {
		cout << "1,2,3" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T4, B1T5, B1T6, faction)) {
		cout << "4,5,6" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T7, B1T8, B1T9, faction)) {
		cout << "7,8,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T1, B1T4, B1T7, faction)) {
		cout << "1,4,7" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T2, B1T5, B1T8, faction)) {
		cout << "2,5,8" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T3, B1T6, B1T9, faction)) {
		cout << "3,5,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T1, B1T5, B1T9, faction)) {
		cout << "1,5,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T3, B1T5, B1T7, faction)) {
		cout << "3,5,7" << endl;
		TicTacToe->win_status(1);
	}
#pragma endregion
	//			SECOND BOARD:
#pragma region SecondBoardCheck
	else if (check_three_in_row(B2T1, B2T2, B2T3, faction)) {
		cout << "1,2,3" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B2T4, B2T5, B2T6, faction)) {
		cout << "4,5,6" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B2T7, B2T8, B2T9, faction)) {
		cout << "7,8,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B2T1, B2T4, B2T7, faction)) {
		cout << "1,4,7" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B2T2, B2T5, B2T8, faction)) {
		cout << "2,5,8" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B2T3, B2T6, B2T9, faction)) {
		cout << "3,5,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B2T1, B2T5, B2T9, faction)) {
		cout << "1,5,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B2T3, B2T5, B2T7, faction)) {
		cout << "3,5,7" << endl;
		TicTacToe->win_status(1);
	}
#pragma endregion
	//			THIRD BOARD:
#pragma region ThirdBoardCheck
	else if (check_three_in_row(B3T1, B3T2, B3T3, faction)) {
		cout << "1,2,3" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B3T4, B3T5, B3T6, faction)) {
		cout << "4,5,6" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B3T7, B3T8, B3T9, faction)) {
		cout << "7,8,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B3T1, B3T4, B3T7, faction)) {
		cout << "1,4,7" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B3T2, B3T5, B3T8, faction)) {
		cout << "2,5,8" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B3T3, B3T6, B3T9, faction)) {
		cout << "3,5,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B3T1, B3T5, B3T9, faction)) {
		cout << "1,5,9" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B3T3, B3T5, B3T7, faction)) {
		cout << "3,5,7" << endl;
		TicTacToe->win_status(1);
	}

#pragma endregion
	//			CROSS BOARDS:
#pragma region CrossBoardsCheck
	else if (check_three_in_row(B1T1, B2T1, B3T1, faction)) {
		cout << "1,1,1" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T2, B2T2, B3T2, faction)) {
		cout << "2,2,2" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T3, B2T3, B3T3, faction)) {
		cout << "3,3,3" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T4, B2T4, B3T4, faction)) {
		cout << "4,4,4" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T5, B2T5, B3T5, faction)) {
		cout << "5,5,5" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T6, B2T6, B3T6, faction)) {
		cout << "6,6,6" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T7, B2T7, B3T7, faction)) {
		cout << "7,7,7" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T8, B2T8, B3T8, faction)) {
		cout << "8,8,8" << endl;
		TicTacToe->win_status(1);
	} else if (check_three_in_row(B1T9, B2T9, B3T9, faction)) {
		cout << "8,8,8" << endl;
		TicTacToe->win_status(1);
	}
#pragma endregion
	else {
		cout << "Not yet" << endl;
	} //prints "Not yet"
} //function checking if Jon won

void check_if_jacob_won(class Game* TicTacToe, class Gameboard* Board1, class Gameboard* Board2, class Gameboard* Board3) {
#pragma region TilePointers
	Tile* B1T1 = &(Board1->Tiles[0]);
	Tile* B1T2 = &(Board1->Tiles[1]);
	Tile* B1T3 = &(Board1->Tiles[2]);
	Tile* B1T4 = &(Board1->Tiles[3]);
	Tile* B1T5 = &(Board1->Tiles[4]);
	Tile* B1T6 = &(Board1->Tiles[5]);
	Tile* B1T7 = &(Board1->Tiles[6]);
	Tile* B1T8 = &(Board1->Tiles[7]);
	Tile* B1T9 = &(Board1->Tiles[8]);
	Tile* B2T1 = &(Board2->Tiles[0]);
	Tile* B2T2 = &(Board2->Tiles[1]);
	Tile* B2T3 = &(Board2->Tiles[2]);
	Tile* B2T4 = &(Board2->Tiles[3]);
	Tile* B2T5 = &(Board2->Tiles[4]);
	Tile* B2T6 = &(Board2->Tiles[5]);
	Tile* B2T7 = &(Board2->Tiles[6]);
	Tile* B2T8 = &(Board2->Tiles[7]);
	Tile* B2T9 = &(Board2->Tiles[8]);
	Tile* B3T1 = &(Board3->Tiles[0]);
	Tile* B3T2 = &(Board3->Tiles[1]);
	Tile* B3T3 = &(Board3->Tiles[2]);
	Tile* B3T4 = &(Board3->Tiles[3]);
	Tile* B3T5 = &(Board3->Tiles[4]);
	Tile* B3T6 = &(Board3->Tiles[5]);
	Tile* B3T7 = &(Board3->Tiles[6]);
	Tile* B3T8 = &(Board3->Tiles[7]);
	Tile* B3T9 = &(Board3->Tiles[8]);
#pragma endregion
	//region containing pointers to all tiles
	string faction = "Jacob"; //creates temporary string with value "Jon"
	//checks if "three in a row" has been achieved by the Jon.  If so, prints the corresponding numbers and executes win_status(1).  If not, prints "Not yet":
	//			FIRST BOARD:
#pragma region FirstBoardCheck
	if (check_three_in_row(B1T1, B1T2, B1T3, faction)) {
		cout << "1,2,3" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T4, B1T5, B1T6, faction)) {
		cout << "4,5,6" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T7, B1T8, B1T9, faction)) {
		cout << "7,8,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T1, B1T4, B1T7, faction)) {
		cout << "1,4,7" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T2, B1T5, B1T8, faction)) {
		cout << "2,5,8" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T3, B1T6, B1T9, faction)) {
		cout << "3,5,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T1, B1T5, B1T9, faction)) {
		cout << "1,5,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T3, B1T5, B1T7, faction)) {
		cout << "3,5,7" << endl;
		TicTacToe->win_status(2);
	}
#pragma endregion
	//			SECOND BOARD:
#pragma region SecondBoardCheck
	else if (check_three_in_row(B2T1, B2T2, B2T3, faction)) {
		cout << "1,2,3" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B2T4, B2T5, B2T6, faction)) {
		cout << "4,5,6" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B2T7, B2T8, B2T9, faction)) {
		cout << "7,8,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B2T1, B2T4, B2T7, faction)) {
		cout << "1,4,7" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B2T2, B2T5, B2T8, faction)) {
		cout << "2,5,8" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B2T3, B2T6, B2T9, faction)) {
		cout << "3,5,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B2T1, B2T5, B2T9, faction)) {
		cout << "1,5,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B2T3, B2T5, B2T7, faction)) {
		cout << "3,5,7" << endl;
		TicTacToe->win_status(2);
	}
#pragma endregion
	//			THIRD BOARD:
#pragma region ThirdBoardCheck
	else if (check_three_in_row(B3T1, B3T2, B3T3, faction)) {
		cout << "1,2,3" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B3T4, B3T5, B3T6, faction)) {
		cout << "4,5,6" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B3T7, B3T8, B3T9, faction)) {
		cout << "7,8,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B3T1, B3T4, B3T7, faction)) {
		cout << "1,4,7" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B3T2, B3T5, B3T8, faction)) {
		cout << "2,5,8" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B3T3, B3T6, B3T9, faction)) {
		cout << "3,5,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B3T1, B3T5, B3T9, faction)) {
		cout << "1,5,9" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B3T3, B3T5, B3T7, faction)) {
		cout << "3,5,7" << endl;
		TicTacToe->win_status(2);
	}

#pragma endregion
	//			CROSS BOARDS:
#pragma region CrossBoardsCheck
	else if (check_three_in_row(B1T1, B2T1, B3T1, faction)) {
		cout << "1,1,1" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T2, B2T2, B3T2, faction)) {
		cout << "2,2,2" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T3, B2T3, B3T3, faction)) {
		cout << "3,3,3" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T4, B2T4, B3T4, faction)) {
		cout << "4,4,4" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T5, B2T5, B3T5, faction)) {
		cout << "5,5,5" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T6, B2T6, B3T6, faction)) {
		cout << "6,6,6" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T7, B2T7, B3T7, faction)) {
		cout << "7,7,7" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T8, B2T8, B3T8, faction)) {
		cout << "8,8,8" << endl;
		TicTacToe->win_status(2);
	} else if (check_three_in_row(B1T9, B2T9, B3T9, faction)) {
		cout << "8,8,8" << endl;
		TicTacToe->win_status(2);
	}
#pragma endregion
	else {
		cout << "Not yet" << endl;
	}

} //function checking if Jacob won

bool Gameboard::check_not_full() {
	if (Tiles[0].get_occupation() && Tiles[1].get_occupation() && Tiles[2].get_occupation() && Tiles[3].get_occupation() &&
		Tiles[4].get_occupation() && Tiles[5].get_occupation() && Tiles[6].get_occupation() && Tiles[7].get_occupation() &&
		Tiles[8].get_occupation()) {
		return false;
	} else {
		return true;
	}
} //function checking if each tile is occupied on a board

int main()
{
	srand(time(NULL)); //seeds random number generator with system time
	//jascore = &TicTacToe.jacob_score;
	//joscore = &TicTacToe.jon_score;
	for (; num_games < 10; num_games++) {
		class Competition TicTacToe; //initializes class Gameboard named "TicTacToe"
		class Competition* TicTac = &TicTacToe; //initializes pointer to "TicTacToe" called "TicTac"
		who_starts(TicTac); //executes "who_starts" function passing "TicTac" as a parameter
		cout << "Jacob's score:" << jascore << endl;
		cout << "Jon's score:" << joscore << endl;
	}
	if (jascore > joscore) {
		cout << "Jacob is the winner!" << endl;
	} else {
		cout << "Jon is the winner!" << endl;
	}
	cout << "Final score:" << endl;
	cout << "Jacob's score:" << jascore << endl;
	cout << "Jon's score:" << joscore << endl;
	cout << "Exiting program";
}
