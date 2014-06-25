#pragma once
#include <cinttypes>
#include <stdexcept>

namespace rvlm {
namespace core {
namespace memory {

/**
 * Interface for aligned memory allocators.
 * The term "aligned memory allocator" means the object which is capable to
 * return on request a block of usable memory of specified size, just like
 * ordinary allocator does, but with start address aligned to some boundary.
 * For example, some SSE instructions operands must be aligned to 16 bytes
 * boundary in order to operate properly.
 *
 * The guidelines for implementing aligned memory allocators are the following:
 *   - Memory block is obtained using @c alignedAllocate method.
 *   - Obtained memory alignment is guarranted to be as specified.
 *   - Obtained memory values are not initialized in any way.
 *   - Obtained memory may be arbitraryly used within requested size.
 *   - If memory allocation fails for whatever reason, @c std::bad_alloc
 *     exception must be thrown.
 *   - Obtained memory must be utilized using @c alignedDeallocate method of
 *     exactly the same allocator which was used to obtain it.
 *   - If memory deallocation fails for whatever reason, @c std::bad_alloc
 *     exception must be thrown.
 *   - Memory must not be used after utilization.
 *
 * Please, remember to use public virtual inheritance when implementing
 * this interface.
 * @see IAllocator
 * @see http://stackoverflow.com/a/318466/1447225
 */
class IAlignedAllocator {
public:

    /**
     * Destructor is absent from class.
     */
    ~IAlignedAllocator() = delete;

    /**
     * Allocates @a size bytes of memory with alignment guarranty.
     * Desired alignment is passed through @a align parameter, which value
     * must be the positive power of two. Method returns pointer to allocated
     * memory.
     * @see alignedDeallocate
     */
    virtual void* alignedAllocate(size_t size, size_t align)
        throw (std::bad_alloc) = 0;

    /**
     * Deallocates previously allocated aligned memory.
     * @see alignedAllocate
     */
    virtual void alignedDeallocate(void* ptr)
        throw (std::bad_alloc) = 0;
};

} // namespace memory
} // namespace core
} // namespace rvlm
