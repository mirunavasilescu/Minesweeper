// mine1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mine.h"
#include <iostream>
using namespace std;

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
void afisareUtilizator()
{
	int i, j;
	cout << "  ";
	for (i = 0; i < nrOfRows; i++)
		cout << i << " ";
	cout << "\n";
	for (i = 0; i < nrOfRows; i++)
	{
		cout << i << " ";
		for (j = 0; j < nrOfColumns; j++)
			cout << playerMatrix[i][j] << " ";
		cout << "\n";
	}
}
void easy()
{
	cout << "tana" << "\n";
	//hiddenMatrix(9, 9, 10);
	
}
void medium()
{
	cout << "tanaa"<<"\n";
	//hiddenMatrix(16, 16, 40);
}
void hard()
{
	cout << "tanaaa" << "\n";
	//hiddenMatrix(16, 30, 99);
}

int valid(int x, int y)
{
	if (x <= y)
		return 1;
	return 0;
}
void initialMatrix()
{
	int i, j;
	for (i = 0; i < nrOfRows; i++)
		for (j = 0; j < nrOfColumns; j++)
			playerMatrix[i][j] = '?';
	afisareUtilizator();
}
void nextMove()
{
	cout << "Choose your next move:" << "\n" << "1.Flag" << "\n" << "2.Not a bomb" << "\n";
	char type2;
	cin >> type2;
	cout << "Give the row" << "\n";
	int newrow;
	cin >> newrow;
	cout << "Give the column" << "\n";
	int newcolumn;
	cin >> newcolumn;
	if (type2 == '1')
	{
		playerMatrix[newrow][newcolumn] = 'F';
		afisareUtilizator();
	}
	//else

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
			nrOfRows= nrOfColumns=9;
			easy();
		}
	else if (type == '2')
		{
			nrOfMines = 40;
			nrOfRows = nrOfColumns=16;
			medium();
		}
	else if (type == '3')
	{
		nrOfRows = 16;
		nrOfColumns = 30;
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
		//hiddenMatrix(nrOfRows,nrOfColumns,nrOfMines);
	}
	initialMatrix();
	nextMove();
}
int main()
{
	
	newGame();
	return 0;
}

