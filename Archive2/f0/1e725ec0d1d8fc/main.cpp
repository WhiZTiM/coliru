#include <utility>
#include <iostream>
 
class Noisy
{
    public:

    Noisy() : i(-1)
    {
        std::cout << "Noisy::Noisy()\n";
        std::cout << "  this = " << (void*) this << "\n";
        std::cout << "  this.i = " << this->i << "\n";
    }

    Noisy(int i_) : i(i_)
    {
        std::cout << "Noisy::Noisy(int i)\n";
        std::cout << "  this = " << (void*) this << "\n";
        std::cout << "  this.i = " << this->i << "\n";
    }

    Noisy(const Noisy & that)
    {
        std::cout << "Noisy::Noisy(const Noisy & that)\n";
        std::cout << "  this = " << (void*) this  << "\n";
        std::cout << "  that = " << (void*) &that << "\n";
        std::cout << "  preconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
        this->i = that.i;
        std::cout << "  postconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
    }

    Noisy(Noisy && that)
    {
        std::cout << "Noisy::Noisy(Noisy && that)\n";
        std::cout << "  this = " << (void*) this  << "\n";
        std::cout << "  that = " << (void*) &that << "\n";
        std::cout << "  preconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
        this->i = that.i;
        that.i = -1;
        std::cout << "  postconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
    }

    Noisy & operator=(const Noisy & that)
    {
        std::cout << "Noisy::operator=(const Noisy & that)\n";
        std::cout << "  this = " << (void*) this  << "\n";
        std::cout << "  that = " << (void*) &that << "\n";
        std::cout << "  preconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
        this->i = that.i;
        std::cout << "  postconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
        return *this;
    }

    Noisy & operator=(Noisy && that)
    {
        std::cout << "Noisy::operator=(Noisy && that)\n";
        std::cout << "  this = " << (void*) this  << "\n";
        std::cout << "  that = " << (void*) &that << "\n";
        std::cout << "  preconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
        this->i = that.i;
        that.i = -1;
        std::cout << "  postconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        std::cout << "  that.i = " << that.i  << "\n";
        return *this;
    }

    ~Noisy()
    {
        std::cout << "~Noisy():\n";
        std::cout << "  this = " << (void*) this << "\n";
        std::cout << "  preconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
        this->i = -1;
        std::cout << "  postconditions:\n";
        std::cout << "  this.i = " << this->i << "\n";
    }

    private:
    int i;
};
 
Noisy f(int i)
{
    Noisy v = Noisy(i); // copy elision from temporary to v
    return v; // NRVO from v to the nameless temporary that is returned
}
 
int main()
{
    Noisy v = f(1);
    v = f(2);
    v = std::move(f(3));
}