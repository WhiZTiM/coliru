#include<iostream>
using namespace std;

int main()
{
    int board[8][7] = {0};

for (int i = 0; i < 9; i++)
{
    for (int j = 0; j < 8; j++) 
    {       
        cout << board[i][j] << " ";
    }
cout << endl;
}  
}