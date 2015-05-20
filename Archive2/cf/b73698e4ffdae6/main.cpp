#include <vector>
using namespace std;

struct POD
{
    int x[100];
    char y;
    bool z;
};

void test(const vector<POD> &x, vector<POD> &y)
{
    y = x;
}

int main()
{
}