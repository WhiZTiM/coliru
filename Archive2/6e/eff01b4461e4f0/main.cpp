
#include <iostream>
#include <set>
#include <vector>
int h(std::vector<int>l){int W=0,y;std::set<std::pair<int,int>>S{{-1,0}};for(w:l){S.insert({w,y=prev(S.lower_bound({w,-1}))->second+w});W=y>W?y:W;}return W;}

int main() {
    std::cout << h({9, 1, 2, 3, 4, 5, 6, 10}) << "\n";
    return 0;
}