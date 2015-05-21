#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;


template<int I, typename F>
void wow(F& f)
{
    int n = I >> 1;
    switch(I%2)
    {
        case 0: do{
            cout << "lolli" << endl;
            for(auto i : f){
                i();
            }
        case 1:
            cout << "pop" << endl;
            for(auto i : f){
                i();
            }
        }while(--n);
    };
}


int main()
{
    // a pure-{love}-function lambda
    auto make_it_true = [](
        auto total,
        auto bin,
        auto line,
        auto apart=0,
        auto ch='-'){
        return [=] () mutable{
            int space;
            if (bin){
                space = total - (line<<1) - apart;
                while(space-->0){
                    cout << " ";
                }
                int half_line = line;
                line = line<<1;
                while(line-->half_line){
                    cout << ch;
                }
                while(apart-->0){
                    cout << " ";
                }
                while(line-->=0){
                    cout << ch;
                }
                cout << endl;
            }
            else{
                space = total - line;
                while(space-->0){
                    cout << " ";
                }
                while(line-->0){
                    cout << ch;
                }
                cout << endl;
            }
        };
    };

    using MAKE_IT_TRUE = function<void(void)>;
    vector<MAKE_IT_TRUE> mit;
    mit.reserve(12);
    mit.push_back(make_it_true(11,1,2,5,'_'));
    mit.push_back(make_it_true(13,0,13,0,'-'));
    mit.push_back(make_it_true(12,0,11,0,'_'));
    mit.push_back(make_it_true(11,0,9,0,'-'));
    mit.push_back(make_it_true(8,0,3,0,'_'));
    mit.push_back(make_it_true(7,0,1,0,'-'));
    fill_n(back_inserter(mit), 6, make_it_true(7,0,1,0,'#'));

    wow<520>(mit);
}
