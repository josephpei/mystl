#ifndef _N_MYSTL_ALLOCATOR_H
#define _N_MYSTL_ALLOCATOR_H
#include <new>
#include <cstddef>

namespace numb {
template <typename _Tp>
class Allocator {
public:
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp& reference;
    typedef const _Tp& const_reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    // c++11 use noexcept replace throw()
    Allocator() throw() {}

    Allocator(const Allocator&) throw() {}

    template <typename Other>
    Allocator(const Allocator<Other>&) throw() {}

    ~Allocator() throw() {}

    template <typename U>
    struct rebind {
        typedef Allocator<U> other;
    };

    pointer address(reference x) { return static_cast<_Tp*>(&x); }

    const_pointer address(const_reference x) {
        return static_cast<const _Tp*>(&x);
    }

    pointer allocate(size_type n, const void* = 0) {
        if (n > this->max_size()) throw std::bad_alloc();
        return static_cast<_Tp*>(::operator new(n * sizeof(_Tp)));
    }

    void deallocate(pointer p, size_type) { ::operator delete(p); }

    void construct(pointer p, const _Tp& val) { ::new ((void*)p) _Tp(val); }

    void destroy(pointer p) { p->~_Tp(); }

    // no const, c++98 compiler error
    size_type max_size() const { return size_t(-1) / sizeof(_Tp); }
};

template <>
class Allocator<void> {
public:
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef void* pointer;
    typedef const void* const_pointer;
    typedef void value_type;

    template <typename _Tp>
    struct rebind {
        typedef Allocator<_Tp> other;
    };
};

template <typename _T1, typename _T2>
inline bool operator==(const Allocator<_T1>&, const Allocator<_T2>&) {
    return true;
}

template <typename _Tp>
inline bool operator==(const Allocator<_Tp>&, const Allocator<_Tp>&) {
    return true;
}

template <typename _T1, typename _T2>
inline bool operator!=(const Allocator<_T1>&, const Allocator<_T2>&) {
    return false;
}

template <typename _Tp>
inline bool operator!=(const Allocator<_Tp>&, const Allocator<_Tp>&) {
    return false;
}
}

#endif

