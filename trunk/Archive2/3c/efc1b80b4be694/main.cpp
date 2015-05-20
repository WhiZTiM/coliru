#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>

/**** LIBRARY CODE - HEADER ****/

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

void callback_wrapper(const double x, double& fx, void* p_user);

int function_with_callback_err(void(*c)(const double, double&, void*), const double x, double& fx,
                               void* p_user = NULL);

template <class Callable, class ValueType>
int function_with_callback(Callable& c, const ValueType x, ValueType& fx) {
    // Inefficiency (1) - allocation of callback data object
    std::unique_ptr<CallbackData_Base> callback_data = std::make_unique<CallbackData<Callable>>(c);
    int status = function_with_callback_err(callback_wrapper, x, fx, callback_data.get());
    if (callback_data->error) {
        std::string message = "Callback threw exception: ";
        message += std::string(callback_data->msg_buffer);
        throw user_exception(message);
    }
    return status;
    // Inefficiency (3) - deletion of callback data object
}

/**** LIBRARY CODE - SOURCE ****/

void CallbackData_Base::set_error(const char *msg) {
    error = true;
    const size_t len = std::max<size_t>(1023, strlen(msg));
    std::copy(msg, msg + len, msg_buffer);
    msg_buffer[len] = 0;
}

int function_with_callback_err(void(*c)(const double, double&, void*), const double x, double& fx,
                               void* p_user) {
    c(x, fx, p_user);
    return 0;
}

void callback_wrapper(const double x, double& fx, void* p_user) {
    CallbackData_Base *callback_data = static_cast<CallbackData_Base*>(p_user);
    try {
        callback_data->call(x, fx); // Inefficiency (2) - virtual function call
    }
    catch (const std::runtime_error& e) {
        callback_data->set_error(e.what());
    }
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