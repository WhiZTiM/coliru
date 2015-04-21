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
    
    template <typename Ret>
    struct JFunction<Ret()>
    {
        static std::string Sig()
        {
            return "()" + Ret().Name();
        }
    };
    
    template <typename Ret, typename Arg1>
    struct JFunction<Ret(Arg1)>
    {
        static std::string Sig()
        {
            return "(" + Arg1().Name() + ")" + Ret().Name();
        }
    };
    
    template <typename Ret, typename Arg1, typename Arg2>
    struct JFunction<Ret(Arg1, Arg2)>
    {
        static std::string Sig()
        {
            return "(" + Arg1().Name() + Arg2().Name() + ")" + Ret().Name();
        }
    };
}

int main()
{
    using namespace JNI;
    std::cout << JFunction<JInt(JInt)>::Sig() << std::endl;
    std::cout << JFunction<JInt(JArray<JInt>)>::Sig() << std::endl;
    std::cout << JFunction<JVoid(JInt, JArray<JInt>)>::Sig() << std::endl;
    std::cout << JFunction<JVoid(JInt, JString)>::Sig() << std::endl;
    std::cout << JFunction<JVoid()>::Sig() << std::endl;
}