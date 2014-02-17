#include <stdio.h>
#include <stdlib.h>
#define N1 5000
#define N2 5000
int main() {
    int imagen[N1][N2];
    int i, histo[10];
    for(i=0; i<N1*N2; i++) imagen[i/N2][i%N2]=rand()%10;
    for(i=0; i<10; i++) histo[i] = 0;
    #pragma omp parallel
    {
        int i, j, histogram_private[10];
        for(i=0; i<10; i++) histogram_private[i] = 0;
        #pragma omp for nowait
        for(i=0; i<N1; i++) {
           for(j=0; j<N2; j++) {    
               histogram_private[imagen[i][j]]++;
           }
        }      
        #pragma omp critical 
        {
            for(i=0; i<10; i++) histo[i] += histogram_private[i];
        }
    }
    for(i=0; i<10; i++) printf("%d\n", histo[i]);
    return 0;
}