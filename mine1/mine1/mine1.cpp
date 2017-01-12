// mine1.cpp : Defines the entry point for the console application.
//
#include"stdafx.h"
#include "mine.h"
#include <iostream>
#include <queue>
#include <vector>
#include <utility>
#include <random>

#include <fstream>

using namespace std;
void newGame();
void nextMove();
int replay();
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
	cout << "    ";
	for (i = 0; i < nrOfColumns; i++)
		if (i <= 9)
			cout << i << "    ";
		else
			cout << i << "   ";
	cout << "\n";
	for (i = 0; i < nrOfRows; i++)
	{
		if (i <= 9)
			cout << i << "  ";
		else
			cout << i << " ";
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
	cout << "    ";
	for (i = 0; i < nrOfColumns; i++)
		if(i<=9)
			cout << i << "    ";
		else
			cout << i << "   ";
	cout << "\n";
	for (i = 0; i < nrOfRows; i++)
	{
		if (i<=9)
			cout << i <<"  ";
		else
			cout << i << " ";
		for (j = 0; j < nrOfColumns; j++)
			cout <<"|"<< mask[i][j] << "|  ";
		cout << "\n";
	}
	cout << "\n";
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
	//startTime();
	difficulty = 1;
	nrOfMines = 10;
	minesLeft = nrOfMines;
	nrOfRows = nrOfColumns = 9;
	reset(9, 9);
	hiddenMatrix(9, 9, 10);
}
void medium()
{
	//startTime();
	difficulty = 2;
	nrOfMines = 40;
	minesLeft = nrOfMines;
	nrOfRows = nrOfColumns = 16;
	reset(16, 16);
	hiddenMatrix(16, 16, 40);
}
void hard()
{
	//startTime();
	difficulty = 3;
	nrOfRows = 16;
	nrOfColumns = 30;
	minesLeft = nrOfMines;
	nrOfMines = 99;
	reset(16, 30);
	hiddenMatrix(16, 30, 99);
}

int validForCustom(char coord[101], int dimMax)
{
	
	int position;
	if (coord[0] > '0'&&coord[0] <= '9')
	{
		position = coord[0] - '0';
		if (coord[1] == NULL)
		{
			if (position <= dimMax && position>1) 
				return position;
			else
			{
				cout << "You can't give such a big/small number of lines/columns"<<"\n";
				return -1;
			}
		}
		else if (coord[2] == NULL)
		{

			if ((coord[1] >= '0'&&coord[1] <= '9'))
			{
				position = (coord[0] - 48) * 10 + coord[1] - '0';
				//////cond max
				if ( position < dimMax) 
				{
					cout << "position=" << position << " " << dimMax << endl;
					return position;
				}
				else
				{
					cout << "1 Wrong input.Please give a valid one" << "\n";
					return -1;
				}
			}
			else
			{
				cout << "2 Wrong input.Please give a valid one" << "\n";
				return -1;
			}

		}
		else
		{
			cout << "3 Wrong input.Please give a valid one" << "\n";
			return -1;
		}
	}
	else
	{
		cout << "4 Wrong input.Please give a valid one" << "\n";
		return -1;
	}
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
	if ((dim[0] > '0'&&dim[0] <= '9') || (dim[0] == '0'&&dim[1]==NULL))
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
					cout << "1 Wrong input.Please give a valid one" << "\n";
					return -1;
				}
			}
			else
			{
				cout << "2 Wrong input.Please give a valid one" << "\n";
				return -1;
			}

		}
		else
		{
			cout << "3 Wrong input.Please give a valid one" << "\n";
			return -1;
		}
	}
	else
	{
		cout << "4 Wrong input.Please give a valid one" << "\n";
		return -1;
	}

}
void cinValidNewLine()
{
	cout << "\n" << "Give the row:" << "\n";
	cin.getline(dim1, 101);
	cout << "dim1 " << dim1 << "\n";
	newRow = validLineOrColumn(dim1, 1);
}
void cinValidNewColumn()
{
	cout << "\n" << "Give the column:" << "\n";
	cin.getline(dim2, 101);
	cout << "dim2 " << dim2 << "\n";
	newColumn = validLineOrColumn(dim2, 2);
}
void cinLineAndColumn()
{
    newRow = -1;
	while (newRow == -1)
		cinValidNewLine();
	newColumn = -1;
	while (newColumn == -1)
		cinValidNewColumn();
}
int checkJustUncoveredMinesLeft()
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

void addToRanking()
{
	string name;
	cout << "Enter your name:" << "\n";
	cin >> name;
	char* file;
	switch (difficulty)
	{
	case '1':
		file = "Begginer.in";
		actualizeazaClasament(name, duration, file);
		break;
	case '2':
		file = "Medium.in";
		actualizeazaClasament(name, duration, file);
		break;
	case '3':
		file = "Expert.in";
		actualizeazaClasament(name, duration, file);
		break;
	}
}
void winner()
{
	cout << "You won!" << "\n";
	finishedPrevGame++;
	afisareCastigator();
	finalTime();
	if (difficulty != 4)
	{
		addToRanking();
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
	{
		cout << "That space is uncovered or you have a flag or a hint there.Please give a valid one:";
		return 0;
	}
	return 1;
}
int possibilityOfHint()
{
	if (mask[hintRow][hintColumn] == '?'&&map.grid[hintRow][hintColumn] != 'B')
		return 1;
	else
		return 0;
}
void putHint()
{
	int foundHint = 0;
	srand(time(0));
	while (foundHint == 0)
	{
		hintRow = rand() % nrOfRows;
		hintColumn = rand() % nrOfColumns;
		if (possibilityOfHint()==1)
		{
			foundHint = 1;
			nrOfLeftHints--;
			mask[hintRow][hintColumn] = 'H';
			afisareUtilizator();
			cout << "You have " << nrOfLeftHints << " left hint(s)" << "\n";
			resetHint = 1;
		}
	}
}

void nextMoveIsFlag()
{
	cinLineAndColumn();
	while (possibilityOfFlag() == 0)
		cinLineAndColumn();
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
void gameOver()
{
	cout << "Game Over!" << "\n";
	finishedPrevGame++;
	finalTime();
	replay();
}
void nextMoveIsRevealMask()
{
	cinLineAndColumn();
	while (mask[newRow][newColumn] != '?'&&mask[newRow][newColumn] != 'H')
	{
		cout << "That is an uncoverded zone .Please give another one!";
		cinLineAndColumn();
	}
	if (map.grid[newRow][newColumn] == 'B')
		gameOver();
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
			if (checkJustUncoveredMinesLeft() == 1)
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
			if (checkJustUncoveredMinesLeft() == 1) 
				winner();
			else
			{
				afisareUtilizator();
				nextMove();
			}
	}
}
void nextMoveIsUndoFlag()
{
	if (checkAnyFlag() == 0)
	{
		cout << "You have no Flags as to undo them!" << "\n"<<"\n";
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
void nextMove()
{
	cout << "Choose your next move:(Number of left mines:" << minesLeft << ")";
	cout << "\n" << "1.Flag" << "\n" << "2.Not a bomb" << "\n" << "3.Undo flag" << "\n"<<"4.New game"<<"\n"<<"5.Hint"<<"\n"<<"\n";
	cout << "Your answer:"<<"\n";
	char moveType[100];
	if (difficulty == 4 && nrOfMoves==0)
	{
		char c;
		cin.get(c);
	}
	cin.getline(moveType, 101);
	cout << "moveType " << moveType << "\n";
	while (moveType[0] <= 48 || moveType[0] >= 54 || moveType[1] != NULL)
	{
		showInvalid();
		cout << "Your answer:" << "\n";
		cin.getline(moveType, 101);
	}
	nrOfMoves++;
	if (moveType[0] == '4')
	{
		nrOfMoves = 0;
		system("cls");
		newGame();
	}
	else
	{ 
		if (resetHint == 1 && mask[hintRow][hintColumn] == 'H')
		{
			mask[hintRow][hintColumn] = '?';
			resetHint = 0;
		}
		wrongFlag = 0;
		if (moveType[0] == '1')
		{
			nextMoveIsFlag();
		}
		else if (moveType[0] == '2')
		{
			nextMoveIsRevealMask();
		}
		//delete flag
		else if (moveType[0] == '3')
		{
			nextMoveIsUndoFlag();
		}
		
		else if (moveType[0] == '5')
		{
			if (nrOfLeftHints >= 1)
			{
				putHint();
			}
			else
				cout << "You have no hints left!"<<"\n";
			nextMove();
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
void setNrOfHints()
{
	if (nrOfRows*nrOfColumns < 81)
		nrOfLeftHints = 1;
	else
		nrOfLeftHints = 3;
}
void validGameType()
{
	
	cout << "gameType" << gameType << "\n";
	while (gameType[0] <= 48 || gameType[0] >= 53 || gameType[1] != NULL)
	{
		showInvalid();
		cout << "Your answer:" << "\n";
		cin.getline(gameType, 102);
	}
}
void cinValidCustomRow()
{
	char customRows[101];
	cout << "Give the height:";
	cin.getline(customRows, 102);
	cout << "nrofrows " << customRows << "\n";
	nrOfRows = validForCustom(customRows, 16);
}
void cinValidCustomColumn()
{
	char customColumns[101];
	cout << "Give the width:";
	cin.getline(customColumns, 102);
	cout << "nrocolumns " << customColumns << "\n";
	nrOfColumns = validForCustom(customColumns, 30);
}
void cinValidCustomMines()
{
	char customMines[101];
	cout << "Give the number of mines(maximum number=rows*columns)/4:" << "\n";
	cin.getline(customMines, 102);
	cout << "nrofmines " << customMines << "\n";
	nrOfMines = validForCustom(customMines, nrOfColumns*nrOfRows / 4);
}
void customGame()
{
	difficulty = 4;
	startTime();
	nrOfRows = -1;
	while (nrOfRows == -1)
		cinValidCustomRow();
	nrOfColumns = -1;
	while (nrOfColumns == -1)
		cinValidCustomColumn();
	setNrOfHints();
	
	nrOfMines = -1;
	while (nrOfMines == -1)
		cinValidCustomMines();
	minesLeft = nrOfMines;
	reset(nrOfRows, nrOfColumns);
	hiddenMatrix(nrOfRows, nrOfColumns, nrOfMines);
}
void newGame()
{
	nrOfPlayedGames++;
	cout << "   Choose the dificulty:";
	cout << "\n";
	cout <<"1. Beginner (height:9   width:9   mines:10)" << "\n" << "2. Intermediate (height:16   width:16   mines:40)" << "\n" << "3. Expert (height:16   width:30   mines:99)"<<"\n"<<"4. Custom(max characteristics-expert)"<<"\n"<<"\n";
	cout << "Your answer:" << "\n";
	if (finishedPrevGame > 0)
	{
		cin.get();
		finishedPrevGame = 0;
	}
	cin.getline(gameType, 102);
	validGameType();
	if (gameType[0] == '1')
	{
			startTime();
			easy();
	}
	else if (gameType[0] == '2')
		{
			startTime();
			medium();
		}
	else if (gameType[0] == '3')
		{
			startTime();
			hard();
		}
	else
	{
		customGame();
	}
	//pt toate
	initialMatrix();
	nextMove();
}

int replay()
{
	char option;
	cout << "1) Replay 2) Quit" << endl;
	cin >> option;
	switch (option)
	{
		case '1':
			nrOfMoves = 0;
			system("cls");
			newGame();
			return 1;
			//break;
		case '2':
			return 0;
			//break;
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

