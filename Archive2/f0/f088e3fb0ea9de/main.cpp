#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

/**** LIBRARY CODE ****/

struct user_exception : public std::runtime_error {
    user_exception(const char *msg) : std::runtime_error(msg) {}
    user_exception(const std::string& msg) : std::runtime_error(msg.c_str()) {}
};

struct CallbackData_Base {
  CallbackData_Base() : error(false) {}
  virtual ~CallbackData_Base() {}
  virtual void call(const double x, double& fx) = 0;
  void set_error(const char *msg);
  
  bool error;
  char msg_buffer[1024];
};

void CallbackData_Base::set_error(const char *msg) {
    error = true;
    const size_t len = std::max<size_t>(1023, strlen(msg));
    std::copy(msg, msg + len, msg_buffer);
    msg_buffer[len] = 0;
}

template <class Callable>
struct CallbackData : public CallbackData_Base {
    CallbackData(Callable& callable) : c(callable) {}
    virtual ~CallbackData() {}
    virtual void call(const double x, double& fx);
    
    Callable& c;
};

template <class Callable>
void CallbackData<Callable>::call(const double x, double& fx) {
    fx = c(x);
}

int function_with_callback_err(void(*c)(const double, double&, void*), const double x, double& fx,
                               void* p_user = NULL) {
    c(x, fx, p_user);
    return 0;
}

void callback_wrapper(const double x, double& fx, void* p_user) {
    CallbackData_Base *callback_data = static_cast<CallbackData_Base*>(p_user);
    try {
        callback_data->call(x, fx);
    }
    catch (const std::runtime_error& e) {
        callback_data->set_error(e.what());
    }
}

template <class Callable, class ValueType>
int function_with_callback(Callable& c, const ValueType x, ValueType& fx) {
    CallbackData_Base* callback_data = new CallbackData<Callable>(c);
    int status = function_with_callback_err(callback_wrapper, x, fx, callback_data);
    if (callback_data->error) {
        std::string message = "Callback threw exception: ";
        message += std::string(callback_data->msg_buffer);
        delete callback_data;
        throw user_exception(message);
    }
    else {
        delete callback_data;
    }
    return status;
}


/**** USER CODE ****/

struct Callback {
    double operator()(const double x) {
        if (x < 0.0)
          throw std::runtime_error("x must be non-negative");
          return std::sqrt(x);
    }
};

int main() {
    try {
        Callback callback;
        double fx;
        int status = function_with_callback(callback, 2.0, fx);
        std::cout << status << " " << fx << "\n";
        status = function_with_callback(callback, -10.0, fx);
        std::cout << status << " " << fx << "\n";
    }
    catch (const user_exception& e) {
        std::cout << e.what() << "\n";
    }
}