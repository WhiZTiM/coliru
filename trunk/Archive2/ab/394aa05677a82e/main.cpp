#include <iostream>
#include <exception>

/* Crazy crappy lib */
struct crap_exception {
    int unused_parameter;
    std::string what;
    std::ifstream *crazy;
};

void crazy(int param) {
    std::cout << "crazy" << std::endl;
    
    if(param == 5)
        throw std::runtime_error("param can't be 5");
    if(param < 0)
        throw new crap_exception();
}
/* End crazy lib */

void register_failure() {
    // stuff...
}

void myfunc(int param) { 
    try {
        crazy(param);
    } 
    catch(std::exception &e) {
        std::clog << "Exception caught: " << e.what() << std::endl;
        register_failure();
        
        std::string message = std::string("myfunc(): exception ") + e.what();
        throw std::runtime_error(message);
    }
    catch(...) {
        std::clog << "Exception caught: unknown" << std::endl;
        register_failure();
        
        std::string message = std::string("myfunc(): exception unknown");
        throw std::runtime_error(message);
    }
}

int main() {
    try {
        myfunc(7);
    } 
    catch(std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    try {
        myfunc(5);
    } 
    catch(std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
    
    try {
        myfunc(-1);
    } 
    catch(std::exception &e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }
}
