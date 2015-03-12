#pragma once
#include <memory>

namespace rvlm {

template<typename T>
class object_ptr: public std::shared_ptr<T> {
public:

    object_ptr(const object_ptr&) noexcept = default;

    template<typename T1, typename =
             typename std::enable_if<std::is_convertible<T1*, T*>::value>::type>
    object_ptr(const object_ptr<T1>& r) noexcept
            : std::shared_ptr<T>(r) { }

    object_ptr(object_ptr<T>&& r) noexcept
            : std::shared_ptr<T>(std::move(r)) { }

    template<typename T1, typename =
             typename std::enable_if<std::is_convertible<T1*, T*>::value>::type>
    object_ptr(object_ptr<T1>&& r) noexcept
            : std::shared_ptr<T>(std::move(r)) { }

    object_ptr& operator=(const object_ptr&) noexcept = default;

    template<typename T1>
    object_ptr& operator=(const object_ptr<T1>& r) noexcept {
        this->std::shared_ptr<T>::operator=(r);
        return *this;
    }

    object_ptr& operator=(object_ptr&& r) noexcept {
        this->std::shared_ptr<T>::operator=(std::move(r));
        return *this;
    }

    template<class T1>
    object_ptr& operator=(object_ptr<T1>&& r) noexcept {
        this->std::shared_ptr<T>::operator=(std::move(r));
        return *this;
    }

private:

    void check_not_null(const std::shared_ptr<T>& p) {
        if (!p)
            throw std::bad_alloc();
    }

    object_ptr(const std::shared_ptr<T>& p) {
        check_not_null(p);
    }

template <typename T1, typename TAlloc, typename... TArgs>
friend object_ptr<T1> allocate_object(const TAlloc& a, TArgs&&... args);

template <typename T1, typename... TArgs>
friend object_ptr<T1> make_object(TArgs&&... args);

};

template <typename T, typename TAlloc, typename... TArgs>
object_ptr<T> allocate_object(const TAlloc& a, TArgs&&... args) {
    return object_ptr<T>(
                std::allocate_shared<T>(a, std::forward<TArgs>(args)...));
}

template <typename T, typename... TArgs>
object_ptr<T> make_object(TArgs&&... args) {
    return object_ptr<T>(std::make_shared<T>(std::forward<TArgs>(args)...));
}

} // namespace rvlm
