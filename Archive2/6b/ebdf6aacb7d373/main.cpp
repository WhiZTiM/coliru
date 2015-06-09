#include <iostream>

#define HAI do{std::cout << __PRETTY_FUNCTION__ << '\n'; }while(0)

namespace EMPTY_detail {
    template <class T>
    struct rank {
        rank(T) {};
    };
    
    template <class T>
    void EMPTY(T &t, char(*)[sizeof &T::EMPTY]) {
        t.EMPTY();
    }
    
    template <class T>
    void EMPTY(T &t, rank<void*>) {
        (void)t;
        HAI;
    }
}

template <class T>
void EMPTY(T &t) {
    EMPTY_detail::EMPTY(t, NULL);
}

struct HasEmpty {
    void EMPTY() { HAI; }
};

struct HasNoEmpty {
    
};

int main() {
    HasEmpty he;
    HasNoEmpty hne;
    int i;
    EMPTY(he);
    EMPTY(hne);
    EMPTY(i);
}
