
auto async_call(int i)
{
    return rxcpp::observable<>::create<int>([i](auto s)
    {
        std::cout << "+async call" << std::endl;
        usleep(1000000);
        s.on_next(i);
        s.on_completed();
        std::cout << "-async call" << std::endl;
    });
}


int main(int argc,char** argv)
{
    rxcpp::sources::range(0,10)
    .flat_map([](auto x)
    {
        return async_call(x);
    },
    [](auto l,auto r)
    {
        return std::make_tuple(l,r);
    })
    .subscribe([](auto x)
    {
        std::cout << std::get<0>(x) << ":" << std::get<1>(x) << std::endl;
    });

    return 0;
}

