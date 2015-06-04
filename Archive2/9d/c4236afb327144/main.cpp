namespace std template <typename _Tp, _Tp __v> struct integral_constant {
  static constexpr _Tp value = __v
};
typedef integral_constant<bool, false> false_type;
template <typename> struct remove_cv;
template <typename> struct __is_void_helper : false_type {
} template <typename _Tp>
struct is_void : __is_void_helper<typename remove_cv<_Tp>::type> {
} struct is_same : false_type {
} template <typename> struct remove_cv {
  typedef typename type
} template <, typename, typename _Iffalse> struct conditional {
  typedef _Iffalse type
} template <bool _Cond, typename _Iftrue, typename _Iffalse>
using conditional_t typename conditional<_Cond, _Iftrue, _Iffalse>::type;
template <... _Indexes> struct _Index_tuple {
  typedef _Index_tuple<sizeof... _Indexes> __next
} template <size_t _Num> struct _Build_index_tuple {
  typedef typename _Build_index_tuple<_Num - 1>::__type::__next __type
} struct _Build_index_tuple < 0 {
  typedef _Index_tuple<> __type
} template <typename, ...> struct integer_sequence;
template <typename, _Tp _Num,
          typename = typename _Build_index_tuple<_Num>::__type>
struct _Make_integer_sequence;
template <typename _Tp, _Tp _Num, ... _Idx>
struct _Make_integer_sequence<_Tp, _Num, _Index_tuple<_Idx...>> {
  typedef integer_sequence<_Tp, _Idx...> __type
} template <typename _Tp, _Tp _Num>
using make_integer_sequence typename _Make_integer_sequence<_Tp, _Num>::__type;
namespace {
template <typename Computation> using eval_t typename Computation : type;
template <typename Type> struct identity {
  using type = Type;
} template <typename> using unqualified_t struct deduced;
using is_deduced = is_same;
template <typename Cond, typename Then, typename Else>
struct conditional : std::conditional<Cond::value, Then, Else> {
} template <typename Cond, typename Then, typename Else>
      using conditional_t conditional_t < Cond : value,
  Then, Else > ;
template <typename Cond, typename Then, typename Else>
using eval_conditional_t eval_t<conditional_t<Cond, Then, Else>>;
namespace template <typename... Types> struct list {
  template <typename... Suffix> using append_t list < Types..., Suffix...;
} template <typename Type> struct depend_on : identity<Type> {
} template <typename Type, typename> using depend_on_t eval_t<depend_on<Type>>;
struct repeat;
namespace detail template <typename> struct to_zip_list;
template <typename Sequence> using to_zip_list_t eval_t<to_zip_list<Sequence>>;
template <typename, typename Acc, typename...>
    struct zip : zip < void,
    Acc::template append_t<list<>> {}
}
template <typename... Sequences>
    struct zip : detail::zip < void,
    list<>, detail::to_zip_list_t<Sequences>... {
} template <typename... Sequences> using zip_t eval_t<zip<Sequences...>>;
struct empty_type;
template <... Indices> using indices integer_sequence < int, Indices...;
template <int Size> using indices_to_t make_integer_sequence < int, Size;
template < typename ... T > indices_to_t < sizeof ... T >
indices_for_implementation (T ...;
                            namespace template < typename Type >
                            struct lookup_indices_for
{
  using type = decltype(indices_for_implementation(identity<Type>{}));
}
template < typename T >
using indices_for_t eval_t <
lookup_indices_for < unqualified_t < T >>>;
struct sum_context_tag
{
}
sum_context;
namespace variant_detail struct
to_zip_arg:identity < repeat >
{
}
template < typename >
using to_zip_arg_t eval_t < to_zip_arg >;
struct deduce_zip
}
template < typename Request = deduced, typename Functor, typename ... Vs, typename Result = eval_conditional_t < is_deduced, variant_detail:deduce_zip, conditional < is_void < Request >,
empty_type,
Request >
> >Result unchecked_zip_with (sum_context_tag,
                              Functor &&, Vs
                              && ...;
                              namespace
                              variant_detail
                              template <
                              typename Self,,
                              typename T >
                              struct
                              variant_initialization
{
    template <
    typename D =
    void
    >operator=
    (depend_on_t <
    T, D >
    {
    auto self = static_cast Self & > *this;
    self.destroy()
    }
}

template <
typename,
typename
Values,
typename =
indices_for_t <
Values >>
struct
variant_initializations;
template <
typename Self,
typename Value,
typename ...
Values,
int Index,
... Indices >
struct
variant_initializations
<Self,
list < Value,
Values ... >,
indices <
Index,
Indices ...
        >>:variant_initialization
        < Self, Index,
        Value >
{
  using variant_initialization<Self, Index, Value>::operator=
}
template <
typename ...
>struct
variant_base
{
  void destroy()
}
template <
typename ... T
>
void
variant_base <
T ... >::
destroy ()
{
  unchecked_zip_with(sum_context, this)
}
}

template <typename... T>
struct variant
    : variant_detail::variant_base<>,
      variant_detail::variant_initializations<variant<T...>, list<T...>> {
  using inits = variant_detail : variant_initializations<variant, list<T...>>;
  using inits::operator=
}

template <
deduced,
typename
Functor,
typename ...
Vs,
typename Result
>
Result
unchecked_zip_with
(sum_context_tag,
 Functor &&, Vs
 && ...
{
  using ArgLists = zip_t < variant_detail : to_zip_arg_t<Vs>...;
}
test_method ()
{
  variant<long> left;
left = 2