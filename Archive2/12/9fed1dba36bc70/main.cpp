#include <iostream>
#include <string>

namespace JNI
{
    struct JInt 
    {
        std::string Name()
        {
            return "I";
        }
    };
    
    struct JVoid
    {
        std::string Name()
        {
            return "V";
        }
    };
        
    struct JString
    {
        std::string Name()
        {
            return "java/lang/String;";
        }
    };
    
    template <typename IndexedType>
    struct JArray
    {
        std::string Name()
        {
            return "[" + IndexedType().Name();
        }
    };
    
    template <typename>
    struct JFunction;
    
    template <typename Ret, typename Arg1>
    struct JFunction<Ret(Arg1)>
    {
        std::string Sig()
        {
            return "(" + Arg1().Name() + ")" + Ret().Name();
        }
    };
    
    template <typename Ret, typename Arg1, typename Arg2>
    struct JFunction<Ret(Arg1, Arg2)>
    {
        std::string Sig()
        {
            return "(" + Arg1().Name() + Arg2().Name() + ")" + Ret().Name();
        }
    };
    
    template<typename Sig>
    std::string sig() { return Sig().Sig(); }
}

int main()
{
    using namespace JNI;
    
    std::cout << sig<JFunction<JInt(JInt)> >() << std::endl;
    std::cout << sig<JFunction<JInt(JArray<JInt>)> >() << std::endl;
    std::cout << sig<JFunction<JVoid(JInt, JArray<JInt>)> >() << std::endl;
    std::cout << sig<JFunction<JVoid(JInt, JString)> >() << std::endl;
}