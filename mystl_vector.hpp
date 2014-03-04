#ifndef _MYSTL_VECTOR_H
#define _MYSTL_VECTOR_H
#include "mystl_iterator.hpp"
#include "mystl_algobase.hpp"

namespace numb{
template <typename _Tp>
class Vector {
public:
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp& reference;
    typedef const _Tp& const_reference;
    typedef _Normal_iterator<pointer, Vector> Iterator;
    typedef _Normal_iterator<const_pointer, Vector> Const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

private:
    _Tp* _M_start;
    _Tp* _M_finish;
    _Tp* _M_end_of_storage;

protected:

public:
    Vector() : _M_start(NULL), _M_finish(NULL), _M_end_of_storage(NULL) {}

    explicit Vector(size_type _n) { _M_fill_initialize(_n); }

    Vector(const Vector& rhs)
        : _M_start(NULL), _M_finish(NULL), _M_end_of_storage(NULL) {
        _M_start = new _Tp[rhs.capacity()];
        _M_finish = _M_start + rhs.size();
        _M_end_of_storage = _M_start + rhs.capacity();

        for (size_type i = 0; i < size(); ++i)
            *(_M_start + i) = *(rhs._M_start + i);
    }

    Vector& operator=(const Vector& rhs) {
        Vector copy = rhs;
        Swap(*this, copy);
        return *this;
    }

    ~Vector() throw() { delete[] _M_start; }

    Iterator begin() throw() { return Iterator(_M_start); }
    Const_iterator cbegin() throw() { return Const_iterator(_M_start); }
    Iterator end() throw() { return Iterator(_M_finish); }
    Const_iterator cend() throw() { return Const_iterator(_M_finish); }

    size_type size() const throw() { return size_type(_M_finish - _M_start); }

    size_type capacity() const throw() {
        return size_type(_M_end_of_storage - _M_start);
    }

    bool empty() const throw() { return begin() == end(); }

    reference operator[](size_type _n) {
        if (_n < 0 || _n >= size()) throw;
        return *(_M_start + _n);
    }

    const_reference operator[](size_type _n) const {
        if (_n < 0 || _n >= size()) throw;
        return *(_M_start + _n);
    }

    reference front() { return *begin(); }
    const_reference front() const { return *begin(); }
    reference back() { return *(end() - 1); }
    const_reference back() const { return *(end() - 1); }

    pointer data() throw() { return _M_start; }

    void push_back(const value_type& _x) {
        if (_M_finish == _M_end_of_storage) _reallocate(2 * Max(size(), size_type(1)));
        *_M_finish = _x;
        ++_M_finish;
    }

    value_type pop_back() {
        if (empty()) throw;
        --_M_finish;
        value_type tmp = *(_M_start + _M_finish);
        _shrink();
        return tmp;
    }
    // stl pop_back will call object's deconstructor

protected:
    void _M_fill_initialize(size_type _n) {
        _M_start = new value_type[_n];
        _M_finish = _M_start;
        _M_end_of_storage = _M_start + _n;
    }

    void _reallocate(size_type _n);
    void _shrink() {
        if (size() > capacity() / 4) return;
        _Tp* oldV = _M_start;
        size_type newC = capacity() / 2;
        _M_start = new _Tp[newC];
        for (size_type i = 0; i < size(); ++i) *(_M_start + i) = oldV[i];
        _M_finish = _M_start + size();
        _M_end_of_storage = _M_start + newC;
        delete[] oldV;
    }


};

template <typename _Tp>
void Vector<_Tp>::_reallocate(size_type _n) {
    _Tp* oldV = _M_start;
    size_type numToCopy = _n < size() ? _n : size();

    _Tp* newV = new _Tp[_n];
    for (size_type i = 0; i < numToCopy; i++) newV[i] = *(_M_start + i);
    _M_start = newV;
    _M_finish = _M_start + numToCopy;
    _M_end_of_storage = _M_start + _n;

    delete[] oldV;
}


}

#endif
