template <class T, class A1, class A2> shared_ptr<T> factory(A1&& a1, A2&& a2) {
    return shared_ptr<T> (new T(std::forward<A1>(a1), std::forward<A2>(a2)));
}

struct A {
    A(int&, const double&);
};

void g() {
    shared_ptr<A> sp1 = factory<A> (2, 1.414);  // error: 2 will not bind to int&
    int i = 2;
    shared_ptr<A> sp2 = factory<A> (i, 1.414);  // OK
}