#include <istream>
#include <ostream>
#include <iostream>
#include <functional>
#include <map>
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
#include <type_traits>
#include <iomanip>
#include <boost/io/ios_state.hpp>
#include <boost/optional.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>

using any = boost::spirit::hold_any;

template<typename F, typename Sig>
class any_function;

template<typename F, typename R, typename... Args>
class any_function<F, R(Args...)> {
public:
    any_function(F func) : func_{func} {}

    void operator()(std::istream& args, std::ostream& out) const {
        invoke(args, out, std::is_void<R>{});
    }
    
private:
    void invoke(std::istream& args, std::ostream& out, std::false_type) const {
        out << func_(get<Args>(args)...);
    }
    
    void invoke(std::istream& args, std::ostream& out, std::true_type) const {
        func_(get<Args>(args)...);
    }

    template<typename T>
    T get(std::istream& args) const {
        static_assert(std::is_default_constructible<T>::value, 
                      "Argument must be default constructible");
        T arg{};
        if (!(args >> arg)) {
            throw std::invalid_argument("Cannot extract argument");  
        }
        return arg;
    }

    F func_;
};

template<typename Sig, typename F>
any_function<F, Sig> make_any_function(F func) {
    return {func};
}

template<typename... Args>
void pack_args(std::ostream&, Args&&...);

template<typename X, typename... Xs>
void pack_args(std::ostream& os, X&& x, Xs&&... xs) {
    os << x << std::endl;
    pack_args(os, xs...);
}

template<>
inline void pack_args(std::ostream&) {}

class zwave_module_access_provider
{
public:
    void send(const std::vector<std::uint8_t> payload) {
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
    command_class_base(zwave_module_access_provider& provider) : provider_{provider} {}

    template<typename R, typename... As>
    R invoke(const std::string& name, As&&... args) {
        if (methods.count(name) == 0) {
            throw std::runtime_error("Method not supported");   
        }
        std::stringstream a{}, r{};
        pack_args(a, std::forward<As>(args)...);
        methods.find(name)->second(a, r);
        return do_return<R>(r, std::is_void<R>{});           
    }
    
    virtual void on_notify(const any& value) const = 0;
    
protected:
    void send(const std::vector<std::uint8_t>& payload) {
        provider_.send(payload);   
    }

    std::unordered_map<
        std::string, 
        std::function<void(std::istream& args, std::ostream& out)>
    > methods;
    
private:
    template<typename R>
    R do_return(std::istream& input, std::false_type) {
        R ret{};
        input >> ret;
        return ret;
    }
    
    template<typename R>
    void do_return(std::istream&, std::true_type) {}

    zwave_module_access_provider& provider_;
};

class command_class_basic : public command_class_base {
public:
    command_class_basic(zwave_module_access_provider& provider) 
      : command_class_base{provider} {
        methods = {
            {"get"  , make_any_function<void()>(std::bind(&command_class_basic::get, this))},
            {"set"  , make_any_function<void(std::uint8_t)>(std::bind(&command_class_basic::set, this, std::placeholders::_1))},
            {"\x03" , make_any_function<void(std::uint8_t)>(std::bind(&command_class_basic::report, this, std::placeholders::_1))}
        };
    }
    
private:
    void get() {
        send({0x20, 0x02});
    }
    
    void set(std::uint8_t value) {
        send({0x20, 0x01, value});
    }
    
    void report(std::uint8_t value) const {
        on_notify(any{value});
    }
};

class command_class_basic_printer : public command_class_basic {
public:
    command_class_basic_printer(zwave_module_access_provider& provider)
      :  command_class_basic{provider}
    {}
    
    void on_notify(const any& value) const override {
        std::cout << "Value changed: " << value << std::endl;        
    }
};

int main(int argc, char* argv[]) {
    zwave_module_access_provider provider{};
    command_class_basic_printer basic{provider};
    
    basic.invoke<void>("set", 0);
    basic.invoke<void>("get");
    
    basic.invoke<void>("\x03", 0);
        
    return 0;   
}
