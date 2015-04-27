#include <iostream>
#include <string>
#include <vector>
using namespace std;
int check(int a[], int b[], int a_size, int b_size)
{
    int foundSwitch = 0;
    for (int i = 0; i < a_size; i++)
    {
        for (int j = 0; j < b_size; j++)
        {
            if (a[i] == b[j])
            {
                cout << a[i] << " vs " << b[j] << endl;
                foundSwitch = 1;
            }
        }
        if (!foundSwitch) return 0;
        else continue;
    }
    return 1;
}

int main()
{
    int a[] = {1, 2, 1};
    int b[] = {1, 2, 1};
    int a_size = (sizeof(a)/sizeof(a[0]));
    int b_size = (sizeof(b)/sizeof(b[0]));
    cout << check(a,b,a_size,b_size);
    return 0;
}
