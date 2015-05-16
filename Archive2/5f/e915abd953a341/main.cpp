#include <iostream>
#include <string>
#include <functional>

using Int32 = int;
using BaseObject = int;
using Bool = bool;

struct Helper {
    template<typename Fn>
    Int32 RecurseHierarchy(BaseObject* op, Fn callback) {
        // ...
        return callback(op);
    }
};

struct Exporter {
    Helper helper;
    Int32 WriteActor(BaseObject*) { std::cout << "WriteActor called\n"; return 123; }
    Bool writeT3D(/* ... */) {
        // ...
        int x = 123;
        using namespace std::placeholders;
        Int32 count = helper.RecurseHierarchy(&x, std::bind(&Exporter::WriteActor, this, _1));
        return true;
    }
};

int main() {
    Exporter exporter;
    exporter.writeT3D();
}