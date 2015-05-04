#include <iostream>
#include <string>

template<class ISO = std::string>
class Camera{
public:
    virtual void setIso(ISO iso) {_iso = iso;}
    
protected:
    ISO _iso;
};

class Sx510ISO : public Camera<std::string>{
public:
    Sx510ISO() = default;
    Sx510ISO(std::string iso) {setIso(iso);}
    
    void setIso(std::string iso) override { 
        std::cout << "Sx510ISO::setIso called" << "\n"; 
        Camera::setIso(iso);
    }
    
    void printIso(){ std::cout << "iso is " << _iso << "\n";}
};

class Sx530ISO : public Camera<>{
public:
    Sx530ISO() = default;
    Sx530ISO(std::string iso) {setIso(iso);}
    
    void setIso(std::string iso) override { 
        std::cout << "Sx510ISO::setIso called" << "\n"; 
        Camera::setIso(iso);
        //settar na camera o iso
    }
    
    std::string _iso;
    
    void printIso(){ std::cout << "iso is " << _iso << "\n";}
};


int main()
{

Sx510ISO iso;
Sx510ISO iso1{"1"};

Sx530ISO iso530{std::string{"530"}};

Sx510ISO iso2{"2"};

iso1 = iso2;
iso1.printIso();
iso530.printIso();
}