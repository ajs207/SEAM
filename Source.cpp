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
			E[i][j]=0;
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
//DelV(0,colum#,ENERGY,PIC);
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
	
}
//DelH(row#,0,ENERGY,PIC);
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

	int i = x;
	if (x != en.size())
	{
		for (i; i < en.size() - 1; ++i)
			{
				en[i][y] = en[i+1][y];
				pic[i][y] = pic[i+1][y];
			}
	}
	if(y==0)
	{
		en.resize(en.size()-1);
		pic.resize(pic.size()-1);
	}
	
	
	

}


int main(int argc, char* argv[])
{
	int size = 10;
	int H;
	int V=H=size;

	
	fstream input;

	srand(185);
	
	
		input.open(argv[1]);
		string b;
		

		getline(input,b);
		getline(input,b);
		
		
		input >> H;
		input >>V;
		
		vector<vector<int>> PIC(V, vector<int>(H));
		vector<vector<int>> ENERGY(V, vector<int>(H));
		vector<int>HSEAML(H);
		vector<int>VSEAML(V);
		
		
		getline(input,b);
		getline(input,b);

		
		for(int i=0; i<V;++i)
		{
			for(int j=0;j<H;++j)
				input>>PIC[i][j];
		}
		
	
	
	
	//fill vector for random test!!!
		if(argc!=4 && argc!=2)
		{
		for (int i = 0; i < ENERGY.size(); i++)
		{
			for (int j = 0; j < ENERGY[0].size(); j++)
			{
				PIC[i][j] = rand() % 255;
			}
		}
		}
	
	
	
	
	if(argc==4)
	{
		int VS=atoi(argv[2]);
		int HS=atoi(argv[3]);
		cout<<"Remove "<<VS<<" vertical seams"<<endl;
		cout<<"Remove "<<HS<<" horizontal seams"<<endl;
		int VP;
		int HP=VP=0;
		
		for(int r=0; r<VS;++r)
		{
			cout<<r<<endl;
			
				Energy(PIC, ENERGY);

				for(int i=0;i<ENERGY[0].size();++i)
					{cout<< i<<" ";
						if(CuMinV(0,i,ENERGY)<=CuMinV(0,VP,ENERGY))
						VP=i;			
					}	cout<<endl;
			DelV(0,VP,ENERGY,PIC);
		}
			
	}
	
	
	//test  delete
/*for(int i=0; i<3;++i)
	
	{
		DelH(0,0,ENERGY,PIC);
		Energy(PIC,ENERGY);

	//output after deletion
	for (int i = 0; i < ENERGY.size(); i++)
	{
		for (int j = 0; j < ENERGY[0].size(); j++)
		{
			cout << ENERGY[i][j] << "	";
		}cout << endl;

	}cout << endl;
	}*/


if(argc==2 || argc==4)
{
ofstream output;
string filename=argv[1];
output.open(filename + "_processed.pgm");
output<<"P2"<<endl;
output<<"#processed_"<<argv[1]<<endl;
output<<ENERGY[0].size()<<" "<<ENERGY.size()<<endl;
output<<255<<endl;
for (int i = 0; i < PIC.size(); i++)
	{
		for (int j = 0; j < PIC[0].size(); j++)
		{
			output<<PIC[i][j] <<" ";
		}output<< endl;

	}output<< endl;
output.close();
}
if(input.is_open())
	input.close();

}
