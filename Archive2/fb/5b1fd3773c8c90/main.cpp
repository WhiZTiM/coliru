#include <cstdint>
#include <string>
#include <iostream>
#include <sstream>
#include <memory>
#include <map>

// Base class for pets (its constructor isn't actually relevant)
struct Pet {
    virtual ~Pet() = default;
};

struct PetFactory {
    // Pointer to a function capable of deserializing a Pet
    using PetCtr = std::unique_ptr<Pet> (*)(std::istream &);
    
    // Deserialize a Pet from a stream
    static auto make(std::istream &stream) {
        std::string str;
        stream >> str;
        return ctrMap().at(str)(stream);
    }
    
    // Deserialize a Pet from a string
    static auto make(std::string str) {
        std::istringstream stream(str);
        return make(stream);
    }
    
private:
    friend struct RegisterPet;
    using PetCtrMap = std::map<std::string, PetCtr>;

    // Meyer's singleton to hold the function map
    static PetCtrMap &ctrMap() {
        static PetCtrMap theMap;
        return theMap;
    }
};

// Static registrar
struct RegisterPet {
    RegisterPet(std::string name, PetFactory::PetCtr ctr) {
        PetFactory::ctrMap().emplace(name, ctr);
    }
};

// Some derived classes ////////////////////////////

using Color = std::string;

struct Fish : Pet {
    Fish(int weight, Color color, int fins, bool saltWater) {
        std::cout << "I'm a " << weight << "kg " << color << " fish with " << fins << " fins, living in " << (saltWater ? "salty" : "fresh") << " water.\n";
    }
};

struct Cat : Pet {
    Cat(int weight, Color color, int lives) {
        std::cout << "I'm a " << weight << "kg " << color << " cat with " << lives << " lives.\n";
    }
};

struct Dog : Pet {
    Dog(int weight, Color color, std::string breed, std::string character) {
        std::cout << "I'm a " << weight << "kg " << color << " " << breed << " and I'm " << character << ".\n";
    }
};

////////////////////////////////////////////////////

// Constructor wrapping functions //////////////////

// Main function : deserializes and calls the constructor
template <class T, class... Args, std::size_t... Idx>
auto streamCtr_(std::istream &stream, std::index_sequence<Idx...> const &) {
    // Enable "true" and "false" as boolean input
    stream >> std::boolalpha;
    // Temporary argument storage
    std::tuple<Args...> args;
    
    // Classic pack-unpacker, reads each argument from the stream
    using unpack = int[];
    unpack{0, (void(stream >> std::get<Idx>(args)), 0)...};
    
    // Forward the parameters to the constructor
    return std::make_unique<T>(std::move(std::get<Idx>(args))...);
}

// Wrapper function : generates the index_sequence
template <class T, class... Args>
auto streamCtr(std::istream &stream) {
    return std::unique_ptr<Pet>(streamCtr_<T, Args...>(stream, std::index_sequence_for<Args...>{}));
}

// Register each class with its name and the type of its constructor's parameters
RegisterPet r1("fish", streamCtr<Fish, int, Color, int, bool>);
RegisterPet r2("cat", streamCtr<Cat, int, Color, int>);
RegisterPet r3("dog", streamCtr<Dog, int, Color, std::string, std::string>);

int main() {
    
    // Profit !
    PetFactory::make("fish 1 silver 5 true");
    PetFactory::make("cat 4 tabby 9");
    PetFactory::make("dog 17 white husky playful");
}
