#include <vector>

class DefConst{
    
};
class NonDefConst{
public:
    NonDefConst(int x){}    
};
class Copyable{
public:
    explicit Copyable(const DefConst & x){}
    Copyable(const Copyable &) = default;
    Copyable & operator=(const Copyable &) = delete;
};
class NonCopyable{
public:
    explicit NonCopyable(const DefConst & x){}
    NonCopyable(const NonCopyable &) = delete;
    NonCopyable & operator=(const NonCopyable &) = delete;
};
class Movable{
public:
    explicit Movable(const DefConst & x){}
    Movable(const Movable &) = delete;
    Movable & operator=(const Movable &) = delete;
    Movable(Movable &&) = default;
    Movable & operator=(Movable &&) = delete;
};
class NonMovable{
public:
    explicit NonMovable(const DefConst & x){}
    NonMovable(const NonMovable &) = delete;
    NonMovable & operator=(const NonMovable &) = delete;
    NonMovable(NonMovable &&) = delete;
    NonMovable & operator=(NonMovable &&) = delete;
};
Copyable func(Copyable c){
    return c;    
}
/*NonCopyable func(NonCopyable c){
    return c;    
}*/ // will not work because NonCopyable is not copyable
Movable func(Movable && c){
    return std::move(c);
}
/*NonMovable func(NonMovable && c){
    return std::move(c);
}*/ // will not work becaus NonMovable is not movable
int main(){
    DefConst D;
    //NonDefConst N; // won't work since NonDefConst is not default constructible
    Copyable c1 = func(Copyable(D));
    //NonCopyable nc(D);
    //NonCopyable nc1 = func(NonCopyable(D));// will not work because NonCopyable is not copyable
    Movable m1 = func(Movable(D)); // calls Movable move constructor because the result of func is rvalue
    //NonMovable nm1 = func(NonMovable(D)); // won't work because NonMovable is not movable
}