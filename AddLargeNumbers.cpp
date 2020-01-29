//Code to add large numbers
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

template <typename T>
void swap(T& first, T& second)
{
	T temps;
	temps = first;
	first = second;
	second = temps;
}
void read(vector<string>& number)
{
	int t, s;
	string n;
	ifstream fin("input.txt");
	fin >> t; //number of loops(or number of numbers to add)
	for (int i = 0; i < t; i++)
	{
		fin >> s; //number length(optional)
		getline(fin, n); //the whole number
		number.push_back(n.substr(1));
	}
}
string add(vector<string>& number)
{
	string answer = number[0]; //string that stores final answer
	for (int i = 1; i < number.size(); i++) //loop through every number that needs to be added
	{
		if (answer.size() < number[i].size()) //if number length, that is going to be added, is bigger - swap
		{
			swap(answer, number[i]);
		}
		for (int j = number[i].size() - 1; j >= 0; j--) //loop through the number that is in string from back
		{
			int temp = (answer.size() - 1) - (number[i].size() - (j + 1));
			if ((answer[temp] - '0') + (number[i][j] - '0') < 10) //if sum of 2 numbers is smaller than 10 add them normally
			{
				answer[temp] = (answer[temp] - '0') + (number[i][j] - '0') + '0';
			}
			else
			{
				answer[temp] = ((answer[temp] - '0') + (number[i][j] - '0') + '0') - 10;
				for (int k = temp - 1; k >= -1; k--) //loop through numbers to check whether they are 9 
				{
					if (k == -1) //if adding numbers, length of answer increases - add 1 at front
					{
						answer = "1" + answer;
					}
					else if ((answer[k] - '0') == 9) //if number is 9 turn to 0
					{
						answer[k] = '0';
					}
					else //add number 1
					{
						answer[k] = (answer[k] - '0' + 1) + '0'; 
						break;
					}
				}	
			}
		}
	}
	return answer;
}
int main()
{
	vector<string> number;
	read(number);
	cout << add(number);
}