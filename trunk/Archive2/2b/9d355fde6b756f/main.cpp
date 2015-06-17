#include <string>
#include <memory>
#include <utility>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <stdexcept> 
#include <functional>


class indenting_streambuf : public std::streambuf
{
private:
    std::streambuf& _source;
	bool _indent{true};
	int _indentation;

private:
	int overflow(int ch) override
	{
		if (_indent)
		{
			for (int i = 0; i < _indentation; ++i)
			{
				if (_source.sputc(' ') == EOF) return EOF;
			}
		}

		_indent = (ch == '\n');

		return _source.sputc(ch);	
	}

public:	
	indenting_streambuf(std::streambuf& source, int indentation = 0) 
		: _source(source) 
		, _indentation(indentation) 
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
	indenting_ostream(std::ostream& source, int indentation = 0) 
		: std::ostream(&_streambuf)
        , _streambuf(*source.rdbuf(), indentation)
	{
	}
	
	int indentation() const { return _streambuf.indentation(); }

	void indentation(int indentation) { _streambuf.indentation(indentation); }
};

int main()
{
    indenting_ostream ss(std::cout, 4);
    ss << "4 spaces in\nagain\nand again\nand again";
    return 0;
}