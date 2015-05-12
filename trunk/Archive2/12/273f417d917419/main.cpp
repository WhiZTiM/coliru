#include <stdexcept>
#include <iostream>

#include <boost/exception/diagnostic_information.hpp>

class xb : public boost::exception {};

class xd : virtual public std::exception, public xb {
public:
    xd(const xb& exc)
    : xb(exc) {
		std::cerr << "exc: " << boost::diagnostic_information(exc)
		          << "\n*this: " << boost::diagnostic_information(*this);
	}
};


int main() {
	try {
		boost::throw_exception( xd( xb() << boost::throw_file(__FILE__)
		                                 << boost::throw_line(__LINE__)
		                          )
		                      );
	} catch(xb& exc) {
		std::cerr << "\ncaught: " << boost::diagnostic_information(exc);
        return 0;
	}
    return 1;
}



