#include "scoreboard.h"

int main(void)
{
	int num_players = 0, initialize_players_index = 0, round_count = 3;

	Player all_players[MAX_PLAYERS]; // array of player structs

	FILE *logfile = NULL; // initialize file pointer

	Play_again play_quit = PLAY;

	while (play_quit == PLAY)
	{
		logfile = fopen("logfile.txt", "a"); // opens logfile

		if (logfile == NULL) // failsafe for logfile
		{
			printf("File did not open properly.\n");
		}

		num_players = number_people(); // gets number of players

		printf("For Player 1, pick the person who will be dealing first.\n");
		printf("The next player should be the person to their left, and so on.\n\n"); // Order is important for game flow

		for (initialize_players_index = 0; initialize_players_index < num_players; initialize_players_index++)
		{
			initialize_player_struct(all_players, initialize_players_index);
		} // initialize each player struct

		print_player_struct_screen(all_players, num_players); // prints

		while (round_count <= 13)
		{
			main_play(all_players, round_count, num_players);
			print_player_struct_screen(all_players, num_players);
			round_count++;
		}
		round_count = 3;
		printf("***FINAL SCORE***\n\n");
		determine_winner(all_players, num_players);
		print_player_struct_screen(all_players, num_players);
		play_quit = play_again_or_quit();
	}
	
	printf("\nGoodbye!\n\n");

	fclose(logfile);

	return 0;
}