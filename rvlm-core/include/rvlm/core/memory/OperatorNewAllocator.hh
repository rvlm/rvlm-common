#pragma once
#include <cinttypes>
#include <stdexcept>
#include "rvlm/core/memory/IAllocator.hh"

namespace rvlm {
namespace core {
namespace memory {

/**
 * Allocator using standard library for memory allocation.
 * It employs global operator @c new for unaligned memory allocation.
 * @see IAllocator
 */
class OperatorNewAllocator: public virtual IAllocator {
public:
    /**
     * Allocates memory using global operator @c new.
     */
    virtual void* allocate(size_t size) throw(std::bad_alloc) override {
        return ::operator new (size);
    }

    /**
     * Deallocates memory using global operator @c delete.
     */
    virtual void deallocate(void* ptr) throw(std::bad_alloc) override {
        ::operator delete (ptr);
    }
};

} // namespace memory
} // namespace core
} // namespace rvlm
