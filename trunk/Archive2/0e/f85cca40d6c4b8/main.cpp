#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class RenderPass;

class Pass
{
};

class OnePass : public Pass
{
public:
    OnePass(RenderPass *p) {}
};

class TwoPass : public Pass
{
public:
    TwoPass(RenderPass *p) {}
};

class RenderPass
{
public:
    template<typename SpecificPass, typename...Passess>
    void Construct();
    
    vector<shared_ptr<Pass>>& get() {return m_passes;}
    
private:
    template<typename SpecificPass, typename...Rest>
    class F
    {
    public:
        static void go(RenderPass *p)
        {
            p->m_passes.push_back(make_shared<SpecificPass>(p));
            F<Rest...>::go(p);
        }
    };
    
    template<typename S>
    class F<S>
    {
    public:
        static void go(RenderPass *p)
        {
            p->m_passes.push_back(make_shared<S>(p));
        }
    };
    
private:
    vector<shared_ptr<Pass>> m_passes;
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
    cout << rp.get().size() << endl;
    return 0;
}
