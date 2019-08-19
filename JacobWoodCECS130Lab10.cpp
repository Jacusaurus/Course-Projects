/*
Name: Jacob Wood
Lab: 10
Section: 02
Date: 4/14/19
Description: This lab is an expansion of the previous Tic-Tac-Toe lab.  What is new is that this lab is 3D Tic-Tac-Toe.
*/
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <windows.h>

using namespace std; //974

void who_starts(class Game* TicTacToe);
bool player_chooses(class Tile * player_choice);
bool cp_chooses(class Tile * choice);
void check_if_player_won(class Game * TicTacToe, class Gameboard * Board1, class Gameboard * Board2, class Gameboard * Board3);
void check_if_cp_won(class Game * TicTacToe, class Gameboard * Board1, class Gameboard * Board2, class Gameboard * Board3);
void player_starts(class Game* TicTacToe);
void cp_starts(class Game* TicTacToe);
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
	void player_turn();
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
	void select_board();
	void check_if_tie();
	void cp_ai();
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

void player_starts(class Game* TicTacToe) {
	//here, "TicTacToe" is a pointer to a class of Game
	TicTacToe->Board1.display_board();
	TicTacToe->Board2.display_board();
	TicTacToe->Board3.display_board();
	//calls the function to display each gameboard
	class Gameboard* Board1 = &(TicTacToe->Board1);
	class Gameboard* Board2 = &(TicTacToe->Board2);
	class Gameboard* Board3 = &(TicTacToe->Board3);
	//creates pointer classes to class instances, in order to pass these pointers later
	while (TicTacToe->gameover == false) {
		TicTacToe->select_board();
		TicTacToe->Board1.display_board();
		TicTacToe->Board2.display_board();
		TicTacToe->Board3.display_board();
		check_if_player_won(TicTacToe, Board1, Board2, Board3);
		TicTacToe->check_if_tie();
		TicTacToe->cp_ai();
		TicTacToe->Board1.display_board();
		TicTacToe->Board2.display_board();
		TicTacToe->Board3.display_board();
		check_if_cp_won(TicTacToe, Board1, Board2, Board3);
	} //repeating functions that execute while "gameover" is false in order to update the board, take player input, and make cp moves
} //definition for function that executes the code necessary for the player to go first

void Game::cp_ai() {
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
	cout << "Opponent thinking..." << endl;
	_sleep(3000); //gives false compute time for opponent
	while (move_success == false) { //while move is not successful
		if (!tile_selection->get_occupation()) { //if the tile is unoccupied
			move_success = cp_chooses(tile_selection); //set "move_success" equal to return value of "cp_chooses" and executes the function
		} else {
			tile_selection = tileList[i++]; //otherwise increment i and set "tile_selection" equal to tileList entry
		}
	}
} //declaration of "cp_ai"

void cp_starts(class Game* TicTacToe) {
	TicTacToe->Board1.display_board();
	TicTacToe->Board2.display_board();
	TicTacToe->Board3.display_board();
	//calls the function to display each gameboard
	class Gameboard* Board1 = &(TicTacToe->Board1);
	class Gameboard* Board2 = &(TicTacToe->Board2);
	class Gameboard* Board3 = &(TicTacToe->Board3);
	//creates pointers to "Gameboard" class instances
	while (TicTacToe->gameover == false) {
		TicTacToe->cp_ai();
		TicTacToe->Board1.display_board();
		TicTacToe->Board2.display_board();
		TicTacToe->Board3.display_board();
		check_if_cp_won(TicTacToe, Board1, Board2, Board3);
		TicTacToe->check_if_tie();
		TicTacToe->select_board();
		TicTacToe->Board1.display_board();
		TicTacToe->Board2.display_board();
		TicTacToe->Board3.display_board();
		check_if_player_won(TicTacToe, Board1, Board2, Board3);
	} //repeating functions that execute while "gameover" is false, executing the player's turn, cp's turn, and updating the board
} //definition for function that executes the code necessary for the computer to go first

void who_starts(class Game* TicTacToe) {
	int starter = rand() % 2;
	if (starter == 0) {
		player_starts(TicTacToe);
	} else {
		cp_starts(TicTacToe);
	}
} //definition for function that decides whether the player or the computer goes first

bool player_chooses(class Tile *player_choice) {
	if (player_choice->get_occupation() == false) {
		player_choice->allegiance = "player";
		player_choice->set_occupation();
		return true; //if the tile is unoccupied, set allegiance to "player", set occupation, and return true
	} else {
		cout << "INVALID MOVE.  Please try again." << endl;
		return false;
	} //otherwise, report move as invalid and return false
} //function definition for executing the player's turn

bool cp_chooses(class Tile *choice) {
	if (choice->get_occupation() == false) {
		choice->allegiance = "computer";
		choice->set_occupation();
		return true; //if the tile is unoccupied, set allegiance to "computer", set occupation, and return true
	} else {
		return false;
	} //otherwise, return false
} //function definition for executing the computer's turn

void Game::win_status(int dub) {
	if (dub == 1) {
		cout << "Congratulations, you won!" << endl;
	} else if (dub == 2) {
		cout << "Sorry, the computer beat you." << endl;
	} else if (dub == 3) {
		cout << "It's a CATS game! (why is it called that?)";
	} else {
		cout << "ERROR";
		exit(1);
	} //gives appropriate message for who won, tie, or an error if something weird happened
	gameover = true; //sets "gameover" as "true"
	_sleep(5000); //pauses execution for five seconds
	exit(0); //exits program with "success" status
} //executes the proper message to be displayed

void Game::select_board()
{
	int active_board;
	bool valid_int = false;
	Gameboard* board_selection = &Board1;
	//initializations of local variables
	while (valid_int == false) {
		cout << "Please give the board that you would like to play on" << endl;
		cin >> active_board;
		switch (active_board) {
		case 1:
			board_selection = &Board1;
			break;
		case 2:
			board_selection = &Board2;
			break;
		case 3:
			board_selection = &Board3;
			break;
		} //sets "board_selection" equal to the corresponding choice by player
		valid_int = board_selection->check_not_full(); //checks if the board is already full and breaks the loop if it is not
	}
	board_selection->player_turn(); //executes "player_turn" function on the appropriate board
} //definition for "select_board" function

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

void Gameboard::player_turn() {
	bool valid_int = false;
	bool move_success = false;
	int choice;
	//defines temporary variables used by the function
	Tile* tile_selection = &Tiles[0]; //creates temporary class instance pointer and initializes it to point to the first element in the "Tiles" array
	while (move_success == false) { //as long as "move_success" is false
		cout << "Please give the numerical designation of the tile you would like to choose" << endl; //prompts for input from user
		cin >> choice; //stores user's choice in integer named "choice"
		switch (choice) {
		case 1:
			tile_selection = &Tiles[0];
			valid_int = true;
			break;
		case 2:
			tile_selection = &Tiles[1];
			valid_int = true;
			break;
		case 3:
			tile_selection = &Tiles[2];
			valid_int = true;
			break;
		case 4:
			tile_selection = &Tiles[3];
			valid_int = true;
			break;
		case 5:
			tile_selection = &Tiles[4];
			middle_tile_taken = true;
			valid_int = true;
			break;
		case 6:
			tile_selection = &Tiles[5];
			valid_int = true;
			break;
		case 7:
			tile_selection = &Tiles[6];
			valid_int = true;
			break;
		case 8:
			tile_selection = &Tiles[7];
			valid_int = true;
			break;
		case 9:
			tile_selection = &Tiles[8];
			valid_int = true;
			break;
		default:
			cout << "Invalid choice" << endl;
			choice = 0;
			break;
		} //switch that sets "tile_selection" to reference the correct instance in the array, the "hard" way (could have used "choice -1" as index)
		move_success = player_chooses(tile_selection); //sets "move_success" equal to return status of "player_chooses" function, so loop will be broken if the turn is successful
	}
} //function definition for "player_turn"

void Gameboard::cp_turn() {
	bool move_success = false;
	int rand_int;
	//defines local variables used in function
	Tile *tile_selection = &Tiles[4]; //creates temporary class instance pointer and initializes it to point to the fifth element in the "Tiles" array
	cout << "Opponent thinking..." << endl; //prints "Opponent thinking..."
	_sleep(3000); //creates a false loading or "thinking" time of three seconds to make the game flow smoother and not print immediately after player's turn
	if (middle_tile_taken == false) {
		move_success = cp_chooses(tile_selection);
		middle_tile_taken = true; //if middle tile is not taken, computer takes middle tile and sets "middle_tile_taken" to true
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
		move_success = cp_chooses(tile_selection); //sets "move_success" equal to return status of "cp_chooses" function, so loop will be broken if the turn is successful
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
	const char player_space[3][6] = { " X X ", "  X  ", " X X " }; //array of character arrays containing the characters needed to print each line of the "X" symbol
	const char cp_space[3][6] = { "  OO ", " O  O", "  OO " }; //array of character arrays containing the characters needed to print each line of the "O" sybmol
	const char empty_space[3][6] = { "     ", "     ", "     " }; //array of character arrays containing empty spaces needed to print a blank cell
	char temp[6]; //creates temporary character array
	//goes through each "Tile" and assigns each character array in "board_rep" with an appropriate value:
	for (int i = 0; i < 9; i++) {
		for (int k = 0; k < 3; k++) {
			if (Tiles[i].allegiance == "player") {
				strcpy(temp, player_space[k]);
				strcpy(board_rep[i][k], temp);
			} else if (Tiles[i].allegiance == "computer") {
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

void check_if_player_won(class Game* TicTacToe, class Gameboard* Board1, class Gameboard* Board2, class Gameboard* Board3) {
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
	string faction = "player"; //creates temporary string with value "player"
	//checks if "three in a row" has been achieved by the player.  If so, prints the corresponding numbers and executes win_status(1).  If not, prints "Not yet":
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
} //function checking if player won

void check_if_cp_won(class Game* TicTacToe, class Gameboard* Board1, class Gameboard* Board2, class Gameboard* Board3) {
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
	string faction = "computer"; //creates temporary string with value "player"
	//checks if "three in a row" has been achieved by the player.  If so, prints the corresponding numbers and executes win_status(1).  If not, prints "Not yet":
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

} //function checking if computer won

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
	class Game TicTacToe; //initializes class Gameboard named "TicTacToe"
	class Game* TicTac = &TicTacToe; //initializes pointer to "TicTacToe" called "TicTac"
	who_starts(TicTac); //executes "who_starts" function passing "TicTac" as a parameter
	cout << "Exiting program";
}
