#ifndef SHUT_THE_BOX
#define SHUT_THE_BOX

#define BOX_SIZE            9
#define LENGHT_PLAYER_NAME  10

#define C_HORZ              0xcd
#define C_VERT              0xba
#define ANGLE_LEFT_UP       0xc9
#define ANGLE_RIGHT_UP      0xbb
#define ANGLE_LEFT_DOWN     0xc8
#define ANGLE_RIGHT_DOWN    0xbc
#define CON_UP_DOWN         0xcb
#define CON_DOWN_UP         0xca
#define CON_LEFT_RIGHT      0xcc
#define CON_RIGHT_LEFT      0xb9

void init_game(int box[]);
void print_box(int box[]);
void ShutBox(int box[], int boxToShut);
int BoxIsOpen(int box[], int boxToVerify);
int SelectNumberOfPlayers();
void SelectPlayersNames(char *playersNames[], int nbr_joueurs);
void SuppCarriageReturn(char string[]);
void RollDices(int Dices[]);
void PrintDices(int Dices[]);
int CheckWin(int box[], int Dices[]);
void GetUserInput(int input[]);
int CheckUserInput(int box[], int input[], int Dices[]);
int SumOfBoxes(int box[]);
void help();
void help_french();
#endif