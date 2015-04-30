#include <iostream>
#include <string>
#include <vector>

#define ECHO(v) std::cout << (v) << std::endl;
#define ECHO_FN ECHO(__PRETTY_FUNCTION__)

using std::string;
using std::move;

class BaseService
{
public:
    string baseDataPublic = "bazis adat publikus";
protected:
    string baseDataProtected = "bazis adat vedett";
private:
    string baseDataPrivate = "bazis adat privat";
};

// End BaseService

class Service : public BaseService
{
public:
    string dataPublic = "adat publikus";
protected:
    string dataProtected = "adat vedett";
private:
    string dataPrivate = "adat privat";
    

protected:
    class Logger
    {
    public:
        Logger() = delete;
        static void log(Service*);
    };

public:
    void handleEvent();
};

void Service::handleEvent() {
    Logger::log(this);
}

void Service::Logger::log(Service* s) {
    ECHO(s->dataPublic);
    ECHO(s->dataProtected);
    ECHO(s->dataPrivate);
    
    ECHO(s->baseDataPublic);
    ECHO(s->baseDataProtected);
    //ECHO(s->baseDataPrivate);
}

// End Service and Service::Logger

class Foo
{
public:
    Foo(int v) {
        ECHO("Foo constructor running");
        ECHO(v);
    }
};

class S
{
public:
    /* explicit S(const string& v) {
    //S(const char *v) {
        ECHO("DEBUG: S constructor running");
        ECHO(v.c_str());
        //ECHO(v);
    } */
    
    S(const Foo &f) {
        ECHO("DEBUG: S constructor running");
    }
};

class Asd
{
public:
    enum AsdAsd {
        ERTEK_1, ERTEK_2, ERTEK_UNDEF
    };
    
private:
    static AsdAsd state;
    
public:
    Asd() /*: state(ERTEK_1)*/ {}
    
    const char * fn(AsdAsd e = state) {
        switch (e) {
            case ERTEK_1: return "ERTEK_1";
            case ERTEK_2: return "ERTEK_2";
            case ERTEK_UNDEF: return "ERTEK_UNDEF";
            default:
                return "EMPTYSTR";
        }
    }
};

Asd::AsdAsd Asd::state = Asd::ERTEK_1;

#define UNUSED(v) (void *) &(v)

int main_() {
    //Service s; s.handleEvent();
    S *s = new S(11);
    delete s;
    
    string a("egy"), b("egy");
    ECHO(a == b ? "true" : "false");
    Asd aaa;
    ECHO(aaa.fn());
    
    return 0;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class Sajt
{
protected:
    string name;

public:
    Sajt()                              { ECHO(__func__); }
    explicit Sajt(const char *name)   : name(name) { ECHO("Sajt::Sajt(" + this->name + ")"); }
    explicit Sajt(const string &name) : name(name) { ECHO("Sajt::Sajt(" + this->name + ")"); }
    explicit Sajt(string &&name)      : name(name) { ECHO("Sajt::Sajt(" + this->name + ")"); }
    Sajt(const Sajt &other)             { ECHO("Sajt::Sajt(const Sajt &) [" + other.name + " -> " + name + "]");      name = other.name; }
    Sajt(Sajt &&other)                  { ECHO("Sajt::Sajt(Sajt &&) [" + other.name + " -> " + name + "]");           name = other.name; }
    Sajt & operator=(const Sajt &other) { ECHO("Sajt::operator=(const Sajt &) [" + other.name + " -> " + name + "]"); name = other.name; return *this; }
    Sajt & operator=(Sajt &&other)      { ECHO("Sajt::operator=(Sajt &&) [" + other.name + " -> " + name + "]");      name = other.name; return *this; }
    ~Sajt()                             { ECHO("Sajt::~Sajt() [" + name + "]"); }
};

Sajt create() {
    Sajt s = Sajt("fn");
    return s;
}

int main() {
    Sajt a;
    Sajt elso = create();
    return 0;
    ECHO("move assign");
    elso = create();
    
    ECHO("END OF MAIN");
    return 0;
}




















