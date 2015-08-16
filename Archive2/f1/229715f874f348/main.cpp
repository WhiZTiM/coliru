#include <iostream>
#include <vector>

using namespace std;

struct CopyTest {
    int i = 100;
    CopyTest() {
        cout << "default ctr" << endl;
    }

    CopyTest(const CopyTest &other) {
        cout << "Copy ctr" << endl;
    }

    CopyTest(CopyTest &&other) noexcept /* noexcept needed to enable optimizations in containers */
            {
                    cout << "Move ctr" << endl;
            }

    ~CopyTest() noexcept /* explicitly specified destructors should be annotated noexcept as best-practice */
    {
        cout << "Destructor" << endl;
    }

    CopyTest &operator=(const CopyTest &other) {
        cout << " Copy assignment operator" << endl;
        return *this;
    }

    /** Move assignment operator */
    CopyTest &operator=(CopyTest &&other) noexcept {
        cout << " Move assignment operator" << endl;
        return *this;
    }
};

int main() {
    vector< pair<int, CopyTest&&> > c;
    c.emplace_back( 1, CopyTest() );
    
    cout << c[0].second.i << endl;  // Why??? Why no dangling reference?
    
    
    using Dangl = pair<int, CopyTest&&>;
    Dangl dangl(1, CopyTest() );    
    
    cout << std::is_rvalue_reference< typename Dangl::second_type>::value << endl;   // rvalue ref indeed
    
    cout << dangl.second.i << endl;   // correct value too
    
  return 0;
}