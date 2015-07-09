#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

int main()
{
    std::vector<double> v(2);
    std::generate(v.begin(),  v.end(), []() { static double n{0.0}; return n ++;} );
    
    int counter = 0;
    int numOfThreadsUsed = 0;
    
    #pragma omp parallel shared(counter) num_threads(1)
    {
        for (auto& el :  v) 
        {
            printf("outer loop, thread no. %d, \n", omp_get_thread_num());
            counter++;
            
            double t = el - 1.0;
            #pragma omp parallel for num_threads(2)
            for (size_t i = 0; i < v.size(); i ++)
            {
                printf("inner loop, thread no. %d, \n", omp_get_thread_num());
                el += v[i];
                el-= t;
            }
        }
        
        numOfThreadsUsed = omp_get_num_threads();
    }
    
    
    printf("outer loop has been executed %d times (once for each thread)\n", numOfThreadsUsed);
    printf("this can be seen by checking the counter. if only executed once it should be the same size as the vector (%lu). but it really is %d\n", v.size(), counter);
        
}

