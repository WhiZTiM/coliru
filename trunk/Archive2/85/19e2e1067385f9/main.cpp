#include <iostream>
#include <utility>
#include <tuple>

struct Field
{
    int fst, snd, thrd, fth;
};

struct Record
{
    std::tuple<Field, Field> data;
};

template <class Field>
auto process_field(Field&& field)
{
    return std::forward_as_tuple(field.fst, field.snd, field.thrd, field.fth); 
}

template <std::size_t ...ids, class Rec>
auto iterate_record(std::index_sequence<ids...>, Rec && rec)
{
    return std::tuple_cat(
        process_field
        (std::get<ids>( std::forward<Rec>(rec).data))...
    );
}

template <typename T> void TD() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

int main()
{
    auto x = iterate_record(std::index_sequence<0>{}, Record{});
    TD<decltype(x)>();
}
