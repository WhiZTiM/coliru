#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

int main()
{
    const int itemRows = 1;
    const int weightColumns = 5;
    int outerCounter = 0;
    int innerCounter = 0;
    
    #pragma omp parallel shared(outerCounter, innerCounter)
    {
    	for(int i=0; i < itemRows; i++){
            outerCounter++;
            printf("outer: \ti=%d, \tthread=%d\n", i, omp_get_thread_num());
    
    		#pragma omp for
    		for(int c=0; c < weightColumns; c++){
                innerCounter++;
    			printf("inner: \ti=%d, \tthread=%d, \tc=%d \n", i, omp_get_thread_num(), c);
    		}
    	}
    }
     
    printf("outerCounter=%d | this equals number of threads -> outer loop got executed n times although itemRows==1\n", outerCounter);
    printf("innerCounter=%d | this equals weightColumns -> inner loop got executed only once, distributed among the threads\n", innerCounter);
}

