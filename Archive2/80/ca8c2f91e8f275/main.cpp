#include <functional>
#include <queue>
#include <vector>
#include <iostream>
 
 
struct Prio {
    Prio(double x) : m_distance(x) {}
    double m_distance;
    
    bool operator<(const Prio& rhs) const {
        return m_distance > rhs.m_distance;
    }
};

template<typename T> void print_queue(T& q) {
    while(!q.empty()) {
        std::cout << q.top().m_distance << " ";
        q.pop();
    }
    std::cout << '\n';
}
 
int main() {
    std::priority_queue<Prio> q;
 
    for(int n : {1,8,5,6,3,4,0,9,3,2})
        q.push(n);
 
    print_queue(q);
 
    //std::priority_queue<int, std::vector<int>, std::greater<int> > q2;
 
    //for(int n : {1,8,5,6,3,4,0,9,3,2})
        //q2.push(n);
 
    //print_queue(q2);
}