#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

int main()
{
    std::vector<double> v(10000);
    std::generate(v.begin(),  v.end(), []() { static double n{0.0}; return n ++;} );
    
    double start = omp_get_wtime();
    
    // #pragma omp parallel
    for (auto& el :  v) 
    {
        double t = el - 1.0;
        #pragma omp parallel for
        for (size_t i = 0; i < v.size(); i ++)
        {
            el += v[i];
            el-= t;
        }
    }
    double end = omp_get_wtime();
     
    std::cout << omp_get_num_threads() << "   wall time : " << end - start << std::endl;
    for (const auto& el :  v) { std::cout << el << ";"; }
        
}

