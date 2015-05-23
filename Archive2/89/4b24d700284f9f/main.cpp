template<int>
struct A
{
  using type = int;
};
template<>
struct A<0>
{
  using type = short;
};

template<int i>
struct B
{
  using A_type = A<i>;
  using type = typename A_type::type;
};

template<>
struct B<1>
{
  using A_type = A<0>;
  using type = typename A_type::type; /* HERE */
};
