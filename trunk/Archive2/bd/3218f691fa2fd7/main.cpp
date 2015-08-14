#include <iostream>

const int VOIGTR5_[3][3] = {{0, 2, 4}, {2, 1, 3}, {4, 3, -VOIGTR5_[0][0] - VOIGTR5_[0][1]}};

int main() 
{
    for (int i=0; i< 3 ; i++)
    {
        for (int j=0; j< 3 ; j++)
            printf("%d\t", VOIGTR5_[i][j]);
        printf("\n");
    }

    return 0;
}
