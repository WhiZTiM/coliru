#include <iostream>

class Matrix {
 public: 
    Matrix(){};
    virtual ~Matrix(){};
};

class Quadratic {
public:        
    explicit Quadratic(Matrix &QQ) : Q(QQ) {}
    virtual ~Quadratic() {}
        
private:
    Matrix &Q; 
};



int main()
{
   Matrix a;
   Quadratic *q = new Quadratic(a);
      
   delete q; // Y U new+delete, though? Always use smart pointers.
}
