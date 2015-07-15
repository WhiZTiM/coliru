template<class T> 
class MyClass{
    public: 
        //ctor 
//        ... 
        void memberFunction(T& functor, double value)noexcept(noexcept(functor(value)));
    private: 
        T functor; 
};