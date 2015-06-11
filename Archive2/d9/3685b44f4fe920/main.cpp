#include <iostream>
#include "boost/multi_array.hpp"

using namespace std;
using namespace boost;

typedef multi_array<int, 3> array3i;

class Test {
  private:
    array3i test_array_;

    void init(int const x, int const y, int const z)
    {
        test_array_.resize(extents[x][y][z]);
        cout << "Size should be: " << test_array_.size() << endl;
        for (int j = 0; j < x; j++) {
            for (int jj = 0; jj < y; jj++) {
                for (int jjj = 0; jjj < z; jjj++) {
                    test_array_[j][jj][jjj] = j + jj + jjj;
                }
            }
        }
    };

  public:
    array3i test_array() { return test_array_; };

    Test(int x, int y, int z) { init(x, y, z); };
};

int main()
{
    Test test(2, 3, 5);

    cout << "Size from getter: " << test.test_array().size() << endl;
}
