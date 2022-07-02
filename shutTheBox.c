#include "shutTheBox.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void init_game(int box[])
{
    for (int i = 0; i < BOX_SIZE; i++)
    {
        box[i] = i + 1;
    }
}

void print_box(int box[])
{
    // top line
    printf("%c", ANGLE_LEFT_UP);
    for (int i = 0; i <= ((BOX_SIZE + 2) * 3) + 1; i++)
    {
        if ((i + 1) % 4 == 0)
        {
            printf("%c", CON_UP_DOWN);
        }
        else
        {
            printf("%c", C_HORZ);
        }
    }
    printf("%c\n", ANGLE_RIGHT_UP);
    // middle line
    int indice = 0;
    for (int i = 0; i <= (BOX_SIZE + 3) * 3; i++)
    {
        if ((i - 2) % 4 == 0)
        {
            if (box[indice] == 0)
            {
                printf(" %c ", 0xdb);
            }
            else
            {
                printf(" %d ", box[indice]);
            }
            indice++;
        }
        else if (i % 4 == 0)
        {
            printf("%c", C_VERT);
        }
    }
    // bottom line
    printf("\n%c", ANGLE_LEFT_DOWN);
    for (int i = 0; i <= ((BOX_SIZE + 2) * 3) + 1; i++)
    {
        if ((i + 1) % 4 == 0)
        {
            printf("%c", CON_DOWN_UP);
        }
        else
        {
            printf("%c", C_HORZ);
        }
    }
    printf("%c\n", ANGLE_RIGHT_DOWN);
}

void ShutBox(int box[], int boxToShut)
{
    box[boxToShut - 1] = 0;
}

int BoxIsOpen(int box[], int boxToVerify)
{
    return (box[boxToVerify] != 0);
}

int SelectNumberOfPlayers()
{
    int nb_players;
    printf("Number of players (between 1 and 4) : ");
    scanf("%d", &nb_players);
    return nb_players;
}

void SuppCarriageReturn(char string[])
{
    int i = 0;
    while (string[i] != '\0')
    {
        if (string[i] == '\n')
        {
            string[i] = '\0';
            return;
        }
        i++;
    }
}

void SelectPlayersNames(char *playersNames[], int nbr_joueurs)
{
    getchar();
    for (int i = 0; i < nbr_joueurs; i++)
    {
        printf("Name of the player number %d : ", i + 1);
        playersNames[i] = malloc(sizeof(char) * (LENGHT_PLAYER_NAME + 1));
        fgets(playersNames[i], LENGHT_PLAYER_NAME, stdin);
        SuppCarriageReturn(playersNames[i]);
    }
}

void RollDices(int Dices[])
{
    for (int dice = 0; dice < 2; dice++)
    {
        Dices[dice] = (rand() % 6) + 1;
    }
}

void PrintDices(int Dices[])
{
    printf("%c%c%c %c%c%c\n", ANGLE_LEFT_UP, C_HORZ, ANGLE_RIGHT_UP, ANGLE_LEFT_UP, C_HORZ, ANGLE_RIGHT_UP);
    printf("%c%d%c %c%d%c\n", C_VERT, Dices[0], C_VERT, C_VERT, Dices[1], C_VERT);
    printf("%c%c%c %c%c%c\n", ANGLE_LEFT_DOWN, C_HORZ, ANGLE_RIGHT_DOWN, ANGLE_LEFT_DOWN, C_HORZ, ANGLE_RIGHT_DOWN);
}

int CheckWin(int box[], int Dices[])
{
    if (Dices[0] == 0 && Dices[1] == 0)
    {
        return 0;
    }
    if (box[0] == 0 && box[1] == 0 && box[2] == 0 && box[3] == 0 && box[4] == 0 && box[5] == 0 && box[6] == 0 && box[7] == 0 && box[8] == 0)
    {
        return 1;
    }
    int SumDices = Dices[0] + Dices[1];
    int SumBoxes;
    for (int i = 0; i < BOX_SIZE; i++)
    {
        if (box[i] != 0)
        {
            if (box[i] != SumDices)
            {
                for (int j = 0; j < BOX_SIZE; j++)
                {
                    if (box[j] != 0 && i != j)
                    {
                        SumBoxes = box[i] + box[j];
                        if (SumBoxes != SumDices)
                        {
                            for (int k = 0; k < BOX_SIZE; k++)
                            {
                                if (box[k] != 0 && k != i && k != j)
                                {
                                    SumBoxes = box[i] + box[j] + box[k];
                                    if (SumBoxes != SumDices)
                                    {
                                        for (int l = 0; l < BOX_SIZE; l++)
                                        {
                                            if (box[l] != 0 && l != k && l != j && l != i)
                                            {
                                                SumBoxes = box[i] + box[j] + box[k] + box[l];
                                                if (SumBoxes != SumDices)
                                                {
                                                    continue;
                                                }
                                                else
                                                {
                                                    return 0;
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        return 0;
                                    }
                                }
                            }
                        }
                        else
                        {
                            return 0;
                        }
                    }
                }
            }
            else
            {
                return 0;
            }
        }
    }
    return -1;
}

void GetUserInput(int input[])
{
    printf("Number of the boxes to shut : ");
    char strinput[9];
    fflush(stdin);
    fgets(strinput, 9, stdin);
    SuppCarriageReturn(strinput);
    int i = 0;
    input[i] = atoi(strtok(strinput, " "));
    if (input[i] == 0)
    {
        input[i] = '\0';
    }
    while (input[i] != 0 && i < 4)
    {
        i++;
        input[i] = atoi(strtok(NULL, " "));
    }
    input[i + 1] = '\0';
}

int CheckUserInput(int box[], int input[], int Dices[])
{
    int SumInput = 0;
    int SumDices = Dices[0] + Dices[1];
    int i = 0;
    while (input[i] != '\0')
    {
        SumInput += input[i];
        if (!BoxIsOpen(box, input[i] - 1))
        {
            return 0;
        }
        i++;
    }
    if (SumDices == SumInput)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int SumOfBoxes(int box[])
{
    int Sum = 0;
    for (int i = 0; i < BOX_SIZE; i++)
    {
        Sum += box[i];
    }
    return Sum;
}

void help(){
    printf("In this game the goal is to close the most boxes, when a player has managed to close all the boxes the game ends.\nThe final score is the sum of all the boxes you failed to close during the different rounds, the person with the lowest score wins.\nThe players play one by one, during a turn two dice are thrown and it is necessary to close boxes which have a total value equivalent to the sum of the dice. You can close between 1 and 4 boxes per turn.\nTo close several boxes you must enter their numbers in this way: 3 5 2\nWhen you can't play your turn is over\n");
}

void help_french(){
    printf("Dans ce jeu le but est de fermer le plus de boites, quand un joueur a reussi a fermer toutes les boites le jeu s'arrete.\nLe score final est la somme de toutes les boites que vous n'avez pas reussi a fermer durant les differents tours, la personne avec le score le plus faible l'emporte.\nLe joueurs jouent un par un, durant un tour deux des sont lances et il faut fermer des boites qui ont une valeur totale equivalente a la somme des des. Vous pouvez fermer entre 1 et 4 boites par tour.\nPour fermer plusieurs boites il faut entrer leurs nombres de cette façon : 3 5 2\nQuand vous ne pouvez pas jouer votre tour est termine\n");
}