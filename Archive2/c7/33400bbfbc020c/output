
#include <iostream>
using namespace std;

class VisitorBase { 
    protected:
        virtual ~VisitorBase() { }
};

template <class VisitableT>
class Visitor : virtual public VisitorBase {
    public:
        virtual void visit(VisitableT const &) = 0;
};

class Visitable {
    public:
        virtual void accept(VisitorBase * const p_visitor_base) = 0;
        
    protected:
        template <class VisitableT>
        void dynamicAccept(VisitorBase * const p_visitor_base, VisitableT * const self) {
            Visitor<VisitableT> * const p_visitor = dynamic_cast<Visitor<VisitableT> * const>(p_visitor_base);
            if(p_visitor) {
                p_visitor->visit(*self);
            }
        }
};

class SpaceShip : public Visitable { };

class ApolloSpacecraft : public SpaceShip {
    public:
        void accept(VisitorBase * const p_visitor_base) { dynamicAccept(p_visitor_base, this); }
};

class StarTrekEnterprise : public SpaceShip {
    public:
        void accept(VisitorBase * const p_visitor_base) { dynamicAccept(p_visitor_base, this); }
};

class DeathStar : public SpaceShip {
    public:
        void accept(VisitorBase * const p_visitor_base) { dynamicAccept(p_visitor_base, this); }
};

class ExplodingAsteroid : public Visitor<ApolloSpacecraft>, public Visitor<StarTrekEnterprise>//, public Visitor<DeathStar>
{
    public:
        virtual void visit(ApolloSpacecraft const &) {
            cout << "ExplodingAsteroid destroyed the ApolloSpacecraft =(" << endl;
        }
        virtual void visit(StarTrekEnterprise const &) {
            cout << "ExplodingAsteroid recochetted off the StarTrekEnterprise due to it's front-facing energy shields!" << endl;
        }
//        virtual void visit(DeathStar const &) {
//            cout << "ExplodingAsteroid shattered against the DeathStar due to the fact that it's frickin' massive." << endl;
//        }
};

class EnemyShip : public Visitor<ApolloSpacecraft>, public Visitor<StarTrekEnterprise>, public Visitor<DeathStar>
{
    public:
        virtual void visit(ApolloSpacecraft const &) {
            cout << "EnemyShip obliterated the ApolloSpacecraft with its basic lasers." << endl;
        }
        virtual void visit(StarTrekEnterprise const &) {
            cout << "EnemyShip fired on the StarTrekEnterprise with its lasers, but got shredded by the Enterprise's more powerful gattling lasers!" << endl;
        }
        virtual void visit(DeathStar const &) {
            cout << "EnemyShip saw the DeathStar and fled for its life." << endl;
        }
};

class FriendlyShip : public Visitor<StarTrekEnterprise>, public Visitor<DeathStar> // public Visitor<ApolloSpacecraft>
{
    public:
//        virtual void visit(ApolloSpacecraft const &) {
//            cout << "FriendlyShip bumped the ApolloSpacecraft in the right direction." << endl;
//        }
        virtual void visit(StarTrekEnterprise const &) {
            cout << "FriendlyShip docked with the StarTrekEnterprise for repairs!" << endl;
        }
        virtual void visit(DeathStar const &) {
            cout << "FriendlyShip docked with the DeathStar, and out stepped the Evil Emperor Palpetine... bahh bahh bahh, bah ba ba, bah ba bahhh." << endl;
        }
};

int main()
{
    Visitable *p_apollo = new ApolloSpacecraft();
    Visitable *p_enterprise = new StarTrekEnterprise();
    Visitable *p_deathstar = new DeathStar();
    
    VisitorBase *p_asteroid = new ExplodingAsteroid();
    p_apollo->accept(p_asteroid);
    p_enterprise->accept(p_asteroid);
    p_deathstar->accept(p_asteroid);
    
    VisitorBase *p_enemyship = new EnemyShip();
    p_apollo->accept(p_enemyship);
    p_enterprise->accept(p_enemyship);
    p_deathstar->accept(p_enemyship);
    
    VisitorBase *p_friendlyship = new FriendlyShip();
    p_apollo->accept(p_friendlyship);
    p_enterprise->accept(p_friendlyship);
    p_deathstar->accept(p_friendlyship);
}

// This is an advanced version of the visitor pattern.  Converting the accept() function into a template removes the need
//  for the Visitor class to know about all the possible Visitable classes (no more forward declarations for each derived
//  spaceship type), since the Visitable type can be specified by the derived Visitor class via the template parameter.  
//  Therefore, adding a new class to the family does not proliferate code changes to all classes who implement the Visitor 
//  class.  However, in order to operate this class template through a single interface, we need to create a base class,
//  and we can't specify anything about the Visitable in it.  This leaves us with an empty base class.  It follows that in
//  order to support this slightly new Visitor class heirarchy, we need to dynamically (down)cast our VisitorBase reference
//  to an instance of the Visitor template before performing the second dispatch.  This particular usage of dynamic_cast
//  is relatively safe, because the type it casts to is determined by another template parameter implicitly passed up from a 
//  derived Visitable (its a protected function).  We are able to push the call far up the heirarchy so that it is not 
//  incorrectly tampered with by the client.  So, instead of checking that the Visitor implements a single monolithic interface
//  at compile-time, we check that it implements a single instance of an interface template at run-time.  This means that
//  if we attempt to downcast a VisitorBase to an instance of the Visitor template that it has not implemented, AND THEN
//  DEREFERENCE THE NEW REFERENCE, we will get obscure errors and crashes.  Since being able to hold any derived Visitor 
//  through a single, base interface is a feature of double dispatch, we need to check first if the dynamic_cast fails before
//  we dereference the result.  This seals the deal.  We have now required each derived Visitor to only implement a visit()
//  method for the types it wants and nothing more (no more overrides with empty definitions), in addition to decoupling 
//  the base Visitor class from all the possible Visitables, making it easier to add classes to the Visitable heirarchy.  
//  So we're allowed to avoid inheriting visit() methods we don't want to implement, but the downside is that the compiler 
//  nor the run-time environment can inform us when we accidentally avoid inheriting a visit() method that we DO want to 
//  implement.  The program will just continue silently.  Hopefully your unit tests are thorough in this department!
