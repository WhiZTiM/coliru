#include <iostream>
#include <memory>


// backstory/rationale/defense
//
// Today the only other C++ programmer in my company
// (yes, yes) asked my opinion on how to deal with an
// API that gave resources to client code through 
// functions with pointer-to-pointer arguments, while
// also attempting to manage those resources with smart
// pointers.  
//
// While I did do research to see if anyone else had
// encountered the same problem (answer: yes, @puppy
// among them) and pointed him to those solutions
// as better alternatives to what I have below, but
// I still think what's below has some nice features.  
//
// the UniquePtrToPtrPtr class relies on the
// assumption that the passed unique_ptr will outlive
// it (probable, given its purpose as a temporary
// object to -sort of- transform a unique_ptr for
// the duration of the containing full-expression)
// and that the passed function will deal properly
// with the resource pointed by the pointed pointer.  
//
// It automatically stores the changes made to its
// pointer pointer back into the unique pointer
// referenced on deletion, neatly dealing with
// the pointer creation, passing the pointer and 
// assignment of the modified pointer into a unique
// pointer all by making a temporary object with
// the unique_ptr as an argument, and calling get()
// on it.
//
// While this means that passing in the same unique
// pointer to multiple parts of the same full-expression
// isn't the brightest thing to do, that's ordinarily
// the case. The only really non-intuitive behavior
// that arises from use of this object only happens
// when you assign values to the unique_ptr during
// the lifetime of the UniquePtrToPtrPtr object, which
// is fairly obviously bad if you're using a temporary.


// to show creation and deletion of things
class Foo{
    std::string
        str_;
public:
    Foo(std::string str) : str_{str}{
        std::clog << "Foo constructed with string " << str_ << '\n';
    }
    ~Foo(){
        std::clog << "Foo destructed with string " << str_ << '\n';
    }
    void logContents(){
        std::clog << "Contents: " << str_ << '\n';
    }
};

template <typename Type_, typename Deleter_ = std::default_delete<Type_>>
// used to pass pointers managed by unique pointers to
// functions requiring pointer-to-pointer arguments.
// 'steals' ownership of object associated with unique pointer
// for duration of lifetime, handing it back to the unique pointer
// on destruction.  
// This is primarily meant for use as a temporary object, which 
// would give it the lifetime of its full-expression. While you
// *can* theoretically construct a longer lived version, and then
// alter the contents of the originating unique pointer so your 
// alterations to it are undone on destruction of this object,
// that seems like an even worse plan than using this converter.
class UniquePtrToPtrPtr{
    std::unique_ptr<Type_, Deleter_>
        // reference to smart pointer, which is assumed to outlast this object
        &smartPointer_;
    Type_*
        dumbPointer_;
public:

    // constructed from an lvalue reference. Unique pointer is assumed to exist for
    // at least the lifetime of this conversion wrapper.
    UniquePtrToPtrPtr(std::unique_ptr<Type_, Deleter_> &convertee) : smartPointer_{convertee}{
        // smartPointer_.reset(smartPointer_.release()); is fine.
        // smartPointer_.reset(smartPointer_.get()); is not.
        dumbPointer_ = smartPointer_.release(); 
    }
    ~UniquePtrToPtrPtr(){
        
        // release the managed resources back into the custody of the referenced smart pointer.
        // if the dumb pointer's target has been changed, this will save the change to the 
        // unique pointer.
        smartPointer_.reset(dumbPointer_);
    }
    
    // get the pointer to pointer. Functions using this
    // to alter the pointed pointer are assumed to properly
    // deal with the resources originally pointed by the
    // pointed pointer.
    Type_** get() {return &dumbPointer_;}
};

// some API functions for various (probably portability or clarity of client syntax) reasons
// use pointers to pointers for functions that alter pointers. This is annoying when you
// are attempting to manage the pointed object's lifetime with a smart pointer, because
// calling `get` will return the pointer by value.  
// There are multiple solutions for this issue, I'm aware.
void becauseFuckSmartPointersThatsWhy(Foo **alteredPointer, const std::string &newString){
    delete *alteredPointer;
    *alteredPointer = new Foo(newString);
}

int main(){
    auto fooPointer = std::make_unique<Foo>("Zilch");
    
    becauseFuckSmartPointersThatsWhy(UniquePtrToPtrPtr<Foo>{fooPointer}.get(),"Zot");
    
    {
    UniquePtrToPtrPtr<Foo> fooBandit{fooPointer};
    becauseFuckSmartPointersThatsWhy(fooBandit.get(),"Zod");
    
    // inadvisable
    fooPointer.reset(new Foo("Zwieback"));
    }
}