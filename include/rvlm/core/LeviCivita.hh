#pragma once
#include <stdexcept>

namespace rvlm {
namespace core {


template <typename TInt>
constexpr TInt between(TInt x, TInt a, TInt b) {
    return a <= x && x <= b;
}

template <typename TInt>
constexpr TInt leviCivita(TInt i0, TInt i1, TInt i2) {
    return (i0 < 0 || i0 > 2 ||
            i1 < 0 || i1 > 2 ||
            i2 < 0 || i2 > 2) ? throw std::invalid_argument("")
            : (i0 == 0 && i1 == 1 && i2 == 2) ?  1
            : (i0 == 0 && i1 == 2 && i2 == 1) ? -1
            : (i0 == 1 && i1 == 2 && i2 == 0) ?  1
            : (i0 == 1 && i1 == 0 && i2 == 2) ? -1
            : (i0 == 2 && i1 == 0 && i2 == 1) ?  1
            : (i0 == 2 && i1 == 1 && i2 == 0) ? -1
            : 0;
}

}
}


