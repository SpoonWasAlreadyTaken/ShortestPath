#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>
#include <string>
#include <thread>
#include <windows.h>

using namespace std;

// global variables
vector<vector<char>> grid;
vector<vector<int>> costGrid;
int sizeX;
int sizeY;


// functions
int RandomNumber(int min, int max);
string ShortestPath(vector<int> startPositions, const int endPosition);
int GetX(int position);
int GetY(int position);


int main()
{
	vector<int> startIndex;
	int endIndex;
	cout << "Type in width of the grid: \n";
	cin >> sizeY;
	cout << "Type in height of the grid: \n";
	cin >> sizeX;

	for (int i = 0; i < sizeY; i++)
	{
		grid.push_back({});
		costGrid.push_back({});
		for (int j = 0; j < sizeX; j++)
		{
			grid.at(i).push_back('#');
			costGrid.at(i).push_back(RandomNumber(0, 9));
		}
	}

	while (true)
	{
		int input;
		cout << "Input number of start positions\n";
		int repeats;
		cin >> repeats;
		for (int i = 0; i < repeats; i++)
		{
			cout << "Input index of start position, type -1 for random\n";
			cin >> input;
			if (input > sizeX * sizeY - 1)
			{
				input = sizeX * sizeY - 1;
			}

			if (input < 0)
			{
				input = RandomNumber(0, sizeX * sizeY - 1);
			}
			startIndex.push_back(input);
		}

		cout << "Input index of end position, type -1 for random\n";
		cin >> endIndex;
		if (endIndex > sizeX * sizeY - 1)
		{
			endIndex = sizeX * sizeY - 1;
		}

		if (endIndex < 0)
		{
			endIndex = RandomNumber(0, sizeX * sizeY - 1);
		}

		cout << "target Position: " << GetX(endIndex) << ", " << GetY(endIndex) << "\n";

		cout << ShortestPath(startIndex, endIndex);

		cout << "\n" << "press anything to continue\n";
		cin;
	}
}


int RandomNumber(int min, int max) // generates a random number based on input parameters
{
	random_device rd;
	uniform_int_distribution<> distr(min, max);
	return distr(rd);
}

string ShortestPath(vector<int> startPositions, const int endPosition)
{
	string output;
	bool reachedEnd = false;
	vector<vector<int>> cPos;

	for (int i = 0; i < startPositions.size(); i++)
	{
		cPos.push_back({GetX(startPositions.at(i)), GetY(startPositions.at(i))});
	}


	while (!reachedEnd)
	{
		for (int i = 0; i < cPos.size(); i++)
		{
			grid.at(cPos.at(i).at(0)).at(cPos.at(i).at(1)) = '+';
		}

		for (int i = 0; i < cPos.size(); i++)
		{
			int moveX = 0;
			int moveY = 0;

			if (cPos.at(i).at(1) != GetX(endPosition))
			{
				if (cPos.at(i).at(1) < GetX(endPosition))
				{
					moveX = 1;
				}
				else
				{
					moveX = -1;
				}
			}
			if (cPos.at(i).at(0) != GetY(endPosition))
			{
				if (cPos.at(i).at(0) < GetY(endPosition))
				{
					moveY = 1;
				}
				else
				{
					moveY = -1;
				}
			}

			
			if (moveX != 0 && moveY != 0)
			{
				if (costGrid.at(cPos.at(i).at(0)).at(cPos.at(i).at(1) + moveX) == costGrid.at(cPos.at(i).at(1)).at(cPos.at(i).at(0) + moveY))
				{
					if (abs(GetX(endPosition) - cPos.at(i).at(0)) < abs(GetY(endPosition) - cPos.at(i).at(1)))
					{
						moveX = 0;
					}
					else
					{
						moveY = 0;
					}
				}
				else
				{
					if (costGrid.at(cPos.at(i).at(0)).at(cPos.at(i).at(1) + moveX) > costGrid.at(cPos.at(i).at(1)).at(cPos.at(i).at(0) + moveY))
					{
						moveX = 0;
					}
					else
					{
						moveY = 0;
					}
				}
			}
			
			cPos.at(i).at(1) += moveX;
			cPos.at(i).at(0) += moveY;
		}
		
		reachedEnd = true;
		for (int i = 0; i < cPos.size(); i++)
		{
			if (cPos.at(i).at(0) != GetY(endPosition) || cPos.at(i).at(1) != GetX(endPosition))
			{
				reachedEnd = false;
				break;
			}
		}
		
		output = "";

		for (int i = 0; i < sizeY; i++)
		{
			for (int j = 0; j < sizeX; j++)
			{
				output += grid.at(i).at(j);
				output += " ";
			}
			output += "\n";
		}
		system("CLS");
		cout << output;
		Sleep(50);
	}

	output = "";
	for (int i = 0; i < cPos.size(); i++)
	{
		grid.at(cPos.at(i).at(0)).at(cPos.at(i).at(1)) = '+';
	}

	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			output += grid.at(i).at(j);
			output += " ";
		}
		output += "\n";
	}
	system("CLS");
	return output;
}

int GetX(int position)
{
	int x = 0;

	while (position > sizeX - 1)
	{
		position -= sizeX;
	}

	x = position;

	return x;
}

int GetY(int position)
{
	int y = 0;

	while (position > sizeX - 1)
	{
		y++;
		position -= sizeX;
	}

	return y;
}