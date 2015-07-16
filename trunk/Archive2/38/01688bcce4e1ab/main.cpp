
#include <iostream>
class Window{
    public:
    void init(){std::cout << "Initializing Window\n";}
    void quit(){std::cout << "Quitting Window\n";}
};

class Renderer{
    public:
    void init(){std::cout << "Initializing Renderer\n";}
    void quit(){std::cout << "Quitting Renderer\n";}
};

class Input{
    public:
    void init(){std::cout << "Initializing Input\n";}
    void quit(){std::cout << "Quitting Input\n";}
};

class Audio{
    public:
    void init(){std::cout << "Initializing Audio\n";}
    void quit(){std::cout << "Quitting Audio\n";}
};

class Initializer{
    Window win_;
    Renderer ren_;
    Input in_;
    Audio aud_;
    public:
    Initializer(){
        win_.init();
        ren_.init();
        in_.init();
        aud_.init();
    }
    ~Initializer(){
        aud_.quit();
        in_.quit();
        ren_.quit();
        win_.quit();
    }
    Window& window(){return win_;}
    Renderer& renderer(){return ren_;}
    Input& input(){return in_;}
    Audio& audio(){return aud_;}
};

int main(){
    Initializer myInits;
}