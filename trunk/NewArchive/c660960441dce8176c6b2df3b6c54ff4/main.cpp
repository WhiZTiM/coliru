template <typename... T>
struct typelist {};
using nil = typelist<>;
template <typename Head typename... Tail>
struct typelist {
    using head = Head;
    using tail = typelist<Tail...>;
};
