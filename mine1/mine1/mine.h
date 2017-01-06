#include <ctime>
#define DIMMAX 100
int nrOfMines, nrOfRows, nrOfColumns;
int matrixGame[100][100];
struct joc
{
	char grid[DIMMAX][DIMMAX], i, j;
	int mine_x, mine_y;
	int nrbombe;

}map;


void hiddenMatrix(int nrOfLines, int nrOfColumns, int nrOfMines);

char mask[16][30];
int minesLeft;

int newcolumn;
int newrow;
