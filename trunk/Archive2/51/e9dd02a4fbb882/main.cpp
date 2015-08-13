#include <iostream>
#include <sstream>
#include <cassert>
#include <tuple>
////////////////////////////////////////////////////////////////////////////////
///  Stack Frame Context
////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct Identity
{
    using type = T;
};

template<typename ID,typename T,typename Next>
struct Context{
    constexpr Context(T const& t,Next const& next)
    : value_{t}
    , next_ {next}
    {}

    constexpr std::size_t size() const
    {
        return 1 + next_.size();
    }

    constexpr auto const& get(Identity<ID>) const
    {
        return value_;
    }

    template<typename Identity>
    constexpr auto get(Identity id) const
    {
        return next_.get(id);
    }

    T const& value_;
    Next const& next_;
};

template<typename ID,typename T,typename Next>
constexpr auto makeContext(T const& t, Next const& next)
{
    return Context<ID,T,Next>{t,next};
}

template<typename Next>
struct ForwardContext
{
    constexpr ForwardContext(const Next& next)
    : next_{next} {}

    constexpr std::size_t size() const
    {
        return 1 + next_.size();
    }

    template<typename Identity>
    constexpr auto get(Identity id) const
    {
        return next_.get(id);
    }

    Next const& next_;
};

template<typename T>
constexpr auto makeForwardContext(T const& next)
{
    return ForwardContext<T>{next};
}

struct EmptyContext
{
    struct Undefined{};

    constexpr int size() const
    {
        return -1;
    }

    template<typename Identity>
    constexpr auto get(Identity) const
    {
        return Undefined{};
    }
};


////////////////////////////////////////////////////////////////////////////////
/// Depth Context
////////////////////////////////////////////////////////////////////////////////
struct CallChainTail
{
    constexpr std::size_t const& level() const{
        return level_;
    }

    constexpr static std::size_t depth{1};

    std::size_t const& level_;
};

template<typename Next,std::size_t Step = 1>
struct CallChain
{
    constexpr std::size_t const& level() const{
        return next_.level();
    }

    constexpr static std::size_t depth{Step + Next::depth};

    Next const& next_;
};

template<std::size_t Step,typename Next>
auto makeCallChain(Next const& next)
{
    return CallChain<Next,Step>{next};
}

////////////////////////////////////////////////////////////////////////////////
/// Constexpr string hash
////////////////////////////////////////////////////////////////////////////////

/// FNV-1a hash
constexpr std::uint64_t hash(const char* buf)
{
    constexpr std::uint64_t basis = 0xCBF29CE484222325;
    constexpr std::uint64_t prime = 0x100000001B3;

    std::uint64_t h = basis;
    while(char ch = *buf++){
        h ^= ch;
        h *= prime;
    }
    return h;
}

constexpr std::size_t operator "" _hash(const char *str, std::size_t len)
{
    return hash(str);
}

////////////////////////////////////////////////////////////////////////////////
/// Parameter pack
////////////////////////////////////////////////////////////////////////////////
template<std::size_t N, typename ...Args>
constexpr auto get_arg(Args&& ... args)
{
    return std::forward<decltype(std::get<N>(std::forward_as_tuple(args...)))>
                                (std::get<N>(std::forward_as_tuple(args...)));
}

////////////////////////////////////////////////////////////////////////////////
/// Parsers
////////////////////////////////////////////////////////////////////////////////

namespace Lexer{
//Events
struct StartElement {};
struct EndElement   {};
struct Content      {};

} // namespace Lexer

namespace Ctx{
struct Level;
} // namespace Ctx


template<typename T>
struct Parser
{
    constexpr T const& derived() const{
        return static_cast<T const&>(*this);
    }
};

template<typename Next>
struct LevelFilter : Parser<LevelFilter<Next>>
{
    constexpr LevelFilter(Next next)
    : next_{std::move(next)} {}

    template<typename ... Args>
    auto operator()(Args&& ...args) const
    {
        auto const& ctx = get_arg<1>(std::forward<Args>(args)...);
        if(ctx.depth >= ctx.level())
        {
            next_(std::forward<Args>(args)...);
        }
    }

    Next next_;
};

template<typename Next>
constexpr auto lvl(Next&& next)
{
    return LevelFilter<Next>{std::forward<Next>(next)};
}

template<typename Next,std::size_t Step = 1>
struct ComplexParser : Parser<ComplexParser<Next,Step>>
{
    constexpr ComplexParser(Next next)
    : next_{std::move(next)} {}

    template<
        typename Ev
      , typename Ctx
      , typename ... Args
    >
    auto operator()(Ev&& ev,Ctx&& ctx,Args&& ...args) const
    {
        auto const this_ctx = makeCallChain<Step>(std::forward<Ctx>(ctx));
        return next_(std::forward<Ev>(ev), this_ctx, std::forward<Args>(args)...);
    }

    Next next_;
};

template<typename Next,std::size_t Step = 1>
constexpr auto cmplx(Next&& next)
{
    return ComplexParser<decltype(lvl(std::forward<Next>(next))),Step>{lvl(std::forward<Next>(next))};
}

template<typename Next,std::size_t Hash>
struct NameCheck : Parser<NameCheck<Next,Hash>>
{
    constexpr NameCheck(Next next)
        : next_{std::move(next)} {}

    template<typename ... Args>
    auto operator()(Args&& ... args) const
    {
        const auto& ctx  = get_arg<1>(std::forward<Args>(args)...);
        if(ctx.depth == ctx.level())
        {
            const auto&& name = get_arg<2>(std::forward<Args>(args)...);
            if(hash(name) != Hash)
            {
                std::stringstream err; err << "Unexpected tag: " << name;
                err << " expected:" << Hash;
                throw std::runtime_error(err.str());
            }
        }

        return next_(std::forward<Args>(args)...);
    }

    template<typename ... Args>
    auto operator()(Lexer::Content ev,Args&& ... args) const
    {
        return next_(ev,std::forward<Args>(args)...);
    }

    Next next_;
};

template<std::size_t Hash, typename Next>
constexpr auto name(Next&& next)
{
    return NameCheck<Next,Hash>{std::forward<Next>(next)};
}

template<typename T>
struct Document
{
    constexpr Document(T parser)
    : parser_{std::move(parser)} {}

    template<typename ... Args>
    auto operator()(Lexer::StartElement ev, Args&& ... args) const
    {
        level_++;
        auto const ctx = CallChainTail{level_};
        parser_(ev,ctx,std::forward<Args>(args)...);
    }

    template<typename ... Args>
    auto operator()(Lexer::EndElement ev, Args&& ... args) const
    {
        auto const ctx = CallChainTail{level_};
        parser_(ev,ctx,std::forward<Args>(args)...);
        level_--;
    }

    template<typename Ev, typename ... Args>
    auto operator()(Ev ev,Args&& ... args) const
    {
        auto const ctx = CallChainTail{level_};
        parser_(ev,ctx,std::forward<Args>(args)...);
    }
private:
    T parser_;
    mutable std::size_t level_{0};
};

template<typename T>
constexpr auto doc(T&& t){
    return Document<T>{std::forward<T>(t)};
}

template<typename L,typename R>
struct Seq : Parser<Seq<L,R>>
{
    constexpr Seq(L l,R r)
    : l_{std::move(l)},
      r_{std::move(r)} {}


    template<typename ... Args>
    auto operator()(Lexer::StartElement ev,Args&& ... args) const
    {
        return fwd(ev,std::forward<Args>(args)...);
    }

    template<typename ... Args>
    auto operator()(Lexer::EndElement ev,Args&& ... args) const
    {
        fwd(ev,std::forward<Args>(args)...);

        auto&& ctx = get_arg<0>(args...);
        if(ctx.depth == ctx.level())
        {
            selectLeft_ = false;
        }

    }

    template<typename ...Args>
    auto operator()(Args&& ... args) const
    {
        return fwd(std::forward<Args>(args)...);
    }
private:
    template<typename ...Args>
    auto fwd(Args&& ... args) const{
        if(selectLeft_)
        {
            return l_(std::forward<Args>(args)...);
        }else
        {
            return r_(std::forward<Args>(args)...);
        }
    }

    L l_;
    R r_;

    mutable bool selectLeft_{true};
};

template<typename L,typename R>
constexpr auto operator >> (Parser<L> const& l,Parser<R> const& r)
{
    return Seq<L,R>{l.derived(),r.derived()};
}

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/logic/tribool.hpp>

template<typename T>
struct Simple : Parser<Simple<T>>
{
    Simple(T& value) : value_{std::addressof(value)} {}

    template<typename ... Args>
    void operator()(Lexer::StartElement,Args&& ... args) const
    {}

    template<typename ... Args>
    void operator()(Lexer::EndElement,Args&& ... args) const
    {
        boost::iostreams::stream<
            boost::iostreams::array_source
        > stream{buf_.data(),buf_.size()};
        stream >> (*value_);
    }

    template<typename Ctx>
    void operator()(Lexer::Content, Ctx&&,const char* str) const
    {
        buf_ += str;
    }

    T* value_;
    mutable std::string buf_;
};

template<typename T>
auto constexpr elem(T & t)
{
    return Simple<T>{t};
}


template<typename L,typename R>
struct Choice : Parser<Choice<L,R>>
{
    Choice(L const& l,R const& r)
    : l_{l}
    , r_{r} {}

    using hash = typename L::hash;

    template<typename ... Args>
    auto operator()(Lexer::StartElement ev,Args&& ... args) const
    {
        auto&& name = get_arg<1>(std::forward<Args>(args)...);

        if(boost::logic::indeterminate(selectLeft_)){
            selectLeft_ = hash(name) == L::hash::value ? true : false;
        }

        return fwd(ev,std::forward<Args>(args)...);
    }

    template<typename ...Args>
    auto operator()(Args&& ... args) const
    {
        return fwd(std::forward<Args>(args)...);
    }

private:
    template<typename ... Args>
    auto fwd(Args&& ... args) const
    {
        if(selectLeft_ == true)
        {
            return l_(std::forward<Args>(args)...);
        }else
        if(selectLeft_ == false)
        {
            return r_(std::forward<Args>(args)...);
        }
    }

    L l_;
    R r_;
    mutable boost::logic::tribool selectLeft_{};
};

template<typename L,typename R>
constexpr auto operator | (Parser<L> const& l,Parser<R> const& r)
{
    return Choice<L,R>{l.derived(),r.derived()};
}

template<std::size_t Hash,typename Next>
struct HashBinder : Parser<HashBinder<Hash,Next>>
{
    constexpr HashBinder(Next const& next)
    : next{next} {}

    template<typename ...Args>
    auto operator()(Args&& ...args) const
    {
        return next(std::forward<Args>(args)...);
    }

    Next next;
};

template<std::size_t Hash,typename Next>
constexpr auto bindHash(Next&& next)
{
    return HashBinder<Hash,Next>{std::forward<Next>(next)};
}


template<typename T>
void debugType(T&& t){
    static_assert(sizeof(T) == 0 and sizeof(T) == 1,"");
}

int main(int argc,char** argv)
{

    //TODO minOccurs maxOccurs
    //TODO attribute parsers (mixed)
    //TODO tag selector
    //TODO name check without hash
    //TODO specializations boost::optional
    //TODO specializations boost::variant
    //TODO specializations SequenceContainer,AssociativeContainer
    //TODO actions
    //TODO ignore
    
    
    std::string a;
    std::string b;

    //debugType(x);
    auto const x = doc(name<hash("a")>(cmplx(
        name<hash("b")>(elem(a)) >> name<hash("c")>(elem(b))
    )));

    x(Lexer::StartElement{},"a");
    x(Lexer::StartElement{},"b");
    x(Lexer::Content{},"123");
    x(Lexer::EndElement{},"b");
    x(Lexer::StartElement{},"c");
    x(Lexer::Content{},"321");
    x(Lexer::EndElement{},"c");
    x(Lexer::EndElement{},"a");
    
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    
    return 0;
}
