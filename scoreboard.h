#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

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

int number_people(void); // returns number of players

void initialize_player_struct(Player *player_array, int player_index); // initalizes player struct

void print_player_struct_screen(Player *player_array, int num_players); // Print screen

Play_again play_again_or_quit(void);

void main_play(Player *player_array, int round_count, int num_players);

void write_stats_to_file(FILE *logfile, Player *player_array, int num_players);

void determine_winner(Player *player_array, int num_players);

