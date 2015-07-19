#include <list>
#include <iterator>
#include <iostream>

struct Piece {
    void Normalize() const {}
    void Normalize(int&) const {}

    int  GetMaxDims()   const { return 1; }
    int  GetMaxUnits()  const { return 2; }
    int  GetDepth(int&) const { return 2; }
    void Translate(int) const { }

    bool operator==(Piece const&) const { return false; }
};

class TranslationList 
{ 
    public: 
        TranslationList(Piece const& rhs):original(rhs){} 
        TranslationList(TranslationList const& rhs):original(rhs.original){} 
        TranslationList& operator=(TranslationList const& rhs){original = rhs.original;return *this;} 

        class iterator 
        { 
            public: 
                friend class TranslationList; 
                iterator(){} 
                iterator(iterator const&);

                Piece operator*(); 
                iterator& operator++(); 
                iterator& operator=(iterator const&); 
                bool operator!=(iterator const&); 

            private: 
                Piece * starter; 
                Piece translator; 
                bool last; 
        }; 

        iterator first();
        iterator last(); 

    private: 
        Piece original; 
        TranslationList(){} 
};

// Project 2: Soma Hypercube                         Rob Leach
// TranslationList.cpp                               5/5/2000
//---------------------------------------------------------------------------------------

//#include "TranslationList.h"

TranslationList::iterator TranslationList::first()
{
    iterator i;
    i.starter = &original;
    i.translator = original;
    i.translator.Normalize();
    i.last=false;
    return i;
}

TranslationList::iterator TranslationList::last()
{
    iterator i;
    i.starter    = &original;
    i.translator = original;  // Note: Not normalizing or anything.  Must 'abnormalize'
    i.last       = true;      // manually if add a --
    return i;
}

Piece TranslationList::iterator::operator*()
{
    
    if(last)
    {
        std::cerr
            << "TranslationList.cpp:Piece& TranslationList::iterator::operator*():Error: "
            << "You can't dereference the last element in the list!"                       << std::endl;
        exit(1);
    }
    return translator;
}

TranslationList::iterator& TranslationList::iterator::operator=(const iterator& rhs)
{
    starter    = rhs.starter;
    translator = rhs.translator;
    last       = rhs.last;
    return *this;
}

TranslationList::iterator::iterator(iterator const& rhs):translator(rhs.translator)
{
    starter = rhs.starter;
    last    = rhs.last;
}

TranslationList::iterator& TranslationList::iterator::operator++()
{
    if(last)
    {
        std::cerr
             << "TranslationList.cpp:TranslationList::iterator& TranslationList::iterator::"
             << "operator++():Error: Iteration past the end of the list!" 
             << std::endl;
        exit(1);
    }
    int dimension=1;
    //The dimension whose units are moving is the lowest one that's not on its last translation
    while(
            (dimension <= translator.GetMaxDims() )&& 
            (translator.GetMaxUnits()-translator.GetDepth(dimension) == 0)
         )
    {
        translator.Normalize(dimension);
        dimension++;
    }

    if (dimension <= translator.GetMaxDims()) {
        translator.Translate(dimension);
    } else {
        // No more dimensions left to translate in, so translating all to the end and
        // setting last to true...
        for (dimension = 1; dimension <= translator.GetMaxDims(); dimension++) {
            while (translator.GetMaxUnits() - translator.GetDepth(dimension) > 0) {
                translator.Translate(dimension);
            }
        }
        last = true;
    }
    return *this;
}

bool TranslationList::iterator::operator!=(TranslationList::iterator const& rhs)
{
    if((last && !rhs.last) || (!last && rhs.last))
        return true;
    if(last && rhs.last)
        return false;
    return !(translator == rhs.translator);
}



int main() {
    Piece p;
    TranslationList tl(p);

    for (auto it = tl.first(); it!=tl.last(); ++it) {
    }
}
