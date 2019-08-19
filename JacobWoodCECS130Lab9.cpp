#include <stdio.h>
#include <iostream>
#include <string.h>
#include <time.h>
#include <windows.h>

using namespace std;
/*
Name: Jacob Wood
Lab: 9
Section: 02
Date: 4/1/19
Description: A program with an AI that plays TicTacToe against the player.  The AI will always take the center tile if possible.  First player is randomly determined.
Board reads left to right and then down, so the first tile in each row is numbered like so: 1,4,7.  Program also says if any player has won  Have fun!
*/

using namespace std;


void who_starts(class Gameboard* TicTacToe);
void player_starts(class Gameboard* TicTacToe);
void cp_starts(class Gameboard* TicTacToe);
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
	} //default constructor.  Never called, but still left in
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
	int winner = 0;
	bool gameover = false;
	bool middle_tile_taken = false;
	//definitions for public variables of "Gameboard"
	char board_rep[9][3][6]; //array of array of array of characters used to store the values needed to print the correct shapes on the board
	class Tile Tiles[9] = {
		Tile(1), Tile(2), Tile(3), Tile(4), Tile(5), Tile(6), Tile(7), Tile(8), Tile(9)
	}; //creates an array of class instances of "Tile" under the name "Tiles"
	void player_turn();
	void cp_turn();
	void check_if_player_won();
	void check_if_cp_won();
	void check_if_tie();
	void win_status(int);
	void display_board();
	void update_allegiance();
	void print_row(int first, int second, int third);
	//function prototypes used by the class
	~Gameboard() {}; //destructor
}; //class declaration for class "Gameboard"

void Gameboard::display_board() {
	update_allegiance(); //calls function "update_allegiance
	//lines used to  print the board with ASCII art and print each row with the "print_row" function
	cout << "-------------------" << endl;
	print_row(0, 1, 2);
	cout << "|#################|" << endl;
	print_row(3, 4, 5);
	cout << "|#################|" << endl;
	print_row(6, 7, 8);
	cout << "-------------------" << endl;

	//code that was going to be implemenented but is now deprecated.  Just a sample of code that I've excluded to document my effort
	//
	////tile, line, allegiance
	//
	//int side;
	//for (int i = 0; i < 9; i++) {
	//	//if (i % 3 == 0) {
	//		//cout << "-------------" << endl;
	//		for (int k = 0; k < 3; k++) {
	//			if (Tiles[i].allegiance == "player") {
	//				board_rep[i][k][0] = 1;
	//				//gives player identifier to array entry
	//			} else if (Tiles[i].allegiance == "computer") {
	//				board_rep[i][k][0] = 2;
	//				//gives computer identifier to array entry
	//			} else {
	//				board_rep[i][k][0] = 0;
	//				//gives "none" identifier to array entry
	//			}
	//		}
	//	//}
	//}
	//for (int i = 0; i < 9; i++) {
	//	if (i % 3 == 0) {
	//		for (int j = 0; j < 3; j++) {
	//			//if (i % 3 == 0) {
	//			for (int k = 0; k < 3; k++) {
	//				if (board_rep[i][k][0] == 1) {
	//					cout << '|' << player_space[j];
	//					//gives player identifier to array entry
	//				} else if (board_rep[i][k][0] == 2) {
	//					cout << '|' << cp_space[j];
	//					//gives computer identifier to array entry
	//				} else {
	//					cout << '|' << empty_space[j];
	//					//gives "none" identifier to array entry
	//				}
	//				//add some kind of counter that prevents the for statement from running three times
	//			}
	//			cout << '|' << endl;
	//			//cout << '|' << endl;
	//			//cout << "-------------" << endl;
	//		//}
	//			//cout << '|' << endl;
	//		}
	//		//cout << '|' << endl;
	//		cout << "-------------" << endl;
	//	}
	//	//cout << '|' << endl;
	//	//cout << "-------------" << endl;
	//	//cout << endl;
	//}
	//*int spot[3];
	//for (int i = 0; i < 9; i++) {
	//	if (i % 3 == 0) {
	//		for (int k = 0; k < 3; k++) {
	//			spot[k] = i;
	//		}
	//		for (int j = 0; j < 3; j++) {
	//			;
	//		}
	//	}
	//	
	//}*/
	//	
} //function definition for function used to display the TicTacToe board 

void player_starts(class Gameboard* TicTacToe) {
	//here, "TicTacToe" is a pointer to a class of Gameboard
	TicTacToe->display_board();
	//calls the function to display the gameboard
	while (TicTacToe->gameover == false) {
		TicTacToe->player_turn();
		TicTacToe->display_board();
		TicTacToe->check_if_player_won();
		TicTacToe->check_if_tie();
		TicTacToe->cp_turn();
		TicTacToe->display_board();
		TicTacToe->check_if_cp_won();
	} //repeating functions that execute while "gameover" is false
} //definition for funciton that executes the code necessary for the player to go first

void cp_starts(class Gameboard* TicTacToe) {
	TicTacToe->display_board();
	//calls the function to display the gameboard
	while (TicTacToe->gameover == false) {
		TicTacToe->cp_turn();
		TicTacToe->display_board();
		TicTacToe->check_if_cp_won();
		TicTacToe->check_if_tie();
		TicTacToe->player_turn();
		TicTacToe->display_board();
		TicTacToe->check_if_player_won();
	} //repeating functions that execute while "gameover" is false
} //definition for function that executes the code necessary for the computer to go first

void who_starts(class Gameboard* TicTacToe) {
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


void Gameboard::win_status(int dub) {
	if (dub == 1) {
		cout << "Congratulations, you won!" << endl;
	} else if (dub == 2) {
		cout << "Sorry, the computer beat you." << endl;
	} else if (dub == 3) {
		cout << "It's a CATS game! (why is it called that?)";
	} else {
		cout << "ERROR";
		exit(1);
	} //gives appropriate message for who won, or an error if something weird happened
	gameover = true; //sets "gameover" as "true"
	_sleep(5000); //pauses execution for five seconds
	exit(0); //exits program with "success" status
} //executes the proper message to be displayed if 

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
} //function for checking if three tiles in a row all have the same allegiance

int check_allegiance(class Tile *check) {
	if (check->allegiance == "player") {
		return 1;
	} else if (check->allegiance == "computer") {
		return 2;
	} else {
		return 0;
	}
} //function for checking the allegiance of a tile.  Unimplemented.

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
}



void Gameboard::check_if_player_won() {
	//creates pointers to each "Tile" in the "Tiles" array:
	Tile* ptr1 = &Tiles[0];
	Tile* ptr2 = &Tiles[1];
	Tile* ptr3 = &Tiles[2];
	Tile* ptr4 = &Tiles[3];
	Tile* ptr5 = &Tiles[4];
	Tile* ptr6 = &Tiles[5];
	Tile* ptr7 = &Tiles[6];
	Tile* ptr8 = &Tiles[7];
	Tile* ptr9 = &Tiles[8];
	string faction = "player"; //creates temporary string with value "player"
	//checks if "three in a row" has been achieved by the player.  If so, prints the corresponding numbers and executes win_status(1).  If not, prints "Not yet":
	if (check_three_in_row(ptr1, ptr2, ptr3, faction)) {
		cout << "1,2,3" << endl;
		win_status(1);
	} else if (check_three_in_row(ptr4, ptr5, ptr6, faction)) {
		cout << "4,5,6" << endl;
		win_status(1);
	} else if (check_three_in_row(ptr7, ptr8, ptr9, faction)) {
		cout << "7,8,9" << endl;
		win_status(1);
	} else if (check_three_in_row(ptr1, ptr4, ptr7, faction)) {
		cout << "1,4,7" << endl;
		win_status(1);
	} else if (check_three_in_row(ptr2, ptr5, ptr8, faction)) {
		cout << "2,5,8" << endl;
		win_status(1);
	} else if (check_three_in_row(ptr3, ptr6, ptr9, faction)) {
		cout << "3,5,9" << endl;
		win_status(1);
	} else if (check_three_in_row(ptr1, ptr5, ptr9, faction)) {
		cout << "1,5,9" << endl;
		win_status(1);
	} else if (check_three_in_row(ptr3, ptr5, ptr7, faction)) {
		cout << "3,5,7" << endl;
		win_status(1);
	} else {
		cout << "Not yet" << endl;
	}
} //function checking if the player won

void Gameboard::check_if_cp_won() {
	//creates pointers to each "Tile" in the "Tiles" array:
	class Tile* ptr1 = &Tiles[0];
	class Tile* ptr2 = &Tiles[1];
	class Tile* ptr3 = &Tiles[2];
	class Tile* ptr4 = &Tiles[3];
	class Tile* ptr5 = &Tiles[4];
	class Tile* ptr6 = &Tiles[5];
	class Tile* ptr7 = &Tiles[6];
	class Tile* ptr8 = &Tiles[7];
	class Tile* ptr9 = &Tiles[8];
	string faction = "computer"; //creates temporary string with value "computer"
	//checks if "three in a row" has been achieved by the computer.  If so, prints the corresponding numbers and executes win_status(2).  If not, prints "Not yet":
	if (check_three_in_row(ptr1, ptr2, ptr3, faction)) {
		cout << "1,2,3" << endl;
		win_status(2);
	} else if (check_three_in_row(ptr4, ptr5, ptr6, faction)) {
		cout << "4,5,6" << endl;
		win_status(2);
	} else if (check_three_in_row(ptr7, ptr8, ptr9, faction)) {
		cout << "7,8,9" << endl;
		win_status(2);
	} else if (check_three_in_row(ptr1, ptr4, ptr7, faction)) {
		cout << "1,4,7" << endl;
		win_status(2);
	} else if (check_three_in_row(ptr2, ptr5, ptr8, faction)) {
		cout << "2,5,8" << endl;
		win_status(2);
	} else if (check_three_in_row(ptr3, ptr5, ptr9, faction)) {
		cout << "3,5,9" << endl;
		win_status(2);
	} else if (check_three_in_row(ptr1, ptr5, ptr9, faction)) {
		cout << "1,5,9" << endl;
		win_status(2);
	} else if (check_three_in_row(ptr3, ptr5, ptr7, faction)) {
		cout << "3,5,7" << endl;
		win_status(2);
	} else {
		cout << "Not yet" << endl;
	}
	//more deprecated code as proof of what I've tried:
	/*if ((Tiles[0], Tile2, Tile3).allegiance == "computer") {
		cout << "1,2,3" << endl;
		winner = 2;
		gameover = true;
	} else if ((Tile4, Tile5, Tile6).allegiance == "computer") {
		cout << "4,5,6" << endl;
		winner = 2;
		gameover = true;
	} else if ((Tile7, Tile8, Tile9).allegiance == "computer") {
		cout << "7,8,9" << endl;
		winner = 2;
		gameover = true;
	} else if ((Tiles[0], Tile4, Tile7).allegiance == "computer") {
		cout << "1,4,7" << endl;
		winner = 2;
		gameover = true;
	} else if ((Tile2, Tile5, Tile8).allegiance == "computer") {
		cout << "2,5,8" << endl;
		winner = 2;
		gameover = true;
	} else if ((Tile3, Tile6, Tile9).allegiance == "computer") {
		cout << "3,5,9" << endl;
		winner = 2;
		gameover = true;
	} else if ((Tiles[0], Tile5, Tile9).allegiance == "computer") {
		cout << "1,5,9" << endl;
		winner = 2;
		gameover = true;
	} else if ((Tile3, Tile5, Tile7).allegiance == "computer") {
		cout << "3,5,7" << endl;
		winner = 2;
		gameover = true;
	} else {
		cout << "Not yet" << endl;
	}*/
} //function checking if player won

void Gameboard::check_if_tie() {
	if (Tiles[0].get_occupation() && Tiles[1].get_occupation() && Tiles[2].get_occupation() && Tiles[3].get_occupation() &&
		Tiles[4].get_occupation() && Tiles[5].get_occupation() && Tiles[6].get_occupation() && Tiles[7].get_occupation() &&
		Tiles[8].get_occupation()) {
		winner = 3;
		win_status(3);
	}
} //function checking if each tile is occupied

int main()
{
	srand(time(NULL)); //seeds random number generator with system time
	class Gameboard TicTacToe; //initializes class Gameboard named "TicTacToe"
	class Gameboard* TicTac = &TicTacToe; //initializes pointer to "TicTacToe" called "TicTac"
	who_starts(TicTac); //executes "who_starts" function passing "TicTac" as a parameter

	cout << "Exiting program";
	//std::cout << "Hello World!\n"; 
}



