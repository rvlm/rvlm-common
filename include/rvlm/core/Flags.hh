#pragma once
#include <cstdint>
#include <type_traits>

namespace rvlm {
namespace core {

/**
 *
 */
template<typename TEnum>
struct Flags {
public:

    /**
     * Convenience alias for enumeration type being wrapped.
     * This may be useful in some rare situations.
     */
    typedef TEnum EnumType;

    /**
     * Convenience alias for underlying integer type implementing bitmask.
     * This may be useful in some rare situations.
     */
    typedef std::uint_fast32_t IntType;

    /**
     * Constructs empty set of flags.
     */
    Flags()
        : value(0) {}

    /**
      Constructs set with single flag @c item included.
     */
    Flags(const TEnum& item)
        : value(static_cast<IntType>(1) << static_cast<IntType>(item)) {}

    /**
     * Includes flag for @a item into this set.
     * Nothing bad happens if the @a item has been already included, though.
     */
    void include(const TEnum& item) {
        *this += item;
    }

    /**
     * Excludes flag for @a item from this set.
     * Nothing bad happens if the @a item has been already excluded, though.
     */
    void exclude(const TEnum& item) {
        *this -= item;
    }

    /**
     * Return whether this set is (does not have any flags included).
     * The following two expressions are semantically equivalent:
     * @code
     *     flags.empty()
     *     flags == Flags<TEnum, TInt>()
     * @endcode
     */
    bool empty() const {
        return this->value == 0;
    }

    /**
     * Returns whether this set contains flag for @a item.
     * The following two expressions are semantically equivalent:
     * @code
     *     flag.contains(item)
     *     item <= flags
     * @endcode
     */
    bool contains(const TEnum& item) const {
        return item <= *this;
    }

    /**
     *
     */
    Flags<TEnum>& operator &= (const Flags<TEnum>& other) {
        return value &= other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum>& operator |= (const Flags<TEnum>& other) {
        value |= other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum>& operator ^= (const Flags<TEnum>& other) {
        value ^= other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum>& operator *= (const Flags<TEnum>& other) {
        return *this &= other;
    }

    /**
     *
     */
    Flags<TEnum>& operator += (const Flags<TEnum>& other) {
        return *this |= other;
    }

    /**
     *
     */
    Flags<TEnum>& operator -= (const Flags<TEnum>& other) {
        value &= value ^ other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum> operator & (const Flags<TEnum>& other) const {
        return Flags<TEnum>::fromValue(value & other.value);
    }

    /**
     *
     */
    Flags<TEnum> operator | (const Flags<TEnum>& other) const {
        return Flags<TEnum>::fromValue(value | other.value);
    }

    /**
     *
     */
    Flags<TEnum> operator ^ (const Flags<TEnum>& other) const {
        return Flags<TEnum>::fromValue(value ^ other.value);
    }

    /**
     *
     */
    Flags<TEnum> operator * (const Flags<TEnum>& other) const {
        return Flags<TEnum>::fromValue(value & other.value);
    }

    /**
     *
     */
    Flags<TEnum> operator + (const Flags<TEnum>& other) const {
        return Flags<TEnum>::fromValue(value | other.value);
    }

    /**
     *
     */
    Flags<TEnum> operator - (const Flags<TEnum>& other) const {
        return Flags<TEnum>::fromValue(value & (value ^ other.value));
    }

    /**
     *
     */
    bool operator == (const Flags<TEnum>& other) const {
        return value == other.value;
    }

    /**
     *
     */
    bool operator != (const Flags<TEnum>& other) const {
        return value != other.value;
    }

    /**
     *
     */
    bool operator <= (const Flags<TEnum>& other) const {
        return *this | other == other;
    }

    /**
     *
     */
    bool operator < (const Flags<TEnum>& other) const {
        return *this <= other && *this != other;
    }

    /**
     *
     */
    bool operator >= (const Flags<TEnum>& other) const {
        return other <= *this;
    }

    /**
     *
     */
    bool operator > (const Flags<TEnum>& other) const {
        return other < *this;
    }

private:
    /**
     * @internal
     * Raw bitmask value of enumeration flags.
     * The rest of this class does nothing more than simply wraps this value
     * with convenience operators and methods, with hope they will be optimized
     * and inlined out by the compiler, leading to machine code accessing this
     * value directly without any overhead.
     */
    IntType value;

    /**
     * @internal
     * Returns class instance with raw value set to @a val.
     * This method is heavily used for implementing operators on sets.
     */
    static Flags<TEnum> fromValue(const IntType val) {
        auto result = Flags<TEnum>();
        result.value = val;
        return result;
    }
};

/**
 *
 */
template<typename TEnum>
Flags<TEnum> operator | (const TEnum& a, const TEnum& b) {
    return Flags<TEnum>(a) | b;
}

/**
 *
 */
template<typename TEnum>
Flags<TEnum> operator + (const TEnum& a, const TEnum& b) {
    return Flags<TEnum>(a) + b;
}

} // namespace core
} // namespace rvlm
