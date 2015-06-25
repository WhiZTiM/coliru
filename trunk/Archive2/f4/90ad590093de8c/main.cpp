#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Pass
{
};

class OnePass : public Pass
{
};

class TwoPass : public Pass
{
};

class RenderPass
{
public:
    template<typename SpecificPass, typename...Passess>
    void Construct();
    
private:
    template<typename SpecificPass, typename...Rest>
    class F
    {
    public:
        static void go(RenderPass *p)
        {
            p->m_passes.push_back(new SpecificPass());
            F<Rest...>::go(p);
        }
    };
    
    template<typename S>
    class F<S>
    {
    public:
        static void go(RenderPass *p)
        {
            p->m_passes.push_back(new S());
        }
    };
    
private:
    vector<Pass*> m_passes;
};

template<typename SpecificPass, typename...Rest>
inline void RenderPass::Construct()
{
    F<SpecificPass, Rest...>::go(this);
}

int main(int argc, char **argv)
{
    RenderPass rp;
    rp.Construct<OnePass, TwoPass, TwoPass, OnePass>();
    return 0;
}
