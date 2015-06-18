#include <stdio.h>
#include <stdlib.h>
#define DEBUG 1

void allocate (int ***mat,int n,int m){
    int i;
    *mat = (int **) malloc (n*sizeof(int*));
    for (i=0; i<n; i++){
        (*mat)[i] = (int *) malloc (m*sizeof(int));
    }
    #if DEBUG
        printf ("allocate n: %d m: %d\n",n,m);
    #endif // DEBUG
}

void initialize (int **mat, int n, int m){
    int i,j;
    #if DEBUG
        printf ("initialize n: %d m: %d\n",n,m);
    #endif // DEBUG
    for (i=0; i<n; i++){
        for (j=0; j<m; j++){
            printf ("Enter value for position [%d][%d]: ",i,j);
            scanf ("%d",&(mat[i][j]));
        }
    }
}

int main()
{
        int n=2;
        int m=3;
        int **mat=NULL;
        #if DEBUG
            printf ("before allocate n: %d m: %d\n",n,m);
        #endif // DEBUG
        allocate (&mat,n,m);
         #if DEBUG
            printf ("after allocate n: %d m: %d\n",n,m);
        #endif // DEBUG
        initialize (mat,n,m);
        return 0;
}