#include <boost/units/unit.hpp>
#include <boost/units/base_unit.hpp>
#include <boost/units/derived_dimension.hpp>
#include <boost/units/quantity.hpp>
#include <boost/units/systems/si.hpp>
#include <boost/units/cmath.hpp>

namespace my_units {
    using power_dimension = boost::units::power_dimension;

    struct watt_base_unit       : boost::units::base_unit<watt_base_unit      , power_dimension, 1> {};
    struct voltampere_base_unit : boost::units::base_unit<voltampere_base_unit, power_dimension, 2> {};
    
    using watt       = typename watt_base_unit::unit_type;
    using voltampere = typename voltampere_base_unit::unit_type;
    
}
BOOST_UNITS_DEFINE_CONVERSION_FACTOR(my_units::watt_base_unit, my_units::voltampere_base_unit, int, 1);

template<typename T>
using watt_t = boost::units::quantity<my_units::watt, T>;

template<typename T>
using voltampere_t = boost::units::quantity<my_units::voltampere, T>;


int main()
{
    watt_t<double> watt(watt_t<double>::from_value(2));

    voltampere_t<double> va(voltampere_t<double>::from_value(2));
 
    watt_t<double> x = boost::units::sqrt(watt * watt + watt_t<double>(va) * watt_t<double>(va));
}

       
    //how to achieve
    //using watt       = boost::units::unit<power_dimension, boost::units::si_system>;
    //using voltampere = boost::units::unit<power_dimension, boost::units::si_system>;