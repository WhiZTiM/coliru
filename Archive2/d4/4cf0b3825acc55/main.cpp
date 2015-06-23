#include <fstream>

using namespace std;

int main()
{
    ofstream OrganismSave; 
    OrganismSave.open("OrganismM.dat"); 
    
    int OrganismM = 1; 
    OrganismSave << OrganismM;
}
