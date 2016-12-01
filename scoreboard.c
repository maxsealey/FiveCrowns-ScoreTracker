#include "scoreboard.h"

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

void initialize_player_struct(Player *player_array, int player_index)
{
	char temp[10] = { '\0' };

	player_array[player_index].is_occupied = TRUE; // player struct is occupied

	printf("What is Player %d's name?\n", player_index + 1);
	scanf("%s", temp); // Gets player name

	for (int index = 0; index < 10; index++)
	{
		player_array[player_index].name[index] = temp[index];
	}	// assigns name string to struct

	player_array[player_index].score = 0; // set score to 0

	player_array[player_index].final_ranking = 0;

	player_array[player_index].identity = player_index + 1; // unique int identifier

	system("cls");
}

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

void main_play(Player * player_array, int round_count, int num_players)
{
	int id_number = 0, index = 0, player_index = 0, player_index2 = 0, temp_score = 0, p_index3 = 0;

	char temp[10] = { '\0' };

	do
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
		printf("Enter the player's NUMBER who first went out.\n");
		printf("Reminder:\n");
		printf("--------------\n");
		for (index = 0; index < num_players; index++)
		{
			printf("Player %d: %s\n", index + 1, player_array[index].name);
		}
		printf("--------------\n");
		scanf("%d", &id_number);
		//system("cls");

	} while ((id_number < 1 || id_number > num_players));

	int left = 0, right = 0, mid = 0;

	left = 1;
	mid = id_number;
	right = num_players;

	if (mid == right)
	{
		for (player_index = left; player_index < right; player_index++)
		{
			printf("What is %s's score?\n", player_array[player_index - 1].name);
			scanf("%d", &temp_score);
			player_array[player_index - 1].score += temp_score;
		}
	}
	else if (mid == left)
	{
		for (p_index3 = left + 1; p_index3 <= num_players; p_index3++)
		{
			printf("What is %s's score?\n", player_array[p_index3 - 1].name);
			scanf("%d", &temp_score);
			player_array[p_index3 - 1].score += temp_score;
		}
	}
	else
	{
		for (player_index2 = mid + 1; player_index2 <= right; player_index2++)
		{
			printf("What is %s's score?\n", player_array[player_index2 - 1].name);
			scanf("%d", &temp_score);
			player_array[player_index2 - 1].score += temp_score;
		}

		for (player_index = left; player_index < mid; player_index++)
		{
			printf("What is %s's score?\n", player_array[player_index - 1].name);
			scanf("%d", &temp_score);
			player_array[player_index - 1].score += temp_score;
		}
	}
	temp_score = 0;
}

void write_stats_to_file(FILE * logfile, Player * player_array, int num_players)
{
	int index = 0;

	for (index = 0; index < num_players; index++)
	{
		fprintf(logfile, "Player %d: %s\n", index + 1, player_array[index].name);
		fprintf(logfile, "Final Score: %d\n\n", player_array[index].score);
	}
}

void determine_winner(Player * player_array, int num_players)
{
	int winner = 0, index2 = 0;
	// 1, 2, 3, 4
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
	printf("---------------------------------\n");
	

}



