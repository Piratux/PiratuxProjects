//This code is for Plates challenge from Kick Start competition
//https://codingcompetitions.withgoogle.com/kickstart/round/000000000019ffc7/00000000001d40bb
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;

ifstream fin("input.txt");
int n, k, p; //total stacks, plates in 1 stack, plates that need to be taken
int maxValue;

vector<vector<int>> v;
unordered_map<string, int> m;

void read()
{
	vector<int> tempv(k);
	fin >> tempv[0];
	for (int j = 1; j < k; j++)
	{
		fin >> tempv[j];
		tempv[j] += tempv[j - 1];
	}
	v.push_back(tempv);
}

void plate(int stack, int plates) //current stack, subproblem plates 
{
	if (stack == 0)
	{
		maxValue = v[0][plates - 1];
		return;
	}
	if (plates <= k)
	{
		maxValue = max(v[stack][plates - 1], m[to_string(stack) + to_string(plates)]);
		for (int i = 1; i < plates; i++)
		{
			maxValue = max(maxValue, v[stack][plates - i - 1] + m[to_string(stack) + to_string(i)]);
		}
	}
	else
	{
		int temp; //used to calculate in how many ways subproblem can be solved
		if (stack * k >= plates)
		{
			maxValue = m[to_string(stack) + to_string(plates)];
			temp = k;
		}
		else
		{
			temp = (plates % k == 0) ? 1 : (k + 1 - plates % k);
		}	
		for (int i = 0; i < temp; i++)
		{
			maxValue = max(maxValue, v[stack][k - temp + i] + m[to_string(stack) + to_string(plates - (k - temp + i + 1))]);
		}
	}
}

int main()
{
	int t; //test cases
	fin >> t;
	v.reserve(50);
	for(int i = 1; i <= t; i++)
	{
		fin >> n >> k >> p;
		v.clear();
		m.clear();
		for (int j = 1; j < n; j++) //read stack one by one
		{
			read();
			for (int h = 1; h <= (p > j * k ? j * k : p); h++) //loop through all possible subproblems
			{
				maxValue = 0;
				plate(j-1, h);
				m[to_string(j) + to_string(h)] = maxValue; //store maxValue, to use it later
			}
		}
		read();
		maxValue = 0;
		plate(n - 1, p);
		cout << "Case #" << i << ": " << maxValue << '\n';
	}
}
