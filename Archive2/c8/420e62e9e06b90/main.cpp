#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>

#include <boost/preprocessor.hpp>

#define STR2(x) #x
#define STR(x) STR2(x)

#define MPL_STR_MACRO(z, n, data) ::push_back_t<char_at(data, n)>

#define MPL_STR(x) mpl_string<> BOOST_PP_REPEAT(100, MPL_STR_MACRO, STR(x))

template<char... Chars>
struct mpl_string {
    template<char C>
    using push_back_t = std::conditional_t<C == '\0', mpl_string<Chars...>, mpl_string<Chars..., C>>;
    
    std::string str() const {
        return {Chars...};
    }
};

template<std::size_t N>
constexpr char char_at(const char(&arr)[N], std::size_t index) {
    return index < N ? arr[index] : '\0';
}

template<typename T, typename Name>
struct type {};

#define FACTORY_MACRO(z, n, data) type<BOOST_PP_TUPLE_ELEM(n, data), MPL_STR(BOOST_PP_TUPLE_ELEM(n, data))>

#define FACTORY(result, ...) Factory<result, BOOST_PP_ENUM(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), FACTORY_MACRO, (__VA_ARGS__))>


template<typename Result, typename...>
struct CreateResult;

template<typename Result>
struct CreateResult<Result> {
    static Result *create(const std::string &) {
        return nullptr;
    }
};

template<typename Result, typename HeadType, typename HeadTypeName, typename... TailTypes>
struct CreateResult<Result, type<HeadType, HeadTypeName>, TailTypes...> {
    static Result *create(const std::string &name) {
        return name == HeadTypeName{}.str() ? new HeadType{} : CreateResult<Result, TailTypes...>{}.create(name);
    }
};

template<typename Result, typename... Types>
struct Factory;

template<typename Result, typename... Types, typename... Names>
struct Factory<Result, type<Types, Names>...> {
    static Result *create(const std::string &name) {
        return CreateResult<Result, type<Types, Names>...>{}.create(name);
    }
};

struct Shape {virtual ~Shape() {}};

struct Circle : Shape {};
struct Rectangle : Shape {};

using ShapeFactory = FACTORY(Shape, Circle, Rectangle);

void print(const Shape *s) {
    std::cout << "Null? " << (s ? "No" : "Yes") << '\n';
    std::cout << "Type: ";
    
    if (dynamic_cast<const Circle *>(s)) {
        std::cout << "Circle\n";
    } else if (dynamic_cast<const Rectangle *>(s)) {
        std::cout << "Rectangle\n";
    } else {
        std::cout << "Shape\n";
    }
    
    std::cout << '\n';
}

int main() {
    auto s1 = ShapeFactory::create("Circle");
    auto s2 = ShapeFactory::create("Rectangle");
    auto s3 = ShapeFactory::create("Square");
    
    print(s1);
    print(s2);
    print(s3);
}