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
			E[i][j] = 0;
			if (i == 0)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i + 1][j]);
			if (j == 0)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i][j + 1]);
			if (i == pic.size() - 1)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i - 1][j]);
			if (j == pic[1].size() - 1)
				E[i][j] = E[i][j] + abs(pic[i][j] - pic[i][j - 1]);
			if (i != 0 && i != pic.size() - 1 && j != 0 && j != pic[1].size() - 1)
				E[i][j] = abs(pic[i][j] - pic[i - 1][j]) + abs(pic[i][j] - pic[i + 1][j]) + abs(pic[i][j] - pic[i][j - 1]) + abs(pic[i][j] - pic[i][j + 1]);

		}
	}

}

double CuMinH(int x, int y, vector<vector<int>>& en)
{
	
	if (y != en[0].size() - 1)
	{

		if (x == 0)
		{
			if (en[x][y + 1] <= en[x + 1][y + 1])
				return en[x][y]+CuMinH(x, y + 1, en);
			else
				return en[x][y] + CuMinH(x + 1, y + 1, en);

		}
		else if (x == en.size() - 1)
		{
			if (en[x - 1][y + 1] <= en[x][y + 1])
				return en[x][y] + CuMinH(x - 1, y + 1, en);
			else
				return en[x][y] + CuMinH(x, y + 1, en);

		}
		else
		{
			if (en[x - 1][y + 1] <= en[x][y + 1] && en[x - 1][y + 1] <= en[x + 1][y + 1])
				return en[x][y] + CuMinH(x - 1, y + 1, en);
			else if (en[x][y + 1] <= en[x + 1][y + 1])
				return en[x][y] + CuMinH(x, y + 1, en);
			else
				return en[x][y] + CuMinH(x + 1, y + 1, en);

		}
	}
	return en[x][y];
}

double CuMinV(int x, int y, vector<vector<int>>& en)
{
	

	if (x != en.size() - 1)
	{

		if (y == 0)
		{
			if (en[x + 1][y] <= en[x + 1][y + 1])
				return en[x][y] +CuMinV(x + 1, y, en);
			else
				return en[x][y] + CuMinV(x + 1, y + 1, en);

		}
		else if (y == en[0].size() - 1)
		{
			if (en[x + 1][y - 1] <= en[x + 1][y])
				return en[x][y] + CuMinV(x + 1, y - 1, en);
			else
				return en[x][y] + CuMinV(x + 1, y, en);

		}
		else
		{
			if (en[x + 1][y - 1] <= en[x + 1][y] && en[x + 1][y - 1] <= en[x + 1][y + 1])
				return en[x][y] + CuMinV(x + 1, y - 1, en);
			else if (en[x + 1][y] <= en[x + 1][y + 1])
				return en[x][y] + CuMinV(x + 1, y, en);
			else
				return en[x][y] + CuMinV(x + 1, y + 1, en);

		}
	}

	return en[x][y];
}
//DelV(0,colum#,ENERGY,PIC);
void DelV(int x, int y, vector<vector<int>>& en, vector<vector<int>>& pic)
{

	if (x != en.size() - 1)
	{

		if (y == 0)
		{
			if (en[x + 1][y] <= en[x + 1][y + 1])
				DelV(x + 1, y, en, pic);
			else
				DelV(x + 1, y + 1, en, pic);

		}
		else if (y == en[0].size() - 1)
		{
			if (en[x + 1][y - 1] <= en[x + 1][y])
				DelV(x + 1, y - 1, en, pic);
			else
				DelV(x + 1, y, en, pic);

		}
		else
		{
			if (en[x + 1][y - 1] <= en[x + 1][y] && en[x + 1][y - 1] <= en[x + 1][y + 1])
				DelV(x + 1, y - 1, en, pic);
			else if (en[x + 1][y] <= en[x + 1][y + 1])
				DelV(x + 1, y, en, pic);
			else
				DelV(x + 1, y + 1, en, pic);

		}
	}

	pic[x].erase(pic[x].begin() + y);
	en[x].erase(en[x].begin() + y);

}
//DelH(row#,0,ENERGY,PIC);
void DelH(int x, int y, vector<vector<int>>& en, vector<vector<int>>& pic)
{
	if (y != en[0].size() - 1)
	{

		if (x == 0)
		{
			if (en[x][y + 1] <= en[x + 1][y + 1])
				DelH(x, y + 1, en, pic);
			else
				DelH(x + 1, y + 1, en, pic);

		}
		else if (x == en.size() - 1)
		{
			if (en[x - 1][y + 1] <= en[x][y + 1])
				DelH(x - 1, y + 1, en, pic);
			else
				DelH(x, y + 1, en, pic);

		}
		else
		{
			if (en[x - 1][y + 1] <= en[x][y + 1] && en[x - 1][y + 1] <= en[x + 1][y + 1])
				DelH(x - 1, y + 1, en, pic);
			else if (en[x][y + 1] <= en[x + 1][y + 1])
				DelH(x, y + 1, en, pic);
			else
				DelH(x + 1, y + 1, en, pic);

		}
	}

	int i = x;
	if (x != en.size())
	{
		for (i; i < en.size() - 1; ++i)
		{
			en[i][y] = en[i + 1][y];
			pic[i][y] = pic[i + 1][y];
		}
	}
	if (y == 0)
	{
		en.resize(en.size() - 1);
		pic.resize(pic.size() - 1);
	}




}


int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "invald number of arguments" << endl;
			return 0;
	}
	int size = 10;
	int H;
	int V = H = size;


	fstream input;

	srand(185);


	input.open(argv[1]);
	string b;


	getline(input, b);
	getline(input, b);


	input >> H;
	input >> V;

	vector<vector<int>> PIC(V, vector<int>(H));
	vector<vector<int>> ENERGY(V, vector<int>(H));
	vector<int>HSEAML(V);
	vector<int>VSEAML(H);


	getline(input, b);
	getline(input, b);


	for (int i = 0; i<V; ++i)
	{
		for (int j = 0; j<H; ++j)
			input >> PIC[i][j];
	}

	

	
	
	Energy(PIC, ENERGY);
	
	

	if (argc == 4)
	{
		int VS = atoi(argv[2]);
		int HS = atoi(argv[3]);
		cout << "Remove " << VS << " vertical seams" << endl;
		cout << "Remove " << HS << " horizontal seams" << endl;
			
		int mins;
		//remove vertical
		for (int i = 0; i < VS; ++i)
		{
			mins = 0;
			
			for (int y = 0; y < ENERGY[0].size(); ++y)
			{
				VSEAML[y] = CuMinV(0, y, ENERGY);
				if (VSEAML[y] < CuMinH(0, mins, ENERGY))
					mins = y;
			}
			DelV(0, mins, ENERGY, PIC);
			VSEAML.erase(VSEAML.begin());
			
		}
		//remove horizontal
		for (int i = 0; i < HS; ++i)
		{
			mins = 0;
			for (int y = 0; y < ENERGY.size(); ++y)
			{
				HSEAML[y] = CuMinH(y, 0, ENERGY);
				if (HSEAML[y] < CuMinH(mins, 0, ENERGY))
					mins = y;
			}
			DelH(mins, 0, ENERGY, PIC);
			HSEAML.erase(HSEAML.begin());
			
		}
		

	}


	


	if (argc == 2 || argc == 4)
	{
		ofstream output;
		string filename = argv[1];
		int VS = atoi(argv[2]);
		int HS = atoi(argv[3]);
		
		output.open(filename + "_processed.pgm");
		output << "P2" << endl;
		output << "#processed_" << argv[1] << endl;
		output << ENERGY[0].size() << " " << ENERGY.size() << endl;
		output << 255 << endl;
		for (int i = 0; i < PIC.size(); i++)
		{
			for (int j = 0; j < PIC[0].size(); j++)
			{
				output << PIC[i][j] << " ";
			}output << endl;

		}output << endl;
		output.close();
	}
	if (input.is_open())
		input.close();

}
