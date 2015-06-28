#include <iostream>
#include <string>
#include <vector>
#include <type_traits>

template <bool base>
struct inverter : public std::true_type {};

template <>
struct inverter <true> : public std::false_type {};

template <typename A>
class CRTP{
    A* impl() {return static_cast<A*>(this);}
    A const * impl() const {return static_cast<A const*>(this);}
public:
    void bar() const {impl()->bar();}
};

class Alpha : public CRTP<Alpha>{
public:
    Alpha(std::string::size_type length) : contents_(length, 'w'){}
    void bar() const {std::cout << contents_ << " Alpha\n";}
private:
    std::string
        contents_;
};

class Beta : public CRTP<Beta>{
public:
    Beta(const std::string & name) : contents_{name}{}
    void bar() const {std::cout << contents_ << " Beta\n";}
private:
    std::string
        contents_;
};

template <typename Implementer>
class execute{
    public:
    static typename std::enable_if<std::is_base_of<CRTP<Implementer>, Implementer>::value>::type Bar(const CRTP<Implementer> &impler){impler.bar();}
    static typename std::enable_if<inverter<std::is_base_of<CRTP<Implementer>, Implementer>::value>::value>::type Bar(const Implementer &impler){std::cout << "Not Implementer\n";}
};

template <typename Implementer>
void executeBar(const Implementer &a){
    execute<Implementer>::Bar(a);
}

int main(){
    Beta
        beta{"Zooks!"};
    executeBar(Alpha{3});
    executeBar(beta);
}