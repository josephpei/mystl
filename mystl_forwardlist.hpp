#ifndef _MYSTL_SLIST_H
#define _MYSTL_SLIST_H
#include "mystl_iterator_base.hpp"
#include "mystl_algobase.hpp"

namespace numb {
template <typename _Tp>
struct _SList_node {
    _Tp _data;
    _SList_node* _next;

    _SList_node() : _data(_Tp()), _next(NULL) {}
    explicit _SList_node(_Tp _x, _SList_node* _p = NULL)
        : _data(_x), _next(_p)  {}
};

template <typename _Tp>
struct _SList_iterator {
    _SList_node<_Tp>* _M_node;

    typedef _SList_iterator<_Tp> _Self;
    typedef _SList_node<_Tp> _Node;
    typedef ptrdiff_t difference_type;
    typedef Forward_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;

    _SList_iterator() : _M_node() {}

    explicit _SList_iterator(_SList_node<_Tp>* _x) : _M_node(_x) {}

    reference operator*() const { return _M_node->_data; }

    pointer operator->() const { return __Addressof(_M_node->_data); }

    _Self& operator++() {
        _M_node = _M_node->_next;
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _M_node = _M_node->_next;
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _M_node == _x._M_node; }

    bool operator!=(const _Self& _x) const { return _M_node != _x._M_node; }
};

template <typename _Tp>
struct _SList_const_iterator {
    _SList_node<_Tp>* _M_node;

    typedef _SList_const_iterator<_Tp> _Self;
    typedef _SList_node<_Tp> _Node;
    typedef ptrdiff_t difference_type;
    typedef Forward_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;

    _SList_const_iterator() : _M_node() {}

    explicit _SList_const_iterator(_SList_node<_Tp>* _x) : _M_node(_x) {}

    reference operator*() const { return _M_node->_data; }

    pointer operator->() const { return __Addressof(_M_node->_data); }

    _Self& operator++() {
        _M_node = _M_node->_next;
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _M_node = _M_node->_next;
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _M_node == _x._M_node; }

    bool operator!=(const _Self& _x) const { return _M_node != _x._M_node; }
};

template <typename _Val>
inline bool operator==(const _SList_iterator<_Val>& __x,
                       const _SList_const_iterator<_Val>& __y) {
    return __x._M_node == __y._M_node;
}

template <typename _Val>
inline bool operator!=(const _SList_iterator<_Val>& __x,
                       const _SList_const_iterator<_Val>& __y) {
    return __x._M_node != __y._M_node;
}

template <typename _Tp>
class Forward_list {
public:
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp& reference;
    typedef const _Tp& const_reference;
    typedef _SList_iterator<_Tp> Iterator;
    typedef _SList_const_iterator<_Tp> Const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    typedef _SList_node<_Tp> _Node;
    _Node* _head;
    size_type _size;

public:
    Forward_list() : _head(new _Node()), _size(0) {
        _head->_next = NULL;
        _head->_data = value_type();
    }
    ~Forward_list() { _M_clear(); }

    Forward_list(const Forward_list& _rhs) : _head(new _Node), _size(0) {
        _head->_next = _head;
        _head->_data = value_type();
        for (Const_iterator _iter = _rhs.begin(); _iter != _rhs.end();
             ++_iter)
            push_front(*_iter);
    }

    Forward_list& operator=(const Forward_list& _rhs) {
        Forward_list _copy = _rhs;
        numb::Swap(*this, _copy);
        return *this;
    }

    Iterator begin() throw() { return Iterator(_head->_next); }

    Iterator end() throw() { return Iterator(NULL); }

    Const_iterator begin() const throw() {
        return Const_iterator(_head->_next);
    }

    Const_iterator end() const throw() { return Const_iterator(NULL); }

    reference front() { return *begin(); }

    const_reference front() const { return *begin(); }

    size_type size() const { return _size; }

    bool empty() const { return _size == 0; }

    void push_front(const value_type& _x) {
        _Node* cur = new _Node(_x, _head->_next);
        _head->_next = cur;
        _size++;
    }

    value_type pop_front() {
        if (empty()) throw;
        value_type _tmp = *begin();
        _Node* _d = _head->_next;
        _head->_next = _d->_next;
        delete _d;
        --_size;
        return _tmp;
    }


protected:
    void _M_clear() {
        _Node* _q = _head->_next;
        _Node* _p;
        while (_q != NULL) {
            _p = _q->_next;
            delete _q;
            _q = _p;
        }
        delete _head;
    }
};
}

#endif
