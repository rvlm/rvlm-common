#pragma once

namespace rvlm {
namespace core {

/**
 * @namespace rvlm.constants
 * This namespace contains various mathematical and physycal universal
 * constants. The physical one must be stated in the SI unit system with
 * dimention name specified in parentheses.
 */
template <typename TFloatType>
class Constants {

/**
 * Euclid pi number (dimensionless quantity).
 * This constant is defines here because C++ standard library does not
 * guarantee to have @c M_PI defined.
 * @see http://stackoverflow.com/questions/1727881.
 */
static const FloatType PI = 3.141592653589793;

/**
 * Light's speed in vacuum (meter/second).
 * @see http://en.wikipedia.org/wiki/Speed_of_light
 */
static const FloatType C = 299792501.0;

/**
 * Electric constant or vacuum permittivity (farad/meter).
 * @see http://en.wikipedia.org/wiki/Vacuum_permittivity
 */
static const FloatType EPS_0 = 8.8541878187E-12;

/**
 * Magnetic constant or vacuum permeability (Henry/meter).
 * @see http://en.wikipedia.org/wiki/Vacuum_permeability
 */
static const FloatType MU_0 = 4*PI*1E-7;

/** @todo Find proper name and write documentation. */
static const FloatType ETA_0 = 120*PI;

};

} // namespace core
} // namespace rvlm
