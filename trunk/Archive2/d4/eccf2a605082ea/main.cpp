class CBase
{
    public:
        CBase(): p(0) {}
        ~CBase() {}
    protected:
        int *p;
};

class CDerived : public CBase
{
    CDerived() { p = new int[1000]; }
    ~CDerived()
    {
        if (p)
        {
            delete[] p;
            p = 0;
        }
    }
};

void main()
{
    CBase* cBase = new CDerived;
    delete cBase;
}