#include<regex>
#include<iostream>

using namespace std;
int main() {
    int count = 0,t;
    cin >> t;
    string s="I love #hacker";
    bool ans;
    while(t--){
        cin >> s;
        smatch sm;
       // regex rgx("(.*)hacker(.*)",regex_constants::icase);
        regex rgx("hacker",regex_constants::icase);
        ans = regex_search(s,sm,rgx);
        if(ans){
            count += 1;
        }         
    }
    cout << ans << endl;
    return 0;
}