#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <vector>
#include <boost/io/ios_state.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>

using any = boost::spirit::hold_any;

template<typename T>
T dynamic_any_cast(const any& operand) {
    std::stringstream ss{};
    ss << operand << std::endl;;
    T tmp{};
    ss >> tmp;
    return tmp;    
}

class value_base {
public:
    template<typename T>
    void set(const T& value) {
        set_impl(any{value});   
    }
    
    template<typename T>
    T get() const {
        return dynamic_any_cast<T>(get_impl());   
    }

protected:
    virtual void set_impl(const any& value) = 0;
    virtual any get_impl() const = 0;    
};

template<typename T>
class value : public value_base {
public:
    value() : value_{} {}
    
    explicit value(const T& value) : value_{value} {}
    
    value(const value&) = default;
    value(value&&) = default;
    
    value& operator=(const value&) = default;
    value& operator=(value&&) = default;
    
protected: 
    void set_impl(const any& value) override {
        value_ = dynamic_any_cast<T>(value);
    }
    
    any get_impl() const override {
        return any{value_};   
    }
    
private:
    T value_;
};

class sink {
public:
    void send(const std::vector<std::uint8_t>& payload) {
        boost::io::ios_iostate_saver saver{std::cout};
        std::cout << "SEND[" << std::uppercase << std::hex << std::setfill('0');
        for (const auto& v : payload) {
            std::cout << std::setw(2) << static_cast<int>(v);            
        }
        std::cout << "]" << std::endl;
    }
};

class command_class_base {
public:
    command_class_base(sink& sink) : sink_{sink} {}

    virtual void commit() = 0;
    virtual void update() = 0;
    
    std::unordered_map<
        std::string, std::shared_ptr<value_base>
    > values;

protected:
    void send(const std::vector<std::uint8_t>& payload) {
        sink_.send(payload);   
    }
    
private:
    sink& sink_;
};

class command_class_basic : public command_class_base {
public:
    command_class_basic(sink& sink) : command_class_base{sink} {
        values = {
            {"value", std::make_shared<value<int>>(0)}          
        };
    }
    
    void commit() override {
        std::uint8_t value = values["value"]->get<int>();
        send({0x20, 0x01, value}); // BASIC_SET
    }
    
    void update() override {
        send({0x20, 0x02});        // BASIC_GET
    }
};

int main(int argc, char* argv[]) {
    sink sink{};
    command_class_basic basic{sink};
    command_class_base& cc = basic;
    
    cc.values["value"]->set(255);
    cc.commit();
    
    return 0;
}
