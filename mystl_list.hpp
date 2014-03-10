#ifndef _MYSTL_LIST_H
#define _MYSTL_LIST_H
#include "mystl_iterator_base.hpp"
#include "mystl_algobase.hpp"

namespace numb {
template <typename _Tp>
struct _List_node {
    _Tp _data;
    _List_node* _next;
    _List_node* _prev;

    _List_node() : _data(_Tp()), _next(NULL), _prev(NULL) {}
    explicit _List_node(_Tp _x, _List_node* _p = NULL, _List_node* _n = NULL)
        : _data(_x), _next(_n), _prev(_p) {}
};

template <typename _Tp>
struct _List_iterator {
    _List_node<_Tp>* _M_node;

    typedef _List_iterator<_Tp> _Self;
    typedef _List_node<_Tp> _Node;
    typedef ptrdiff_t difference_type;
    typedef Bidirectional_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;

    _List_iterator() : _M_node() {}

    explicit _List_iterator(_List_node<_Tp>* _x) : _M_node(_x) {}

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

    _Self& operator--() {
        _M_node = _M_node->_prev;
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _M_node = _M_node->_prev;
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _M_node == _x._M_node; }

    bool operator!=(const _Self& _x) const { return _M_node != _x._M_node; }
};

template <typename _Tp>
struct _List_const_iterator {
    _List_node<_Tp>* _M_node;

    typedef _List_const_iterator<_Tp> _Self;
    typedef _List_node<_Tp> _Node;
    typedef ptrdiff_t difference_type;
    typedef Bidirectional_iterator_tag iterator_category;
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef _Tp& reference;

    _List_const_iterator() : _M_node() {}

    explicit _List_const_iterator(_List_node<_Tp>* _x) : _M_node(_x) {}

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

    _Self& operator--() {
        _M_node = _M_node->_prev;
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _M_node = _M_node->_prev;
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _M_node == _x._M_node; }

    bool operator!=(const _Self& _x) const { return _M_node != _x._M_node; }
};

template <typename _Val>
inline bool operator==(const _List_iterator<_Val>& __x,
                       const _List_const_iterator<_Val>& __y) {
    return __x._M_node == __y._M_node;
}

template <typename _Val>
inline bool operator!=(const _List_iterator<_Val>& __x,
                       const _List_const_iterator<_Val>& __y) {
    return __x._M_node != __y._M_node;
}

template <typename _Tp>
class List {
public:
    typedef _Tp value_type;
    typedef _Tp* pointer;
    typedef const _Tp* const_pointer;
    typedef _Tp& reference;
    typedef const _Tp& const_reference;
    typedef _List_iterator<_Tp> Iterator;
    typedef _List_const_iterator<_Tp> Const_iterator;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

protected:
    typedef _List_node<_Tp> _Node;
    _Node* _head;
    size_type _size;

public:
    List() : _head(new _Node), _size(0) {
        _head->_prev = _head;
        _head->_next = _head;
        _head->_data = value_type();
    }
    ~List() { _M_clear(); }

    List(const List& _rhs) : _head(new _Node), _size(0) {
        _head->_prev = _head;
        _head->_next = _head;
        _head->_data = value_type();
        for (Const_iterator _iter = _rhs.begin(); _iter != _rhs.end();
             ++_iter)
            push_back(*_iter);
    }

    List& operator=(const List& _rhs) {
        List _copy = _rhs;
        numb::Swap(*this, _copy);
        return *this;
    }

    Iterator begin() throw() { return Iterator(_head->_next); }

    Iterator end() throw() { return Iterator(_head); }

    Const_iterator begin() const throw() {
        return Const_iterator(_head->_next);
    }

    Const_iterator end() const throw() { return Const_iterator(_head); }

    reference front() { return *begin(); }

    const_reference front() const { return *begin(); }

    reference back() {
        Iterator _tmp = end();
        --_tmp;
        return *_tmp;
    }

    const_reference back() const {
        Iterator _tmp = end();
        --_tmp;
        return *_tmp;
    }

    size_type size() const { return _size; }

    bool empty() const { return _size == 0; }

    void push_front(const value_type& _x) {
        _Node* cur = new _Node(_x, _head, _head->_next);
        _head->_next->_prev = cur;
        _head->_next = cur;
        _size++;
    }

    value_type pop_front() {
        if (empty()) throw;
        value_type _tmp = *begin();
        _M_erase(begin());
        return _tmp;
    }

    void push_back(const value_type& _x) {
        _Node* cur = new _Node(_x, _head->_prev, _head);
        _head->_prev->_next = cur;
        _head->_prev = cur;
        _size++;
    }

    value_type pop_back() {
        if (empty()) throw;
        value_type _tmp = *end();
        _M_erase(--end());

        return _tmp;
    }

    value_type erase(Iterator _it) {
        value_type _tmp = *_it;
        _M_erase(_it);
        return _tmp;
    }

    value_type erase(difference_type _n) {
        Iterator _it = begin();
        Advance(_it, _n);
        value_type _tmp = *_it;
        _M_erase(_it);
        return _tmp;
    }

protected:
    void _M_clear() {
        _Node* _q = _head->_next;
        _Node* _p;
        while (_q != _head) {
            _p = _q->_next;
            delete _q;
            _q = _p;
        }
        delete _head;
    }

    void _M_erase(Iterator _iter) {
        _iter._M_node->_prev->_next = _iter._M_node->_next;
        _iter._M_node->_next->_prev = _iter._M_node->_prev;
        delete _iter._M_node;
        --_size;
    }
};
}

#endif
