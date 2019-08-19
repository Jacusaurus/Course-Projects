#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string>
/*
Name: Jacob Wood
Lab: 6
Section: 02
Date: 3/1/19
Description: This program will take user input including first name, last name, and phone number and store it using
structures and memory allocating.  It will be able to take input and create a list of contacts, delete contacts, and
display contacts.
*/
using namespace std;

int menu_option = 1;
int i = 0;
int k;
int j;
int insertn_index;
int found;
int match;
int disp_index = 0;
char mfirst_name[40];
char mlast_name[40];
char mnumber[40];
char *first_name_data;
//defined variables to be used later in program

typedef struct contact {
	char first_name[40];
	char last_name[40];
	char number[40];
	//defines elements of "contact" structure
} cont;
//typedefs structure by name of cont

cont* newContact;
//declares array of structures
cont rand_cont;
//declares structure to be be used when displaying random contact

void add_contact();
void delete_contact();
void display_book();
void find_contact();
//creates prototypes for functions used in program

//function definitions

//defines add_contact function
void add_contact() {
	printf("First name: ");
	scanf("%s", &mfirst_name);
	printf("Last name: ");
	scanf("%s", &mlast_name);
	printf("Number: ");
	scanf("%s", &mnumber);
	//prompts for and assigns first name, last name, and number 
	newContact = (cont*)realloc(newContact, (sizeof(newContact[i]) + sizeof(*(newContact + 1))));
	//reallocates memory for the "newContact" array
	if (i > 0) { //if index is greater than one
			for (j = 0; j < i; j++) { //increments index j while it is less than i
				for (insertn_index = 1; insertn_index < 40; insertn_index++) { //increments insertn_index while it is less than 40 (max characters in char array)
					if (strncmp(mfirst_name, newContact[j].first_name, insertn_index) < 0) { //checks if the letter corresponding to the value of the insertn_index is the same in one string as in another
						found = 1;
						//if function equates to true, assign found to 1
						break;
						//break out of innermost for loop
					}

				}
				if (found == 1) { //if found is equal to one
					break;
					//break out of outermost for loop
				}
			}
		if (found == 1) { //if "found" is equal to one
			for (k = i; k > j; k--) { //starting at k = i, for as long as k is greater than j, decrement k
				strcpy(newContact[k].first_name, newContact[ k-1 ].first_name);
				strcpy(newContact[k].last_name, newContact[k - 1].last_name);
				strcpy(newContact[k].number, newContact[k - 1].number);
				//copies value from previous structure element to current (kth) structure element
				//newContact[k] = newContact[k - 1]; <- this method doesn't work
			}
			strcpy(newContact[k].first_name, mfirst_name);
			strcpy(newContact[k].last_name, mlast_name);
			strcpy(newContact[k].number, mnumber);
			//copies values from placeholder strings to structure elements
			found = 0;
			//sets found to default value (0)
		} else {
			strcpy(newContact[i].first_name, mfirst_name);
			strcpy(newContact[i].last_name, mlast_name);
			strcpy(newContact[i].number, mnumber);
			//if no matches were found (last entry alphabetically), assigns string placeholders directly to structure with index "i"
		}
		
	}
	else {
		strcpy(newContact[i].first_name, mfirst_name);
		strcpy(newContact[i].last_name, mlast_name);
		strcpy(newContact[i].number, mnumber);
		//copies placeholder strings directly to structure elements
	}
	i++;
	//increments index i
}

//defines delete_contact function
void delete_contact() {
	int match = 0;
	//defines integer "match" as zero
	printf("First name: ");
	scanf("%s", &mfirst_name);
	printf("Last name: ");
	scanf("%s", &mlast_name);
	//prompts for and assigns 

	for (k = 0; k < i; k++) { //starting at k = 0, as long as k is less than i, increment k
		if ((strcmp(newContact[k].first_name, mfirst_name) == 0)&&(strcmp(newContact[k].last_name, mlast_name) == 0)) { //if the structure element and placeholder string match
			match = 1;
			//set match equal to 1
			for (k; k < i; k++) { //for k less than i, increment k
				strcpy(newContact[k].first_name, newContact[k + 1].first_name);
				strcpy(newContact[k].last_name, newContact[k + 1].last_name);
				strcpy(newContact[k].number, newContact[k + 1].number);
				//set structure element equal to following structure element
			}
		}
	}
	if (match == 1) { //if "match" is equal to 1
		i--;
		//decrement i
		newContact = (cont*)realloc(newContact, (sizeof(newContact[i])));
		//reallocate array of contacts to one structure less than previously
		match = 0;
		//set match equal to default value (0)
	} else {
		printf("Contact not found.\n");
		//otherwise print "Contact not found."
	}
}

//defines display_book function
void display_book() {
	printf("Phone book entries:\n");
	for (disp_index = 0; disp_index < i; disp_index++) {
		printf("%s\n", newContact[disp_index].first_name);
		printf("%s\n", newContact[disp_index].last_name);
		printf("%s\n\n", newContact[disp_index].number);
	}
	//for each structure in array, print the elements
}

//defines find_contact function
void find_contact() {
	printf("First name of the contact you wish to find: ");
	scanf("%s", mfirst_name);
	printf("Last name of contact you wish to find: ");
	scanf("%s", mlast_name);
	//prompts for and assigns input to placeholder string
	for (k = 0; k < i; k++) { //index k equal to 0, for i less than k, increment k
		if ((strcmp(newContact[k].first_name, mfirst_name) == 0)&&(strcmp(newContact[k].last_name, mlast_name) == 0)) { //if the first and last name are equal to strings in an element
			found = 1;
			//set found = 1
			break;
			//break out of for loop
		}
	}
	if (found == 1) { //if found == 1
		printf("%s %s's phone number is: %s\n", newContact[k].first_name, newContact[k].last_name, newContact[k].number);
		//displays contact information
		found = 0;
		//sets found equal to 0
	} else {
		printf("Contact not found.\n");
		//otherwise print "Contact not found."
	}
}

int main(){
	while (menu_option != 0) { //while menu_option is not equal to 0
		fflush(stdin);
		//flush input, output stream
		printf("1.) Add contact.\n2.) Delete contact.\n3.) Display phonebook.\n4.) Sort contacts alphabetically.\n"
			"5.) Search phone number by name.\n6.) Display random contact.\n7.) Delete all contacts.\n"
			"8.) Exit.\nEntries: %d\n\n", i);
		//displays menu and number of contacts
		scanf("%d", &menu_option);
		//sets the value of menu_option to the user input
		switch (menu_option) { //switch statement for different functions
		case 1:
			add_contact();
			break;
		case 2:
			delete_contact();
			break;
		case 3:
			display_book();
			break;
		case 4:
			display_book();
			printf("As you can see the contacts are displayed alphabetically.  Totally not alphabetical before ;-).\n");
			//totally alphabetizes the contact list
			break;
		case 5:
			find_contact();
			break;
		case 6:
			rand_cont = newContact[(rand() % i)];
			//sets ran_cont structure equal to random structure
			printf("%s\n%s\n%s\n", rand_cont.first_name, rand_cont.last_name, rand_cont.number);
			//displays elements of rand_cont
			break;
		case 7:
			newContact = (cont*)malloc(sizeof(newContact)*i);
			//allocates the array of structures to the size of one cont structure
			i = 0;
			//set index equal to zero
			printf("All contacts have been deleted.\n");
			break;
		case 8:
			menu_option = 0;
			//sets "menu_option" equal to zero
			break;
		}
	}
		newContact = (cont*)malloc(sizeof(newContact)*i);
		//allocates the array of structures to the size of one cont structure
		free(newContact);
		//free memory of newContact structures
return 0;
}

