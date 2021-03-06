#pragma once
#include <cstdint>
#include <stdexcept>

namespace rvlm {
namespace core {
namespace memory {

/**
 * Interface for unaligned memory allocators
 *
 * The term "allocator" means the object which is capable to return on request
 * a block of usable memory of specified size, just like @c malloc function or
 * operator @c new. Here are the guidelines for implementing allocators:
 *
 *   - memory block is obtained using @c allocate method;
 *   - obtained memory alignment is not guarranteed;
 *   - obtained memory values are not initialized in any way;
 *   - obtained memory may be arbitrarily used within requested size;
 *   - if memory allocation fails for whatever reason, @c std::bad_alloc
 *     exception must be thrown;
 *   - obtained memory must be utilized using @c deallocate method of exactly
 *     the same allocator which was used to obtain it;
 *   - if memory deallocation fails for whatever reason, @c std::bad_alloc
 *     exception must be thrown;
 *   - memory must not be used after utilization.
 *
 * Please, remember to use public virtual inheritance when implementing
 * this interface.
 *
 * @see AlignedAllocator
 * @see OperatorNewAllocator
 * @see StlAllocator
 * @see http://stackoverflow.com/a/318466/1447225
 */
class Allocator {
public:

    /**
     * Allocates @a size bytes of memory with no alignment guarranty.
     * Returns pointer to allocated memory. This pointer doesn't have to be
     * aligned in any way.
     * @see deallocate
     */
    virtual void* allocate(size_t size) throw (std::bad_alloc) = 0;

    /**
     * Deallocates previously allocated memory.
     * @see allocate
     */
    virtual void deallocate(void* ptr) throw (std::bad_alloc) = 0;
};

} // namespace memory
} // namespace core
} // namespace rvlm
