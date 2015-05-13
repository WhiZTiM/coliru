#include <string>
#include <iostream>

using String = std::string;

namespace Ogre {
    namespace StringConverter {
        template<class T>
        String toString(T t) { return std::to_string(t); }
        
        String toString(String) { return "true"; }
        String toString(const char *) { return "true"; }
    }
}

namespace U {
    template<typename T>
    inline String c(T a)
    {
        return Ogre::StringConverter::toString( a );
    }
    inline String c(String s)
    {
        return s;
    }
    inline String c(const char s[])
    {
        return s;
    }
    template<typename T, typename... Args>
    inline String c(T a, Args... args);
    template<typename... Args>
    inline String c(String s, Args... args);
    template<typename... Args>
    inline String c( const char s[], Args... args);
    
    template<typename T, typename... Args>
    inline String c(T a, Args... args)
    {
        return Ogre::StringConverter::toString( a ) + c(args...);
    }
    template<typename... Args>
    inline String c(String s, Args... args)
    {
        return s + c(args...);
    }
    template<typename... Args>
    inline String c( const char s[], Args... args)
    {
        return s + c(args...);
    }
}
int main(){
    static int dMap[501][501] = {};
    dMap[500][500] = 112;
    std::cout << U::c( "This is dMap[500][500]: ", dMap[500][500], " and this is 5: ", 5, "." ) << U::c("\n");
}