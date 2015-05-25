

#include <iostream>
#include <algorithm>
#include <vector>


void printVector (std::vector<std::string> v)   
{
    for (int i=0; i<v.size();++i)
	{
		if(i==v.size()-1)
		{
			std::cout << v[i] << std::endl;
		}
		else
		{
			std::cout << v[i] << ", ";
		}
	}
}

int main ()
{

std::vector<std::string> face = {"Kreuz ", "Pik ", "Herz ", "Karo "};
std::vector<std::string> value = {"7", "8", "9","10","Bube", "Dame", "Koenig", "Ass"};

std::vector<std::string> kartenspiel;

std::string karte = " ";

	for (int j =0; j<face.size();++j)
	{
			for (int i= 0; j<value.size();++i)
		{
			karte += face[j];
			karte += value[i];
			kartenspiel.push_back(karte);
			karte = " ";
		}
	}


printVector(kartenspiel);


}

