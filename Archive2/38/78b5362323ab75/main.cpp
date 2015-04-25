#include <cstdio>
#include <string>

using namespace std;

int main( int argc, char ** argv )
{
    string hi[] = { "hi", "cool", "what" };

    for (string s : hi)
    {
        printf("%s \n", s);
    }

    return 0;
}