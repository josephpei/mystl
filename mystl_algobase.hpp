#ifndef _MYSTL_ALGOBASE_H
#define _MYSTL_ALGOBASE_H
#include "mystl_iterator_base.hpp"

namespace numb {
template <typename _Tp>
inline const _Tp& Min(const _Tp& a, const _Tp& b) {
    return b < a ? b : a;
}

template <typename _Tp>
inline const _Tp& Max(const _Tp& a, const _Tp& b) {
    return a < b ? b : a;
}

template <typename _Tp, typename _Compare>
inline const _Tp& Min(const _Tp& a, const _Tp& b, _Compare comp) {
    return comp(b < a) ? b : a;
}

template <typename _Tp, typename _Compare>
inline const _Tp& Max(const _Tp& a, const _Tp& b, _Compare comp) {
    return comp(a < b) ? b : a;
}

template <typename _Tp>
inline void Swap(_Tp& _a, _Tp& _b)
{
    _Tp _tmp = _a;
    _a = _b;
    _b = _tmp;
}

template<typename _Tp, size_t _Nm>
inline void Swap(_Tp (&_a)[_Nm], _Tp (&_b)[_Nm])
{
    for (size_t _n = 0; _n < _Nm; ++_n)
        swap(_a[_n], _b[_n]);
}

template <typename _InIter, typename _OutIter>
inline _OutIter Copy(_InIter first, _InIter last, _OutIter result) {
    for (; first != last; ++result, ++first) *result = *first;
    return result;
}

template <typename _T1, typename _T2>
inline void _Construct(_T1* p, const _T2& value) {
    ::new (static_cast<void*>(p)) _T1(value);
}

template <typename _Tp>
inline void _Destroy(_Tp* __pointer) {
    __pointer->~_Tp();
}

template <typename _Tp>
inline _Tp* __Addressof(_Tp& __r) throw() {
    return reinterpret_cast<_Tp*>(
        &const_cast<char&>(reinterpret_cast<const volatile char&>(__r)));
}

template <bool _TrivialValueType>
struct _Uninitialized_copy {
    template <typename _InputIterator, typename _ForwardIterator>
    static _ForwardIterator _uninit_copy(_InputIterator _first,
                                         _InputIterator _last,
                                         _ForwardIterator _result) {
        _ForwardIterator _cur = _result;
        for (; _first != _last; ++_first, ++_cur)
            numb::_Construct(numb::__Addressof(*_cur), *_first);
        return _cur;
    }
};

template <>
struct _Uninitialized_copy<true> {
    template <typename _InputIterator, typename _ForwardIterator>
    static _ForwardIterator _uninit_copy(_InputIterator _first,
                                         _InputIterator _last,
                                         _ForwardIterator _result) {
        return numb::Copy(_first, _last, _result);
    }
};

template <typename _InputIterator, typename _ForwardIterator>
inline _ForwardIterator Uninitialized_copy(_InputIterator _first,
                                           _InputIterator _last,
                                           _ForwardIterator _result) {
    typedef typename Iterator_traits<_InputIterator>::value_type _ValueType1;
    typedef typename Iterator_traits<_ForwardIterator>::value_type _ValueType2;

    return numb::_Uninitialized_copy<
        (__is_trivial(_ValueType1) &&
         __is_trivial(_ValueType2))>::_uninit_copy(_first, _last, _result);
}
//__is_trivial is a compiler intrinsic provided by G++



}
#endif
