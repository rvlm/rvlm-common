#pragma once

namespace rvlm {
namespace core {

template <typename valueType,
          typename indexType,
          typename cursorType>
class ITraversable3D {
public:

    typedef indexType IndexType;
    typedef valueType ValueType;
    typedef cursorType CursorType;

    virtual IndexType getCountX() const = 0;
    virtual IndexType getCountY() const = 0;
    virtual IndexType getCountZ() const = 0;

    IndexType getTotalCount() const {
        return getCountX()*getCountY()*getCountZ();
    }

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
     * arguments are all in valid ranges.
     *
     * @see at(const CursorType&) const
     */
    ValueType& at(IndexType ix, IndexType iy, IndexType iz) const = 0;
    ValueType& at(IndexType ix, IndexType iy, IndexType iz) = 0;

    ValueType& at(const CursorType& cursor) const = 0;
    ValueType& at(const CursorType& cursor) = 0;

    /**
     * Constructs cursor pointing to given item.
     * This method is the only way to obtain a valid cursor object.
     * Arguments @a ix, @a iy and @iz are the coordinates of the item which
     * is pointed by the created cursor.
     */
    CursorType getCursor(IndexType ix, IndexType iy, IndexType iz) const = 0;

    void cursorMoveTo(
        CursorType& cursor, IndexType ix, IndexType iy, IndexType iz) const = 0;

    void cursorMoveToPrevX(CursorType& cursor) const = 0;
    void cursorMoveToPrevY(CursorType& cursor) const = 0;
    void cursorMoveToPrevZ(CursorType& cursor) const = 0;
    void cursorMoveToNextX(CursorType& cursor) const = 0;
    void cursorMoveToNextY(CursorType& cursor) const = 0;
    void cursorMoveToNextZ(CursorType& cursor) const = 0;
};

} // namespace core
} // namespace rvlm
