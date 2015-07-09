#include <iostream>
#include <memory>

using namespace std;

class Matrix {
 public: 
    virtual ~Matrix(){};
    void transform(float f) {
        cout << f << '\n';
        // Would do something on internal state or w/e 
    }
};

class Quadratic {
public:        
    Quadratic() : Q(make_shared<Matrix>()) {}
    Quadratic(const Quadratic &) = default;
    Quadratic(Quadratic &&) = default;
    explicit Quadratic(const shared_ptr<Matrix> & QQ) : Q(QQ) {}
    virtual ~Quadratic() {}
        
    void transformQuads() {
        Q->transform(1.5);  // We always have a valid Matrix! It's an invariant! W00T!
    }
private:
    shared_ptr<Matrix> Q; 
};



int main() {
    {
        Quadratic example1;
        /// example1 automatically allocates itself a Matrix!
        example1.transformQuads();
    }
    
    {
        Quadratic example2(make_shared<Matrix>(/*Or whatever custom constructor you wanna use*/));
        /// example 2 uses a user-provided Matrix!
        example2.transformQuads();
    }
    
    {
        auto mat = make_shared<Matrix>(/*Or whatever custom constructor you wanna use*/);
        mat->transform(2.54);
        
        {
            Quadratic example3(mat);
            /// example 3 also uses a user-provided Matrix, and this Matrix can be used afterwards!
            example3.transformQuads();
        }
        mat->transform(6.66);
    }
}
