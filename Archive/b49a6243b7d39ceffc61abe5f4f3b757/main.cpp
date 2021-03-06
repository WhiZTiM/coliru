#include <boost/variant.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>


template<typename R, typename A>
struct Visitor : boost::static_visitor<>
{
    Visitor(const A & a) : a(a) {}
    
    template<typename F>
    void operator()(const F & f)
    {
        r = std::move(f(a));
    }
    
    const A & a;
    R r;
};


template<typename R, typename Variant, typename A>
R visit(Variant & var, const A & a)
{
    Visitor<R, A> visitor{a};
    var.apply_visitor(visitor);
    return visitor.r;
}


struct Void {}; // for Void return type


//
// Example
//
struct Zip
{    
    std::string operator()(const std::string &s) const
    {
        return "zipped: " + s; // dummy implementation
    }
};


struct Plain
{    
    std::string operator()(const std::string &s) const
    {
        return "plain: " + s;
    }
};


struct StandardOut
{
    template<typename T>
    Void operator()(const T & t) const
    {
        std::cout << t << std::flush;
        return Void{};
    }
};


struct FileOut
{
    FileOut(const std::string & filename) : filename(filename) {}
    
    template<typename T>
    Void operator()(const T & t) const
    {
        std::ofstream of(filename.c_str());
        of << t;
        return Void{};
    }
    
    std::string filename;
};


struct Archive
{
    template<typename Compression, typename Output>
    Archive(const Compression & c, const Output & o) :
        compression{c},
        output{o}
    {
    }
    
    void store(const std::string & s)
    {
        visit<Void>(output, apply<std::string>(compression, s));
    }
    
    boost::variant<Zip, Plain> compression;
    boost::variant<FileOut, StandardOut> output;
};


int main()
{
    Archive archive(Zip{}, StandardOut{});
    archive.store("test");
}
