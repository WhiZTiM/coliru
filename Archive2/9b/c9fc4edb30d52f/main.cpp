#include <boost/serialization/access.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

struct ComponentVisitor;

struct Component {
    virtual ~Component() = default;
    virtual void accept(ComponentVisitor &v) = 0;
  private:
    // Serialization routine.
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &, const unsigned int) {}
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Component)

struct GraphicComponent;
struct PositionComponent;

struct ComponentVisitor {
    virtual void visitGraphicComponent(GraphicComponent   const &){};
    virtual void visitPositionComponent(PositionComponent const &){};
};

// Graphic component.
struct GraphicComponent : public Component {
    void accept(ComponentVisitor &vis) { vis.visitGraphicComponent(*this); }

  private:
    // Serialization routine.
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &a, const unsigned int v);
};
BOOST_CLASS_EXPORT_KEY(GraphicComponent)

// Position component.
struct PositionComponent : public Component {
    void accept(ComponentVisitor &vis) { vis.visitPositionComponent(*this); }

  private:
    // Serialization routine.
    friend class boost::serialization::access;

    template <class Archive>
    void serialize(Archive &a, const unsigned int v);
};

BOOST_CLASS_EXPORT_KEY(PositionComponent)

/////////////////////////////////////////////////////

BOOST_CLASS_EXPORT_IMPLEMENT(GraphicComponent)
BOOST_CLASS_EXPORT_IMPLEMENT(PositionComponent)
//...

template <class Archive>
void GraphicComponent::serialize(Archive &a, const unsigned int)
{
    a &boost::serialization::base_object<Component>(*this);
    //... serialize data members ...
}

template <class Archive>
void PositionComponent::serialize(Archive &a, const unsigned int)
{
    a &boost::serialization::base_object<Component>(*this);
    //... serialize data members ...
}

#include <boost/make_shared.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>

int main() {
    std::stringstream ss;

    {
        std::vector<boost::shared_ptr<Component> > components {
            boost::make_shared<GraphicComponent>(),
                boost::make_shared<PositionComponent>(),
                boost::make_shared<PositionComponent>(),
                boost::make_shared<GraphicComponent>(),
        };

        boost::archive::text_oarchive oa(ss);
        oa << components;
    }

    {
        std::vector<boost::shared_ptr<Component> > deserialized;

        boost::archive::text_iarchive ia(ss);
        ia >> deserialized;

        struct printer : ComponentVisitor {
            void visitPositionComponent(PositionComponent const & /*pc*/){ std::cout << __PRETTY_FUNCTION__ << "\n"; }
            void visitGraphicComponent(GraphicComponent   const & /*gc*/){ std::cout << __PRETTY_FUNCTION__ << "\n"; }
        } print;

        for (auto c : deserialized)
            c->accept(print);
    }
}
