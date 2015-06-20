#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class c 
{
  public:
    c(const string& s) { s_ = s; }
    bool operator <(const c& c2) { return s_ < c2.s_; }

    string      s_;
};

bool abs_comp (const int & lhs, const int& rhs)
{
    return abs(lhs) < abs(rhs);
}

int main()
{
    vector<c>  cvec;
    cvec.push_back(c("xb"));
    cvec.push_back(c("xaa"));
    cvec.push_back(c("ra"));
    vector<c>::const_iterator it = max_element(cvec.begin(), cvec.end());
    std::cout << "max_element of c is : " << (*it).s_ << std::endl;

    vector<int> ints({3, -8, 9, 2, 18, -26, 2, 23});
    int max = *(max_element(ints.begin(), ints.end()));
    cout << "max integer is : " << max << endl;
    
    max = *(max_element(ints.begin(), ints.end(), abs_comp));
    cout << "max abs integer is : " << max << endl;
    
}
