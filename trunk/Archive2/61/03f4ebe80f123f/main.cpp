#include <functional>
#include <memory>
#include <utility>
#include <iostream>

template<typename Signature>
class function;

template<typename Ret, typename... Args>
class function<Ret(Args...)>
{
    struct CallbackBase
    {
        virtual Ret operator()(Args... args) const = 0;
    };

    template<typename Function>
    struct Callback : CallbackBase
    {
    template<typename F>
        Callback(F&& func)
        :
            func_(std::forward<F>(func))
        {
        } 

        Ret operator()(Args... args) const override final
        {
            return func_(args...);
        }

        Function func_;
    };

public:
    function()
    {
    }
    
    template<typename Function>
    function(Function&& func)
    :
        callback_(new Callback<Function>(std::forward<Function>(func)))
    {
    }

    Ret operator()(Args... args) const
    {
        return (*this->callback_)(args...);
    }

private:
    std::shared_ptr<CallbackBase> callback_;
};

int derp (int x, int y)
{
    return x * y;   
}

int main()
{
    function<int()> f = std::bind(derp, 1, 2);
    auto g = f;
    std::cout << f() << "\n";
    std::cout << g() << "\n";
    return 0;
}
