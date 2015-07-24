    #include <tuple>
    #include <experimental/tuple>
    #include <string>
    #include <iostream>
    #include <unordered_map>
     
    template <typename I, typename F>
    void for_tie(I it, I end, F func)
    {
        for (; it != end; ++it) std::experimental::apply(func, *it);
    }
     
    int main()
    {
        std::unordered_map<int,std::string> map {{5,"five"},{1,"one"},{-7,"minus seven"}};
        for_tie(begin(map), end(map), [](int x, const std::string &s) {
            std::cout << x << "->" << s << "\n";
        });
    }