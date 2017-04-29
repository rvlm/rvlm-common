#pragma once
#include <cmath>

namespace rvlm {
namespace core {

template <typename valueType>
class Cuboid {
public:
    typedef valueType ValueType;

    ValueType const& getX1() const { return mX1; }
    ValueType const& getY1() const { return mY1; }
    ValueType const& getZ1() const { return mZ1; }
    ValueType const& getX2() const { return mX2; }
    ValueType const& getY2() const { return mY2; }
    ValueType const& getZ2() const { return mZ2; }
    ValueType const& getProjectionX() const { return mX2 - mX1; }
    ValueType const& getProjectionY() const { return mY2 - mY1; }
    ValueType const& getProjectionZ() const { return mZ2 - mZ1; }
    ValueType const& getLengthX() const { return std::abs(getProjectionX()); }
    ValueType const& getLengthY() const { return std::abs(getProjectionY()); }
    ValueType const& getLengthZ() const { return std::abs(getProjectionZ()); }

private:
    ValueType mX1;
    ValueType mY1;
    ValueType mZ1;
    ValueType mX2;
    ValueType mY2;
    ValueType mZ2;
};

} // namespace core
} // namespace rvlm
