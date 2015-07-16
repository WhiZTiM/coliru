#include <iostream>
#include <utility>
#include <type_traits>
#include <typeinfo>
#include <vector>
#include <memory>

/////////////////////////////////////////
// Base class for all objects
/////////////////////////////////////////
class CoreBase 
{
    public:
        enum eOBJ_TYPE {TREE, CONTAINER, OBJECT};
        virtual eOBJ_TYPE GetObjType() {return OBJECT;};
        
        void AddChild(CoreBase* obj) {m_children.push_back(obj);}
        std::vector<CoreBase*>& GetChildren() {return m_children;}
        
    private:
        std::vector<CoreBase*> m_children;
};


/////////////////////////////////////////
//TREES
/////////////////////////////////////////

// Base class for trees -- reports its obj type as tree and defines a 
// base implementation of DoA();
class TreeBase : public CoreBase
{
    public:
        eOBJ_TYPE GetObjType() { return TREE; }
        
        virtual int DoA() {return 1;}
};


// Templatized tree class
template <typename T>
class Tree : public TreeBase {
        virtual int DoA() { return 11;}
};



/////////////////////////////////////////
//CONTAINERS 
/////////////////////////////////////////

// Base class for containers -- reports its obj type as container, also provides DoB(), 
//which is used for all containers, and DoC(), which must be overridden by subclasses.
class ContainerBase : public CoreBase
{
    public:
        eOBJ_TYPE GetObjType() { return CONTAINER; }
        
        int DoB() {return 2;}
        virtual int DoC() = 0;
};

// Templatized container class
template <typename T>
class Container : public ContainerBase {
    int DoC() override {return 22;}
};



/////////////////////////////////////////
// Some operation that does type-specific stuff 
/////////////////////////////////////////

void PerformCrazyFunc(CoreBase& obj) {
    // Peform some operation on our object's children
    for (CoreBase* child : obj.GetChildren()) {
        switch (child->GetObjType()) {
            case CoreBase::TREE: {
                // Logic specialized for tree objects
                TreeBase *treeObj = static_cast<TreeBase*>(child);
                printf("Performing some tree-specific logic (%d)\n",
                    treeObj->DoA());
                break; }
            case CoreBase::CONTAINER: {
                // Logic specialized for container objects
                ContainerBase *containerObj = static_cast<ContainerBase*>(child);
                printf("Performing some container-specific logic (%d)\n",
                    containerObj->DoB() + containerObj->DoC());
                break; }
            case CoreBase::OBJECT:
                // Logic for general objects
                printf("Peforming some general object logic.\n");
        }
    }
}


// Driver
int main()
{
    CoreBase obj;
    obj.AddChild(new CoreBase);
    obj.AddChild(new Container<int>);
    obj.AddChild(new Tree<float>);
    PerformCrazyFunc(obj);
}
