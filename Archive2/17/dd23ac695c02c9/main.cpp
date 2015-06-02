#include <iostream>
#include <string>
#include <vector>

void arrayadd(int A[5],int B[5], int R[5]){
    for(int i=0;i<5;i++){
        R[i]=A[i]+B[i];
    }
}

int main()
{
    int A[5] = {1,2,3,4,5};
    int B[5] = {3,4,5,4,3};
    int R[5];
    arrayadd(A, B, R);
    printf("%d , %d, %d, %d, %d \n", R[0], R[1], R[2], R[3], R[4]);
}
