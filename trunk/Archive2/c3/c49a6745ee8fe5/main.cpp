#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

int main()
{
    std::vector<double> v(3);
    std::generate(v.begin(),  v.end(), []() { static double n{0.0}; return n ++;} );
    
    int counter = 0;
    int numOfThreadsUsed = 0;
    
    #pragma omp parallel shared(counter)
    {
        for (auto& el :  v) 
        {
            counter++;
            printf("outer loop, thread no. %d, \n", omp_get_thread_num());
            
            double t = el - 1.0;
            #pragma omp for
            for (size_t i = 0; i < v.size(); i ++)
            {
                el += v[i];
                el-= t;
            }
        }
        
        numOfThreadsUsed = omp_get_num_threads();
    }
    
    
    printf("outer loop has been executed %d times (once for each thread)\n", numOfThreadsUsed);
    printf("this can be seen by checking the counter. if only executed once it should be the same size as the vector (%lu). but it really is %d\n", v.size(), counter);
        
}

