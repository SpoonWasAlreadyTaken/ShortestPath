#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>
#include <string>

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
	cin >> sizeX;
	cout << "Type in height of the grid: \n";
	cin >> sizeY;

	for (int i = 0; i < sizeX; i++)
	{
		grid.push_back({});
		costGrid.push_back({});
		for (int j = 0; j < sizeY; j++)
		{
			grid.at(i).push_back('#');
			costGrid.at(i).push_back(RandomNumber(0, 3));
		}
	}

	while (true)
	{
		int input;

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
			cout << "posX: " << cPos.at(i).at(0) << " posY: " << cPos.at(i).at(1) << "\n";
		}
		

		for (int i = 0; i < cPos.size(); i++)
		{
			grid.at(cPos.at(i).at(0)).at(cPos.at(i).at(1)) = '+';
		}

		for (int i = 0; i < cPos.size(); i++)
		{
			bool right;
			bool moveX = false;
			bool moveY = false;
			bool up;

			if (cPos.at(i).at(0) != GetX(endPosition))
			{
				if (cPos.at(i).at(0) < GetX(endPosition))
				{
					right = true;
				}
				else
				{
					right = false;
				}
			}

			if (cPos.at(i).at(1) != GetY(endPosition))
			{
				if (cPos.at(i).at(1) < GetY(endPosition))
				{
					up = true;
				}
				else
				{
					up = false;
				}
			}

			if (up && right)
			{
				if (costGrid.at(cPos.at(i).at(0)).at(cPos.at(i).at(1) + 1) > costGrid.at(cPos.at(i).at(1)).at(cPos.at(i).at(0) + 1))
				{

				}
				else
			}
			else if (up && !right)
			{

			}
			else if (!up && right)
			{

			}
			else if (!up && !right)
			{

			}


			if (moveX)
			{
				if (right)
				{
					cPos.at(i).at(0)++;
				}
				else
				{
					cPos.at(i).at(0)--;
				}
			}
			
			if (moveY)
			{
				if (up)
				{
					cPos.at(i).at(1)++;
				}
				else
				{
					cPos.at(i).at(1)--;
				}
			}
		}

		reachedEnd = true;
		for (int i = 0; i < cPos.size(); i++)
		{
			if (cPos.at(i).at(0) != GetX(endPosition) && cPos.at(i).at(1) != GetY(endPosition))
			{
				reachedEnd = false;
				break;
			}
		}
	}

	for (int i = 0; i < cPos.size(); i++)
	{
		grid.at(cPos.at(i).at(0)).at(cPos.at(i).at(1)) = '+';
	}

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			output += grid.at(i).at(j);
			output += " ";
		}
		output += "\n";
	}

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