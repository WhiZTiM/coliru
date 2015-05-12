#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

void bar(std::vector<std::vector<int>>& par)
{
    std::vector<int> v1 = { 1,2,3 };
    par.push_back(v1);
}


struct GlobalWrapper
{
        std::vector<std::vector<int>> _data;

        size_t size() const { return _data.size(); }
        std::vector<int>& Get( size_t i ) { return _data[i]; }
        const std::vector<int>& Get( size_t i ) const { return _data[i]; }
};

struct Wrapper
{
    std::vector<int>* _data;
        
    void DoSomething() const
    {
        cout << "values: "; 
        std::copy( _data->begin(), _data->end(), std::ostream_iterator<int>(std::cout, " "));        
    }
    Wrapper( std::vector<int>& value ) : _data(&value)
    {
    }
};



int main(int argc, char ** argv)
{
    GlobalWrapper gw;

    cout << "size before=" << gw.size() << endl;
	bar( gw._data );
    cout << "size after=" << gw.size() << endl;

// get first element and do something with it
    Wrapper w = gw.Get(0); // todo write a [] operator
    w.DoSomething();
    
	return 0;
}
