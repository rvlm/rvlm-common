#pragma once
#include <cstddef>
#include <stdexcept>
#include <utility>
#include "rvlm/core/memory/Allocator.hh"
#include "rvlm/core/memory/OperatorNewAllocator.hh"
#include "rvlm/core/NonAssignable.hh"

namespace rvlm {
namespace core {

/**
 * Tridimensional array in a solid block of memory.
 *
 * It allocates memory in a way different from ordinary C and C++ arrays. All
 * data is stored in contigurous block of memory, layd out from the first
 * dimension (@em X) to the last one (@em Z). This kind of memory layout is
 * also known as "Pascal array", which is opposed to "Fortran array" and, of
 * course, "C array".
 *
 * Like with ordinary arrays, after the class instance is created, it is not
 * possible to change its dimensions. Moreover, neither range checking, not
 * object initialization in individual cells is performed. This is done
 * intentionally for runtime performance.
 */
template <typename TValue, typename TIndex = std::size_t>
class SolidArray3d: public rvlm::core::NonAssignable {
public:

    using Allocator         = rvlm::core::memory::Allocator;
    using StandardAllocator = rvlm::core::memory::OperatorNewAllocator;
    using IndexType         = TIndex;
    using ValueType         = TValue;
    using CursorType        = TValue*;

    /**
     * Constructs array with given dimentions and allocator.
     * Arguments @a countX, @a countY and @a countZ must be all positive,
     * or @c std::range_error exception will be thrown.
     * Argument @a allocator specifies the allocator object to use for
     * memory allocation. The allocation occurs only once for the entire
     * object's lifetime, as well as deallocation. Allocator should throw
     * @c std::bad_alloc exception in case of errors.
     */
    SolidArray3d(
        IndexType countX,
        IndexType countY,
        IndexType countZ,
        ValueType const& fillValue,
        Allocator* allocator = 0)
        throw(std::bad_alloc, std::range_error) {

        // Because 'IndexType' may be a signed type, ensure that all three
        // counts are positive. Intermediate constant 'zero' is here to
        // prevent "signed-unsigned comparison" compiler warning.
        const IndexType zero = 0;
        if (countX <= zero || countY <= zero || countZ <= zero)
            throw std::range_error("wrong array count");

        mBeginX     = 0;
        mBeginY     = 0;
        mBeginZ     = 0;
        mCountX     = countX;
        mCountY     = countY;
        mCountZ     = countZ;
        mTotalCount = countX * countY * countZ;
        mOffsetDX   = countY * countZ;
        mOffsetDY   = countZ;
        mAllocator  = allocator ? allocator
                                : static_cast<Allocator*>(&mStdAllocator);

        // TODO: use unique_ptr<ValueType*> (with polymorphic allocator attached?!)
        mData = static_cast<ValueType*>(mAllocator->allocate(mTotalCount * sizeof(ValueType)));
        fill(fillValue);
    }

    template <typename TTriple>
    SolidArray3d(TTriple const& counts,
                 ValueType const& fillValue,
                 Allocator* allocator = 0)
                 throw (std::bad_alloc, std::range_error)
        : SolidArray3d(std::get<0>(counts),
                       std::get<1>(counts),
                       std::get<2>(counts),
                       fillValue,
                       allocator) {}

    // NB: Ranges are semi-inclusive: [start, stop).
    SolidArray3d(
            HalfOpenRange<TIndex> const& xRange,
            HalfOpenRange<TIndex> const& yRange,
            HalfOpenRange<TIndex> const& zRange,
            ValueType const& fillValue,
            Allocator* allocator = 0)
            throw(std::bad_alloc, std::range_error)
                : SolidArray3d(xRange.stop - xRange.start,
                               yRange.stop - yRange.start,
                               zRange.stop - zRange.start,
                               fillValue,
                               allocator) {

        mBeginX = xRange.start;
        mBeginY = yRange.start;
        mBeginZ = zRange.start;
    }

    /**
     * Destructs array with all its data.
     * The allocator passed to constructor is also used for deallocation.
     */
    ~SolidArray3d() {
        mAllocator->deallocate(mData);
    }

    void fill(ValueType const& val) {
        ValueType *data = mData;
        std::fill(data, data + mTotalCount, val);
    }

    IndexType getBeginX() const { return mBeginX; }
    IndexType getBeginY() const { return mBeginY; }
    IndexType getBeginZ() const { return mBeginZ; }

    IndexType getEndX() const { return mCountX - mBeginX; }
    IndexType getEndY() const { return mCountY - mBeginY; }
    IndexType getEndZ() const { return mCountZ - mBeginZ; }

    /**
     * Gets number of items along X dimension.
     * This value is constant and equals to the argument @a countX passed
     * to constructor.
     */
    IndexType getCountX() const { return mCountX; }

    /**
     * Gets number of items along Y dimension.
     * This value is constant and equals to the argument @a countY passed
     * to constructor.
     */
    IndexType getCountY() const { return mCountY; }

    /**
     * Gets number of items along Z dimension.
     * This value is constant and equals to the argument @a countZ passed
     * to constructor.
     */
    IndexType getCountZ() const { return mCountZ; }

    /**
     * Gets total number of items count in array.
     * This value is constant and equals to the product of all three count
     * arguments passed to constructor (@a countX * @a countY * @a countZ).
     */
    IndexType getTotalCount() const { return mTotalCount; }


    /**
     * Accesses item for reading by its coordinates.
     * Argument indexes @a ix, @a iy and @a iz must satisfy the following
     * range condition:
     * @code
     *     0 <= ix && ix < getCountX()
     *     0 <= iy && iy < getCountY()
     *     0 <= iz && iz < getCountZ()
     * @endcode
     * For performance reasons, this function DOES NOT check whether its
     * arguments are all in valid ranges. These checks may be enabled for
     * debug purposes with macro @c RVLM_CONFIG_RANGE_CHECK == 1.
     *
     * @see RVLM_CONFIG_RANGE_CHECK
     */
    ValueType& at(IndexType ix, IndexType iy, IndexType iz) const {
        size_t idx = itemIndex(ix, iy, iz);
        if (idx >= mTotalCount)
            throw std::runtime_error("Fuck");

        return mData[idx];
    }

    /**
     * Accesses item for both reading and writing by its coordinates.
     * For performance reasons no range checking is performed.
     */
    ValueType& at(IndexType ix, IndexType iy, IndexType iz) {
        size_t idx = itemIndex(ix, iy, iz);
        if (idx >= mTotalCount)
            throw std::runtime_error("Fuck");

        return mData[idx];
    }

    /**
     * Accesses item pointed by cursor for reading only.
     * @see REF_SECTION_CURSORS
     */
    ValueType& at(const CursorType& cursor) const {
        if (cursor < mData || cursor >= mData + mTotalCount)
            throw std::runtime_error("Fuck");
        return *cursor;
    }

    /**
     * Accesses item pointed by cursor for reading and writing.
     * @see REF_SECTION_CURSORS
     */
    ValueType& at(const CursorType& cursor) {
        return *cursor;
    }

    /**
     * Constructs cursor pointing to given item.
     * This method is the only way to obtain a valid cursor object.
     * Arguments @a ix, @a iy and @a iz are the coordinates of the item which
     * is pointed by the created cursor.
     * @see REF_SECTION_CURSORS
     */
    CursorType getCursor(IndexType ix, IndexType iy, IndexType iz) const {
        return itemAddress(ix, iy, iz);
    }

    void cursorMoveTo(
        CursorType& cursor, IndexType ix, IndexType iy, IndexType iz) const {
        cursor = itemAddress(ix, iy, iz);
    }

    void cursorMoveToPrevX(CursorType& cursor) const {
        cursor -= mOffsetDX;
    }

    void cursorMoveToNextX(CursorType& cursor) const {
        cursor += mOffsetDX;
    }

    void cursorMoveToPrevY(CursorType& cursor) const {
        cursor -= mOffsetDY;
    }

    void cursorMoveToNextY(CursorType& cursor) const {
        cursor += mOffsetDY;
    }

    void cursorMoveToPrevZ(CursorType& cursor) const {
        --cursor;
    }

    void cursorMoveToNextZ(CursorType& cursor) const {
        ++cursor;
    }

    void cursorCoordinates(CursorType cursor, IndexType& ix, IndexType& iy, IndexType& iz) {
        if (cursor < mData || cursor >= mData + mTotalCount)
            throw std::runtime_error("Fuck");

        size_t idxl = cursor - mData;
        iz = idxl % mCountZ;
        idxl /= mCountZ;

        iy = idxl % mCountY;
        idxl /= mCountY;

        ix = idxl;

        ix += mBeginX;
        iy += mBeginY;
        iz += mBeginZ;
    }

private:

    size_t itemIndex(IndexType ix, IndexType iy, IndexType iz) const {
        //RVLM_RANGE_ASSERT(0 <= ix && ix < mCountX);
        //RVLM_RANGE_ASSERT(0 <= iy && ix < mCountY);
        //RVLM_RANGE_ASSERT(0 <= iz && ix < mCountZ);
        size_t aix = static_cast<size_t>(ix - mBeginX);
        size_t aiy = static_cast<size_t>(iy - mBeginY);
        size_t aiz = static_cast<size_t>(iz - mBeginZ);
        return aix*mOffsetDX + aix*mOffsetDY + aiz;
    }

    ValueType* itemAddress(IndexType ix, IndexType iy, IndexType iz) const {
        return &mData[itemIndex(ix, iy, iz)];
    }

    IndexType      mBeginX;
    IndexType      mBeginY;
    IndexType      mBeginZ;
    IndexType      mCountX;
    IndexType      mCountY;
    IndexType      mCountZ;
    IndexType      mTotalCount;
    IndexType      mOffsetDX;
    IndexType      mOffsetDY;
    Allocator*     mAllocator;
    ValueType*     mData;
    StandardAllocator mStdAllocator;
};

} // namespace core
} // namespace rvlm

