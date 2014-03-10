#ifndef _N_MYSTL_ITERATOR_BASE_H
#define _N_MYSTL_ITERATOR_BASE_H

#include <stddef.h>

namespace numb {
struct Input_iterator_tag {};
struct Output_iterator_tag {};
struct Forward_iterator_tag : public Input_iterator_tag {};
struct Bidirectional_iterator_tag : public Forward_iterator_tag {};
struct Random_access_iterator_tag : public Bidirectional_iterator_tag {};

template <typename _Category, typename _Tp, typename _Distance = ptrdiff_t,
          typename _Pointer = _Tp*, typename _Reference = _Tp&>
struct Iterator {
    typedef _Category iterator_category;
    typedef _Tp value_type;
    typedef _Distance difference_type;
    typedef _Pointer pointer;
    typedef _Reference reference;
};

template <typename _Iter>
struct Iterator_traits {
    typedef typename _Iter::iterator_category iterator_category;
    typedef typename _Iter::value_type value_type;
    typedef typename _Iter::difference_type difference_type;
    typedef typename _Iter::pointer pointer;
    typedef typename _Iter::reference reference;
};

/// Partial specialization for pointer type
template <typename _Tp>
struct Iterator_traits<_Tp*> {
    typedef Random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};


template <typename _Tp>
struct Iterator_traits<const _Tp*> {
    typedef Random_access_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef ptrdiff_t difference_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;
};

template <typename _Iter>
inline typename Iterator_traits<_Iter>::iterator_category
_Iterator_category(const _Iter&)
{ return typename Iterator_traits<_Iter>::iterator_category(); }

template <typename _InputIterator>
inline typename Iterator_traits<_InputIterator>::difference_type
_Distance(_InputIterator _first, _InputIterator _last, Input_iterator_tag)
{
    typename Iterator_traits<_InputIterator>::difference_type n = 0;
    while (_first != _last) {
        ++_first;
        ++n;
    }
    return n;
}

template <typename _RandomAccessIterator>
inline typename Iterator_traits<_RandomAccessIterator>::difference_type
_Distance(_RandomAccessIterator _first, _RandomAccessIterator _last, Random_access_iterator_tag)
{
    return _last - _first;
}


template <typename _Iter>
inline typename Iterator_traits<_Iter>::difference_type
Distance(_Iter _first, _Iter _last)
{
    return _Distance(_first, _last, _Iterator_category(_first));
}

template <typename _InputIterator, typename _Distance>
inline void _Advance(_InputIterator& _i, _Distance _n, Input_iterator_tag)
{
    while(_n--)
        ++_i;
}

template <typename _BidirectionalIterator, typename _Distance>
inline void _Advance(_BidirectionalIterator& _i, _Distance _n, Bidirectional_iterator_tag)
{
    if (_n > 0)
        while(_n--)
            ++_i;
    else
        while(_n++)
            --_i;
}

template <typename _RandomAccessIterator, typename _Distance>
inline void _Advance(_RandomAccessIterator& _i, _Distance _n, Random_access_iterator_tag)
{
    _i += _n;
}

template <typename _Iter, typename _Distance>
inline void Advance(_Iter& i, _Distance n)
{
    typename Iterator_traits<_Iter>::difference_type d = n;
    _Advance(i, d, _Iterator_category(i));
}

template <typename _ForwardIterator>
inline _ForwardIterator Next(_ForwardIterator _x, typename Iterator_traits<_ForwardIterator>::difference_type _n = 1)
{
    Advance(_x, _n);
    return _x;
}


template <typename _BidirectionalIterator>
inline _BidirectionalIterator Prev(_BidirectionalIterator _x, typename Iterator_traits<_BidirectionalIterator>::difference_type _n = 1)
{
    Advance(_x, -_n);
    return _x;
}
}

#endif
