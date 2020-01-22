#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string>

using namespace std;

const char path1[] = "input1.txt";
const char path2[] = "input2.txt";
const char path3[] = "output.txt";

string read1(const char path[])
{
	ifstream fin(path);
	string s;
	getline(fin, s);
	for (auto& x : s)
	{
		if (isalpha(x) && isupper(x))
			x = tolower(x);
	}
	return s;
}
string getCode(const char path[], string& word)
{
	ifstream fin(path2);
	string tempn = "", line;
	while (getline(fin, line))
	{
		for (auto lineSymbol : line)
		{
			for (int i = 0; i < word.length(); i++)
			{
				if (lineSymbol == word[i] || (isalpha(lineSymbol) && isupper(lineSymbol) && tolower(lineSymbol) == word[i]))
				{
					tempn += to_string(i);
					break;
				}
			}
		}
	}
	return tempn;
}
void print(const char path[], string& word)
{
	ofstream fout(path);
	fout << word << endl;
	fout.close();
}

int main()
{
	string word, secretCode;
	word = read1(path1);
	secretCode = getCode(path2, word);
	print(path3, secretCode);
}