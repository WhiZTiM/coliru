struct A {
    template <int> void foo() {}
};

template <typename, typename>
struct B {
	void foo() {}
	template <int> void bar() ;
};

class C {
    
    int v = 0 ;
    
	template <int> friend void A::foo();
	template <typename T, typename U> friend void B<T,U>::foo();
    template <typename T, typename U> template <int N> friend void B<T,U>::bar();
};

template <typename T, typename U > template < int N > void B<T,U>::bar() { C c ; c.v = 8 ; }
