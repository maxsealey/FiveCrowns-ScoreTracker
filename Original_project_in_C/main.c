/*
Project: Five Crowns Scoreboard
Programmer: Max Sealey (Washington State University student)
Created: 11/25/16
Last Edited: 11/30/16
This is a personal project; not related to schoolwork

Go Cougs!
*/

#include "scoreboard.h"

int main(void)
{
	int num_players = 0, initialize_players_index = 0, round_count = 3;

	Player all_players[MAX_PLAYERS]; // array of structs

	FILE *logfile = NULL; // initialize file pointer

	Play_again play_quit = PLAY;

	logfile = fopen("logfile.txt", "w"); // opens logfile

	if (logfile == NULL) // failsafe for logfile
	{
		printf("File did not open properly.\n");
	}

	while (play_quit == PLAY)
	{
		num_players = number_people(); // gets number of players

		display_order_message(); // Displays message on how to order players

		for (initialize_players_index = 0; initialize_players_index < num_players; initialize_players_index++)
		{
			initialize_player_struct(all_players, initialize_players_index);
		} // initialize each player struct

		print_player_struct_screen(all_players, num_players); // prints

		while (round_count <= 13) // Count starts at 3 goes up through 13 - one for each round of a game
		{
			main_play(all_players, round_count, num_players); // plays through each round
			print_player_struct_screen(all_players, num_players); // after each round, prints running scores
			round_count++; // increment round count
		}
		round_count = 3; // reset round_count in case player wants to play again
		printf("***FINAL SCORE***\n\n");
		determine_winner(all_players, num_players);	// determine who won, display message
		print_player_struct_screen(all_players, num_players); // print scores to window
		write_stats_to_file(logfile, all_players, num_players);	// writes stats to file
		play_quit = play_again_or_quit(); // asks user wants to play another round
	}
	
	printf("\nGoodbye!\n\n");

	fclose(logfile); // close logfile

	return 0;
}