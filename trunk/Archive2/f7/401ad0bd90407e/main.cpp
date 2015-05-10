#include <memory>
#include <iostream>
#include <string>

class Dummy{
public:
    Dummy() : name("Clown"){}
    ~Dummy() {
        std::cout << "Dummy DTOR" << std::endl;
    }
    std::string name;

};

class Contain{
    public:
        Contain(int a, Dummy &du):age(a),d(&du){
            std::cout << "Contain CTOR" << std::endl;
        }
//        ~Contain(){
//            std::cout << "Contain DTOR" << std::endl;
//        }
        int get_age(){
            return age;
        }

        void set_age(int a){
            age = a;
        }

        std::string get_name(){
            return d -> name;
        }
    private:
        int age;
        Dummy *d;
};

int main(){
    Dummy dol;
    std::unique_ptr<Contain> upp(new Contain(27, dol));
    std::cout << upp -> get_age() << std::endl;
    Contain *contain_p = upp.get();
    std::cout << contain_p -> get_age() << std::endl;
    upp.reset();
    contain_p -> set_age(393);
    std::cout << "Reset unique ptr. Raw ptr value:" << std::endl;
    std::cout << contain_p -> get_age() << std::endl;
    std::cout << contain_p -> get_name() << std::endl;
}