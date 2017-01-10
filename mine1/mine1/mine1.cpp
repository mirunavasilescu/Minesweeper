// mine1.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include "mine.h"
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <random>
#include <string>
#include <fstream>

using namespace std;
void newGame();
void nextMove();
void replay();
void finalTime();
string line;
//clasament
void actualizeazaClasament(string searchedName, double scorFinal, char* numeFisier)
{
	ifstream fin(numeFisier);
	ofstream temp("temp.out");
	int gasitOnce = 0;
	string newLine = searchedName + " " + to_string(scorFinal);
	while (getline(fin, line) && line != "")
	{
		string delimiter = " ";
		string name = line.substr(0, line.find(delimiter));
		string score = line.substr(line.find(delimiter), line.length());
		double scoreInt = stod(score);
		if (name == searchedName && gasitOnce == 0)
		{
			gasitOnce = 1;
			if (scoreInt > scorFinal)
			{
				temp << newLine << endl;
			}
			else if (scoreInt <= scorFinal)
			{
				temp << line << endl;
			}
		}
		else if (scoreInt >= scorFinal && gasitOnce == 0)
		{
			temp << newLine << endl;
			temp << line << endl;
			gasitOnce = 1;
		}
		else if (name != searchedName)
			temp << line << endl;

	}
	if (gasitOnce == 0)
	{
		temp << newLine;
	}
	temp.close();
	fin.close();
	remove(numeFisier);
	rename("temp.out", numeFisier);
}
int verificareFinal()
{
	for (int i = 0; i < nrOfRows; i++)
		for (int j = 0; j < nrOfColumns; j++)
			if (mask[i][j] == '?')
				return 0;
	return 1;
}
void afisareCastigator()
{
	int i, j;
	cout << "     ";
	for (i = 0; i < nrOfColumns; i++)
		if (i <= 9)
			cout << i << "     ";
		else
			cout << i << "    ";
	cout << "\n";
	for (i = 0; i < nrOfRows; i++)
	{
		if (i <= 9)
			cout << i << "   ";
		else
			cout << i << "  ";
		for (j = 0; j < nrOfColumns; j++)
			cout << "|" << map.grid[i][j] << "|   ";
		cout << "\n";
	}
	cout << "\n";
}
//dupa fiecare pas
void afisareUtilizator()
{
	int i, j;
	cout << "     ";
	for (i = 0; i < nrOfColumns; i++)
		if(i<=9)
			cout << i << "     ";
		else
			cout << i << "    ";
	cout << "\n";
	for (i = 0; i < nrOfRows; i++)
	{
		if (i<=9)
			cout << i <<"   ";
		else
			cout << i << "  ";
		for (j = 0; j < nrOfColumns; j++)
			cout <<"|"<< mask[i][j] << "|   ";
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
	reset(9, 9);
	hiddenMatrix(9, 9, 10);
}
void medium()
{
	reset(16, 16);
	hiddenMatrix(16, 16, 40);
}
void hard()
{
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
//initializarea matricei utilizatorului
void initialMatrix()
{
	int i, j;
	for (i = 0; i < nrOfRows; i++)
		for (j = 0; j < nrOfColumns; j++)
			mask[i][j] = '?';
	afisareUtilizator();
}
void hiddenMatrix(int nrOfLines, int nrOfColumns, int nrOfMines)
{
	map.nrBombs = nrOfMines;
	srand(time(0));
	int linVecina, colVecina;
	while (map.nrBombs>0)
	{
		map.mine_x = rand() % nrOfLines;
		map.mine_y = rand() % nrOfColumns;
		if (map.grid[map.mine_x][map.mine_y] != 'B')
		{
			map.grid[map.mine_x][map.mine_y] = 'B';  //
			map.nrBombs--;
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
	afisareCastigator();
}

void showInvalid()
{
	cout << "Invalid answer. Please give a valid one:" << "\n";

}
int validLineOrColumn(char dim[100],int type)
{
	int position;
	if (dim[0] >= '0'&&dim[0] <= '9')
	{
		position = dim[0] - '0';
		if (dim[1] == NULL)
		{
			if ((type == 1 && position < nrOfRows) || (type == 2 && position < nrOfColumns))
				return position;
			else
			{
				cout << "Your position is out of game";
				return -1;
			}
		}
		else if (dim[2] == NULL)
		{

			if ((dim[1] >= '0'&&dim[1] <= '9'))
			{
				position = (dim[0] - 48) * 10 + dim[1] - '0';
				//////cond max
				if ((type == 1 && position < nrOfRows) || (type == 2 && position < nrOfColumns))
				{
					cout << "position=" << position << " " << nrOfRows << endl;
					return position;
					
				}
				else
				{
					cout << "Wrong input.Please give a valid one" << "\n";
					return -1;
				}
			}
			else
			{
				cout << "Wrong input.Please give a valid one" << "\n";
				return -1;
			}

		}
		else
		{
			cout << "Wrong input.Please give a valid one" << "\n";
			return -1;
		}
	}
	else
	{
		cout << "Wrong input.Please give a valid one" << "\n";
		return -1;
	}

}
void cinLineAndColumn()
{
    newRow = -1;
	while (newRow == -1)
	{
		cout << "\n" << "Give the row:" << "\n";
		cin >> dim1;
		newRow = validLineOrColumn(dim1, 1);
	}

	newColumn = -1;
	while (newColumn == -1)
	{
		cout << "\n" << "Give the column:" << "\n";
		cin >> dim2;
		newColumn = validLineOrColumn(dim2, 2);
	}

}
int checkJustMinesLeft()
{
	for (int i = 0; i < nrOfRows; i++)
		for (int j = 0; j < nrOfColumns; j++)
			if (mask[i][j]=='?'&&map.grid[i][j] !='B')
				return 0;
	return 1;
}
int checkAnyFlag()
{
	if (nrOfMines == minesLeft)
		return 0;
	return 1;
}
void winner()
{
	cout << "You won!" << "\n";
	afisareCastigator();
	finalTime();
	//clasament
	string name;
	cout << "Enter your name:" << "\n";
	cin >> name;
	char* file;
	if (difficulty == 1)
	{
		file = "Begginer.in";
		actualizeazaClasament(name, duration, file);
	}
	else if (difficulty == 2)
	{
		file = "Medium.in";
		actualizeazaClasament(name, duration, file);
	}
	else if (difficulty == 3)
	{
		file = "Expert.in";
		actualizeazaClasament(name, duration, file);
	}
	replay();
}
int identicMatrix()
{
	for (int i = 0; i < nrOfRows; i++)
		for (int j = 0; j < nrOfColumns; j++)
			if (map.grid[i][j] != mask[i][j])
				return 0;
	return 1;
}
int possibilityOfFlag()
{
	if (mask[newRow][newColumn] != '?')
		return 0;
	return 1;
}
void nextMove()
{
	cout << "Choose your next move:(Number of left mines:" << minesLeft << ")";
	cout << "\n" << "1.Flag" << "\n" << "2.Not a bomb" << "\n" << "3.Undo flag" << "\n"<<"4.New game"<<"\n";
	cout << "Your answer:"<<"\n";
	char moveType[101];
	cin >> moveType;
	while (moveType[0] <= 48 || moveType[0] >= 53 || moveType[1] != NULL)
	{
		showInvalid();
		cout << "Your answer:" << "\n";
		cin >> moveType;
	}
	if (moveType[0] == '4')
		newGame();
	else
	{ 
		bool wrongFlag = 0;
		if (moveType[0] == '1')
		{
			cinLineAndColumn(); 
			while (possibilityOfFlag() == 0)
			{
				cout << "That space is uncovered or you have a flag there.Please give a valid one:";
				cinLineAndColumn();
			}
			mask[newRow][newColumn] = 'F';
			if (map.grid[newRow][newColumn] != 'B')
				wrongFlag = 1;
			afisareUtilizator();
			minesLeft--;
			if (minesLeft == 0 && wrongFlag == 0)
			{
				if (verificareFinal() == 1)
					winner();
				else
					nextMove();
			}
			else
				nextMove();
		}
		else if (moveType[0] == '2')
		{
			cinLineAndColumn();
			while (mask[newRow][newColumn] != '?')
			{
				cout << "That is an uncoverded zone .Please give another one!";
				cinLineAndColumn();
			}
			if (map.grid[newRow][newColumn] == 'B')
			{
				cout << "Game Over!"<<"\n";
				finalTime();
				replay();
			}
			//descoperim bucata mai mare
			else if (map.grid[newRow][newColumn] == '0')
			{
				//If our location isn't in proximity to a mine we reveal all neighboring locations indicate no neighboring mine
					//openLocations holds neighboring locations that also are not in proximity to a mine
					queue<pair<int, int> > openLocations;
					openLocations.push(make_pair(newRow, newColumn));
					//Walk through all 0 locations and reveal their neighboars
					while (!openLocations.empty())
					{
						//Get the next location from our queue
						pair<int, int> next = openLocations.front();
						//The two for loops iterate over a 3x3 block within our map surrounding the point next.  It will check the point itself
						for (int dx = next.first - 1; dx <= next.first + 1; dx++)
						{
							for (int dy = next.second - 1; dy <= next.second + 1; dy++)
							{
								//Let's make sure the current location is within the bounds of our map.
								if (dx >= 0 && dx < nrOfRows && dy >= 0 && dy < nrOfColumns)
								{
									//if this neighbor is a 0 location and hasn't previously been revealed, add it to our list
									if (map.grid[dx][dy] == '0' && mask[dx][dy] == '?')
										openLocations.push(make_pair(dx, dy));
									//reveal this neighboring location
									mask[dx][dy] = map.grid[dx][dy];
								}
							}
						}
						//We're done with the current location in our queue, so we can remove it
						openLocations.pop();
					}
					if (verificareFinal() == 1)
						winner();
					else
						if (checkJustMinesLeft() == 1)// && identicMatrix() == 1)
							winner();
						else
						{
							afisareUtilizator();
							nextMove();
						}
			}
			//are 1-..8 bombe
			else
			{
				mask[newRow][newColumn] = map.grid[newRow][newColumn];
				if (verificareFinal() == 1)
					winner();
				else
					if (checkJustMinesLeft() == 1) //&& identicMatrix() == 1)
						winner();
					else
					{
						afisareUtilizator();
						nextMove();
					}
			}
		}
		//delete flag
		else if (moveType[0] == '3')
		{
			if (checkAnyFlag() == 0)
			{
				cout << "It's your first move,you have no Flags there!";
				nextMove();
			}
			else
			{
				cinLineAndColumn();
				while (mask[newRow][newColumn] != 'F')
				{
					cout << "You don't have a flag there" << "\n" << "Please give a valid one!";
					cinLineAndColumn();
				}
				mask[newRow][newColumn] = '?';
				minesLeft++;
				if (wrongFlag == 1 && map.grid[newRow][newColumn] == 'B')
					wrongFlag = 0;
				afisareUtilizator();
				nextMove();
			}
		}
	 }
}
void startTime()
{
	start = clock();
}
void finalTime()
{
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;
	std::cout << "Your time:" << duration <<"s"<< '\n';
}
void newGame()
{
	cout << "Choose the dificulty:";
	cout << "\n";
	cout <<"1. Beginner (height:9   width:9   mines:10)" << "\n" << "2. Intermediate (height:16   width:16   mines:40)" << "\n" << "3. Expert (height:16   width:30   mines:99)"<<"\n"<<"4. Custom"<<"\n";
	cout << "Your answer:" << "\n";
	char gameType[101];
	cin >> gameType;
	while (gameType[0] <= 48 || gameType[0] >= 53 || gameType[1] != NULL)
	{
		showInvalid();
		cout << "Your answer:" << "\n";
		cin >> gameType;
	}
	if (gameType[0] == '1')
		{
			startTime();
			difficulty = 1;
			nrOfMines = 10;
			minesLeft = nrOfMines;
			nrOfRows= nrOfColumns=9;
			easy();
		}
	else if (gameType[0] == '2')
		{
			startTime();
			difficulty = 2;
			nrOfMines = 40;
			minesLeft = nrOfMines;
			nrOfRows = nrOfColumns=16;
			medium();
		}
	else if (gameType[0] == '3')
	{
		startTime();
		difficulty = 3;
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
		startTime();
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
			exit(0);
			break;
		default:
			showInvalid();
			cout << "Your answer:" << "\n";
			replay();
			break;
	}
}

int main()
{
	newGame();
	return 0;
}

