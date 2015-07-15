template<class T> 
class MyClass{
    public: 
        //ctor 
//        ... 
        void memberFunction(double value)noexcept(noexcept(functor(value)));
    private: 
        T functor; 
};