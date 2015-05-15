template<class TYPE>
struct Manager;

class A{
    template<class TYPE>
    friend struct Manager;
    
    int aVar;
public:
    A(){}
    virtual ~A(){};
};

template<class BASE>
class B: public BASE{
    template<class TYPE>
    friend struct Manager;
    
    int bVar;
public:
    B():BASE(){};
    virtual ~B(){};
};

template<class BASE>
class C: public BASE{
    template<class TYPE>
    friend struct Manager;
    
    int cVar;
public:
    C():BASE(){};
    virtual ~C(){};
};

template<class TYPE>
struct Manager{
    TYPE current;

    Manager(){
        current.aVar++;
        current.bVar++;
        current.cVar++;    
    }
    ~Manager(){}
};

int main()
{
    Manager<C<B<A>>> m;
}