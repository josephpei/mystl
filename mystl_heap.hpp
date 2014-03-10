#ifndef _MYSTL_HEAP_H
#define _MYSTL_HEAP_H
#include "mystl_iterator_base.hpp"

namespace numb {
// Heap-manipulation functions: push_heap, pop_heap, make_heap, sort_heap

template <typename _RandomAccessIterator, typename _Distance, typename _Tp>
void _Push_heap(_RandomAccessIterator _first, _Distance _holeIndex,
                _Distance _topIndex, _Tp _value) {
    _Distance _parent = (_holeIndex - 1) / 2;
    while (_holeIndex > _topIndex && *(_first + _parent) < _value) {
        *(_first + _holeIndex) = *(_first + _parent);
        _holeIndex = _parent;
        _parent = (_holeIndex - 1) / 2;
    }
    *(_first + _holeIndex) = _value;
}

template <typename _RandomAccessIterator>
inline void Push_heap(_RandomAccessIterator _first,
                      _RandomAccessIterator _last) {
    typedef typename Iterator_traits<_RandomAccessIterator>::value_type
        _ValueType;
    typedef typename Iterator_traits<_RandomAccessIterator>::difference_type
        _DistanceType;

    _ValueType _value = *(_last - 1);
    _Push_heap(_first, _DistanceType((_last - _first) - 1), _DistanceType(0),
               _value);
}

template <typename _RandomAccessIterator, typename _Distance, typename _Tp,
          typename _Compare>
void _Push_heap(_RandomAccessIterator _first, _Distance _holeIndex,
                _Distance _topIndex, _Tp _value, _Compare _comp) {
    _Distance _parent = (_holeIndex - 1) / 2;
    while (_holeIndex > _topIndex && _comp(*(_first + _parent), _value)) {
        *(_first + _holeIndex) = *(_first + _parent);
        _holeIndex = _parent;
        _parent = (_holeIndex - 1) / 2;
    }
    *(_first + _holeIndex) = _value;
}

template <typename _RandomAccessIterator, typename _Compare>
inline void Push_heap(_RandomAccessIterator _first, _RandomAccessIterator _last,
                      _Compare _comp) {
    typedef typename Iterator_traits<_RandomAccessIterator>::value_type
        _ValueType;
    typedef typename Iterator_traits<_RandomAccessIterator>::difference_type
        _DistanceType;

    _ValueType _value = *(_last - 1);
    _Push_heap(_first, _DistanceType((_last - _first) - 1), _DistanceType(0),
               _value, _comp);
}

template <typename _RandomAccessIterator, typename _Distance, typename _Tp>
void _Adjust_heap(_RandomAccessIterator _first, _Distance _holeIndex,
                  _Distance _len, _Tp _value) {
    const _Distance _topIndex = _holeIndex;
    _Distance _secondChild = _holeIndex;
    while (_secondChild < (_len - 1) / 2) {
        _secondChild = 2 * (_secondChild + 1);
        if (*(_first + _secondChild) < *(_first + (_secondChild - 1)))
            _secondChild--;
        *(_first + _holeIndex) = *(_first + _secondChild);
        _holeIndex = _secondChild;
    }
    if ((_len & 1) == 0 && _secondChild == (_len - 2) / 2) {
        _secondChild = 2 * (_secondChild + 1);
        *(_first + _holeIndex) = *(_first + (_secondChild - 1));
        _holeIndex = _secondChild - 1;
    }
    _Push_heap(_first, _holeIndex, _topIndex, _value);
}

template <typename _RandomAccessIterator>
inline void _Pop_heap(_RandomAccessIterator _first, _RandomAccessIterator _last,
                      _RandomAccessIterator _result) {
    typedef typename Iterator_traits<_RandomAccessIterator>::value_type
        _ValueType;
    typedef typename Iterator_traits<_RandomAccessIterator>::difference_type
        _DistanceType;

    _ValueType _value = *_result;
    *_result = *_first;
    _Adjust_heap(_first, _DistanceType(0), _DistanceType(_last - _first),
                 _value);
}

template <typename _RandomAccessIterator>
inline void Pop_heap(_RandomAccessIterator _first,
                     _RandomAccessIterator _last) {
    typedef typename Iterator_traits<_RandomAccessIterator>::value_type
        _ValueType;

    if (_last - _first > 1) {
        --_last;
        _Pop_heap(_first, _last, _last);
    }
}

template <typename _RandomAccessIterator, typename _Distance, typename _Tp,
          typename _Compare>
void _Adjust_heap(_RandomAccessIterator _first, _Distance _holeIndex,
                  _Distance _len, _Tp _value, _Compare _comp) {
    const _Distance _topIndex = _holeIndex;
    _Distance _secondChild = _holeIndex;
    while (_secondChild < (_len - 1) / 2) {
        _secondChild = 2 * (_secondChild + 1);
        if (_comp(*(_first + _secondChild), *(_first + (_secondChild - 1))))
            _secondChild--;
        *(_first + _holeIndex) = *(_first + _secondChild);
        _holeIndex = _secondChild;
    }
    if ((_len & 1) == 0 && _secondChild == (_len - 2) / 2) {
        _secondChild = 2 * (_secondChild + 1);
        *(_first + _holeIndex) = *(_first + (_secondChild - 1));
        _holeIndex = _secondChild - 1;
    }
    _Push_heap(_first, _holeIndex, _topIndex, _value, _comp);
}

template <typename _RandomAccessIterator, typename _Compare>
inline void _Pop_heap(_RandomAccessIterator _first, _RandomAccessIterator _last,
                      _RandomAccessIterator _result, _Compare _comp) {
    typedef typename Iterator_traits<_RandomAccessIterator>::value_type
        _ValueType;
    typedef typename Iterator_traits<_RandomAccessIterator>::difference_type
        _DistanceType;

    _ValueType _value = *_result;
    *_result = *_first;
    _Adjust_heap(_first, _DistanceType(0), _DistanceType(_last - _first),
                 _value, _comp);
}

template <typename _RandomAccessIterator, typename _Compare>
inline void Pop_heap(_RandomAccessIterator _first, _RandomAccessIterator _last,
                     _Compare _comp) {
    if (_last - _first > 1) {
        --_last;
        _Pop_heap(_first, _last, _last, _comp);
    }
}

template <typename _RandomAccessIterator>
void Make_heap(_RandomAccessIterator _first, _RandomAccessIterator _last) {
    typedef typename Iterator_traits<_RandomAccessIterator>::value_type
        _ValueType;
    typedef typename Iterator_traits<_RandomAccessIterator>::difference_type
        _DistanceType;

    if (_last - _first < 2) return;

    const _DistanceType _len = _last - _first;
    _DistanceType _parent = (_len - 2) / 2;
    while (true) {
        _ValueType _value = *(_first + _parent);
        _Adjust_heap(_first, _parent, _len, _value);
        if (_parent == 0) return;
        _parent--;
    }
}

template <typename _RandomAccessIterator, typename _Compare>
void Make_heap(_RandomAccessIterator _first, _RandomAccessIterator _last,
               _Compare _comp) {
    typedef typename Iterator_traits<_RandomAccessIterator>::value_type
        _ValueType;
    typedef typename Iterator_traits<_RandomAccessIterator>::difference_type
        _DistanceType;

    if (_last - _first < 2) return;

    const _DistanceType _len = _last - _first;
    _DistanceType _parent = (_len - 2) / 2;
    while (true) {
        _ValueType _value = *(_first + _parent);
        _Adjust_heap(_first, _parent, _len, _value, _comp);
        if (_parent == 0) return;
        _parent--;
    }
}

template <typename _RandomAccessIterator>
void Sort_heap(_RandomAccessIterator _first, _RandomAccessIterator _last) {
    while (_last - _first > 1) {
        --_last;
        _Pop_heap(_first, _last, _last);
    }
}

template <typename _RandomAccessIterator, typename _Compare>
void Sort_heap(_RandomAccessIterator _first, _RandomAccessIterator _last,
               _Compare _comp) {
    while (_last - _first > 1) {
        -_last;
        _Pop_heap(_first, _last, _last, _comp);
    }
}
}

#endif
