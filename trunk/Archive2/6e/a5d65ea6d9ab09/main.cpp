#include <iostream>
#include <string>
#include <vector>
#include <memory>

// degenerate Visitor base for Visitable specification
struct Visitor {
    virtual ~Visitor() = 0; // empty class, provide with virtual destructor to make class pure virtual
};

Visitor::~Visitor(){} // empty destructor, define here (would be hidden in implementation) because a Visitor must still be destructable (duh)


// define Visitable to accept a Visitor. All Visitables must define accept..
struct Visitable {
    virtual bool accept(Visitor &visitor) = 0;
};

// define an interface that is Visitable
struct Person : public Visitable {
    virtual std::string getRace() = 0;
};

// now define a template helper to use CRTP to make DERIVED inherit accept, so that implementing Person does not require you to write accept...
template<typename DERIVED>
struct MakePerson : public Person { // NOTE: Inheritance from Person must occur here otherwise DERIVED will be an incomplete type

    // DEFINE AN INNER TYPE : express idea that making a person gives that person a type that says how to visit it
    struct VisitorType {
        virtual void visit(DERIVED &visitable) = 0;
    };

    // THIS IS WHERE WE WRITE ACCEPT FOR YOU
    virtual bool accept(Visitor &visitor) {
        try {
            dynamic_cast<VisitorType&>(visitor).visit( static_cast<DERIVED&>(*this) ); // try to cross-cast visitor from Visitor -> MakePerson<DERIVED>::VisitorType
            return true;
        } catch(const std::bad_cast &bc) { // catches bad_cast from dynamic_cast: means whatever Visitor we actually passed doesnt implement MakePerson<DERIVED>::VisitorType, thus it does not visit this type, thus we do nothing and return false (acyclic visitor)
            return false;
        }
    }
};


// and finally define a template to create Visitors for Persons:
template <class... VISITEES>
struct MakeVisitor : public Visitor, VISITEES::template VisitorType... { }; // empty class, just need to compose interface that is a Visitor base + gets specification for virtual visit() for each VISITEE via the embedded VisitorType

// example:

struct Cracker : public MakePerson<Cracker> {
    // i get accept for free!
    
    virtual std::string getRace() { return "Cracker"; }
};

struct Nigger : public MakePerson<Nigger> {
    // i get accept for free!
    
    virtual std::string getRace() { return "Nigger"; }
};

struct WetBack : public MakePerson<WetBack> {
    // i get accept for free!
    
    virtual std::string getRace() { return "WetBack"; }
};

struct Chink : public MakePerson<Chink> {
    // i get accept for free!
    
    virtual std::string getRace() { return "Chink"; }
};


// now add algorithms to the subclasses by representing them with Visitors:

struct BorderPatrol : public MakeVisitor<WetBack,Chink> {
    
    // we visit WetBacks and Chinks, must implement these virtual functions or BorderPatrol is incomplete type and cannot instantiate!
    virtual void visit(WetBack &pp) { std::cout << "Deporting " << pp.getRace() << std::endl; }
    virtual void visit(Chink &pp) { std::cout << "Excluding (lol chinese exclusion) " << pp.getRace() << std::endl; }
};

struct Police : public MakeVisitor<Cracker,Nigger,WetBack,Chink> {
    
    // we visit WetBacks and Chinks, must implement these virtual functions or BorderPatrol is incomplete type and cannot instantiate!
    virtual void visit(Cracker &pp) { std::cout << "Leaving alone the " << pp.getRace() << std::endl; }
    virtual void visit(Nigger &pp) { std::cout << "Shooting unarmed " << pp.getRace() << std::endl; }
    virtual void visit(WetBack &pp) { std::cout << "Beating " << pp.getRace() << std::endl; }
    virtual void visit(Chink &pp) { std::cout << "Fining " << pp.getRace() << std::endl; }
};


int main( ) {
    
    std::vector<std::shared_ptr<Person>> people;
    people.push_back(std::make_shared<Cracker>());
    people.push_back(std::make_shared<Nigger>());
    people.push_back(std::make_shared<WetBack>());
    people.push_back(std::make_shared<Chink>());
    
    std::vector<std::shared_ptr<Visitor>> visitors; // has no idea what concrete types are, just has handles to them as Visitors so they can be anything
    visitors.push_back(std::make_shared<BorderPatrol>());
    visitors.push_back(std::make_shared<Police>());
    
    for(const auto &visitor : visitors) {
        for(const auto &person : people) {
           if(not person->accept(*visitor) ) {
               std::cout << "Visitor ignored " << person->getRace() << std::endl;
           }
        }
    }
    
    
 return 0;   
}

