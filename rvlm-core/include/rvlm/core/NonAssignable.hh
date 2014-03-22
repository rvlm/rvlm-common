#pragma once

namespace rvlm {
namespace core {

/**
 * Helper class for disabling copy constructor and assignment operator
 * in derived class (with help of multiple inheritance).
 * Use it as in the example below:
 * @code
 *     class DerivedClass: public BaseClass, public NonAssignable {
 *     };
 * @endcode
 *
 * This class was inspired by Qt's @c Q_DISABLE_COPY macro, please read their
 * documentation page for more information.
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
