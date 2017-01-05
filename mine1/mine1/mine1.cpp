// mine1.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include "mine.h"
#include <iostream>
using namespace std;
void newGame();
void nextMove();
void replay();
//unused
void afisare(int dim1, int dim2)
{
	int i, j;
	for (i = 0; i < dim1; i++)
	{
		for (j = 0; j < dim2; j++)
			cout << matrixGame[i][j] << " ";
		cout << "\n";
	}
}
//dupa fiecare pas
void afisareUtilizator()
{
	int i, j;
	cout << "  ";
	for (i = 0; i < nrOfColumns; i++)
		cout << i << " ";
	cout << "\n";
	for (i = 0; i < nrOfRows; i++)
	{
		cout << i << " ";
		for (j = 0; j < nrOfColumns; j++)
			cout << mask[i][j] << " ";
		cout << "\n";
	}
}
void reset(int nrOfLines, int nrOfColumns)
{
	int i, j;
	for (i = 0; i<nrOfLines; i++)
		for (j = 0; j<nrOfColumns; j++)
			map.grid[i][j] = '0';

}
//situatiile clasice
void easy()
{
	cout << "tana" << "\n";
	reset(9, 9);
	hiddenMatrix(9, 9, 10);
	
}
void medium()
{
	cout << "tanaa"<<"\n";
	reset(16, 16);
	hiddenMatrix(16, 16, 40);
}
void hard()
{
	cout << "tanaaa" << "\n";
	reset(16, 30);
	hiddenMatrix(16, 30, 99);
}
//verificare date valide
int valid(int x, int y)
{
	if (x <= y)
		return 1;
	return 0;
}
//inceputul
void initialMatrix()
{
	int i, j;
	for (i = 0; i < nrOfRows; i++)
		for (j = 0; j < nrOfColumns; j++)
			mask[i][j] = '?';
	afisareUtilizator();
}/////////////////////
//atasez mine2//
/////////////////////



void hiddenMatrix(int nrOfLines, int nrOfColumns, int nrOfMines)
{
	map.nrbombe = nrOfMines;
	srand(time(0));
	int linVecina, colVecina;
	while (map.nrbombe>0)
	{
		map.mine_x = rand() % nrOfLines;
		cout << map.mine_x << " ";
		map.mine_y = rand() % nrOfColumns;
		cout << map.mine_y << " " << "\n";

		if (map.grid[map.mine_x][map.mine_y] != 'B')
		{
			map.grid[map.mine_x][map.mine_y] = 'B';  //
			map.nrbombe--;
			for (linVecina = -1; linVecina <= 1; linVecina++)
				for (colVecina = -1; colVecina <= 1; colVecina++)
					if (linVecina != 0 || colVecina != 0)
						if (map.grid[map.mine_x][map.mine_y] == 'B')
						{
							int linieCurenta, colCurenta;
							linieCurenta = map.mine_x + linVecina; colCurenta = map.mine_y + colVecina;
							if ((linieCurenta >= 0 && colCurenta >= 0) && (linieCurenta <= nrOfLines&&colCurenta <= nrOfColumns))
								if (map.grid[linieCurenta][colCurenta] != 'B')
									map.grid[linieCurenta][colCurenta]++;
						}

		}
	}
	int i, j;
	cout << "  ";
	for (i = 0; i <= nrOfColumns - 1; i++)
		cout << i << " ";
	cout << "\n";
	for (i = 0; i <= nrOfLines - 1; i++)
	{
		cout << i << " ";
		for (j = 0; j<nrOfColumns; j++)
			cout << map.grid[i][j] << " ";
		cout << endl;
	}
}


/////////////////////////////////


void nextMove()
{
	cout << "Choose your next move:(Number of left mines:" << minesLeft << ")";
	cout << "\n" << "1.Flag" << "\n" << "2.Not a bomb" << "\n" << "3.Undo flag" << "\n";
	char type2;
	cin >> type2;
	cout << "Give the row" << "\n";
	int newrow;
	cin >> newrow;
	cout << "Give the column" << "\n";
	int newcolumn;
	cin >> newcolumn;
	bool wrongFlag = 0;
	if (type2 == '1')
	{
		mask[newrow][newcolumn] = 'F';
		if (map.grid[newrow][newcolumn] != 'B')
			wrongFlag = 1;
		afisareUtilizator();
		minesLeft--;
		if (minesLeft == 0 && wrongFlag == 0)
		{
			cout << "You win!"<<"\n";
			replay();
			
		}
		else
			nextMove();
	}
	else if (type2 == '2')
	{
		if (map.grid[newrow][newcolumn] =='B')
		{
			cout << "Game Over!"<<"\n";
			replay();
		}

		//descoperim bucata mai mare????
		else if (map.grid[newrow][newcolumn] == 0)
		{

		}

		//are 1-..8 bombe
		else
		{
			mask[newrow][newcolumn] = map.grid[newrow][newcolumn];
			afisareUtilizator();
			nextMove();
		}
	}
	//sterg flag
	else
	{
		mask[newrow][newcolumn] = '?';
		minesLeft++;
		if (wrongFlag == 1 && map.grid[newrow][newcolumn] == 'B')
			wrongFlag = 0;
		afisareUtilizator();
		nextMove();
	}

}
void newGame()
{
	cout << "Choose the dificulty:";
	cout << "\n";
	cout <<"1. Beginner (height:9   width:9   mines:10)" << "\n" << "2. Intermediate (height:16   width:16   mines:40)" << "\n" << "3. Expert (height:16   width:30   mines:99)"<<"\n"<<"4. Custom"<<"\n";
	char type;
	cin >> type;
	if (type == '1')
		{
			nrOfMines = 10;
			minesLeft = nrOfMines;
			nrOfRows= nrOfColumns=9;
			easy();
		}
	else if (type == '2')
		{
			nrOfMines = 40;
			minesLeft = nrOfMines;
			nrOfRows = nrOfColumns=16;
			medium();
		}
	else if (type == '3')
	{
		nrOfRows = 16;
		nrOfColumns = 30;
		minesLeft = nrOfMines;
		nrOfMines = 99;
		hard();
	}
	else
	{
		cout << "Give the height:"; 
		cin >> nrOfRows;
		while (valid(nrOfRows, 16) == 0)
		{
			cout << "Incorect dates"<<"\n"<<"Give a valid height:"<<"\n";
			cin >> nrOfRows;
		}
		cout << "Give the width:";
		cin >> nrOfColumns;
		while (valid(nrOfColumns, 30) == 0)
		{
			cout << "Incorect dates" << "\n" << "Give a valid width:" << "\n";
			cin >> nrOfColumns;
		}
		cout << "Give the number of mines:";
		cin >> nrOfMines;
		while (valid(nrOfMines, 99) == 0)
		{
			cout << "Incorect dates" << "\n" << "Give a valid number of mines:" << "\n";
			cin >> nrOfMines;
		}
		minesLeft = nrOfMines;
		reset(nrOfRows,nrOfColumns);
		hiddenMatrix(nrOfRows,nrOfColumns,nrOfMines);
	}
	initialMatrix();
	nextMove();
}
////replay

void replay()
{
	char a;
	cout << "1) Replay 2) Quit" << endl;
	cin >> a;
	switch (a)
	{
	case '1':
		newGame();
		break;
	case '2':
		cout << "Quit" << endl;
		break;
	default:
		cout << "Invalid input" << endl;
		replay();
		break;
	}
}

int main()
{
	newGame();
	return 0;
}

