#include <thread>
#include <future>
#include <iostream>
#include <memory> 
 
    struct release_deleter {
        template <typename T>
        void operator()(T* t) { 
            if (t) t->Release(); 
        }
    };
 
    template <typename T, typename Deleter = release_deleter>
    struct release_ptr 
    {
        T* t_{};

        release_ptr() noexcept {};
        release_ptr(T* t) noexcept : t_{t} {}
        release_ptr(release_ptr const&) = delete;
        release_ptr(release_ptr&& other) noexcept : t_{other.t_} { other.t_ = nullptr; }

        release_ptr& operator=(release_ptr const&) = delete;
        release_ptr& operator=(release_ptr&& other) noexcept { (std::swap)(t_,other.t_); return *this; }

        ~release_ptr() { if (t_) Deleter{}(t_); t_ = nullptr; }

        void reset(T* t = nullptr) noexcept { if (t_) { Deleter{}(t_); } t_ = t; }

        T* release() noexcept { T* tmp = t_; t_ = nullptr; return tmp; }
        T* get() const noexcept { return t_; }

        T*& expose_ptr() noexcept { if (t_) { Deleter{}(t_); t_ = nullptr; } return t_; } 
        
        T& operator*() const noexcept { return *t_; }
        T* operator->() const noexcept { return t_; }
        
        operator T*() const noexcept { return t_; }
    };
    
    struct foo {
        void Release() { std::cout << "released..\n"; }
    };

void gimme_a_foo(foo& f, foo** ptr) {
    *ptr = &f;   
}

int main() {

    foo f;
    release_ptr<foo> ptr;
    
    gimme_a_foo(f,&ptr.expose_ptr());
    std::cout << "--\n";
    
}