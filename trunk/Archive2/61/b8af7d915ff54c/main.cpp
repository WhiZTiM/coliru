    #include <tuple>
    #include <string>
    #include <iostream>
    #include <unordered_map>
     
    template <typename I, typename... Ts>
    bool for_tie(std::pair<I,I>& its, Ts&&... parts)
    {
        if (its.first == its.second) return false;
    	std::tie(std::forward<Ts>(parts)...) = *its.first++;
    	return true;
    }
     
    int main()
    {
        std::unordered_map<int,std::string> map {{5,"five"},{1,"one"},{-7,"minus seven"}};
        int x;
        std::string s;
        auto map_its = std::make_pair(begin(map), end(map));
        while(for_tie(map_its, x, s))
            std::cout << x << "->" << s << "\n";
    }