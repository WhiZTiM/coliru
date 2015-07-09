#include <iostream>

class Matrix {
 public: 
    Matrix(){};
    virtual ~Matrix(){};
};

class Quadratic {
public:
    Quadratic(){
        Q = NULL;
        }
        
    Quadratic(const Matrix &QQ){
        Q = const_cast<Matrix*>(&QQ);    
    }
    
    virtual ~Quadratic(){
        if (Q!=NULL)
            delete Q;
        }
        
private:
    Matrix *Q; 

};



int main()
{
   Matrix *a = new Matrix();
   Quadratic *q = new Quadratic(*a);
      
   delete q; // this will also delete a
   return 0;  
}
