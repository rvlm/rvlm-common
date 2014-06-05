#pragma once

namespace rvlm {
namespace core {

/**
 * Helper class for disabling copy constructor and assignment operator
 * in derived class (may be with multiple inheritance).
 * Use it as in the example below, once for the whole inheritance tree which
 * should be protected against copying:
 * @code
 *     class DerivedClass: public BaseClass, public NonAssignable {
 *         ...
 *     };
 * @endcode
 *
 * This class was inspired by Qt's @c Q_DISABLE_COPY macro, please read their
 * documentation page for more information. Also note that they say that
 * disabling copying for the base class only may be not enough in some cases.
 *
 * @see http://stackoverflow.com/questions/6077143
 * @see http://stackoverflow.com/questions/19854371
 * @see http://qt-project.org/doc/qt-5.0/qtcore/qobject.html#Q_DISABLE_COPY
 */
class NonAssignable {
private:
    NonAssignable(NonAssignable const&);
    NonAssignable& operator=(NonAssignable const&);
public:
    NonAssignable() {}
};

} // namespace core
} // namespace rvlm
