//This code works with input that looks like this:
//6
//1 5
//3 7
//7 6
//8 2

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Elevator {
	int per; //person
	int dest; //destination
};

void read(int& sFloor, vector<Elevator>& Elevator, vector<int>& testArr);
void print(int sFloor, vector<Elevator> Elevator, vector<vector<int>> permedArr, int lFloor, int sComb);
void elevate(int sFloor, vector<vector<int>> permedArr, vector<Elevator> Elevator, int& lFloor, int& sComb);
vector<vector<int>> permutations(vector<int> arr);

int main()
{
	int sFloor; //starting floor
	int lFloor; //lowest elevator moves
	int sComb; //index of shortest permutation
	vector<Elevator> Elevator; //vector of elevating data
	vector<int> testArr; //array that helps getting all permutations
	vector<vector<int>> permedArr; //2D vector array that stores all permutations

	read(sFloor, Elevator, testArr);

	permedArr = permutations(testArr);

	elevate(sFloor, permedArr, Elevator, lFloor, sComb);

	print(sFloor, Elevator, permedArr, lFloor, sComb);
}
void read(int& sFloor, vector<Elevator>& Elevator, vector<int>& testArr)
{
	int p, d, n = 0;
	ifstream fin("input.txt");
	fin >> sFloor;
	while (fin >> p, fin >> d)
	{
		Elevator.push_back({ p, d });
		testArr.push_back(n);
		n++;
	}
}
vector<vector<int>> permutations(vector<int> arr)
{
	if (arr.size() == 1)
	{
		vector<vector<int>> trivialArr;
		trivialArr.push_back(arr);
		return trivialArr;
	}
	else
	{
		vector<vector<int>> allPerms;
		for (unsigned int i = 0; i < arr.size(); i++)
		{
			vector<int> copyArr = arr;
			copyArr.erase(copyArr.begin() + i);
			vector<vector<int>> permed = permutations(copyArr);
			for (vector<int> perm : permed)
			{
				perm.push_back(arr[i]);
				allPerms.push_back(perm);
			}
		}
		return allPerms;
	}
}
void elevate(int sFloor, vector<vector<int>> permedArr, vector<Elevator> Elevator, int& lFloor, int& sComb)
{
	int f; //floors travelled
	int cf; //current floor
	int ti; //temp index
	for (unsigned int i = 0; i < permedArr.size(); i++)
	{
		f = 0;
		cf = sFloor;
		for (unsigned int j = 0; j < permedArr[i].size(); j++)
		{
			ti = permedArr[i][j];
			f += abs(Elevator[ti].per - cf) + abs(Elevator[ti].per - Elevator[ti].dest);
			cf = Elevator[ti].dest;
		}
		if (i == 0)
		{
			lFloor = f;
			sComb = i;
		}	
		else if (lFloor > f)
		{
			lFloor = f;
			sComb = i;
		}
	}
}
void print(int sFloor, vector<Elevator> Elevator, vector<vector<int>> permedArr, int lFloor, int sComb)
{
	cout << "Starting floor: " << sFloor << endl;
	for (unsigned int i = 0; i < Elevator.size(); i++)
	{
		cout << "[" << Elevator[i].per << ", " << Elevator[i].dest << "] ";
	}
	cout << endl << endl;
	cout << "Fastest path:" << endl;
	for (unsigned int i = 0; i < Elevator.size(); i++)
	{
		int ti = permedArr[sComb][i];
		cout << "[" << Elevator[ti].per << ", " << Elevator[ti].dest << "] ";
	}
	cout << endl << "Quickest route is: " << lFloor << endl;
}