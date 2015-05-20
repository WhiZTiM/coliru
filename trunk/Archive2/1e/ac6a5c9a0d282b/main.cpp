#include <iostream>
#include <functional>
using namespace std;


template<int I, typename F>
void wow(F& f)
{
    int n = I >> 1;
    switch(I%2)
    {
        case 0: do{
            cout << "lali" << endl;
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
    // a pure-function love lambda
    auto make_it_true = [](
        auto total,
        auto bin,
        auto line,
        auto apart=0,
        auto ch){
        return [total, bin, line, apart, ch] () mutable{
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
    MAKE_IT_TRUE mit[6] = {
        make_it_true(11,1,2,5,'_'),
        make_it_true(13,0,13,0,'-'),
        make_it_true(12,0,11,0,'_'),
        make_it_true(11,0,9,0,'-'),
        make_it_true(8,0,3,0,'_'),
        make_it_true(7,0,1,0,'-')};

    wow<520>(mit);
}
