#include "shutTheBox.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    printf("Do you need help to know how to play ? (y/n) : ");
    char resp;
    scanf("%c",&resp);
    if (resp == 'y' || resp == 'Y')
    {
        help();
    }
    
    srand(time(NULL));
    int nb_players = SelectNumberOfPlayers();
    char *PlayersNames[4];
    int scores[4] = {0, 0, 0, 0};
    SelectPlayersNames(PlayersNames, nb_players);
    int box[9];
    int Dices[2] = {0, 0};
    int input[5];
    int j;
    init_game(box);
    while (CheckWin(box, Dices) != 1)
    {
        for (int i = 0; i < nb_players; i++)
        {
            init_game(box);
            Dices[0] = 0;
            Dices[1] = 0;
            printf("%s's turn\n", PlayersNames[i]);
            while (1)
            {
                print_box(box);
                RollDices(Dices);
                PrintDices(Dices);
                if (CheckWin(box, Dices) != 0)
                {
                    printf("Round finished\n");
                    scores[i] += SumOfBoxes(box);
                    break;
                }
                do
                {
                    GetUserInput(input);
                } while (!CheckUserInput(box, input, Dices));
                j = 0;
                while (input[j] != '\0')
                {
                    ShutBox(box, input[j]);
                    j++;
                }
            }
            if (CheckWin(box, Dices) == 1)
            {
                break;
            }
        }
    }
    int i_min;
    int min = 0;
    for (int i = 0; i < nb_players; i++)
    {
        printf("%s : %d\n", PlayersNames[i], scores[i]);
        if (scores[i] > min)
        {
            min = scores[i];
            i_min = i;
        }
    }
    printf("Winner : %s with %d points", PlayersNames[i_min], min);

    return EXIT_SUCCESS;
}