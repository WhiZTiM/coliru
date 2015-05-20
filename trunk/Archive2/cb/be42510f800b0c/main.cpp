#include <iostream>
using namespace std;


template<int I, typename F>
void wow(F f)
{
    int n = I >> 1;
    switch(I%2)
    {
        case 0: do{
            cout << "lali" << endl;
            f(11,1,2,5);
            f(13,0,13,0);
            f(12,0,11,0);
            f(11,0,9,0);
            f(8,0,3,0);
            f(7,0,1,0);
        case 1:
            cout << "pop" << endl;
            f(11,1,2,5);
            f(13,0,13,0);
            f(12,0,11,0);
            f(11,0,9,0);
            f(8,0,3,0);
            f(7,0,1,0);
        }while(--n);
    };
}


int main()
{
    // a love lambda has side-effects
    auto make_it_true = [](
        auto total,
        auto bin,
        auto line,
        auto apart=0){
        int space;
        if (bin){
            space = total - (line<<1) - apart;
            while(space-->0){
                cout << " ";
            }
            int half_line = line;
            line = line<<1;
            while(line-->half_line){
                cout << "_";
            }
            while(apart-->0){
                cout << " ";
            }
            while(line-->=0){
                cout << "_";
            }
            cout << endl;
        }
        else{
            space = total - line;
            while(space-->0){
                cout << " ";
            }
            while(line-->0){
                cout << "_";
            }
            cout << endl;
        }
    };
    wow<520>(make_it_true);
}
