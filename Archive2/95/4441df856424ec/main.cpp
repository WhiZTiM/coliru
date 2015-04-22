#define FIELD(type, name)   \
template<typename T>        \
struct column_ ## name      \
{                           \
    struct field            \
    {                       \
        T name;             \
    };                      \
};                          \
column_ ## name <type> name \
/**/

template<typename ...Columns>
struct row : Columns::field...
{};

template<typename ...Columns>
auto select(Columns...)
{
    return row<Columns...>{};
}

/********************************************/

struct
{
    FIELD(int, id);
    FIELD(double, value);
    FIELD(bool, flag);
} table;

int main()
{
    auto x = select(table.id, table.value);
    x.id = 11;
    x.value = 0.11;
    x.flag = true;

    auto y = select(table.id, table.flag);
    y.id = 11;
    y.value = 0.11;
    y.flag = true;
}

