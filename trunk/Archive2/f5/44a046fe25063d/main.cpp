#include <algorithm>
#include <type_traits>
#include <utility>

#include <iostream>
#include <functional>

namespace detail {
    struct CustomDeleter {
        template <typename Dealloc, typename T>
        CustomDeleter(Dealloc dealloc, T*) : 
            deallocator_ {cp_dealloc_(dealloc)},
            dealloc_{&del_ptr_<Dealloc, T>},
            del_deallocator_{is_ptr_or_fun_t<Dealloc>::value ? 
                    &nop : 
                    &default_dealloc<Dealloc>} {}

        CustomDeleter(const CustomDeleter &) = delete;
        auto operator =(const CustomDeleter &) -> CustomDeleter& = delete;
        
        CustomDeleter(CustomDeleter &&mv) :
            deallocator_{mv.deallocator_},
            dealloc_{mv.dealloc_},
            del_deallocator_{mv.del_deallocator_} {
            mv.deallocator_ = nullptr;
        }

        auto operator =(CustomDeleter &&rhs) -> CustomDeleter& {
            if (deallocator_ != rhs.deallocator_) {
                std::swap(deallocator_,     rhs.deallocator_);
                std::swap(dealloc_,         rhs.dealloc_);
                std::swap(del_deallocator_, rhs.del_deallocator_);
            }
            return *this;
        }

        auto operator ()(void *p) -> void {
            dealloc_(deallocator_, p);
        }

        auto get() const -> void* { return deallocator_; }

        template <typename T>
        static auto default_dealloc(void *p) -> void {
            delete reinterpret_cast<T*>(p);
        }
    private:
        using DeallocFunc           = void(*)(void*, void*);
        using DeallocatorDeleteFunc = void(*)(void*);
    
        void                  *deallocator_;
        DeallocFunc            dealloc_;
        DeallocatorDeleteFunc  del_deallocator_;
        
        template <typename enable, typename T>
        using enable_if_t = typename std::enable_if<enable::value, T>::type;
        
        template <bool use_T1, typename T1, typename T2>
        using conditional_t = typename std::conditional<use_T1, T1, T2>::type;
        
        template <typename Bool>
        using not_t = conditional_t<!Bool::value, std::true_type, std::false_type>;
            
        template <typename disable, typename T>
        using disable_if_t = enable_if_t<not_t<disable>, T>;
        
        template <typename T>
        using remove_fun_ptr_t = conditional_t<std::is_pointer<T>::value,
            typename std::remove_pointer<T>::type, T>;
            
        template <typename T>
        using is_function = conditional_t<std::is_function<remove_fun_ptr_t<T>>::value,
            std::true_type, std::false_type>;
        
        template <typename T>
        using is_ptr_or_fun_t = conditional_t<
            std::is_pointer<T>::value || is_function<T>::value,
            std::true_type, std::false_type>;
  
        static auto nop(void*) -> void {}
                
        template <typename Dealloc>
        static auto cp_dealloc_(Dealloc *p) -> void* {
            return reinterpret_cast<void*>(p);
        }
        
        template <typename Dealloc>
        static auto cp_dealloc_(Dealloc&& p) -> disable_if_t<
                std::is_pointer<Dealloc>, void*> {
            using Deallocator = typename std::decay<Dealloc>::type;
            return reinterpret_cast<void*>(new Deallocator{std::forward<Dealloc>(p)});
        }
        
        template <typename Dealloc, typename T>
        static auto del_ptr_(void *d, void *p) -> disable_if_t<is_function<Dealloc>, void> { 
            reinterpret_cast<Dealloc*>(d)->operator ()(reinterpret_cast<T*>(p));
        }
        
        template <typename Dealloc, typename T>
        static auto del_ptr_(void *d, void *p) -> enable_if_t<is_function<Dealloc>, void> { 
            reinterpret_cast<Dealloc>(d)(reinterpret_cast<T*>(p));
        }
    };
}  // namespace detail


template <typename T>
struct UniquePtr {        
    UniquePtr() : UniquePtr{nullptr} {}        
    
    explicit UniquePtr(T *ptr) : 
        ptr_{ptr},
        deleter_{&detail::CustomDeleter::default_dealloc<T>, ptr} {}
    
    template <typename Deleter>
    UniquePtr(T *ptr, Deleter deallocator) : 
        ptr_{ptr},
        deleter_{deallocator, ptr} {}
    
    UniquePtr(const UniquePtr &) = delete;
    auto operator =(const UniquePtr &) -> UniquePtr& = delete;
    
    UniquePtr(UniquePtr &&mv) : 
        ptr_{mv.ptr_},
        deleter_{std::move(mv.deleter_)} {
        mv.ptr_ = nullptr;
    }
    
    auto operator =(UniquePtr &&rhs) -> UniquePtr& {
        std::swap(ptr_, rhs.ptr_);
        std::swap(deleter_, rhs.deleter_);
        
        return *this;
    }
    
    ~UniquePtr() { deleter_(ptr_); }
    
    template <typename Deleter>
    auto get_deleter() const -> Deleter* {
        return reinterpret_cast<Deleter*>(deleter_.get());
    }
private:
    T *ptr_;
    detail::CustomDeleter deleter_;
};



struct Test {
    explicit Test(const char *name) : 
        name_{name} { 
        std::cout << "Test:" << name << " constructed\n";
    }
    
    Test(Test &o) = delete;
    auto operator =(const Test &) -> Test&  = delete;
    ~Test() { std::cout << "Test:" << name_ << " destroyed\n"; }
private:
    const char *name_;
};

auto delTest(Test *p) -> void {
    std::cout << "delTest -> ";
    delete p;
}

int main() {
    using TestPtr = UniquePtr<Test>;
    TestPtr ptr_1{new Test{"ptr_1"}};
    TestPtr ptr_2{new Test{"ptr_2"}, [](Test *p) { std::cout << "lambda -> "; delete p; }};
    TestPtr ptr_3{new Test{"ptr_3"}, &delTest};
    TestPtr ptr_4{new Test{"ptr_4"}, std::bind(&delTest, std::placeholders::_1)};
    TestPtr ptr_5{new Test{"ptr_5"}, std::function<void(Test*)>{&delTest}};
}
