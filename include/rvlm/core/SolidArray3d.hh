#pragma once
#include <stdexcept>
#include "rvlm/core/memory/Allocator.hh"

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
template <typename TValue>
class SolidArray3d {
public:

    typedef std::int_fast32_t IndexType;
    typedef TValue ValueType;
    typedef TValue*  CursorType;

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
        const Allocator* allocator = 0)
        throw(std::bad_alloc, std::range_error) {

        // Because 'IndexType' may be a signed type, ensure that all three
        // counts are positive. Intermediate constant 'zero' is here to
        // prevent "signed-unsigned comparison" compiler warning.
        const IndexType zero = 0;
        if (countX <= zero || countY <= zero || countZ <= zero)
            throw std::range_error("wrong array count");

        mCountX     = countX;
        mCountY     = countY;
        mCountZ     = countZ;
        mTotalCount = countX * countY * countZ;
        mOffsetDX   = sizeof(ValueType) * countY * countZ;
        mOffsetDY   = sizeof(ValueType) * countZ;
        mAllocator  = allocator ? allocator : &mStdAllocator;
        mData       = mAllocator->allocate(mTotalCount);
    }

    /**
     * Destructs array with all its data.
     * The allocator passed to constructor is also used for deallocation.
     */
    ~SolidArray3d() {
        mAllocator->deallocate(mData);
    }

    /**
     * Gets number of items along X dimension.
     * This value is constant and equals to the argument @a countX passed
     * to constructor.
     * @see getCountY
     * @see getCountZ
     * @see getTotalCount
     */
    IndexType getCountX() const { return mCountX; }

    /**
     * Gets number of items along Y dimension.
     * This value is constant and equals to the argument @a countY passed
     * to constructor.
     * @see getCountX
     * @see getCountZ
     * @see getTotalCount
     */
    IndexType getCountY() const { return mCountY; }

    /**
     * Gets number of items along Z dimension.
     * This value is constant and equals to the argument @a countZ passed
     * to constructor.
     * @see getCountX
     * @see getCountY
     * @see getTotalCount
     */
    IndexType getCountZ() const { return mCountZ; }

    /**
     * Gets total number of items count in array.
     * This value is constant and equals to the product of all three count
     * arguments passed to constructor (@a countX * @a countY * @a countZ).
     * @see getCountX
     * @see getCountY
     * @see getCountZ
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
     * @edcode
     * For performance reasons, this function DOES NOT check whether its
     * arguments are all in valid ranges. These checks may be enabled for
     * debug purposes with macro @c RVLM_CONFIG_RANGE_CHECK == 1.
     *
     * @see at(const CursorType&) const
     * @see RVLM_CONFIG_RANGE_CHECK
     */
    ValueType& at(IndexType ix, IndexType iy, IndexType iz) const {
        return *itemAddress(ix, iy, iz);
    }

    /**
     * Accesses item for both reading and writing by its coordinates.
     * For performance reasons no range checking is performed.
     */
    ValueType& at(IndexType ix, IndexType iy, IndexType iz) {
        return *itemAddress(ix, iy, iz);
    }

    /**
     * Accesses item pointed by cursor for reading only.
     * @see REF_SECTION_CURSORS
     */
    ValueType& at(const CursorType& cursor) const {
        return *reinterpret_cast<ValueType*>(cursor);
    }

    /**
     * Accesses item pointed by cursor for reading and writing.
     * @see REF_SECTION_CURSORS
     */
    ValueType& at(const CursorType& cursor) {
        return *reinterpret_cast<ValueType*>(cursor);
    }

    /**
     * Constructs cursor pointing to given item.
     * This method is the only way to obtain a valid cursor object.
     * Arguments @a ix, @a iy and @iz are the coordinates of the item which
     * is pointed by the created cursor.
     * @see REF_SECTION_CURSORS
     */
    CursorType getCursor(IndexType ix, IndexType iy, IndexType iz) const {
        return reinterpret_cast<CursorType>(itemAddress(ix, iy, iz));
    }

    void cursorMoveTo(
        CursorType& cursor, IndexType ix, IndexType iy, IndexType iz) const {
        cursor = getCursor(ix, iy, iz);
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
        // Note that there is no 'mOffsetDZ' member for the sake
        // of performance since it is a constant expression which
        // would be not optimized by compiler if stored in a class
        // member variable.
        cursor -= sizeof(ValueType);
    }

    void cursorMoveToNextZ(CursorType& cursor) const {
        // See comment in cursorMoveToPrevZ method.
        cursor += sizeof(ValueType);
    }

private:

    IndexType itemOffset(IndexType ix, IndexType iy, IndexType iz) const {
        //RVLM_RANGE_ASSERT(0 <= ix && ix < mCountX);
        //RVLM_RANGE_ASSERT(0 <= iy && ix < mCountY);
        //RVLM_RANGE_ASSERT(0 <= iz && ix < mCountZ);
        return ix*mOffsetDX + iy*mOffsetDY + iz*sizeof(ValueType);
    }

    ValueType* itemAddress(IndexType ix, IndexType iy, IndexType iz) const {
        return reinterpret_cast<ValueType*>(
            reinterpret_cast<void*>(mData) + itemOffset(ix, iy, iz));
    }

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

} // namespace Core
} // namespace Rvlm
