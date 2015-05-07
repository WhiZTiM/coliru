#include <iostream>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

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
    return string("ABC");
}

int main()
{
    const int MAX_LOOPS = 5000000;

    {
        double start = GetTicks();
        for(int i=0; i<MAX_LOOPS; ++i)
            transformA(getSomeString());
        double end = GetTicks();

        cout << "\nRuntime transformA: " << end - start << " ms" << endl;
    }

    {
        double start = GetTicks();
        for(int i=0; i<MAX_LOOPS; ++i)
            transformB(getSomeString());
        double end = GetTicks();

        cout << "\nRuntime transformB: " << end - start << " ms" << endl;
    }

    {
        double start = GetTicks();
        for(int i=0; i<MAX_LOOPS; ++i)
            transformC(getSomeString());
        double end = GetTicks();

        cout << "\nRuntime transformC: " << end - start << " ms" << endl;
    }

    return 0;
}

