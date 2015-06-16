#include <algorithm>
#include <iostream>
#include <vector>
#include <type_traits>

template<typename T1>
std::ostream& operator<<(std::ostream& stream, std::vector<T1> r) {
    if (r.size() == 0) {
        return stream;
    }
    else {
        stream << "(";
        for (int i = 0; i < r.size(); i++) {
            if (i < (r.size() - 1)) {
                stream << r[i] << ", ";
            }
            else {
                stream << r[i] << ")";
            }
        }
    }
    return stream;
};

template <typename T1, typename T2>
struct Add : std::plus<typename std::common_type<T1,T2>::type> { };//<-Here T1 or T2 depending on their types.

template <typename T1, typename T2>
struct Add<std::vector<T1>, std::vector<T2>>
{
    auto operator()(const std::vector<T1>& l, const std::vector<T2>& r)
    -> std::vector < decltype(Add<T1, T2> {}(l[0], r[0])) >
    {
        using type = decltype(Add<T1, T2>{}(l[0], r[0]));
        std::vector<type> ans;

        if (l.size() == std::max(l.size(), r.size()))
            std::transform(r.begin(), r.end(), l.begin(), std::back_inserter(ans), Add<T1, T2>{});
        else
            std::transform(l.begin(), l.end(), r.begin(), std::back_inserter(ans), Add<T1, T2>{});
        return ans;
    };
};

template <typename T1, typename T2>
auto operator+(const std::vector<T1>& lhs, const std::vector<T2>& rhs)
-> decltype(Add<std::vector<T1>, std::vector<T2>> {}(lhs, rhs))
{
    return Add<std::vector<T1>, std::vector<T2>> {}(lhs, rhs);
}

int main() {
    std::vector<int> e = {1};
    std::vector<double> q = {1.5};

    //Incorrect result = 2
    std::cout << (e + q) << std::endl;
    //Correct result = 2.5
    std::cout << (q + e) << std::endl;

    return 0;
}