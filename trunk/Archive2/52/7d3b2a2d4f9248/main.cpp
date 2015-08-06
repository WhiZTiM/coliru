template<typename... T>
struct type_list;

template<typename T>
struct filtered_list;

template<typename T, typename... U>
struct filtered_list<type_list<T,U...>> {
    using type = type_list<U...>;
};

template<typename TypeList>
using filtered_list_t = typename filtered_list<TypeList>::type;

template<typename T>
struct filtered_base_classes;

template<typename... T>
struct filtered_base_classes<type_list<T...>> : public T... {};

struct A { void test_a() {} };
struct B { void test_b() {} };
struct C { void test_c() {} };

class Test : public filtered_base_classes<filtered_list_t<type_list<A,B,C>>> {};

int main() {
    Test t;
    t.test_a(); //error, we dropped A from our base class list
    t.test_b();
    t.test_c();
}
