#include <iostream>
#include <string>

class LibraryInterface {
public:
    std::string name;
    std::string name1;
    std::string name2;
    std::string name3;
    std::string name4;
    std::string name5;
    std::string name6;
};

class Library : private LibraryInterface
{
public:
    Library() {name="BOB";}
private:
    LibraryInterface* getLibraryInterface() {return this;} //only LibraryCustomer can aquire the interface pointer
    friend class LibraryCustomer;
};

class LibraryCustomer
{
   protected:
       LibraryInterface* getLibraryInterface(Library& lib) {return lib.getLibraryInterface();} //only things deriving from LibraryCustomer can aquire the interface pointer
};

class Kid : public LibraryCustomer
{
public:
    void function(Library& lib) {
        LibraryInterface* interface = getLibraryInterface(lib);
        std::cout << interface->name;
    }
};

int main() {
    Library lib;
    Kid k;
    k.function(lib);
}