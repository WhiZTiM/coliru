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

void __attribute__((noinline)) foo(vector< pair<int, CopyTest&&> >& v) {
    v.emplace_back( 1, CopyTest() );
}
void __attribute__((noinline)) bar(vector< pair<int, CopyTest&&> >& v) {
    volatile int i[10] = {42, 42, 42, 42, 42, 42, 42, 42};
    cout << (void*)(&v[0].second.i) << " : " << (void*)(&i[0]) << "\n";
    cout << v[0].second.i << " : " << i[0] << endl;  // Why??? Why no dangling reference?
}

int main() {
    vector< pair<int, CopyTest&&> > c;
    
    foo(c);
    bar(c);
    
    
    using Dangl = pair<int, CopyTest&&>;
    Dangl dangl(1, CopyTest() );    
    
    cout << std::is_rvalue_reference< typename Dangl::second_type>::value << endl;   // rvalue ref indeed
    
    cout << dangl.second.i << endl;   // correct value too
    
  return 0;
}