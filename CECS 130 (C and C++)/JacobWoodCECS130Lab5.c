#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
/*
Name: Jacob Wood
Lab: 5
Section: 02
Date: 2/12/19
Description: This is a program that requests user input and creates a story using that data and randomized elements.
The story should be significantly different every time.
***WARNING: Results may vary***
*/


/*char title_options[4][50];
strcpy(char title_options[0], "Sir");
srcpy(char title_options[1], "Lady");
strcpy(char title_options[2], "Prince");
strcpy(char title_options[3], "Princess");*/
//char *title_options[] = {"Sir", "Lady", "Prince", "Princess"};
//above code is deprecated
char *title_options[8];
char *monster_options[7];
char *mount_options[8];
char *lost_item_options[4];
char *terrain_options[8];
//pointers to arrays of strings used in story/program

char *name;
char *title;
char *descriptor;
char *where_from;
char *weapon;
char *mount;
char *terrain;
char *trophy;
//pointers to strings used in story/program
void knights_tale();
//knights_tale function prototype

int age;
int gold;
//initialization of two integers used in story

void knights_tale(){
	//strcpy(*title, *(title_options + (rand() % 8)));
	//char *title = *(title_options + (rand() % 8));
	//size_t destination_size = sizeof (*title);
	//strncpy(*title, *(title_options + (rand() % 8)), destination_size);
	//title[destination_size - 1] = '\0';
	//all commented code above (in this function) is deprecated
	
	
	char *title_options[] = {"Sir", "Lady", "Prince", "Noble", "Duke", "Dutchess", "Count", "Countess"};
	title = *(title_options + (rand() % 8));
	char *monster_options[] = {"dragon", "gryphon", "ogre", "giant", "necromancer", "cyclops", "cockatrice"};
	char *monster = *(monster_options + (rand() % 7));
	char *lost_item_options[] = {"princess", "crown jewels", "ancient records", "scepter"};
	char *lost_item = *(lost_item_options + (rand() % 4));
	char *mount_options[] = {"trusty horse", "sturdy mare", "blazing stallion", "noble steed", "cheap donkey",
	"timid pony", "magical unicorn", "loyal mule"};
	char *mount = *(mount_options + (rand()) % 8);
	char *terrain_options[] = {"spooky, ghoulish cave", "Cavern of a Thousand Whispers", "Cove of the Dead Men",
	"Rope Bridge of No Return", "Dessert Of Bones", "Seas Of Misfortune", "Jungle Of Imminent Death", "Swamp Of Decay"};
	char *terrain = *(terrain_options+ (rand() % 8));
	/*
	each of the above lines does the following: First line: defines values in array.  Second: Assigns a value to a
	pointer to a string
	*/
	
	printf("You are %s %s \"the %s\" of %s.\n\n\n", title, &name, &descriptor, &where_from);
	//first part of story
	printf("How many gold pieces for your reward?\n");
	//prompts for user input
	scanf("%d", &gold);
	//assigns user input
	
	printf("You have been tasked by the king with defeating the %s and returning the stolen %s, in exchange for %d"
	" gold pieces.\n", monster, lost_item, gold);
	//second part of story 
	printf("What weapon would you like to bring?\n");
	//prompts user for input
	scanf("%s", &weapon);
	//assigns user input
	printf("You set off on your %s and brave the %s, finally arriving at the %s's lair.\n", mount, terrain, monster);
	//third part of story
	printf("You fight and kill the %s with your %s.\nWhat part of the creature would you like to bring home as"
	" bring home as a trophy?\n", monster, &weapon);
	//fourth part of story and prompt
	scanf("%s", &trophy);
	//assigns user input
	printf("You return home with the %s.  The people chant \"%s %s has returned!  Long live %s the %s!\"  The king"
	" personally congratulates you on defeating the %s.  You return the %s and display the %s's %s as proof of your"
	" feat.  You receive your %d gold pieces as well as a pile of jewels.\n", lost_item, title, &name, &name,
	&descriptor, monster, lost_item, monster, &trophy, gold);
	//final part of story
	printf("Congratulations!  Thanks for playing!");
	//brief thanks
}

int main(){
/*
title_options[0] = "Sir ";
title_options[1] = "Lady ";
title_options[2] = "Prince ";
title_options[3] = "Princess ";
*/
//deprecated commented code above
srand(time(NULL));
//char *title = calloc(5, 20000000); <= deprecated code

printf("Hello, this is a short, (semi-)interactive text based adventure.  Please provide the requested information.\n");
//brief description of what to expect
printf("What is your name?\n");
//prompt for input
scanf("%s", &name);
//assigns user input
printf("Please tell me your age.\n");
//prompt for input
scanf("%d", &age);
//assigns user input
printf("Please give me an adjective describing you.\n");
//prompt for input
scanf("%s", &descriptor);
//assigns user input
printf("Where are you from?\n");
//prompt for input
scanf("%s", &where_from);
//assigns user input
int story_val = 0;
//int test_int = rand();
//above is a section of commented code that was used for debugging purposes
knights_tale();
//calls knights_tale function
return 0;
}

