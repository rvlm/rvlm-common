#pragma once

#include <type_traits>

namespace rvlm {
namespace core {

// TODO: Think if it's safe to mark (almost) everything as 'noexcept'.
template <typename TInt=int>
struct HalfOpenRange {
private:
    using SentinelType = typename std::enable_if<std::is_integral<TInt>::value>::type;

public:
    TInt const start;
    TInt const stop;

    HalfOpenRange(TInt start, TInt stop)
        : start(start), stop(std::max(start, stop)) {}

    HalfOpenRange(HalfOpenRange<TInt> const& other)
        : start(other.start), stop(other.stop) {}

    bool contains(TInt const& val) {
        return (start <= val && val < stop);
    }

    class const_iterator {
    public:
        const_iterator& operator ++ () {
            ++mCurrentValue; return *this;
        }

        const_iterator& operator --() {
            --mCurrentValue; return *this;
        }

        TInt const& operator *() const {
            return mCurrentValue;
        }

        bool operator == (const_iterator const& other) const {
            return mCurrentValue == other.mCurrentValue;
        }

        bool operator != (const_iterator const& other) const {
            return !(*this == other);
        }

        const_iterator(const_iterator const& other)
                : mCurrentValue(other.mCurrentValue) {}

    private:
        const_iterator(TInt currVal, TInt rangeEnd)
            : mCurrentValue(currVal) {}

        TInt mCurrentValue;

        friend class HalfOpenRange<TInt>;
    };

    const_iterator begin() const {
        return const_iterator(start, stop);
    }

    const_iterator end() const {
        return const_iterator(stop, stop);
    }
};

}
}
