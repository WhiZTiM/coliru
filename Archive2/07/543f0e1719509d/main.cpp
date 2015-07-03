#include <iostream>

template<typename... Types>
struct Visitor;
 
template<typename... Visitors>
struct Visitable;
 
template<typename T>
struct Visitor<T>
{
    virtual void visit(T & visitable) = 0;
};
 
template<typename T, typename... Types>
struct Visitor<T, Types...> : public Visitor<Types...> 
{
    using Visitor<Types...>::visit;
 
    virtual void visit(T & visitable) = 0;
};
 
template<typename V>
struct Visitable<V>
{
    virtual void accept(V& visitor) = 0;
};
 
template<typename Derived, typename V>
struct Visitable<Derived, V> : Visitable<V>
{
    virtual void accept(V& visitor)
    {
        visitor.visit(dynamic_cast<Derived&>(*this));
        //dynamic_cast<Derived*>(this)->accept_impl(visitor);
    }
};
 
template<typename Derived, typename V, typename... Visitors>
struct Visitable<Derived, V, Visitors...> : public Visitable<Derived, Visitors...>, Visitable<V>
{
    using Visitable<Derived, Visitors...>::accept;
 
    virtual void accept(V& visitor)
    {
        visitor.visit(dynamic_cast<Derived&>(*this));
        //dynamic_cast<Derived*>(this)->accept_impl(visitor);
    }
};

class OtherTypeAsteroid;
class ExplodingAsteroid;
class ApolloSpacecraft;
class OthersSpacecraft;
 
class SpaceShip {};
class Asteroid : public Visitor<ApolloSpacecraft, OthersSpacecraft>{};
class Alien : public Visitor<ApolloSpacecraft, OthersSpacecraft>{};
 
struct OthersSpacecraft : public SpaceShip, public Visitable<OthersSpacecraft, Asteroid, Alien> {};
 
struct ApolloSpacecraft : public SpaceShip, public Visitable<ApolloSpacecraft, Asteroid, Alien> {};
 
class ExplodingAsteroid : public Asteroid {
public:
  virtual void visit(OthersSpacecraft&) {
    std::cout << "ExplodingAsteroid hit a OthersSpacecraft" << std::endl;
  }
  virtual void visit(ApolloSpacecraft&) {
    std::cout << "ExplodingAsteroid hit an ApolloSpacecraft" << std::endl;
  }
};
 
class OtherTypeAsteroid : public Asteroid {
public:
  virtual void visit(OthersSpacecraft&) {
    std::cout << "OtherTypeAsteroid hit a OthersSpacecraft" << std::endl;
  }
  virtual void visit(ApolloSpacecraft&) {
    std::cout << "OtherTypeAsteroid hit an ApolloSpacecraft" << std::endl;
  }
};
 
struct AlienA : public Alien
{
    virtual void visit(OthersSpacecraft&) {
        std::cout << "AlienA hit a OthersSpacecraft" << std::endl;
    }
    virtual void visit(ApolloSpacecraft&) {
        std::cout << "AlienA hit an ApolloSpacecraft" << std::endl;
    }
};
 
struct AlienB : public Alien
{
    virtual void visit(OthersSpacecraft&) {
        std::cout << "AlienB hit a OthersSpacecraft" << std::endl;
    }
    virtual void visit(ApolloSpacecraft&) {
        std::cout << "AlienB hit an ApolloSpacecraft" << std::endl;
    }
};
 
int main()
{
    OthersSpacecraft theOthersSpacecraft;
    ApolloSpacecraft theApolloSpacecraft;
    
    OtherTypeAsteroid theOtherTypeAsteroid;
    ExplodingAsteroid theExplodingAsteroid;
 
    Asteroid& theAsteroidReference = theExplodingAsteroid;
    Visitable<Asteroid>& theSpaceShipReference_1 = theApolloSpacecraft;
 
    theSpaceShipReference_1.accept(theOtherTypeAsteroid);
    theSpaceShipReference_1.accept(theAsteroidReference);
    
    AlienA theAlienA;
    AlienB theAlienB;
 
    Alien& theAlienReference = theAlienB;
    Visitable<Alien>& theSpaceShipReference_2 = theOthersSpacecraft;
 
    theSpaceShipReference_2.accept(theAlienA);
    theSpaceShipReference_2.accept(theAlienReference);
 
    return 0;
}
