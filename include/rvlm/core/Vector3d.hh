#pragma once

namespace rvlm {
namespace core {

template<typename valueType>
class Vector3d {
public:
    typedef valueType ValueType;

    Vector3d(ValueType const& x, ValueType const& y, ValueType const& z)
            : X(x), Y(y), Z(z) {}

    ValueType getX() const { return X; }
    ValueType getY() const { return Y; }
    ValueType getZ() const { return Z; }
private:
    ValueType X;
    ValueType Y;
    ValueType Z;
};

}//namespace core
}//namespace rvlm

