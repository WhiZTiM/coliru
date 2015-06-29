    #include <iostream>
    #include <chrono>
 
    using std::chrono::duration_cast;
    using std::chrono::nanoseconds;
    using std::chrono::high_resolution_clock;
    
    int main( int argc, char *argv[] )
    {
        high_resolution_clock::time_point start = high_resolution_clock::now();
        high_resolution_clock::time_point end = high_resolution_clock::now();

        std::cout << duration_cast<nanoseconds>(end - start).count() << " nsec.\n";

        return 0;
    }