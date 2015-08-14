#include <iostream>

using namespace std;

char* findx(const char* s, const char* x)
{
    int count_s = 0;

    while (s[count_s] != 0)
    {
        int count_x = 0;
        while (x[count_x] != 0)
        {
            if (s[count_s] == x[count_x])
            {
                cout << "Found match " << x[count_x] << " at X[" << count_x
                << "] with " << s[count_s] << " at S[" << count_s
                << "]" << endl;
                return 0;
                break;
            }
            ++count_x;
        }
        ++count_s;
    }

    cout << "Match " << *x << " not found" << endl;
    return 0;
}

int main()
{
    char* p = new char[6]{ "Zorro" };
    char* p1 = new char[4]{ "Zio" };
    findx(p, p1);
    delete[] p;
    delete[] p1;
    return 0;
}