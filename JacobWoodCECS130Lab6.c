#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
Name: Jacob Wood
Lab: 6
Section: 02
Date: 3/1/19
Description: This program will take user input including first name, last name, and phone number and store it using
structures and memory allocating.  It will be able to take input and create a list of contacts, delete contacts, and
display contacts.
*/

int menu_option = 1;
int i = 0;
int k;
int j;
int disp_index = 0;
char *mfirst_name;
char *mlast_name;
char *mnumber;
char *empty_string = "";
void add_contact();
void delete_contact();
void display_book();
//function definitions

typedef struct contact{
	char first_name[40];
	char last_name[40];
	char number[40];
} cont;
cont *newContact;


void add_contact(){
	
	newContact = (cont*) realloc(newContact, sizeof(newContact) + sizeof(*(newContact+1)));
	i++;
	//newContact[i].first_name = realloc(newContact[i].first_name, sizeof(newContact[i].first_name) * (i+1));
	//struct contact newContact[i];
	printf("First name: ");
	scanf("%s", &(newContact[i].first_name));
	printf("Last name: ");
	scanf("%s", &(newContact[i].last_name));
	printf("Phone number: ");
	scanf("%s", &(newContact[i].number));
	printf("Record added to phone book.\n");
	printf("%s %s %s\n", newContact[i].first_name, newContact[i].last_name, newContact[i].number);
}

void delete_contact(){
	printf("First name: ");
	scanf("%s", &mfirst_name);
	printf("Last name: ");
	scanf("%s", &mlast_name);
	//int len = sizeof(newContact)/sizeof(newContact[0]);
	for(k=0; k<i; ++k){
		if(!strcmp(newContact[k].first_name, mfirst_name)){
			//if(!strcmp(newContact[k].last_name, mlast_name)){
				printf("%s", newContact[k].last_name);
				//newContact[k].first_name = "";
				strcpy(newContact[k].first_name, empty_string);
				//newContact[k].last_name = NULL;
				strcpy(newContact[k].last_name, empty_string);
				//newContact[k].number = NULL;
				strcpy(newContact[k].number, empty_string);
				j = i;
				for(j; j > k; k++){
					newContact[k] = newContact[k-1];
				}
			//}
		}
	}
}

void display_book(){
	//struct contact newContact[disp_index];
	printf("Phone book entries:\n");
	disp_index = i;
	for (i; i > 0; i--){
		printf("%s %s %s\n", newContact[i].first_name, newContact[i].last_name, newContact[i].number);		
		//printf("%s\n", *(newContact->first_name + disp_index);
	}
	i = disp_index;
	// disp_index >= (sizeof(newContact) / sizeof(newContact[0]))
	//struct contact dispContact[disp_index];
	//printf("Phone book entries:\n");
	//while (newContact[disp_index] != null){
//	}
}

int main(){
printf("This is a phone book application.  Please select a number corresponding to the action you would like to perform.\n");
while(menu_option != 0){
	fflush(stdin);
	printf("1.) Add contact.\n2.) Delete contact.\n3.) Display phonebook.\n4.) Exit.\n");
	scanf("%d", &menu_option);
	switch(menu_option){
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
			menu_option = 0;
			break;
	}
}
return 0;
}

