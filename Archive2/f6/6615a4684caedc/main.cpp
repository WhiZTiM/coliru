#include <iostream>
#include <memory>

template <typename T, typename...Args_>
void setPointerToValue(T **ptr, Args_(...args)){
  delete *ptr; // no check because nothing happens in the null case
  *ptr = new T(args...);
}

template <typename T, typename DeleterType_ = std::default_delete<T>>
// this class assumes anything that calls get is either going to leave well enough alone, or
// properly delete and allocate the resource pointed by the smart pointer
class doublePointer{
    std::unique_ptr<T, DeleterType_>
        &smartPointer_;
    T*
        pointer_;
    public:
    
    // takes a reference to an existing unique pointer object
    doublePointer(std::unique_ptr<T, DeleterType_> &uPtr) : smartPointer_{uPtr}{
        
        // avoid self-reset on deconstruction
        pointer_ = smartPointer_.release();
    }
    doublePointer(const doublePointer&) = delete; // remove copy-construction
    doublePointer(doublePointer&&) = delete; // move construction is theoretically feasible, but this is already juggling pit vipers
    ~doublePointer(){
        
        // if pointer was altered, change contents, otherwise reestablish old contents
        smartPointer_.reset(pointer_);
    }
    
    doublePointer& operator=(const doublePointer&) = delete; // no copy assignment
    doublePointer& operator=(doublePointer&&) = delete; // no move assignment because again, pit viper juggling
    
    // get a pointer to the pointer which will be used to set the unique pointer's internal value
    T** get(){return &pointer_;}
    
};

class A{
    virtual void release() = 0;
protected:
    A(){std::cout << "A constructed\n";}
public:
    virtual ~A(){std::cout << "A destructed\n";}
    
    void Release(){ std::cout << "A::Release\n"; release();}
};

class B: public A{
    int 
        number_;
    B(int number) : number_{number}{
        std::cout << "B created with " << number_ << " as internal value.\n";
    }
    virtual void release(){std::cout << number_ << " values released. Now have 0\n"; number_ = 0;}
public:
    static void make(B** b){
        std::cout << "Making a B\n";
        *b = new B(13);
    }
    virtual ~B(){std::cout << "Destroying a B with " << number_ << " as internal value.\n";}
    
    int getNumber() const {return number_;}
    
};

template <typename T, void (*FactoryFunction_)(T**)>
T* makeA(){
    T* ptr;
    FactoryFunction_(&ptr);
    return ptr;
}

template <typename T>
class aDeleter{
    public:
    void operator()(T*ptr){
        std::cout << "aDeleter Releasing A\n";
        ptr->Release();
        std::cout << "aDeleter Deleting A\n";
        delete ptr;
    }
};

int main() {
    std::cout << "---PART I---\n";
    {
    std::unique_ptr<std::string>
        ptr = std::make_unique<std::string>("first value of unique pointer");
    std::cout << *ptr << '\n';
    setPointerToValue(doublePointer<std::string>{ptr}.get(),"second value of unique pointer");
    std::cout << *ptr << "\n\n";
    }
    std::cout << "---PART II---\n";
    {
    std::unique_ptr<B,aDeleter<B>> customPtr(makeA<B,B::make>());
    std::cout << "\nContents of customPtr: " << customPtr->getNumber() << "\n\n";
    }
}
