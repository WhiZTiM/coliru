#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

#include <random>

std::mt19937& getRandomGenerator()
{
    static std::mt19937 algo;

    static bool initialise = true;
    if (initialise) {
        initialise = false;
        std::random_device rd;
        algo.seed(rd());
    }

    return algo;
}

template <typename T>
T uniform(T min, T max)
{
    using condition = typename std::is_integral<T>;
    using integer_dist = typename std::uniform_int_distribution<T>;
    using real_dist = typename std::uniform_real_distribution<T>;

    using distribution_type = typename std::conditional<condition::value, integer_dist, real_dist>::type;

    distribution_type dist(min, max);

    return dist(getRandomGenerator());
}

using namespace std;

double GetTicks()
{
    struct timeval tv;
    if(!gettimeofday (&tv, NULL))
        return (tv.tv_sec*1000 + tv.tv_usec/1000);
    else
        return -1;
}

std::string& transform(std::string& input)
{
    // transform the input string
    // e.g toggle first character
    if(!input.empty())
    {
        if(input[0]=='A')
            input[0] = 'B';
        else
            input[0] = 'A';
    }
    return input;
}

std::string&& transformA(std::string&& input)
{
    return std::move(transform(input));
}

std::string transformB(std::string&& input)
{
    return transform(input); // calls the lvalue reference version
}

std::string transformC(std::string&& input)
{
    return std::move( transform( input ) ); // calls the lvalue reference version
}


string getSomeString()
{
    string ret;
    
    auto size = uniform(20, 1000);
    for (auto i = 0; i < size; ++i) {
        ret += uniform('a', 'z');
    }
    
    return ret;
}

int main()
{
    const int MAX_LOOPS = 5000000;
    const int MAX_TEST_STRINGS = 100;
    
    vector<string> testStrings;
    testStrings.reserve(MAX_TEST_STRINGS);
    for (auto i = 0; i < MAX_TEST_STRINGS; ++i) {
    	testStrings.push_back(getSomeString());
    	//cout << i << ": " << testStrings.back() << "\n";
    }
    cout << endl;

    {
    	vector<string> testStringsA = testStrings;
        
        double start = GetTicks();
        for(int i=0; i<MAX_LOOPS; ++i)
            testStringsA[i % testStringsA.size()] = transformA(string(testStringsA[i % testStringsA.size()]));
        double end = GetTicks();

        cout << "\nRuntime transformA: " << end - start << " ms" << endl;
    }

    {
    	vector<string> testStringsB = testStrings;
    	
        double start = GetTicks();
        for(int i=0; i<MAX_LOOPS; ++i)
            testStringsB[i % testStringsB.size()] = transformB(string(testStringsB[i % testStringsB.size()]));
        double end = GetTicks();

        cout << "\nRuntime transformB: " << end - start << " ms" << endl;
    }

    {
    	vector<string> testStringsC = testStrings;
    	
        double start = GetTicks();
        for(int i=0; i<MAX_LOOPS; ++i)
            testStringsC[i % testStringsC.size()] = transformC(string(testStringsC[i % testStringsC.size()]));
        double end = GetTicks();

        cout << "\nRuntime transformC: " << end - start << " ms" << endl;
    }

    return 0;
}

