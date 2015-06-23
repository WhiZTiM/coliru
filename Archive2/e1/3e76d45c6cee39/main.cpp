#include <string>
#include <iostream>

class IAppendable {
public:
    virtual void append(const std::string&) = 0;
};

class ICloseable {
public:
    virtual void close() = 0;
};

template <class T>
std::enable_if_t<
    std::is_base_of<IAppendable, T>{} && std::is_base_of<ICloseable, T>{},
    void
> closeThis(T &t) {
    t.append("end");
    t.close();
}

class One : ICloseable {
public:
    void close() override { std::cout << "Closed\n"; }
};

class Both : IAppendable, ICloseable {
public:
    void append(const std::string &str) override { std::cout << "Appended : " << str << '\n'; }
    void close() override { std::cout << "Closed\n"; }
};

int main() {
    One one;
    //closeThis(one); // Won't compile
    
    Both both;
    closeThis(both);
}
