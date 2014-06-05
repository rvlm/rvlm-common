#pragma once
#include <cstdint>
#include <type_traits>

namespace rvlm {
namespace core {

/**
 *
 */
template<
    typename TEnum,
    typename TInt = std::uint_fast32_t>
struct Flags {
private:
    /**
     * @internal
     * Raw bitmask value of enumeration flags.
     * The rest of this class does nothing more than simply wraps this value
     * with convenience operators and methods, with hope they will be optimized
     * and inlined out by the compiler, leading to machine code accessing this
     * value directly without any overhead.
     */
    TInt value;

    /**
     * @internal
     * Returns class instance with raw value set to @a val.
     * This method is heavily used for implementing operators on sets.
     */
    static Flags<TEnum,TInt> fromValue(TInt val) {
        auto result = Flags<TEnum,TInt>();
        result.value = val;
        return result;
    }

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
    typedef TInt IntType;

    /**
     * Constructs empty set of flags.
     */
    Flags()
        : value(0) {}

    /**
     * Constructs set with single flag @c item included.
     */
    Flags(const TEnum& item)
        : value(static_cast<TInt>(1) <<
                static_cast<std::underlying_type<TEnum>::type>(item)) {}

    /**
     * Includes flag for @a item into this set.
     * Nothing bad happens if the @item has been already included, though.
     */
    void include(const TEnum& item) {
        *this += item;
    }

    /**
     * Excludes flag for @a item from this set.
     * Nothing bad happens if the @item has been already excluded, though.
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
    Flags<TEnum,TInt>& operator &= (const Flags<TEnum,TInt>& other) {
        return value &= other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum,TInt>& operator |= (const Flags<TEnum,TInt>& other) {
        value |= other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum,TInt>& operator ^= (const Flags<TEnum,TInt>& other) {
        value ^= other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum,TInt>& operator *= (const Flags<TEnum,TInt>& other) {
        return *this &= other;
    }

    /**
     *
     */
    Flags<TEnum,TInt>& operator += (const Flags<TEnum,TInt>& other) {
        return *this |= other;
    }

    /**
     *
     */
    Flags<TEnum,TInt>& operator -= (const Flags<TEnum,TInt>& other) {
        value &= value ^ other.value;
        return *this;
    }

    /**
     *
     */
    Flags<TEnum,TInt> operator & (const Flags<TEnum,TInt>& other) const {
        return Flags<TEnum,TInt>::fromValue(value & other.value);
    }

    /**
     *
     */
    Flags<TEnum,TInt> operator | (const Flags<TEnum,TInt>& other) const {
        return Flags<TEnum,TInt>::fromValue(value | other.value);
    }

    /**
     *
     */
    Flags<TEnum,TInt> operator ^ (const Flags<TEnum,TInt>& other) const {
        return Flags<TEnum,TInt>::fromValue(value ^ other.value);
    }

    /**
     *
     */
    Flags<TEnum,TInt> operator * (const Flags<TEnum,TInt>& other) const {
        return Flags<TEnum,TInt>::fromValue(value & other.value);
    }

    /**
     *
     */
    Flags<TEnum,TInt> operator + (const Flags<TEnum,TInt>& other) const {
        return Flags<TEnum,TInt>::fromValue(value | other.value);
    }

    /**
     *
     */
    Flags<TEnum,TInt> operator - (const Flags<TEnum,TInt>& other) const {
        return Flags<TEnum,TInt>::fromValue(value & (value ^ other.value));
    }

    /**
     *
     */
    bool operator == (const Flags<TEnum,TInt>& other) const {
        return value == other.value;
    }

    /**
     *
     */
    bool operator != (const Flags<TEnum,TInt>& other) const {
        return value != other.value;
    }

    /**
     *
     */
    bool operator <= (const Flags<TEnum,TInt>& other) const {
        return *this | other == other;
    }

    /**
     *
     */
    bool operator < (const Flags<TEnum,TInt>& other) const {
        return *this <= other && *this != other;
    }

    /**
     *
     */
    bool operator >= (const Flags<TEnum,TInt>& other) const {
        return other <= *this;
    }

    /**
     *
     */
    bool operator > (const Flags<TEnum,TInt>& other) const {
        return other < *this;
    }
};

/**
 *
 */
template<
    typename TEnum,
    typename TInt>
Flags<TEnum,TInt> operator | (const TEnum& a, const TEnum& b) {
    return Flags<TEnum,TInt>(a) | b;
}

/**
 *
 */
template<
    typename TEnum,
    typename TInt>
Flags<TEnum,TInt> operator + (const TEnum& a, const TEnum& b) {
    return Flags<TEnum,TInt>(a) + b;
}

} // namespace core
} // namespace rvlm
