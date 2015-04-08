#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <random>

using namespace std;



void Energy(const vector<vector<int>>& pic, vector<vector<int>>& E)
{
	
	
	for (int i = 0; i < pic.size(); ++i)
	{
		
		for (int j = 0; j < pic[0].size(); ++j)
		{
			
			if (i == 0)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i + 1][j]);
			if (j == 0)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i][j + 1]);
			if (i == pic.size()-1)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i - 1][j]);
			if (j == pic[1].size()-1)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i][j - 1]);
			if (i != 0 && i != pic.size() - 1 && j != 0 && j != pic[1].size() - 1)
				E[i][j] = abs(pic[i][j] - pic[i - 1][j]) + abs(pic[i][j] - pic[i + 1][j]) + abs(pic[i][j] - pic[i][j - 1]) + abs(pic[i][j] - pic[i][j + 1]);
		
		}
	}
	
}

double CuMinH(int x, int y, vector<vector<int>>& EN)
{
	double total = 0;

	if (y != EN[0].size() - 1)
	{
		
		if (x == 0)
		{
			total = EN[x][y] + min(CuMinH(x, y + 1, EN), CuMinH(x + 1, y + 1, EN));
		}
		else if (x == EN.size()-1)
		{
			total = EN[x][y] + min(CuMinH(x - 1, y + 1, EN), CuMinH(x, y + 1, EN));
		}
		else
		{
			total = EN[x][y] + min(min(CuMinH(x - 1, y + 1, EN), CuMinH(x, y + 1, EN)), CuMinH(x + 1, y + 1, EN));
		}
	}
	else if (y == EN[0].size()-1)
		total = EN[x][y];

	//cout << total << endl;
	return total;
}

double CuMinV(int x, int y, vector<vector<int>>& EN)
{
	double total = 0;

	

	if (x != EN.size() - 1)
	{

		if (y == 0)
		{
			total = EN[x][y] + min(CuMinV(x+1,y, EN), CuMinV(x + 1, y + 1, EN));
		}
		else if (y == EN[0].size() - 1)
		{
			total = EN[x][y] + min(CuMinV(x + 1,y - 1, EN), CuMinV(x + 1, y, EN));
		}
		else
		{
			total = EN[x][y] + min(min(CuMinV(x + 1, y - 1, EN), CuMinV(x + 1, y, EN)), CuMinV(x + 1, y + 1, EN));
		}
	}
	else if (x == EN.size() - 1)
		total = EN[x][y];

	//cout << total << endl;
	return total;
}
void DelV(int x, int y, vector<vector<int>>& en, vector<vector<int>>& pic)
{

	if (x != en.size() - 1)
	{

		if (y == 0)
		{
			if (en[x+1][y] < en[x + 1][y + 1])
				DelV(x+1, y , en, pic);
			else
				DelV(x + 1, y + 1, en, pic);
			
		}
		else if (y == en[0].size() - 1)
		{
			if (en[x+1][y ] < en[x + 1][y - 1])
				DelV(x+1, y, en, pic);
			else
				DelV(x + 1, y - 1, en, pic);

		}
		else
		{
			if (en[x + 1][y - 1] < en[x+1][y] && en[x + 1][y - 1] < en[x + 1][y + 1])
				DelV(x + 1, y - 1, en, pic);
			else if (en[x+1][y] < en[x + 1][y + 1])
				DelV(x+1, y , en, pic);
			else
				DelV(x + 1, y + 1, en, pic);
			
		}
	}

		pic[x].erase(pic[x].begin() + y);
		en[x].erase(en[x].begin() + y);
		//en[x][y] = -1;
}
void DelH(int x, int y, vector<vector<int>>& en, vector<vector<int>>& pic)
{
	if (y != en[0].size() - 1)
	{

		if (x == 0)
		{
			if (en[x][y + 1] < en[x + 1][y + 1])
				DelH(x, y + 1, en, pic);
			else
				DelH(x + 1, y + 1, en, pic);
			
		}
		else if (x == en.size() - 1)
		{
			if (en[x][y + 1] < en[x - 1][y + 1])
				DelH(x, y + 1, en, pic);
			else
				DelH(x - 1, y + 1, en, pic);

		}
		else
		{
			if (en[x - 1][y + 1] < en[x][y + 1] && en[x - 1][y + 1] < en[x + 1][y + 1])
				DelH(x - 1, y + 1, en, pic);
			else if (en[x][y + 1] < en[x + 1][y + 1])
				DelH(x, y + 1, en, pic);
			else
				DelH(x + 1, y + 1, en, pic);
			
		}
	}

		//pic[x].erase(pic[x].begin() + y);
	
	//en[x].erase(en[x].begin() + y);
	int i = x;
	if (x != en.size())
	{
		for (i; i < en.size() - 1; ++i)
			en[i][y] = en[i+1][y];
	}
	//en[en.size() - 1].erase(en[en.size()].begin());
	
	en[x][y] = -1;
	

}


int main(int argc, char* argv[])
{
	int size = 7;
	int Hsize = 7;
	int Vsize = 12;
	vector<vector<int>> PIC(size, vector<int>(size));
	string name;
	string header;
	vector<vector<int>> ENERGY(size, vector<int>(size));
	vector<int>HSEAML(size);
	vector<int>VSEAML(size);
	srand(1024);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			PIC[i][j] = rand() % 10;
			ENERGY[i][j] = 0;
		}

	}

	
	Energy(PIC, ENERGY);
	for (int i = 0; i < ENERGY.size(); i++)
	{
		for (int j = 0; j < ENERGY.size(); j++)
		{
			cout << ENERGY[i][j] << "	";
		}cout << endl;

	}cout << endl;
	cout << "0V=" << CuMinV(0, 0, ENERGY) << endl;
	cout << "0H=" << CuMinH(0, 0, ENERGY) << endl;

DelV(0,4, ENERGY, PIC);

	for (int i = 0; i < ENERGY.size(); i++)
	{
		for (int j = 0; j < ENERGY[0].size(); j++)
		{
			cout << ENERGY[i][j] << "	";
		}cout << endl;

	}cout << endl;

}