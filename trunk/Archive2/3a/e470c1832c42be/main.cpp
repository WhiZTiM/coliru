#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <cassert>
#include <iostream>
 
class indenting_streambuf : public std::streambuf
{
private:
    std::ostream& _out;
	bool _indent{true};
	int _indentation;
 
private:
	int overflow(int ch) override
	{
		if (_indent == true)
		{
			for (int i = 0; i < _indentation; ++i)
			{
				if (_out.rdbuf()->sputc(' ') == EOF) return EOF;
			}
		}
 
		_indent = (ch == '\n');
 
		return _out.rdbuf()->sputc(ch);	
	}
 
public:	
	indenting_streambuf(std::ostream& out, int indentation = 0) 
		: _out{out} 
		, _indentation{indentation} 
	{
	}
 
	int indentation() const { return _indentation; };
 
	void indentation(int indentation) { _indent = true; _indentation = indentation; }
};
 
 
class indenting_ostream : public std::ostream
{
private:
	indenting_streambuf _streambuf;
 
public:	
	indenting_ostream(std::ostream& ostream, int indentation = 0) 
		: _streambuf{ostream, indentation}
		, std::ostream{&_streambuf} 
	{
	}
 
	int indentation() const { return _streambuf.indentation(); }
 
	void indentation(int indentation) { _streambuf.indentation(indentation); }
};


template<typename It>
void print_range(std::ostream& out, It begin, It end) {
    auto it = begin;
    if (it == end) { out << "empty"; return; }
    out << *it++;
    for (; it != end; ++it) 
        out << " " << *it;
}

 template <class ForwardIt>
 void quicksort1(ForwardIt first, ForwardIt last, int indentation = 0)
 {
    if(first == last) return;
    auto pivot = *std::next(first, std::distance(first,last)/2);
    ForwardIt middle1 = std::partition(first, last,
                         [pivot](const auto& em){ return em < pivot; });
    ForwardIt middle2 = std::partition(middle1, last,
                         [pivot](const auto& em){ return !(pivot < em); });
    quicksort1(first, middle1);
    quicksort1(middle2, last);
 }
 
 template <class ForwardIt>
 void quicksort2(ForwardIt first, ForwardIt last, int level = 0)
 {
    indenting_ostream out{std::cout, 4*level};
    if(first == last) 
    {
        out << "done\n";
        return;
    }
    auto pivot = *first;
    ForwardIt middle = std::partition(first, last,
                         [pivot](const auto& em){ return em < pivot; });
    out << "pivot: " << *middle << "\n";
    out << "first recursion (on: ";  print_range(out, first, middle); out << ")\n";
    quicksort2(first, middle, level+1);
    out << "second recursion (on: "; print_range(out, std::next(middle), last); out << ")\n";
    quicksort2(std::next(middle), last, level+1);
    out << "merged: "; print_range(out, first, last); out << "\n";
 }

int main() 
{
    std::vector<int> vec1 { 1, 55, 12, 23, 123, -387, 0, 23 };
    quicksort2(vec1.begin(), vec1.end());
    print_range(std::cout, vec1.begin(), vec1.end());
    return 0;
}
