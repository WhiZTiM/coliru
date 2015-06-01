#include<memory>
#include<iostream>

    struct AA
    {
        //...
    };


    struct BB
    {
        std::shared_ptr<void> smpl;
    
        void setter(std::shared_ptr<void> const& p)
        {
            smpl = p;  //now the ref count of your shared_tr to AA is increased
        }
    };
    
    int main()
    {    
        auto objA = std::make_shared<AA>();
        auto objB = std::make_shared<BB>();

        objB->setter(objA);
        
        std::cout<<objA.use_count()<<std::endl;   //prints "2"
    }
    