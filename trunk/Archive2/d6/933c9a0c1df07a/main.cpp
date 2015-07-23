#include <iostream>
#include <stdio.h>
using namespace std;
int i;

class neko
{
    private:
    int tuyosa;
    public:
    void set_tuyosa(int s){tuyosa = s;}
    void showdata();
}

int main()
{
   neko boss;
   boss.set_tuyosa(100);
   boss.showdata();
    return 0;
}


void neko::showdata()
{
    printf(tuyosa);
}