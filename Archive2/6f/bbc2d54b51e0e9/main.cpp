template<class T>
class C
{   
    int i;
public:
    C(int d) : i(d) {}
    
    template<class U>
    void f(C<U> other)
    {
        i = static_cast<T>(other.i);
    }
    
    template<typename> friend class C;
};

int main()
{
    C<int> ci = 5;
    C<float> cf = 8.0f;
    
    ci.f(cf);
}