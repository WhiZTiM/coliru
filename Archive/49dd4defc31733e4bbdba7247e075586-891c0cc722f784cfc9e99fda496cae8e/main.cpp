#include <iostream>
#include <iterator>
#include <sstream>

template <int tabwidth, typename In, typename Out>
Out mogrify(In f, const In l, Out out)
{
    unsigned ws = 0;

    auto emit = [&]() mutable { 
        while(ws>tabwidth) {
            *out++ = '\t';
            ws -= tabwidth;
        }
        while(ws) {
            *out++ = ' ';
            --ws;
        }
        ws = 0;
    };

    for( ; f!=l; ++f) {
        switch(*f) {
        case ' ': 
            ws+=1; 
            break;
        case '\t': 
            ws = ((ws/tabwidth)+1) * tabwidth; 
            break;
        case '\n': 
            emit(); 
            *out++ = *f; 
            break;
        default: 
            emit(); 
            *out++ = *f; 
            break;
        }
    }
	emit();

    return out;
}


int main()
{
	std::istreambuf_iterator<char> f(std::cin), l;

	mogrify<4>(f, l, std::ostream_iterator<char>(std::cout));
}
