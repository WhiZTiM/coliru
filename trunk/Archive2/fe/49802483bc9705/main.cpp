#include <iostream>
#include <vector>

using namespace std;

int cryptString()
{
    cout << "Vous avez choisis la modification via la Console." << endl;
    cout << "===========================================================================" << endl;
    cout << "Entrez la phrase à modifier " << endl;
  
    string persString;
  
    getline(cin, persString); //je met la première ligne qui arrive de std::cin dans persString
    cout << "La phrase fait: " << persString.size() << endl;
    
    return 0;
}

int main(){
  //je n'ai pas de clavier sur coliru donc je simule la saisie.
  std::string s{ "les chassettes du nain sont trops biens\n" };
  
  for(auto it = s.rbegin(); it != s.rend(); ++it)
    std::cin.putback(*it);
    
  cryptString();
}