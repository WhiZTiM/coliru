
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <cassert>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;

typedef short bit12;

constexpr short pvals = 4096;

struct Img
{
    size_t w,h;
    vector<bit12> data;
    bit12& operator()( size_t x, size_t y ) { return data[ y*w + x ]; }
};

std::default_random_engine gen;

void MakeRandom( Img& img, size_t w, size_t h )
{
    std::uniform_int_distribution<int> dist(0,(1<<12)-1);
    
    img.w = w;
    img.h = h;
    size_t i,n=w*h;
    img.data.resize(n);
    for(i=0;i<n;++i)
        img.data[i] = dist(gen);
}



int main()
{
    const int WW = 3840;
    const int HH = 2748;
    // 3840x2748
 
    gen.seed(high_resolution_clock::now().time_since_epoch().count());
   
    Img img;
    MakeRandom( img, WW, HH );
    
    
    auto t1 = high_resolution_clock::now();
    
    size_t buckets[pvals] = {0};
    
    size_t i,n = WW*HH;
    
    for(i=0;i<n;++i)
    {
        auto pix = img.data[i];
        buckets[pix] += 1;
    }
    
    size_t x = 0;
    for(i=0;i<pvals;++i)
    {
        x += buckets[i];
        if( x > (n/2) ) break;
    }
    
    auto t2 = high_resolution_clock::now();
    
    auto time_span = duration_cast<duration<double>>(t2 - t1);

    
    cout << "median value is " << i << endl;
    cout << "and it took " << time_span.count() << " s. " << endl;


    cout << "\ndone\n";
}

