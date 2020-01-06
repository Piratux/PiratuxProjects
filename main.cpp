#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void Read(int& x, int& y, vector<vector<char>>& map)
{
	char c; //used to read map
	vector<char> temp; //temp vector to help read 2D vector
	ifstream fin("input.txt");

	fin >> x >> y; //read the size of map

	for (int i = 0; i < y; i++) //read entire map
	{
		for (int j = 0; j < x; j++)
		{
			fin >> c;
			temp.push_back(c);
		}
		map.push_back(temp);
		temp.clear();
	}
}

void getPath(int xx, int yy, string& path, const int x, const int y, vector<vector<char>> map, vector<string>& paths)
{
	path += map[yy][xx]; //add current coordinates to the path

	if (xx != x-1) //if possible, go right
		getPath(xx + 1, yy, path, x, y, map, paths);

	if (yy != y-1) //if possible, go down
		getPath(xx, yy + 1, path, x, y, map, paths);

	if (xx == x-1 && yy == y-1) //reset path if impossible to go down and right
	{
		paths.push_back(path); //store all the paths in vector
		path = "";
		return;
	}
}

void Paths(int& x, int& y, vector<vector<char>>& map, vector<string>& paths)
{
	int xx = 0, yy = 0; //used to store coordinates
	string path = ""; //used to store path
	getPath(xx, yy, path, x, y, map, paths); //get all possible paths
}

void fixPaths(vector<string>& paths)
{
	int temp; //used as a const so loop works properly

	for (int i = 1; i < paths.size(); i++) //loop through paths that have to be fixed
	{
		for (int j = i - 1; j >= 0; j--) //loop through all previous paths
		{
			if (paths[i].size() < paths[j].size()) //if previous paths are longer than current one, fix it
			{
				temp = paths[j].size() - paths[i].size();

				for (int h = temp - 1; h >= 0; h--)
				{
					paths[i].insert(paths[i].begin() + 0, paths[j][h]);
				}
			}
		}
	}
}

int Count(vector<string> paths)
{
	int max = 0, tempMax;

	for (int i = 0; i < paths.size(); i++)
	{
		tempMax = 0;
		for (auto x : paths[i])
		{
			if (x == 'x')
				break;
			if (x == 'o')
				tempMax++;
		}
		if (tempMax > max)
			max = tempMax;
	}
	return max;
}

int main()
{
	vector<vector<char>> map; //used to store entire map
	vector<string> paths; //used to store all the possible paths in map
	int x, y; //size of map

	Read(x, y, map); //read input
	Paths(x, y, map, paths); //link to connecting function
	fixPaths(paths); //connect the beginning of path to all possible paths
	cout << Count(paths); //print the maximum amount of coins that is possible to get through every path
	return 0;
}