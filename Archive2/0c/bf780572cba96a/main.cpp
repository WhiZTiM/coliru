#include <iostream>

/*
* Library Code
*/
class BaseVisitor
{
public:
    virtual ~BaseVisitor(){ }
};

template <class T>
class Visitor
{
public:
    virtual void visit(T&) = 0;
};


class BaseVisitable
{
public:
    virtual ~BaseVisitable(){ }
    virtual void accept(BaseVisitor&) = 0;
};

/*
* Application code
*/

class AbstractElement:
    public BaseVisitable
{
public:
    virtual void accept(BaseVisitor& v);
};

void AbstractElement::accept(BaseVisitor& v)
{
    if(Visitor<AbstractElement> *p = dynamic_cast<Visitor<AbstractElement> *>(&v))
    {
        p -> visit(*this);
    }
}

class ConcreteElement:
    public AbstractElement   
{
public:
    virtual void accept(BaseVisitor& v);
};

void ConcreteElement::accept(BaseVisitor& v)
{
    if(Visitor<ConcreteElement> *p = dynamic_cast<Visitor<ConcreteElement> *>(&v))
    {
        p -> visit(*this);
    }
}

class ConcreteVisitor :
    public BaseVisitor,
    public Visitor<ConcreteElement>
{
public:
    virtual void visit(ConcreteElement&);
};

void ConcreteVisitor::visit(ConcreteElement&)
{
     std::cout << "Concrete element's been visited" << std::endl;
}

int main()
{
    ConcreteVisitor v;
    AbstractElement *e = new ConcreteElement;
    e->accept(v);
}