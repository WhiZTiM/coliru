#include <sstream>
#include <memory>
#include <iostream>
#include <boost/iostreams/device/array.hpp>

struct Level;

template<typename T>
struct Identity
{
    using type = T;    
};


template<typename T>
struct Parser
{
    T const& derived() const{
        return static_cast<T const&>(*this);
    }
};


template<typename T,std::size_t Depth = 0>
struct SimpleParser : Parser<SimpleParser<T>>
{
    SimpleParser(T& value)
    : value_{std::addressof(value)} {}
    
    template<typename Context>
    void startElement(const char* name, Context const& ctx)
    {
    }
    
    template<typename Context>
    void endElement(const char* name, Context const& ctx){
    }
    
    template<typename Context>
    void content(const char* name, Context const& ctx){
    }
    
private:
    T* value_;
};


template<typename Left, typename Right>
struct Sequence : Parser<Sequence<Left,Right>>
{
    Sequence(Left left,Right right)
    : left_{std::move(left)}
    , right_{std::move(right)}
    {}
    
    
    template<typename Context>
    void startElement(const char* name,Context const& ctx)
    {
        auto level = ctx.get(Identity<Level>{});
        std::cout << "start:" << level << std::endl;
        left_.startElement(name,ctx);
        right_.startElement(name,ctx);
    }
    
    template<typename Context>
    void endElement(const char* name,Context const& ctx)
    {
        auto level = ctx.get(Identity<Level>{});
        std::cout << "start:" << level << std::endl;

        left_.endElement(name,ctx);
        right_.endElement(name,ctx);
    }
    
    template<typename Context>
    void content(const char* name,Context const& ctx)
    {
        left_.content(name,ctx);
        right_.content(name,ctx);
    }
    
    Left left_;
    Right right_;
};

template<typename Left,typename Right>
auto operator >> (Parser<Left>&& l,Parser<Right> && r)
{
    return Sequence<Left,Right>{l.derived(),r.derived()};
}



template<typename ID,typename T,typename Next>
struct Context
{
    Context(T const& val,Next const& next)
    : value_{val}
    , next_{next} {}
    
    
    T const& value_;
    Next const& next_;
    
    auto& get(Identity<ID>) const
    {
        return value_;
    }
    
    template<typename Identity>
    auto get(Identity id) const{
        return next_.get(id);
    }
};

template<typename ID,typename T,typename Next>
auto makeContext(T&& t,Next&& next)
{
    return Context<ID,T,Next>{std::forward<T>(t),std::forward<Next>(next)};
}


struct EmptyContext
{
    struct Undefined{};
    
    template<typename ID>
    constexpr Undefined get(ID) const {
        return Undefined{};    
    }
};



template<typename Content>
struct Document
{
    Document(Content content)
    : content_{content} {}
    
    void startElement(const char* name)
    {
        level_++;
        auto ctx = makeContext<Level>(level_,EmptyContext{});
        content_.startElement(name,ctx);
    }
    
    void endElement(const char* name)
    {
        auto ctx = makeContext<Level>(level_,EmptyContext{});
        content_.endElement(name,ctx);
        level_--;        
    }
    
    void content(const char* name)
    {
        auto ctx = makeContext<Level>(level_,EmptyContext{});
        content_.content(name);
    }
    
    Content content_;  
    std::size_t level_{0};
};

template<typename Content>
auto xmlDoc(Content&& content)
{
    return Document<Content>{std::forward<Content>(content)};    
}


int main()
{
    int a{};
    int b{};
    int c{};
    
    auto doc = xmlDoc(SimpleParser<int>{a} >> SimpleParser<int>{b} >> SimpleParser<int>{c});
    
    doc.startElement("root");
    
    doc.startElement("x");
    doc.endElement  ("x");
    
    doc.startElement("y");
    doc.endElement  ("y");

    doc.startElement("z");
    doc.endElement  ("z");

    doc.endElement  ("root");
    return 0;
}