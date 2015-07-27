template<typename> struct fx;
 
template<typename R, typename...Args>
struct fx<R(Args...)>
{
    virtual R operator()(const Args & ...x) const = 0;
};
 
template<typename derived, typename base = typename derived::fx> struct fx_err;
 
// I feel here something is wrong, but I can't figure it out.
template<typename derived, template<typename> class F, typename R, typename... Args>
struct fx_err< derived, F<R(Args...)> > : F<R(R,Args...)>
{
    derived f;
 
    R operator ()(const R &y, const Args & ...x) const override
    {
        return y - f(x...);
    }
};
 
struct example_fun : fx<int(int,int,int)>
{
    int operator() (const int &a, const int &b, const int &c) const override
    {
        return a * b * c;
    }
};
 
 
 
//---------------------------------------------------------------
int main(int argc, char *argv[])
{
    fx_err<example_fun> example;
    int err = example(24,2,3,4);
 
    return 0;
}