#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <utility>
#include <initializer_list>

struct base{
    virtual std::string name() = 0;
    virtual void run() = 0;
    virtual ~base(){}
};

struct base_store{
    std::map<std::string, std::unique_ptr<base>> contents;
    
    void run(std::string name){
        auto ittr = contents.find(name);
        if(ittr == contents.end()){
            std::cout << "nothing mapped for '" << name << "'\n"; return;
        }
        ittr->second->run();
    }
    
    template<typename T>
    void attach(T t){
        std::unique_ptr<base> ptr(&t);
        ptr.release();
    }
    
    // How can I get this to take lots of types to add?
    template<typename T>
    void attach_type(){
        std::unique_ptr<base> ptr = std::make_unique<T>();
        auto name = ptr->name();
        auto results = contents.insert(std::make_pair(name, std::move(ptr)));
        if(!results.second){
            std::cout << "Dude, don't add '" << name << "' more than once!\n";
        }
    }
};

struct one:base{
    std::string name(){ return "one"; }
    void run(){ std::cout << "In one\n"; }
};

struct two:base{
    std::string name(){ return "two"; }
    void run(){ std::cout << "In two\n"; }
};

struct three:base{
    std::string name(){ return "three"; }
    void run(){ std::cout << "In three\n"; }
};

int main(){
    auto store = base_store{};
//    store.attach_type<one, one, one>();
    auto my_module = one{};
    store.attach(my_module);
//    store.attach_type<two, three>();
    store.attach_type<three>();
    store.attach_type<two>();
//    store.run("one");
//    store.run("two");
//    store.run("two");
}
