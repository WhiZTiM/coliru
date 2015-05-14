#include <iostream>
#include <string>
#include <vector>
#include <boost/variant.hpp>

namespace test {
    template<typename TaskT, typename PrevDispatcher, typename F, typename RealArgType>
    class template_dispatcher;

    struct give {};
    struct get {};
    
    using task_type = boost::variant<give, get>;
    
    template<typename RealArgType>
    class dispatcher {
        template<typename TaskT, typename PrevDispatcher, typename F, typename RAT>
        friend class template_dispatcher;
    public:
        dispatcher(task_type* t) : task_(t) {}
         
        ~dispatcher() {
            dispatch();
        }
         
        void dispatch() {
        }
         
        template<typename TaskT, typename F>
        template_dispatcher<TaskT, dispatcher, F, RealArgType> handle(F f) {
            return template_dispatcher<TaskT, dispatcher, F, RealArgType>(f);
        }        
    private:
        task_type* task_;
    };
    
    template<typename TaskT, typename PrevDispatcher, typename F, typename RealArgType>
    class template_dispatcher {
        template<typename TT, typename PD, typename FF, typename RAT>
        friend class template_dispatcher;
    public:
        using this_type = template_dispatcher<TaskT,PrevDispatcher,F,RealArgType>;
    
        template_dispatcher(F f) : f_(f) {}
        
        ~template_dispatcher() {
            dispatch<TaskT>();
        }
        
        template<typename ArgType>
        void dispatch(typename std::enable_if<std::is_same<ArgType, RealArgType>::value>::type* = 0) {
            f_();
        }
        
        template<typename ArgType>
        void dispatch(typename std::enable_if<!std::is_same<ArgType, RealArgType>::value>::type* = 0) {
            //f_();
        }
         
        template<typename TT, typename FF>
        template_dispatcher<TT, this_type, FF, RealArgType> handle(FF f) {
            return template_dispatcher<TT, this_type, FF, RealArgType>(f);
        }        
    private:
        F f_;
    };
    
    
    class task_processor {
    public:
        template<typename T>
        auto process(T&& task) {
            task_ = std::forward<T>(task);
            return dispatcher<std::remove_reference_t<T>>(&task_);
        }
    private:
        task_type task_;
    };
    
}

int main() {
    test::task_processor p;
    p.process(test::give{})
        .handle<test::give>([](){ std::cout << "test::give handler\n"; })
        .handle<test::get>([](){ std::cout << "test::get handler\n"; });
        
    p.process(test::get{})
        .handle<test::give>([](){ std::cout << "test::give handler\n"; })
        .handle<test::get>([](){ std::cout << "test::get handler\n"; });
        
}
