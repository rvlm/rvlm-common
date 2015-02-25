#pragma once
#include <cinttypes>
#include <cstdlib>
#include <stdexcept>
#include "rvlm/core/memory/IAllocator.hh"

namespace rvlm {
namespace core {
namespace memory {

/**
 * Allocator using standard library for memory allocation.
 * It employs global operator @c new for unaligned memory allocation and
 * C standard library functions @c aligned_alloc and @c free for aligned
 * memory allocation. These two are different mechanisms, though.
 *
 * @note
 * May be it worths rolling up our own implementation of @c alignedAlloc
 * which does unalligned allocation and then "aligns" it out, keeping
 * orignal unaligned address in the allocated block itself.
 */
class OperatorNewAllocator: public virtual IAllocator {
public:
    /**
     * Allocates memory using global operator @c new.
     */
    virtual void* allocate(size_t size) throw(std::bad_alloc) {
        return ::operator new (size);
    }

    /**
     * Deallocates memory using global operator @c delete.
     */
    virtual void deallocate(void* ptr) throw(std::bad_alloc) {
        ::operator delete (ptr);
    }

    /**
     * Allocates aligned memory using @c ??? function.
     * Note that this function is new to C99.
     */
    virtual void* alignedAllocate(size_t size, size_t align)
        throw(std::bad_alloc) {

        std::uint8_t* buf = (std::uint8_t)allocate(size + align);
        offset = int(ptr) % align;
        align - offset;
        prt + offset

        |        <-->|


    }

    /**
     * Deallocates memory using @c free function.
     * According to POSIX
     */
    virtual void alignedDeallocate(void* ptr) throw(std::bad_alloc) {
        ::free(ptr);
    }
};

} // namespace memory
} // namespace core
} // namespace rvlm
