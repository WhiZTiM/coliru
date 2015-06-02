#include <iostream>
#include <memory>
#include <vector>

struct node
{
    int id;
    std::vector<std::shared_ptr<node> > link;

    void print_connection() const
    {
        std::cout<<id<<std::endl;
        std::cout<<"    ";
        for(auto const& l : link)
        {
            l->print_connection();
        }
    }
};

int main()
{
    int N = 4;
    
    int M = 1<<N;
    std::vector<std::shared_ptr<node> > tree(M, std::make_shared<node>());
    for(int i=0;i<M;++i)
    {
        tree[i]->id=i;
    }
    
    for(int i=0;i<M;++i)
    {
        std::cout<<"node: "<<i<<" is connected to:\n";
           
        for(int p=0;p<N;++p)
        {
            int j= (1<<p) ^ i;

            if(j<=i) continue;
            std::cout<<j<<"  ";        
            
            tree[i]->link.push_back(tree[j]);
        }
        std::cout<<std::endl;        
    }
}
