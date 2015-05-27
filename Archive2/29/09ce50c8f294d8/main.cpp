#include <boost/numeric/ublas/vector.hpp>

namespace ublas = boost::numeric::ublas;

template <typename T = double> using ublasRn = ublas::vector<T>;

struct Base {
    virtual ~Base() {}
};

template <typename T1, typename T2> class Composite : public Base {
  protected:
      template <typename, typename, typename> friend class Trajectory; // or make this public
      using Type1 = T1;
      using Type2 = T2;

      Type1 _i1;
      std::unique_ptr<Type2> _i2;

  public:
      Composite() = default;
};

template <typename T2> class CompositeCT : virtual public Composite<double, T2> {
  public:
    using Composite<double, T2>::Composite;
};

template <typename T1> class CompositeRn : virtual public Composite<T1, ublasRn<double> > {
  public:
    using Composite<T1, ublasRn<double> >::Composite;
};

class CompositeCTRn : public CompositeCT<ublasRn<double> >, public CompositeRn<double> {
    using VBase  = Composite<double, ublasRn<double> >;
    using CTBase = CompositeCT<ublasRn<double> >;
    using RnBase = CompositeRn<double>;
  public:
    CompositeCTRn() : VBase(), CTBase(), RnBase() {
        VBase::_i1 = 1;
        VBase::_i2.reset(new ublasRn<double>(3));

        CTBase::_i1 = 2;
        CTBase::_i2.reset(new ublasRn<double>(3));

        RnBase::_i1 = 3;
        RnBase::_i2.reset(new ublasRn<double>(3));

        assert(3 == VBase::_i1);
        assert(3 == CTBase::_i1);
        assert(3 == RnBase::_i1);

        assert(VBase::_i2.get() == CTBase::_i2.get());
        assert(VBase::_i2.get() == RnBase::_i2.get());

        RnBase::_i2.reset();
        assert(!(VBase::_i2 || CTBase::_i2 || RnBase::_i2));
    };
};

template <typename T1, typename T2, class TComposite> class Trajectory : public Base {
    static_assert(std::is_same<T1, typename TComposite::Type1>::value, "mismatched composite");
    static_assert(std::is_same<T2, typename TComposite::Type2>::value, "mismatched composite");
  protected:
    std::vector<std::unique_ptr<TComposite> > m_Trajectory;

  public:
    Trajectory() { checkType(); }
    void checkType() const {
        std::vector<TComposite> CI(1000);
    }
    virtual ~Trajectory() {}
};

#include <iostream>

int main() {
    Trajectory<double, ublasRn<>, CompositeCTRn> T;
    std::cout << 123 << "\n";
}
