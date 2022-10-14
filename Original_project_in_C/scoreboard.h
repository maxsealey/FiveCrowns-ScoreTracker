#include <stdio.h>
#include <string.h>


#define MAX_PLAYERS 8
#define NUM_ROUNDS 11 // 3,4,5,6,7,8,9,10,J,Q,K

typedef enum occupied
{
	FALSE, TRUE
} Occupied;

typedef enum play_again
{
	QUIT, PLAY
} Play_again;

typedef struct player
{
	Occupied is_occupied; 
	char name[10];
	int score;
	int final_ranking; // 1, 2, 3, 4, 5, 6, 7, 8
	int identity;
} Player;

/*
Function: number_people()
------------------------------
Input Parameters: n/a
Returns: An integer between 2 and 8

Prompts user for the number of players, returns that number
*/

int number_people(void); 

/*
Function: initialize_player_struct()
------------------------------
Input Parameters: Player *player_array, int player_index
Returns: n/a

This function is called in a for loop that runs once for every player. Sets each item's
.is_occupied attribute to TRUE (enumerated type) to show that it represents an actual player.
Prompts for player's name, assigns it to temp string, and then to .name attribute in given struct.
Initializes other attributes.

*player_array: Array of structs (Player, see scoreboard.h)
player_index: Which player to initialize (index for main.c loop that runs through each player)
*/

void initialize_player_struct(Player *player_array, int player_index); 

/*
Function: print_player_struct_screen()
------------------------------
Input Parameters: Player * player_array, int num_players
Returns: n/a

Displays each player's name and score
*/

void print_player_struct_screen(Player *player_array, int num_players); 

/*
Function: play_again_or_quit()
------------------------------
Input Parameters: n/a
Returns: Play_again (enumerated type, so PLAY or QUIT)

Asks user whether they want to keep playing return answer
*/

Play_again play_again_or_quit(void); 

/*
Function: main_play()
------------------------------
Input Parameters: Player * player_array, int round_count, int num_players
Returns: n/a

Plays through each round, contains code for who_went_out, get_score
*/

void main_play(Player *player_array, int round_count, int num_players); 

/*
Function: write_stats_to_file()
------------------------------
Input Parameters: FILE *logfile, Player *player_array, int num_players
Returns: n/a

Writes stats to logfile
*/

void write_stats_to_file(FILE *logfile, Player *player_array, int num_players);

/*
Function: determine_winner()
------------------------------
Input Parameters: Player * player_array, int num_players
Returns: n/a

Determine's winner, displays message
*/

void determine_winner(Player *player_array, int num_players);

/*
Function: display_order_message()
------------------------------
Input Parameters: n/a
Returns: n/a

Prints message telling user what order to enter players
*/

void display_order_message(void);

/*
Function: which_round()
------------------------------
Input Parameters: int round_count
Returns: n/a

Displays which round the user is currently on
*/

void which_round(int round_count);

/*
Function: who_went_out()
------------------------------
Input Parameters: Player * player_array, int round_count, int num_players
Returns: integer between 1 and the number of players

Asks who went out first, returns their id number
*/

int who_went_out(Player * player_array, int round_count, int num_players);

/*
Function: get_score()
------------------------------
Input Parameters: Player * player_array, int player_index
Returns: n/a

Gets score and adds it to player's running score
*/

void get_score(Player * player_array, int player_index);

