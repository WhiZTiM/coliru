#include <iostream>

struct Var {
    Var( const char * name ) : name_{ name } {
        next_ = head_;
        head_ = this;
    }
    
    const char * Name() const { return name_; }
    
    template <typename F>
    static void Do( F&& f) {
        auto ptr = head_;
        while (ptr)
        {
            std::forward<F>(f)( *ptr );
            ptr = ptr->next_;
        }
    }
private:
    const char * name_;    
    Var * next_;

    static Var* head_; 
};
Var* Var::head_ = nullptr;

Var r_something{ "r_something" };
Var r_somethingelse{ "r_somethingelse" };

int main() {
    Var::Do( []( auto & v ) { std::cout << v.Name() << std::endl; } );
}
