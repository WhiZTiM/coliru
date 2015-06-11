#include <iostream>
#include <vector>
#include <map>
#include <boost/assign/list_of.hpp>
using namespace std;

enum steps{
    One,
	Two,
	Three
};

template <typename e>
class CircularBuffer{
	public: 
	CircularBuffer(vector<e> vals)  : _values(vals), _index(0) {}
    e Curr() const { return _values[_index]; }
	e Next(){ return _index == _values.size() - 1 ? _values[_index = 0] : _values[++_index]; }
	e Previous() { return _index==0? _values[_index = _values.size()-1] : _values[--_index]; }
	private:
	vector<e> _values;
	size_t _index;
};

int main() {

    map<steps,string> names;
    names[One]="One";
    names[Two]="Two";
    names[Three]="Three";
    vector<steps> l = boost::assign::list_of(One)(Two)(Three);
	CircularBuffer<steps> s(l);
    cout << names[s.Curr()] <<endl;s.Next();
    cout << names[s.Curr()] <<endl;s.Next();
    cout << names[s.Curr()] <<endl;s.Next();
    cout << names[s.Curr()] <<endl;s.Next();
    cout << names[s.Curr()] <<endl;s.Next();
	return 0;
}