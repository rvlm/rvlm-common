#pragma once
#include <cinttypes>
#include <stdexcept>
#include <memory>
#include "rvlm/core/memory/Allocator.hh"

namespace rvlm {
namespace core {
namespace memory {

/**
 * Wraps @c Allocator for STL.
 */
template <typename T = void>
class StlAllocator {
private:
    /**
     * @internal
     * Underlying allocator which actually allocates memory.
     *
     */
    Allocator *mActualAllocator;

public:
    typedef std::allocator<T>::value_type  value_type;
    typedef std::allocator<T>::pointer     pointer;
    typedef std::allocator<T>::size_type   size_type;

    /**
     * Constructs class instance with underlying allocator.
     * The underlying allocator must be properly initialized before passing
     * to this constructor, and it will not be deleted or uninitialized in any
     * other way after this STL allocator is destroyed.
     */
    StlAllocator(const Allocator* alloc) throw() {
        mActualAllocator = alloc;
    }

    /**
     * Creates a copy of STL allocator binded to different type.
     * This copy constructor is a part of @c std::allocator public interface.
     */
    template <typename TOtherValue>
    StlAllocator(const StlAllocator<TOtherValue> &other) throw() {
        mActualAllocator = other.mActualAllocator;
    }

    /**
     * Destroys class instance.
     * Actually does nothing as there is no need to destroy underlying
     * allocator.
     */
    ~StlAllocator() throw() {
    }

    /**
     * Allocates memory using underlying allocator object.
     * This function is a part of @c std::allocator public interface.
     * @param n    Number of instances to allocate.
     * @param hint Allocation hint (see STL documentation).
     * @return     Pointer to allocated memory.
     */
    pointer allocate(size_type n, std::allocator<void>::const_pointer hint = 0)
                                                                     override {
        (void)hint; // unused
        return static_cast<pointer>(mActualAllocator->allocate(n*sizeof(T)));
    }

    /**
     * Deallocates memory using underlying allocator object.
     */
    void deallocate(pointer p, size_type n) override {
        mActualAllocator->deallocate(p);
    }
};

/**
 *
 */
template <>
inline StlAllocator<void>::pointer StlAllocator<void>::allocate(
                    StlAllocator<void>::size_type n,
                    std::allocator<void>::const_pointer hint = 0) {

    (void)hint; // unused
    return static_cast<StlAllocator<void>::pointer>(
        mActualAllocator->allocate(n));
}

} // namespace memory
} // namespace core
} // namespace rvlm
