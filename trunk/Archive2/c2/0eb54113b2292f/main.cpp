

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <stack>
#include <stdexcept>
#include <string>
#include <set>
#include <utility>
#include <vector>

enum x { a, b };

std::pair<std::string, int>
foo(const std::pair<int, int>& in) {
  return std::make_pair(std::string(in.first, 'x'), in.second);   
}

void bar(char* fa) {
    
}

int main() {
    
    
    std::vector<char> vc(10);
    bar(&vc[0]);
    
    
    typedef std::map<int, int> M1;
    typedef std::map<std::string, int> M2;
    
    M1 m1;
    M2 m2;
    
    m1[2] = 42;
    m1[5] = 36;
    
    std::transform(m1.begin(), m1.end(), std::inserter(m2, m2.begin()), foo);
    
    std::cout << m2["xx"] << " " << m2["xxxxx"];
    
}