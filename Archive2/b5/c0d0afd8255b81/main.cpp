#include <iostream>
#include <utility>
#include <tuple>
#include <boost/preprocessor/variadic/to_seq.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/preprocessor/cat.hpp>

template<char... cs>
using str = std::integer_sequence<char, cs...>;

template<std::size_t... Ns, class S>
inline auto make_str_impl(std::index_sequence<Ns...>, S)
{
    return str<S::get()[Ns]...>();
}

template<class S>
inline auto make_str(S s)
{
    return make_str_impl(std::make_index_sequence<sizeof(S::get()) - 1>(), s);
}

template<char... cs>
std::ostream& operator<<(std::ostream& out, str<cs...>)
{
    static constexpr char s[] = {cs...};
    out.write(s, sizeof(s));
    return out;
}

#define AZ_STRING(s) make_str([]                                                \
{                                                                               \
    struct                                                                      \
    {                                                                           \
        static constexpr decltype(auto) get()                                   \
        {                                                                       \
            return s;                                                           \
        }                                                                       \
    } _;                                                                        \
    return _;                                                                   \
}())

#define AZ_INTEGRAL(val) (std::integral_constant<decltype(val), val>{})

template<bool b>
using bool_ = std::integral_constant<bool, b>;
using true_ = std::integral_constant<bool, true>;
using false_ = std::integral_constant<bool, false>;

template<class Expr, class T = void>
struct enable_if_valid
{
    using type = T;
};

template<class T, class U = void>
using enable_if_valid_t = typename enable_if_valid<T, U>::type;

template<class T, class U>
inline T select(true_, T val, U)
{
    return val;
}

template<class T, class U>
inline U select(false_, T, U val)
{
    return val;
}

template<class Cond, class F1, class F2>
inline auto if_(Cond cond, F1 f1, F2 f2)
{
    return select(cond, f1, f2)();
}

auto const pack = [](auto... ts)
{
    return [=](auto f)
    {
        return f(ts...);
    };
};

auto const chain = [](auto lhs, auto rhs)
{
    return lhs([=](auto... ts)
    {
        return rhs([=](auto... us)
        {
            return pack(ts..., us...);
        });
    });
};

auto const success = [](auto rest, auto data)
{
    return pack(true_{}, rest, data);
};

auto const fail = [](auto rest)
{
    return pack(false_{}, rest, pack());
};

auto const return_ = [](auto val)
{
    return [=]
    {
        return val;
    };
};

namespace detail
{
    template<class Subject, class Enable, class... Ts>
    struct pack_params
    {
        using type = decltype(pack(std::declval<Ts>()...));
        
        static type call(Subject const&, Ts... ts)
        {
            return pack(ts...);
        }
    };
    
    template<class Subject, class... Ts>
    struct pack_params<Subject, enable_if_valid_t<
        decltype(std::declval<Subject const>().transform_params(std::declval<Ts>()...))>, Ts...>
    {
        using type = decltype(pack(std::declval<Subject const>().transform_params(std::declval<Ts>()...)));
        
        static type call(Subject const& subject, Ts... ts)
        {
            return pack(subject.transform_params(ts...));
        }
    };
}

template<class Derived>
struct parser;

template<class Subject, class... Ts>
struct caller : parser<caller<Subject, Ts...>>
{
    using pack_params = detail::pack_params<Subject, void, Ts...>;
    using pack_type = typename pack_params::type;
    
    Subject subject;
    pack_type args;
    
    caller(Subject const& subject, Ts... ts)
      : subject(subject), args(pack_params::call(subject, ts...))
    {}
    
    caller(Subject const& subject, pack_type args)
      : subject(subject), args(args)
    {}

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return args([=](auto... as)
        {
            return subject.parse(s, ctx, as...);
        });
    }
};

struct parser_base {};

template<class Derived>
struct parser : parser_base
{
    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }

    template<class... Ts>
    caller<Derived, Ts...> operator()(Ts... ts) const
    {
        return {derived(), ts...};
    }
};

struct null_context
{
    std::nullptr_t operator()(...) const
    {
        return nullptr;
    }
};

template<class Base, class Tag, class T>
struct context : Base
{
    T val;
    
    context(Base base, T val) : Base(base), val(val) {}

    T operator()(Tag) const
    {
        return val;
    }
};

template<class Tag>
struct context_tag
{
    template<class Context = null_context, class T>
    context<Context, Tag, T> operator()(Context const& ctx, T val) const
    {
        return {ctx, val};
    }
};

struct skipper_t : context_tag<skipper_t> {};
constexpr skipper_t skipper = {};

template<class S>
auto skip_over_impl(S s, std::nullptr_t)
{
    return s;
}

template<class S, class P>
auto skip_over_impl(S s, P p)
{
    return p.parse(s, null_context{})([p](auto ret, auto rest, auto data)
    {
        return skip_over_impl(rest, select(ret, p, nullptr));
    });
}

template<class S, class Context>
auto skip_over(S s, Context const& ctx)
{
    return skip_over_impl(s, ctx(skipper));
}

struct string_parser : parser<string_parser>
{
    template<class S>
    struct parse_impl;
    
    template<char... cs>
    struct parse_impl<str<cs...>>
    {
        template<char... etc>
        static auto apply(str<cs..., etc...>)
        {
            return success(str<etc...>{}, pack(str<cs...>{}));
        }
        
        template<class S>
        static auto apply(S s)
        {
            return fail(s);
        }
    };

    template<class S, class Context, class Str>
    static auto parse(S s, Context const& ctx, Str)
    {
        return parse_impl<Str>::apply(skip_over(s, ctx));
    }
};

template <typename Class>
struct char_parser : parser<char_parser<Class>>, Class
{
    template<char val>
    using val_t = std::integral_constant<char, val>;
    
    template<char c, char... cs, class Context, class... Ts>
    static auto parse_impl(str<c, cs...> s, Context const& ctx, Ts... ts)
    {
        return if_
        (
            bool_<Class::test(c, ctx, ts...)>{}
          , return_(success(str<cs...>{}, pack(val_t<c>{})))
          , return_(fail(s))
        );
    }
    
    template<class Context, class... Ts>
    static auto parse_impl(str<> s, Context const& ctx, Ts...)
    {
        return fail(s);
    }

    template<class S, class Context, class... Ts>
    static auto parse(S s, Context const& ctx, Ts... ts)
    {
        return parse_impl(skip_over(s, ctx), ctx, ts...);
    }
};

struct char_space_class
{
    template<class Context>
    static constexpr bool test(char ch, Context const& ctx)
    {
        return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
    }
};

template<char c1, char c2, class Prev>
struct check_interval
{
    static constexpr bool test(char c)
    {
        return (c1 <= c && c <= c1) || Prev::test(c);
    }
};

template<char ch, class Prev>
struct check_one
{
    static constexpr bool test(char c)
    {
        return ch == c || Prev::test(c);
    }
};

struct check_none
{
    static constexpr bool test(char)
    {
        return false;
    }
};

template<class T>
struct charset {};

template<class Prev, char... cs>
struct build_charset;

template<class Prev, char c, char... cs>
struct build_charset1
{
    using type =
        typename build_charset<check_one<c, Prev>, cs...>::type;
};

template<class Prev, char... cs>
struct build_charset
{
    using type = typename build_charset1<Prev, cs...>::type;
};

template<class Prev>
struct build_charset<Prev>
{
    using type = Prev;
};

template<class Prev, char c1, char c2, char... cs>
struct build_charset<Prev, c1, '-', c2, cs...>
{
    using type =
        typename build_charset<check_interval<c1, c2, Prev>, cs...>::type;
};

struct any_char
{
    template<class Context>
    static constexpr bool test(char ch, Context const& ctx)
    {
        return true;
    }
    
    template<char val, class Context>
    static constexpr bool test(char ch, Context const& ctx, std::integral_constant<char, val> const&)
    {
        return ch == val;
    }
    
    template<char... cs>
    static charset<typename build_charset<check_none, cs...>::type>
    transform_params(str<cs...>)
    {
        return {};
    }
    
    template<class Context, class Charset>
    static constexpr bool test(char ch, Context const& ctx, charset<Charset> const&)
    {
        return Charset::test(ch);
    }
};
    
template<class Positive>
struct negated_char : Positive
{
    template<class Char, class Context, class... Ts>
    static constexpr bool test(Char ch, Context const& ctx, Ts const&... ts)
    {
        return !Positive::test(ch, ctx, ts...);
    }
};

template<class Positive>
struct negate_char
{
    using type = negated_char<Positive>;
};

template<class Positive>
struct negate_char<negated_char<Positive>>
{
    using type = Positive;
};

template<class Base>
inline char_parser<class negate_char<Base>::type>
operator~(char_parser<Base> const&)
{
    return {};
}

template<class Base, class... Ts>
inline caller<char_parser<class negate_char<Base>::type>, Ts...>
operator~(caller<char_parser<Base>, Ts...> const& c)
{
    return {{}, c.args};
}
    
constexpr bool is_digit(char c)
{
    return '0' <= c && c <= '9';
}

template<class T>
struct integer_parser : parser<integer_parser<T>>
{
    template<T val>
    using val_t = std::integral_constant<T, val>;
    
    template<char c, char... cs, T val, class First>
    static auto parse_impl(str<c, cs...> s, val_t<val> v, First first)
    {
        return select
        (
            bool_<is_digit(c)>{}
          , [](auto ch)
            {
                return parse_impl(str<cs...>{}, val_t<val * 10 + (ch.value - '0')>{}, false_{});
            }
          , [=](auto ch)
            {
                return if_
                (
                    first
                  , return_(fail(s))
                  , return_(success(s, pack(v)))
                );
            }
        )(val_t<c>{});
    }

    template<class U, class First>
    static auto parse_impl(str<> s, U val, First first)
    {
        return if_
        (
            first
          , return_(fail(s))
          , return_(success(s, pack(val)))
        );
    }
    
    template<class S, class Context>
    static auto parse(S s, Context const& ctx)
    {
        return parse_impl(skip_over(s, ctx), val_t<0>{}, true_{});
    }
};

struct attr_parser : parser<attr_parser>
{
    template<class S, class Context, class T>
    static auto parse(S s, Context const& ctx, T attr)
    {
        return success(skip_over(s, ctx), pack(attr));
    }
};

constexpr attr_parser attr = {};

namespace extension
{
    template<class T, class Enable = void>
    struct literal;
    
    template<char... cs>
    struct literal<str<cs...>>
    {
        using type = string_parser;
    };
    
    template<char val>
    struct literal<std::integral_constant<char, val>>
    {
        using type = char_parser<any_char>;
    };
    
    template<class T, class Enable = void>
    struct as_parser;
    
    template<class T>
    struct as_parser<T, std::enable_if_t<std::is_base_of<parser_base, T>::value>>
    {
        using type = T;
        
        static T const& call(T const& val)
        {
            return val;
        }
    };
}

template<class T>
using as_parser_t = typename extension::as_parser<T>::type;

template<class T>
inline decltype(auto) as_parser(T const& val)
{
    return extension::as_parser<T>::call(val);
}

template<class Directive, class Subject>
struct directive_parser
  : parser<directive_parser<Directive, Subject>>
{
    Directive directive;
    Subject subject;
    
    directive_parser(Directive const& directive, Subject const& subject)
      : directive(directive), subject(subject)
    {}

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return directive.parse(subject, s, ctx);
    }
};

template<class Directive, class... Ts>
struct directive_caller
{
    using pack_params = detail::pack_params<Directive, void, Ts...>;
    using pack_type = typename pack_params::type;
    
    Directive directive;
    pack_type args;
    
    directive_caller(Directive const& directive, Ts... ts)
      : directive(directive), args(pack_params::call(directive, ts...))
    {}
    
    directive_caller(Directive const& directive, pack_type args)
      : directive(directive), args(args)
    {}

    template<class Subject>
    directive_parser<directive_caller, as_parser_t<Subject>>
    operator[](Subject const& subject) const
    {
        return {*this, as_parser(subject)};
    }
        
    template<class Subject, class S, class Context>
    auto parse(Subject const& subject, S s, Context const& ctx) const
    {
        return args([=](auto... as)
        {
            return directive.parse(subject, s, ctx, as...);
        });
    }
};

template<class Derived>
struct directive
{
    Derived const& derived() const
    {
        return *static_cast<Derived const*>(this);
    }

    template<class Subject>
    directive_parser<Derived, as_parser_t<Subject>>
    operator[](Subject const& subject) const
    {
        return {derived(), as_parser(subject)};
    }
    
    template<class... Ts>
    directive_caller<Derived, Ts...>
    operator()(Ts... ts) const
    {
        return {derived(), ts...};
    }
};

struct skip_directive : directive<skip_directive>
{
    template<class Skipper>
    static as_parser_t<Skipper> transform_params(Skipper const& skipper)
    {
        return as_parser(skipper);
    }
        
    template<class Subject, class S, class Context, class Skipper>
    auto parse(Subject const& subject, S s, Context const& ctx, Skipper const& skip) const
    {
        return subject.parse(s, skipper(ctx, skip));
    }
};

constexpr skip_directive skip = {};

struct lit_parser : parser<lit_parser>
{
    template<class T>
    static caller<typename extension::literal<T>::type, T> transform_params(T val)
    {
        return {{}, val};
    }
    
    template<class S, class Context, class Parser>
    static auto parse(S s, Context const& ctx, Parser p)
    {
        return p.parse(s, ctx)([=](auto ret, auto rest, auto data)
        {
            return pack(ret, rest, pack());
        });
    }
};

template<class Left, class Right>
struct sequence_parser : parser<sequence_parser<Left, Right>>
{
    Left left;
    Right right;
    
    sequence_parser(Left left, Right right)
      : left(left), right(right)
    {}

    template<class Back, class S, class T, class Context>
    auto parse_impl(true_, S rest, T attr, Context const& ctx) const
    {
        return right.parse(rest, ctx)([attr](auto ret, auto rest, auto data)
        {
            return if_
            (
                ret
              , return_(success(rest, chain(attr, data)))
              , return_(fail(Back{}))
            );
        });
    }
    
    template<class Back, class S, class T, class Context>
    auto parse_impl(false_, S, T, Context) const
    {
        return fail(Back{});
    }

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return left.parse(s, ctx)([=](auto... ts)
        {
            return this->parse_impl<S>(ts..., ctx);
        });
    }
};

template<class Left, class Right>
struct alternate_parser : parser<alternate_parser<Left, Right>>
{
    Left left;
    Right right;
    
    alternate_parser(Left left, Right right)
      : left(left), right(right)
    {}
    
    template<class S, class T, class Context>
    auto parse_impl(true_, S rest, T data, Context) const
    {
        return success(rest, data);
    }
    
    template<class S, class T, class Context>
    auto parse_impl(false_, S rest, T, Context const& ctx) const
    {
        return right.parse(rest, ctx);
    }

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return left.parse(s, ctx)([=](auto... ts)
        {
            return this->parse_impl(ts..., ctx);
        });
    }
};

template<class Left, class Right>
struct difference_parser : parser<difference_parser<Left, Right>>
{
    Left left;
    Right right;
    
    difference_parser(Left left, Right right)
      : left(left), right(right)
    {}

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return right.parse(s, ctx)([=](auto ret, auto rest, auto data)
        {
            return if_
            (
                ret
              , return_(fail(s))
              , [=]
                {
                    return left.parse(s, ctx);
                }
            );
        });
    }
};

template<class Left, class Right>
struct list_parser : parser<list_parser<Left, Right>>
{
    Left left;
    Right right;
    
    list_parser(Left left, Right right)
      : left(left), right(right)
    {}

    template<class S, class T, class Context, class Success>
    auto parse_impl(true_, S rest, T attr, Context const& ctx, Success) const
    {
        return right.parse(rest, ctx)([=](auto ret, auto rest, auto data)
        {
            return if_
            (
                ret
              , [=]
                {
                    return left.parse(rest, ctx)([=](auto ret, auto rest, auto data)
                    {
                        return this->parse_impl(ret, rest, chain(attr, data), ctx, true_{});
                    });
                }
              , return_(success(rest, attr))
            );
        });
    }
    
    template<class T, class Context, class Success>
    auto parse_impl(true_, str<> s, T data, Context, Success) const
    {
        return pack(true_{}, s, data);
    }

    template<class S, class T, class Context, class Success>
    auto parse_impl(false_, S rest, T data, Context, Success success) const
    {
        return pack(success, rest, data);
    }

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return left.parse(s, ctx)([=](auto... ts)
        {
            return this->parse_impl(ts..., ctx, false_{});
        });
    }
};

template<class Subject>
struct optional_parser : parser<optional_parser<Subject>>
{
    Subject subject;
    
    optional_parser(Subject subject) : subject(subject) {}

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return subject.parse(s, ctx)([this](auto ret, auto rest, auto data)
        {
            return pack(true_{}, rest, data);
        });
    }
};

template<class Subject, class Nullable>
struct repeat_parser : parser<repeat_parser<Subject, Nullable>>
{
    Subject subject;
    
    repeat_parser(Subject subject) : subject(subject) {}
    
    template<class S, class T, class Context, class Success>
    auto parse_impl(true_, S s, T attr, Context const& ctx, Success) const
    {
        return subject.parse(s, ctx)([=](auto ret, auto rest, auto data)
        {
            return this->parse_impl(ret, rest, chain(attr, data), ctx, true_{});
        });
    }
    
    template<class T, class Context, class Success>
    auto parse_impl(true_, str<> s, T data, Context, Success) const
    {
        return pack(true_{}, s, data);
    }
    
    template<class S, class T, class Context, class Success>
    auto parse_impl(false_, S s, T data, Context, Success success) const
    {
        return pack(success, s, data);
    }

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return subject.parse(s, ctx)([=](auto ret, auto rest, auto data)
        {
            return this->parse_impl(ret, rest, data, ctx, Nullable{});
        });
    }
};

template<class Subject>
struct not_parser : parser<not_parser<Subject>>
{
    Subject subject;
    
    not_parser(Subject subject) : subject(subject) {}

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return subject.parse(s, ctx)([=](auto ret, auto rest, auto data)
        {
            return pack(bool_<!ret.value>{}, s, pack());
        });
    }
};

template<class Subject>
struct and_parser : parser<and_parser<Subject>>
{
    Subject subject;
    
    and_parser(Subject subject) : subject(subject) {}

    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return subject.parse(s, ctx)([=](auto ret, auto rest, auto data)
        {
            return pack(ret, s, pack());
        });
    }
};

template<class Left, class Right>
inline sequence_parser<as_parser_t<Left>, as_parser_t<Right>>
operator>>(Left const& left, Right const& right)
{
    return {as_parser(left), as_parser(right)};
}

template<class Left, class Right>
inline alternate_parser<as_parser_t<Left>, as_parser_t<Right>>
operator|(Left const& left, Right const& right)
{
    return {as_parser(left), as_parser(right)};
}

template<class Left, class Right>
inline difference_parser<as_parser_t<Left>, as_parser_t<Right>>
operator-(Left const& left, Right const& right)
{
    return {as_parser(left), as_parser(right)};
}

template<class Left, class Right>
inline list_parser<as_parser_t<Left>, as_parser_t<Right>>
operator%(Left const& left, Right const& right)
{
    return {as_parser(left), as_parser(right)};
}

template<class Subject>
inline optional_parser<as_parser_t<Subject>>
operator-(Subject const& subject)
{
    return {as_parser(subject)};
}

template<class Subject>
inline repeat_parser<as_parser_t<Subject>, true_>
operator*(Subject const& subject)
{
    return {as_parser(subject)};
}

template<class Subject>
inline repeat_parser<as_parser_t<Subject>, false_>
operator+(Subject const& subject)
{
    return {as_parser(subject)};
}

template<class Subject>
inline not_parser<as_parser_t<Subject>>
operator!(Subject const& subject)
{
    return {as_parser(subject)};
}

template<class Subject>
inline and_parser<as_parser_t<Subject>>
operator&(Subject const& subject)
{
    return {as_parser(subject)};
}



auto const ret = [](auto ret, auto rest, auto data)
{
    return ret;
};

auto const rest = [](auto ret, auto rest, auto data)
{
    return rest;
};

auto const attr_ = [](auto ret, auto rest, auto data)
{
    return data;
};

auto const print = [](auto... ts)
{
    std::initializer_list<bool>{(std::cout << ts << std::endl, true)...};
};

constexpr string_parser string = {};
constexpr integer_parser<int> int_ = {};
constexpr lit_parser lit = {};

using space_type = char_parser<char_space_class>;
constexpr space_type space = {};
using char_type = char_parser<any_char>;
constexpr char_type char_ = {};

namespace extension
{
    template <typename T>
    struct as_parser<T, enable_if_valid_t<typename literal<T>::type>>
    {
        using type = caller<lit_parser, T>;
        
        static type call(T val)
        {
            return {{}, val};
        }
    };
}

template<class LHS, class RHS>
struct rule_def
{
    LHS lhs;
    RHS rhs;
};

void parse_rule(...);

template<class T>
struct no_pack
{
    T&& data;
};

template<class R, class T>
no_pack<T> on_success(R, T&& t)
{
    return {std::forward<T>(t)};
}

template<class Tag>
struct rule : parser<rule<Tag>>
{
    template<class S, class T>
    static auto return_success(S rest, T data)
    {
        return success(rest, pack(data));
    }
    
    template<class S, class T>
    static auto return_success(S rest, no_pack<T> ref)
    {
        return success(rest, std::forward<T>(ref.data));
    }
    
    template<class S, class T>
    auto parse_impl(true_, S rest, T data) const
    {
        return return_success(rest, on_success(*this, data));
    }
    
    template<class S, class T>
    auto parse_impl(false_, S rest, T) const
    {
        return fail(rest);
    }
    
    template<class S, class Context>
    auto parse(S s, Context const& ctx) const
    {
        return parse_rule(*this, s, ctx)([this](auto... ts)
        {
            return this->parse_impl(ts...);
        });
    }
    
    template<class RHS>
    rule_def<rule, RHS> operator=(RHS rhs) const
    {
        return {*this, rhs};
    }
};

#define AZ_RULEDEF(n, i)                                                        \
    BOOST_PP_CAT(BOOST_PP_CAT(BOOST_PP_CAT(_rule_def, n), _), i)
    /***/
#define AZ_DEFINE_(r, data, def)                                                \
    auto const AZ_RULEDEF(__LINE__, r)(def);                                    \
    template<class S, class Context>                                            \
    inline auto parse_rule(                                                     \
        decltype(AZ_RULEDEF(__LINE__, r).lhs), S s, Context const& ctx)         \
    {                                                                           \
        return AZ_RULEDEF(__LINE__, r).rhs.parse(s, ctx);                       \
    }
    /***/
#define AZ_DEFINE(...) BOOST_PP_SEQ_FOR_EACH(                                   \
    AZ_DEFINE_, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
    
namespace fmt { namespace ast
{
    template<class S>
    struct text
    {
        template<class Ostream, class Tuple>
        static void generate(Ostream& out, Tuple const&)
        {
            out << S{};
        }
    };

    template<std::size_t N>
    struct placeholder
    {
        template<class Ostream, class Tuple>
        static void generate(Ostream& out, Tuple const& t)
        {
            static_assert(N < std::tuple_size<Tuple>::value, "index out of bound");
            out << std::get<N>(t);
        }
    };
}}

namespace fmt { namespace grammar
{
    constexpr rule<class start> start = {};
    constexpr rule<class text> text = {};
    constexpr rule<class placeholder> placeholder = {};

#define SL AZ_STRING
#define IL AZ_INTEGRAL

    AZ_DEFINE
    (
        start = *(placeholder | text)
      , text = *~char_(IL('{'))
      , placeholder = IL('{') >> int_ >> IL('}')
    )

#undef SL
#undef IL

    template<class T>
    auto on_success(rule<class text>, T list)
    {
        return list([](auto... c)
        {
            return ast::text<str<c.value...>>{};
        });
    }
    
    template<class T>
    auto on_success(rule<class placeholder>, T list)
    {
        return list([](auto c)
        {
            return ast::placeholder<c.value>{};
        });
    }
}}

namespace fmt
{
    template<class List, class Tuple>
    struct format
    {
        List list;
        Tuple t;
        
        friend std::ostream& operator<<(std::ostream& out, format const& fmt)
        {
            fmt.list([&](auto... c)
            {
                (void)std::initializer_list<bool>{(c.generate(out, fmt.t), true)...};
            });
            return out;
        }
    };

    template<class S, class... Ts>
    auto static_format(S s, Ts&&... ts)
    {
        auto list = grammar::start.parse(s, null_context{})(attr_);
        using tuple = std::tuple<Ts...>;
        return format<decltype(list), tuple>{list, tuple{std::forward<Ts>(ts)...}};
    }
}
#define STATIC_FORMAT(str, ...) fmt::static_format(AZ_STRING(str), __VA_ARGS__)

int main(int argc, char** argv)
{
    std::cout << STATIC_FORMAT("This is {0}, and {2}, {1}...", 1, "wow", 9.9);

    return 0;
}