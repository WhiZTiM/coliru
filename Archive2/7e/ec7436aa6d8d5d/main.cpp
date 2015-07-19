#include <iostream>
using namespace std;


class Type1 {
    int meaing_of_life_;
    int world_;

    public:
    Type1() = default;
    explicit Type1(int mol, int world) : meaing_of_life_(mol), world_(world) {}

    int get_world(){ return world_;}
    int get_mol(){ return meaing_of_life_;}
};


auto get_world= [](auto&& object) {

    return [&object] (...) {
        return [&object]() {
            return object;
        };
    };
};

auto get_mol = [](...) {

    return [](auto&& object) {
        return [&object]{
            return object;
        };
    };
};

/*
 *  create a object of type T
 */
auto make_object = [](auto type, auto&&... args) {

    return [args...](auto&& getter){
        decltype(type) obj{args...};
        return getter(obj.get_world())(obj.get_mol())();
    };
};


int main()
{
    auto object = make_object(Type1{}, 2015, 42);

    cout << object(get_world) << endl;
    cout << object(get_mol) << endl;
}
