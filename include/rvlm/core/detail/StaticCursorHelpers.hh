#pragma once
namespace rvlm {
namespace core {
namespace detail {

template <typename TSolidArray3d, int Axis0, int Axis1, int Axis2>
class GetCursorHelper {
public:

    using CursorType = typename TSolidArray3d::CursorType;
    using IndexType  = typename TSolidArray3d::IndexType;

    static
    CursorType get(TSolidArray3d const& array,
                   IndexType i0, IndexType i1, IndexType i2);
};

#define RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION(A0, A1, A2) \
    template <typename TSolidArray3d>                                    \
    class GetCursorHelper<TSolidArray3d, (A0), (A1), (A2)> {             \
    public:                                                              \
        using CursorType = typename TSolidArray3d::CursorType;           \
        using IndexType  = typename TSolidArray3d::IndexType;            \
                                                                         \
        static                                                           \
        CursorType get(TSolidArray3d const& array,                       \
                       IndexType i0, IndexType i1, IndexType i2) {       \
                                                                         \
            return array.getCursor(i##A0, i##A1, i##A2);                 \
        }                                                                \
    }

RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION(0, 1, 2);
RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION(0, 2, 1);
RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION(1, 0, 2);
RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION(1, 2, 0);
RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION(2, 0, 1);
RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION(2, 1, 0);
#undef RVLM_CORE_DETAIL_STATIC_CURSOR_HELPER_SPECIALIZATION


template <typename TSolidArray3d, int Axis>
class MoveCursorHelper {
public:

    using CursorType = typename TSolidArray3d::CursorType;
    using IndexType  = typename TSolidArray3d::IndexType;

    static
    void moveToNext(TSolidArray3d const& array, CursorType& cursor);

    static
    void moveToPrev(TSolidArray3d const& array, CursorType& cursor);
};

#define RVLM_CORE_DETAIL_MOVE_CURSOR_HELPER_SPECIALIZATION(Axis, Sym)    \
    template <typename TSolidArray3d>                                    \
    class MoveCursorHelper<TSolidArray3d, Axis> {                        \
    public:                                                              \
        using CursorType = typename TSolidArray3d::CursorType;           \
        using IndexType  = typename TSolidArray3d::IndexType;            \
                                                                         \
        static                                                           \
        void moveToNext(TSolidArray3d const& array, CursorType& cursor) {\
            array.cursorMoveToNext##Sym(cursor);                         \
        }                                                                \
                                                                         \
        static                                                           \
        void moveToPrev(TSolidArray3d const& array, CursorType& cursor) {\
            array.cursorMoveToPrev##Sym(cursor);                         \
        }                                                                \
    }

RVLM_CORE_DETAIL_MOVE_CURSOR_HELPER_SPECIALIZATION(0, X);
RVLM_CORE_DETAIL_MOVE_CURSOR_HELPER_SPECIALIZATION(1, Y);
RVLM_CORE_DETAIL_MOVE_CURSOR_HELPER_SPECIALIZATION(2, Z);
#undef RVLM_CORE_DETAIL_MOVE_CURSOR_HELPER_SPECIALIZATION

}
}
}