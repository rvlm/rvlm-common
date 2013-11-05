#pragma once
#include <allocator>
#include <stdexcept>

namespace Rvlm {
namespace Core {

/**
 * Three-dimensional array in a solid block of memory.
 *
 *
 */
template <
    typename valueType,
    typename indexType = size_t,
    typename allocType = std::allocator<valueType> >
class SolidArray3d {
public:

    typedef allocType AllocatorType;
    typedef indexType IndexType;
    typedef valueType ValueType;
    typedef void*     CursorType;

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
        const AllocatorType& allocator = AllocatorType()) {

        // Cause 'IndexType' may be a signed type, ensure that all three
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
        mAllocator  = allocator;
        mData       = allocator.allocate(mTotalCount);
    }

    /**
     * Destructs array with all its data.
     * The allocator passed to constructor is also used for deallocation.
     */
    ~SolidArray() {
        mAllocator.deallocate(mData, mTotalCount);
    }

    /**
     * Gets items count along X dimension.
     * This value is equal to the argument @a countX passed to constructor.
     * @see getCountY
     * @see getCountZ
     * @see getTotalCount
     */
    IndexType getCountX() const { return mCountX; }

    /**
     * Gets items count along Y dimension.
     * This value is equal to the argument @a countY passed to constructor.
     * @see getCountX
     * @see getCountZ
     * @see getTotalCount
     */
    IndexType getCountY() const { return mCountY; }

    /**
     * Gets items count along Z dimension.
     * This value is equal to the argument @a countZ passed to constructor.
     * @see getCountX
     * @see getCountY
     * @see getTotalCount
     */
    IndexType getCountZ() const { return mCountZ; }

    /**
     * Gets items count along X dimension.
     * This value is equal to the argument @a countX passed to constructor.
     * @see getCountX
     * @see getCountY
     * @see getCountZ
     * @see getTotalCount
     */
    IndexType getTotalCount() const { return mTotalCount; }


    /**
     * Accesses item for reading by its coordinates.
     * For performance reasons no range checking is performed.
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

    void cursorPrevX(CursorType& cursor) const {
        cursor -= mOffsetDX;
    }

    void cursorNextX(CursorType& cursor) const {
        cursor += mOffsetDX;
    }

    void cursorPrevY(CursorType& cursor) const {
        cursor -= mOffsetDY;
    }

    void cursorNextY(CursorType& cursor) const {
        cursor += mOffsetDY;
    }

    void cursorPrevZ(CursorType& cursor) const {
        // Note that there is no 'mOffsetDZ' member for the sake
        // of performance since it is a constant expression which
        // would be not optimized by compiler if stored in a class
        // member variable.
        cursor -= sizeof(ValueType);
    }

    void cursorNextZ(CursorType& cursor) const {
        cursor += sizeof(ValueType);
    }

private:

    IndexType itemOffset(IndexType ix, IndexType iy, IndexType iz) const {
        return ix*mOffsetDX + iy*mOffsetDY + iz*sizeof(ValueType);
    }

    ValueType* itemAddress(IndexType ix, IndexType iy, IndexType iz) const {
        return reinterpret_cast<ValueType*>(
            reinterpret_cast<void*>(mData) + itemOffset(ix, iy, iz));
    }

    IndexType      mOffsetDX;
    IndexType      mOffsetDY;
    AllocatorType  mAllocator;
    ValueType*     mData;
};

} // namespace Core
} // namespace Rvlm

