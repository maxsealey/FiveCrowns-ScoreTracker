#include "scoreboard.h"
/*
Function: number_people()
------------------------------
Input Parameters: n/a
Returns: An integer between 2 and 8

Prompts user for the number of players, returns that number
*/
int number_people(void)
{
	int num_players = 0;

	do
	{
		printf("How many players?\n");
		scanf("%d", &num_players);
		system("cls");
	} while (num_players > 8 || num_players < 2);

	return num_players;
}

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

void initialize_player_struct(Player *player_array, int player_index)
{
	char temp[10] = { '\0' };

	player_array[player_index].is_occupied = TRUE; // player struct is occupied

	printf("What is Player %d's name?\n", player_index + 1);
	scanf("%s", temp); // Gets player name, assign it to temporary string

	for (int index = 0; index < 10; index++)
	{
		player_array[player_index].name[index] = temp[index];
	}	// assigns name string to struct

	player_array[player_index].score = 0; // set score to 0

	player_array[player_index].final_ranking = 0;

	player_array[player_index].identity = player_index + 1; // unique int identifier

	system("cls");
}

/*
Function: print_player_struct_screen()
------------------------------
Input Parameters: Player * player_array, int num_players
Returns: n/a

Displays each player's name and score
*/

void print_player_struct_screen(Player * player_array, int num_players)
{
	int index = 0;

	for (index = 0; index < num_players; index++)
	{
		printf("Player %d: %s\n", index + 1, player_array[index].name);
		printf("Score: %d\n\n", player_array[index].score);
	}

	system("pause");
	system("cls");
}

/*
Function: play_again_or_quit()
------------------------------
Input Parameters: n/a
Returns: Play_again (enumerated type, so PLAY or QUIT)

Asks user whether they want to keep playing return answer 
*/

Play_again play_again_or_quit(void)
{
	char answer = '\0';

	do
	{
		printf("Will you be playing another round? (y/n)\n");
		scanf(" %c", &answer);
	} while ((answer != 'y') && (answer != 'n'));

	switch (answer)
	{
	case 'y':
		return PLAY;
	case 'n':
		return QUIT;
	}
}

/*
Function: main_play()
------------------------------
Input Parameters: Player * player_array, int round_count, int num_players
Returns: n/a

Plays through each round, contains code for who_went_out, get_score
*/

void main_play(Player * player_array, int round_count, int num_players)
{
	int id_number = 0, player_index = 0, player_index2 = 0, p_index3 = 0;

	char temp[10] = { '\0' }; // temp char array

	id_number = who_went_out(player_array, round_count, num_players); // Gets number of the person who went out

	int left = 1, right = num_players, mid = id_number;  

	if (mid == right) // Base case - last person went out
	{
		for (player_index = left; player_index < right; player_index++)	// If n is last person, this loops
		{															    // through 1 to n-1
			get_score(player_array, player_index);	// get score and assign to to .score attribute for other players
		}
	}
	else if (mid == left) // Base case - first person went out
	{
		for (p_index3 = left + 1; p_index3 <= num_players; p_index3++) // If n is last person, this loops
		{															   // through 2	through n
			get_score(player_array, p_index3); // get score and assign to to .score attribute for other players
		}
	}
	else 
	{
		for (player_index2 = mid + 1; player_index2 <= right; player_index2++) // Player id (n) is between first and last 
		{																	   // goes from n+1 through last 
			get_score(player_array, player_index2); // get score and assign to to .score attribute for other players
		}

		for (player_index = left; player_index < mid; player_index++) // Player id (n) then goes from 1 to n-1
		{
			get_score(player_array, player_index); // get score and assign to to .score attribute for other players
		}
	}
}

/*
Function: write_stats_to_file()
------------------------------
Input Parameters: FILE *logfile, Player *player_array, int num_players
Returns: n/a

Writes stats to logfile
*/

void write_stats_to_file(FILE * logfile, Player * player_array, int num_players)
{
	int index3 = 0;

	int winner = 0, index2 = 0;
	
	for (int index = 0; (index + 1 < num_players); index++)	// Finds and displays winner
	{
		winner = player_array[index].identity;

		if (player_array[index].score > player_array[index + 1].score)
		{
			winner = player_array[index + 1].identity;
		}
	}

	while (player_array[index2].identity != winner)
	{
		index2++;
	}

	fprintf(logfile, "---------------------------------\n");
	fprintf(logfile, "The WINNER is %s with %d points!\n", player_array[index2].name, player_array[index2].score);
	fprintf(logfile, "---------------------------------\n\n");



	for (index3 = 0; index3 < num_players; index3++)  // Prints each players scores to file
	{
		fprintf(logfile, "Player %d: %s\n", index3 + 1, player_array[index3].name);
		fprintf(logfile, "Final Score: %d\n\n", player_array[index3].score);
	}
}

/*
Function: determine_winner()
------------------------------
Input Parameters: Player * player_array, int num_players
Returns: n/a

Determine's winner, displays message
*/

void determine_winner(Player * player_array, int num_players)
{
	int winner = 0, index2 = 0;

	for (int index = 0; (index + 1 < num_players); index++)
	{
		winner = player_array[index].identity;

		if (player_array[index].score > player_array[index + 1].score)
		{
			winner = player_array[index + 1].identity;
		}
	}

	while (player_array[index2].identity != winner)
	{
		index2++;
	}

	printf("---------------------------------\n");
	printf("The WINNER is %s with %d points!\n", player_array[index2].name, player_array[index2].score);
	printf("---------------------------------\n\n");
	

}

/*
Function: display_order_message()
------------------------------
Input Parameters: n/a
Returns: n/a

Prints message telling user what order to enter players
*/

void display_order_message(void)
{
	printf("For Player 1, pick the person who will be dealing first.\n");
	printf("The next player should be the person to their left, and so on.\n\n"); 
	// Order is important for game flow
}

/*
Function: which_round()
------------------------------
Input Parameters: int round_count
Returns: n/a

Displays which round the user is currently on
*/

void which_round(int round_count)
{
	if (round_count < 11)
	{
		printf("ROUND %d: %ds and Jokers are WILD\n\n", round_count - 2, round_count);
	}
	else
	{
		switch (round_count)
		{
		case 11:
			printf("ROUND #%d: Jacks and Jokers are WILD\n\n", round_count - 2);
			break;
		case 12:
			printf("ROUND #%d: Queens and Jokers are WILD\n\n", round_count - 2);
			break;
		case 13:
			printf("ROUND #%d: Kings and Jokers are WILD\n\n", round_count - 2);
			break;
		}
	}
}

/*
Function: who_went_out()
------------------------------
Input Parameters: Player * player_array, int round_count, int num_players
Returns: integer between 1 and the number of players 

Asks who went out first, returns their id number
*/

int who_went_out(Player * player_array, int round_count, int num_players)
{
	int id_number = 0;
	do
	{
		which_round(round_count);

		printf("Enter the player's NUMBER who first went out.\n");
		printf("Reminder:\n");
		printf("--------------\n");
		for (int index = 0; index < num_players; index++)
		{
			printf("Player %d: %s\n", index + 1, player_array[index].name);
		}
		printf("--------------\n");
		scanf("%d", &id_number);

	} while ((id_number < 1 || id_number > num_players));

	return id_number;
}

/*
Function: get_score()
------------------------------
Input Parameters: Player * player_array, int player_index
Returns: n/a

Gets score and adds it to player's running score
*/

void get_score(Player * player_array, int player_index)
{
	int temp_score = 0;

	printf("What is %s's score?\n", player_array[player_index - 1].name);
	scanf("%d", &temp_score);
	player_array[player_index - 1].score += temp_score;

}



