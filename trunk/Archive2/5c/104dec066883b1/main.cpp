#include <iostream>
#include <string>

template<typename T>
class ISO{
public:
    ISO(){}
    ISO(T iso) : _iso{iso} {}
    virtual ~ISO() {}
    
    virtual void setIso(T iso) {
        _iso = iso;    
    };

protected:
    T _iso;
};

class Sx510ISO : public ISO<std::string>{
public:
    using ISO::ISO;
    ~Sx510ISO(){}
    void setIso(std::string iso) override {ISO::setIso(iso);}
    
    void printIso(){ std::cout << "iso is " << _iso << "\n";}
};

class Camera{
public:
    void setIso(Sx510ISO iso) {_iso = iso;}
    
private:
    Sx510ISO _iso;
};

int main()
{
    Sx510ISO iso{"100"};
    iso.printIso();
}