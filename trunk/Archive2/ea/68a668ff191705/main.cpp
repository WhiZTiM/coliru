class tree; // forward declaration, allows node to contain incomplete types

class node
{
    tree* subTree;
public:
    //some code goes here      
    node(); // only the declaration
};

class tree 
{ 
// implementation
};

node::node()
{
   subTree = new tree; //no more error here !!
}

int main()
{
    node n;
}
