
template<class T>
using alias = T;

class Yo {

    public:
        ~Yo() { }
};

template<class A>
class Lo {
    protected:
        A a;
};

template<class A>
class Foobar : public Lo<A> {
    public:
        typedef Lo<A> super;
        
        using type = alias<A>;
        
        inline void expl() {
                super::a.~type();
        }
};

int main() {
    Foobar<Yo> A;
    A.expl();
}