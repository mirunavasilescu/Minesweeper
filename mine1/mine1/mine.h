#include <ctime>
#define DIMMAX 100
#include <cstdio>
#include <string>
#include <stdlib.h>
#include <queue>
#include <vector>
#include <utility>
#include <random>
#include <fstream>

int nrOfMines, nrOfRows, nrOfColumns;

struct joc
{
	char grid[DIMMAX][DIMMAX], i, j;
	int mine_x, mine_y;
	int nrBombs;

}map;


void hiddenMatrix(int nrOfLines, int nrOfColumns, int nrOfMines);

char mask[16][30];
int minesLeft;

int newColumn;
int newRow;
char dim1[101];
char dim2[101];

//custom
char customRow[101];
char customColumn[101];

//pt timp
double duration;
clock_t start;

//pt clasament
int difficulty;

int nrOfPlayedGames;
int nrOfMoves;

//PT HINT
int nrOfLeftHints=3;
int hintRow;
int hintColumn;
int resetHint = 0;

bool wrongFlag;

int finishedPrevGame = 0;

char gameType[1001];
char endGame[1001];
int wonGame;