#include <memory>
#include <vector>
#include <string>
using namespace std; // Note: for readability only

// Some non-POD object
class Object {
public: 
    Object(const string& desc) : description(desc) { }
    string description;
    void func () { /* do stuff */ }
};

// This class stores a vector of unique pointers to objects
class BaseX {
public:
    const vector< unique_ptr<const Object> > objects;
    BaseX (vector< unique_ptr<Object> > vec) : 
        objects { make_move_iterator(vec.begin()), make_move_iterator(vec.end()) } { }
};

// This class is a special case of BaseX where the object definitions are constant, and known at compile time (static).
// Question is how to initialize them...
class DerivedX : public BaseX {
public:
    DerivedX () : BaseX{ construct_vector() }
    { }
    
    static vector< unique_ptr<Object> > construct_vector()
    {
        unique_ptr<Object> objects[] = {
            make_unique<Object>("My object")
        };
        return { make_move_iterator(begin(objects)), make_move_iterator(end(objects)) };
    }
};

int main()
{}