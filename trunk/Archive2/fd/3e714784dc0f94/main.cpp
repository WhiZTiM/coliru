#include<iostream>
#include<cstdlib>

class  array{
       public:
        void setArray(void** key)
        {
            arr=key;
        }
        
        void** getArray()
        {
            return &(*arr);
        }
    private:
     void** arr;
};
struct Vector: public array{
    int  used;
    int  size;
   
};

Vector* vector_init(const int  size){
    Vector* v =(Vector*) malloc(sizeof(Vector));
    v->used = 0;
    v->size = size;
    void** tem=v->getArray();
    tem=(void**) malloc(size*sizeof(void*));
    v->setArray(key);
}

int main() {}