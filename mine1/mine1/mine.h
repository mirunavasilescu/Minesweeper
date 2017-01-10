#include <ctime>
#define DIMMAX 100
#include <cstdio>

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

//pt timp
double duration;
clock_t start;

int difficulty;
