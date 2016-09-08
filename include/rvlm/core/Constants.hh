#pragma once

namespace rvlm {
namespace core {
/**
 * This class acts as a namespace and contains various mathematical and
 * physycal universal constants. The physical one must be stated in the SI unit
 * system with dimention name specified in parentheses.
 * @see http://en.wikipedia.org/wiki/International_System_of_Units
 */
template <typename TFloat>
class Constants {

public:
    /**
     * Euclid pi number (dimensionless quantity).
     * This constant is defines here because C++ standard library does not
     * guarantee to have @c M_PI defined.
     * @see http://stackoverflow.com/questions/1727881
     */
    static TFloat PI() { return 3.141592653589793; }

    /**
     * Light's speed in vacuum (meter/second).
     * @see http://en.wikipedia.org/wiki/Speed_of_light
     */
    static TFloat C() { return 299792501.0; }

    /**
     * Electric constant or vacuum permittivity (farad/meter).
     * @see http://en.wikipedia.org/wiki/Vacuum_permittivity
     */
    static TFloat EPS_0() { return 8.8541878187E-12; }

    /**
     * Magnetic constant or vacuum permeability (Henry/meter).
     * @see http://en.wikipedia.org/wiki/Vacuum_permeability
     */
    static TFloat MU_0() { return PI() * 4E-7; }

    /** @todo Find proper name and write documentation. */
    static TFloat ETA_0() { return 120*PI(); }
};

} // namespace core
} // namespace rvlm
