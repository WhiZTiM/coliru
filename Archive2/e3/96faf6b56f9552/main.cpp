#include <string>
#include <iostream>
#include <vector>

class Var{
public:
    Var(const char* val) : str{val}{}
    Var(const std::string &val) : str{val}{}
    Var(const int &val) : str{std::to_string(val)}{}
    
    const std::string& getstr() const {return str;}
private:
    std::string
        str;
};

std::ostream& operator<<(std::ostream& out, const Var& var){
    return out << var.getstr();
}

void log(const std::vector<Var> &varset){
    for(auto &&var : varset){
        std::cout << var << '\t';   
    }
}
 
int main() {
    Var a = "aaaugh";
	log({0, "hi", 10, a});
	return 0;
}