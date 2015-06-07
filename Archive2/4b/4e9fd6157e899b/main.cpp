#include <iostream>
#include <fstream>
#include <iterator>

struct name {
    name(int){
    };
    ~name(){
    }
};

struct shader {
    name n;
    shader(std::string src) : n(0) {
    }
    shader(std::ifstream filestream) : shader(std::string(std::istreambuf_iterator<char>(filestream.rdbuf()), std::istreambuf_iterator<char>())) {
    }
};

struct program {
    program(shader vs, shader fs) {
    }
};

struct renderer {
    program p;
    
    renderer() : p(shader(std::ifstream("main.cpp")), shader(std::ifstream("main.cpp"))) {
    }
};

int main() {
    renderer r;
    return 0;
}