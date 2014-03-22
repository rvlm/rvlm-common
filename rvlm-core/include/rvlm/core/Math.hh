#pragma once
#include <cmath>

namespace rvlm {
namespace core {
namespace math {

/**
 * Rounds to nearest integer.
 * Please note that despite its name this function returns a floating point
 * number, not integral. Just like @c std::floor and @c std::ceil, though.
 */
template <typename T>
inline T round(const T& x) { return std::floor(x+static_cast<T>(1)/2); }

} // namespace math
} // namespace core
} // namespace rvlm
