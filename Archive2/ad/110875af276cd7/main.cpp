#include <iostream>
#include <map>
#include <memory>

struct XYZ_message
{
    int value;
};

struct ABC_message
{
    int value;
};

int HandleXYZ(const XYZ_message&)
{
    return 5;
}

int HandleABC(const ABC_message& msg)
{
    return -msg.value;
}

struct HandlerBase
{
    virtual int Invoke(int arg_type) = 0;
};

template<typename T>
struct Handler : HandlerBase
{
    using Func = int(const T&);
    Func* f;

    int Invoke(int arg) override
    {
        T a{arg};
        return f(a);
    }
};

template<typename MessageT>
std::unique_ptr<HandlerBase> CreateHandler(int(*func)(const MessageT&))
{
    std::unique_ptr<Handler<MessageT>> res = std::unique_ptr<Handler<MessageT>>(new Handler<MessageT>);
    res->f = func;
    return std::move(res);
}

enum message_id
{
    mXYZ = 0,
    mABC = 1,
};

std::unique_ptr<HandlerBase> handlers[]
{
    CreateHandler(HandleXYZ),// mXYZ
    CreateHandler(HandleABC),// mABC
};

int main()
{
    std::cout << "XYZ(5)  = " << handlers[mXYZ]->Invoke(5) << '\n';
    std::cout << "XYZ(50) = " << handlers[mXYZ]->Invoke(50) << '\n';
    std::cout << "ABC(5)  = " << handlers[mABC]->Invoke(5) << '\n';
    std::cout << "ABC(50) = " << handlers[mABC]->Invoke(50) << '\n';
}
