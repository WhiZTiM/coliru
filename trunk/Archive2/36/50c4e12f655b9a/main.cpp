#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <numeric>
#include <map>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>

// IOLib error
class IoError
{
public:
    typedef int Code; // not really necessary but differentiate from plain int
    static const Code NoError = 0;
    static const Code FileNotFound = 1;
    
    IoError(Code code):
        m_code(code)
    {
        
    }
    
    // 
    std::string toString() const
    {
        if(m_code == NoError)
            return "NoError";
        else if(m_code == FileNotFound)
            return "FileNotFound";
        else
            return "Invalid error code";
    }
    
    // Conversion to bool returns if error is set or not
    operator bool() const 
    {
        return m_code != NoError;   
    }
    
protected:
    Code m_code;
};

// ImagingLib error
class Error: public IoError
{
public:
    // Error inherits NoError and FileNotFound
    static const Code OutOfMemory = 2;
    
    Error(Code code):
        IoError(code)
    {
    
    }
    
    // implicit conversion from IoError to Error
    Error(const IoError &other):
        IoError(other)
    {
    
    }
    
    std::string toString() const
    {
        if(m_code == OutOfMemory)
            return "OutOfMemory";
        else
            return IoError::toString();
    }
};




// examples:

IoError ioMethod()
{
    return IoError::FileNotFound;    
}


int main()
{
    // Error can be used like a Enum
    
    Error e1 = Error::NoError;
    if(!e1) //uses operator bool()
        std::cout << e1.toString() << std::endl;
        
    Error e2 = Error::OutOfMemory;
    if(e2)
        std::cout << e2.toString() << std::endl;
    
    Error e3 = Error::NoError;
    std::cout << e3.toString() << std::endl;
    e3 = Error::FileNotFound;
    if(e3)
        std::cout << e3.toString() << std::endl;
        
    Error e4 = ioMethod();
    if(e4)
        std::cout << e4.toString() << std::endl;
}
