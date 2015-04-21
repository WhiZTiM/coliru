#include <iostream>
using namespace std;
class GuessMe {
private:   
    int *p;
public:
    GuessMe(int x=0) 
    {
        p = new int;
    }
    int GetX() 
    {
        return *p;
    }
    void SetX(int x) 
     {
        *p = x;
     }
    ~GuessMe() 
     {
        delete p;
     }
};

 int main() {
    GuessMe g1;
    g1.SetX(10);
    GuessMe g2(g1);
    cout << g2.GetX() << endl;
    return 0;
}