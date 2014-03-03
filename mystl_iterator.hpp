#ifndef _MYSTL_ITERATOR_H
#define _MYSTL_ITERATOR_H
#include "mystl_iterator_base.hpp"

namespace numb {
using numb::Iterator;
using numb::Iterator_traits;

// Its primary purpose is to convert an iterator that is
// not a class, e.g. a pointer, into an iterator that is a class.
// The _Container parameter exists solely so that different containers
// using this template can instantiate different types, even if the
// _Iterator parameter is the same.
template <typename _Iter, typename _Container>
class _Normal_iterator {
protected:
    _Iter _M_current;
    typedef Iterator_traits<_Iter> _traits_type;

public:
    typedef _Iter iterator_type;
    typedef typename _traits_type::iterator_category iterator_category;
    typedef typename _traits_type::value_type value_type;
    typedef typename _traits_type::difference_type difference_type;
    typedef typename _traits_type::reference reference;
    typedef typename _traits_type::pointer pointer;

    _Normal_iterator() : _M_current(_Iter()) {}
    explicit _Normal_iterator(const _Iter& i) : _M_current(i) { }

    // Allow iterator to const iterator conversion

    reference operator*() const
    { return *_M_current; }

    pointer operator->() const
    { return _M_current; }

    _Normal_iterator & operator++()
    {
        ++_M_current;
        return *this;
    }

    _Normal_iterator operator++(int)
    { return _Normal_iterator(_M_current++); }

    _Normal_iterator& operator--()
    {
        --_M_current;
        return *this;
    }

    _Normal_iterator operator--(int)
    { return _Normal_iterator(_M_current--); }

    // Random Access iterator requirements
    reference operator[](const difference_type& _n) const
    { return _M_current[_n]; }

    _Normal_iterator& operator+=(const difference_type& _n)
    { _M_current += _n; return *this; }

    _Normal_iterator operator+(const difference_type& _n) const
    { return _Normal_iterator(_M_current + _n); }

    _Normal_iterator& operator-=(const difference_type& _n)
    { _M_current -= _n; return *this; }

    _Normal_iterator operator-(const difference_type& _n) const
    { return _Normal_iterator(_M_current - _n); }

    const _Iter& base() const
    { return _M_current; }
};

// Forward iterator requiements
template <typename _IterL, typename _IterR, typename _Container>
inline bool operator==(const _Normal_iterator<_IterL, _Container> &_lhs,
        const _Normal_iterator<_IterR, _Container> &_rhs)
{ return _lhs.base() == _rhs.base(); }


template <typename _Iter, typename _Container>
inline bool operator==(const _Normal_iterator<_Iter, _Container> &_lhs,
        const _Normal_iterator<_Iter, _Container> &_rhs)
{ return _lhs.base() == _rhs.base(); }

template <typename _IterL, typename _IterR, typename _Container>
inline bool operator!=(const _Normal_iterator<_IterL, _Container> &_lhs,
        const _Normal_iterator<_IterR, _Container> &_rhs)
{ return _lhs.base() != _rhs.base(); }

template <typename _Iter, typename _Container>
inline bool operator!=(const _Normal_iterator<_Iter, _Container> &_lhs,
        const _Normal_iterator<_Iter, _Container> &_rhs)
{ return _lhs.base() != _rhs.base(); }

// Random access iterator requiements
template <typename _IterL, typename _IterR, typename _Container>
inline bool operator<(const _Normal_iterator<_IterL, _Container> &_lhs,
        const _Normal_iterator<_IterR, _Container> &_rhs)
{ return _lhs.base() < _rhs.base(); }

template <typename _Iter, typename _Container>
inline bool operator<(const _Normal_iterator<_Iter, _Container> &_lhs,
        const _Normal_iterator<_Iter, _Container> &_rhs)
{ return _lhs.base() < _rhs.base(); }

template <typename _IterL, typename _IterR, typename _Container>
inline bool operator>(const _Normal_iterator<_IterL, _Container> &_lhs,
        const _Normal_iterator<_IterR, _Container> &_rhs)
{ return _lhs.base() > _rhs.base(); }

template <typename _Iter, typename _Container>
inline bool operator>(const _Normal_iterator<_Iter, _Container> &_lhs,
        const _Normal_iterator<_Iter, _Container> &_rhs)
{ return _lhs.base() > _rhs.base(); }

template <typename _IterL, typename _IterR, typename _Container>
inline bool operator<=(const _Normal_iterator<_IterL, _Container> &_lhs,
        const _Normal_iterator<_IterR, _Container> &_rhs)
{ return _lhs.base() <= _rhs.base(); }

template <typename _Iter, typename _Container>
inline bool operator<=(const _Normal_iterator<_Iter, _Container> &_lhs,
        const _Normal_iterator<_Iter, _Container> &_rhs)
{ return _lhs.base() <= _rhs.base(); }

template <typename _IterL, typename _IterR, typename _Container>
inline bool operator>=(const _Normal_iterator<_IterL, _Container> &_lhs,
        const _Normal_iterator<_IterR, _Container> &_rhs)
{ return _lhs.base() >= _rhs.base(); }

template <typename _Iter, typename _Container>
inline bool operator>=(const _Normal_iterator<_Iter, _Container> &_lhs,
        const _Normal_iterator<_Iter, _Container> &_rhs)
{ return _lhs.base() >= _rhs.base(); }

//accept mixed iterator/const_iterator
template <typename _IterL, typename _IterR, typename _Container>
inline typename _Normal_iterator<_IterL, _Container>::difference_type
operator-(const _Normal_iterator<_IterL, _Container>& _lhs,
        const _Normal_iterator<_IterR, _Container>& _rhs)
{ return _lhs.base() - _rhs.base(); }

template <typename _Iter, typename _Container>
inline typename _Normal_iterator<_Iter, _Container>::difference_type
operator-(const _Normal_iterator<_Iter, _Container>& _lhs,
        const _Normal_iterator<_Iter, _Container>& _rhs)
{ return _lhs.base() - _rhs.base(); }

template <typename _Iter, typename _Container>
inline typename _Normal_iterator<_Iter, _Container>::difference_type
operator+(const _Normal_iterator<_Iter, _Container>& _lhs,
        const _Normal_iterator<_Iter, _Container>& _rhs)
{ return _lhs.base() - _rhs.base(); }
}

#endif
