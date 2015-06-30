#include <utility>
#include <iostream>

//your record function(s)
bool g_profiling;
template<class wrapfunc_type, class return_type, class...Ps>
void record_w_ret(wrapfunc_type wrapfunc, return_type ret, Ps...Vs)
{
    std::cout << wrapfunc.get() << " " << ret << "\n";
}
template<class wrapfunc_type, class...Ps>
void record_no_ret(wrapfunc_type wrapfunc, Ps...Vs)
{
    std::cout << wrapfunc.get() << "\n";
}


//declare the Wrap type
template<class signature, signature func> struct Wrap;

//Wrappers with returns
template<class R, class...Ps, R(&func)(Ps...)> 
struct Wrap<R(Ps...), func>
{
    typedef R(&signature)(Ps...);
    typedef R return_type;
    typedef std::tuple<Ps...> parameters;
    signature get() const {return func;}
    
    static declspec(__stdcall) R call(Ps...Vs) const
    {
        auto result = func(Vs...);
        if (g_profiling) record_w_ret(*this, result, Vs...);
        return result;
    }
};
//Wrappers without returns
template<class...Ps, void(&func)(Ps...)> 
struct Wrap<void(Ps...), func>
{
    typedef void(&signature)(Ps...);
    typedef void return_type;
    typedef std::tuple<Ps...> parameters;
    signature get() const {return func;}
    
    static declspec(__stdcall) void call(Ps...Vs) const
    {
        func(Vs...);
        if (g_profiling) record_no_ret(*this, Vs...);
    }
};
//easymode wrapper
#define WRAP(X) Wrap<decltype(X),X>::call


//just sos it compiles
typedef int HANDLE;
HANDLE OpenHandle(const char*, int flags) {return 0;}
void CloseHandle(HANDLE h) {}

//and then you write these
#define WrapOpenHandle WRAP(OpenHandle)
#define WrapCloseHandle WRAP(CloseHandle)

int main() {
    HANDLE hnd = WrapOpenHandle("file.txt", 3);
    WrapCloseHandle(hnd);
}