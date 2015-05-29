#include <boost/coroutine/symmetric_coroutine.hpp>
#include <vector>
#include <iostream>


using boost::coroutines::symmetric_coroutine;


// merge sorted arrays
std::vector<int> merge(const std::vector<int>& a, const std::vector<int>& b)
{
    std::vector<int> result;
    
    std::size_t i1 = 0; // loop index used for vector a
    std::size_t i2 = 0; // loop index used for vector b
    
    symmetric_coroutine<void>::call_type* other_a = nullptr;
    symmetric_coroutine<void>::call_type* other_b = nullptr;

    // Coroutine a has its own stack.
    symmetric_coroutine<void>::call_type coro_a([&](symmetric_coroutine<void>::yield_type& yield)
    {
        while (i1 < a.size())
        {
            // test if element in b is less than in a
            if (b[i2] < a[i1])   
            {
                // yield to coro_b (jump stack)
                yield(*other_b);     
            }
            result.push_back(a[i1++]); // add element to final array
        }
        
        // add remaining elements of array b
        while (i2 < b.size())
        {
            result.push_back(b[i2++]);
        }
    });

    // Coroutine b has its own stack.
    symmetric_coroutine<void>::call_type coro_b([&](symmetric_coroutine<void>::yield_type& yield)
    {
        while (i2 < b.size())
        {
            // test if element in a is less than in b
            if (a[i1] < b[i2])   
            {
                // yield to coro_a (jump stack)
                yield(*other_a);
            }
            // add element to final array
            result.push_back(b[i2++]); 
        }
        
        // add remaining elements of array a
        while (i1 < a.size())
        {
            result.push_back(a[i1++]);
        }
    });

    other_a = &coro_a;
    other_b = &coro_b;

    // enter coroutine of coro_a
    coro_a(); 

    return result;
}


int main()
{
    // a and b are already sorted
    std::vector<int> a = { 29, 33, 45, 70, 81, 85, 86, 89, 95, 97 }; 
    std::vector<int> b = { 18, 26, 36, 40, 57, 63, 68, 81, 87, 93 };
    
    for (auto& i : merge(a, b))
    {
        std::cout << i << ' ';
    }
}
