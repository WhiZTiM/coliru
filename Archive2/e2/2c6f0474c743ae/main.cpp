#include <iostream>
using namespace std;
const int rows = 2;
const int cols = 2;

int display(const int ray[0][cols]){

for(int i = 0; i < 2; i ++){
    for(int j = 0; j < 2; j ++){

    cout << ray[i][j] << endl;

    }
}
}

int main()
{

int ray[rows][cols] = {{1,2 },
                       {3,4}};

display(ray);

return 0;
}

