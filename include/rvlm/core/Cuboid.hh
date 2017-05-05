#pragma once
#include <cmath>

namespace rvlm {
namespace core {

template <typename valueType>
class Cuboid {
public:
    typedef valueType ValueType;

    Cuboid(ValueType const& x1, ValueType const& y1, ValueType const& z1,
           ValueType const& x2, ValueType const& y2, ValueType const& z2)
        : mX1(x1), mY1(y1), mZ1(z1),
          mX2(x2), mY2(y2), mZ2(z2) {}

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
