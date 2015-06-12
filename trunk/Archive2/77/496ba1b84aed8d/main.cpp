#include <string>
#include <vector>
#include <unordered_map>

#include <boost/variant.hpp>

namespace llvm
{
    struct Function;
    struct AllocaInst;
}

struct Function
{
    std::string returnType;
    std::string name;
    std::vector<std::string> argTypes;

    llvm::Function* function;
};

struct Variable
{
    std::string type;
    std::string name;

    llvm::AllocaInst* alloca;
};

typedef boost::variant<
    Function,
    Variable
> Symbol;

struct Scope
{
    std::size_t parentIdx;
    std::unordered_map<std::string, Symbol> symbols;
    std::vector<std::size_t> childIdxs;
};

int main()
{
    std::vector<Scope> scopes;
    scopes.push_back({ 0, {}, {} });
    
    return 0;
}