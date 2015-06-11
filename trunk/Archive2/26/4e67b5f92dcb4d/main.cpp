#include <vector>
#include <iostream>
#include <algorithm>

struct range {
 range(std::vector<int>& cnt) : m_container(cnt) {}
 range& till(int N) {
     if (N >= m_container.size())
         m_end = m_container.end();
     else
     	m_end = m_container.begin() + N;
     return *this;
 }
 std::vector<int>& m_container;
 std::vector<int>::iterator m_end;
 std::vector<int>::iterator begin() {
 	return m_container.begin();
 }
 std::vector<int>::iterator end() {
 	return m_end;
 }
};

int main() {
    std::vector<int> a{11, 22, 33, 44, 55};
    int n = 4;
    
    for ( int i : range(a).till(n) ) {
       std::cout << i << std::endl;
    }
}