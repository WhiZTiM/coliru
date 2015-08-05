template <typename T>
    struct Foo
    {
        int x_;
    
    	int x() const;
    };
    
    int a;
    
    template <typename T>
    decltype(a) Foo<T>::x() const
    {
    	return x_;
    }
    
    int main()
    {
    }