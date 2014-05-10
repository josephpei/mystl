#ifndef _MYSTL_AVL_H
#define _MYSTL_AVL_H

#include "mystl_algobase.hpp"
#include "mystl_iterator_base.hpp"
#include "mystl_pair.hpp"

namespace numb {

template <typename _Val>
struct _avl_node {
    typedef _avl_node* _Link_type;
    typedef const _avl_node* _Const_Link_type;

    _Link_type _parent;
    _Link_type _left;
    _Link_type _right;
    _Val _value_field;
    int _height;

    _avl_node() {}
    explicit _avl_node(_Val _x, _Link_type _p = NULL, _Link_type _l = NULL,
                       _Link_type _r = NULL)
        : _value_field(_x), _parent(_p), _left(_l), _right(_r), _height(0) {}
};

template <typename _Tp>
struct _AVL_iterator {
    typedef _Tp value_type;
    typedef _Tp& reference;
    typedef _Tp* pointer;

    typedef Bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef _AVL_iterator<_Tp> _Self;
    typedef _avl_node<_Tp>* _Link_type;

    _Link_type _node;

    _AVL_iterator() : _node() {}

    explicit _AVL_iterator(_Link_type _x) : _node(_x) {}

    reference operator*() const { return _node->_value_field; }

    pointer operator->() const { return __Addressof(_node->_value_field); }

    _Self& operator++() {
        _node = _avl_increment(_node);
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _node = _avl_increment(_node);
        return _tmp;
    }

    _Self& operator--() {
        _node = _avl_decrement(_node);
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _node = _avl_decrement(_node);
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _node == _x._node; }

    bool operator!=(const _Self& _x) const { return _node != _x._node; }

    _Link_type _avl_increment(_Link_type _x) throw() {
        if (_x->_right != NULL) {
            _x = _x->_right;
            while (_x->_left != NULL) _x = _x->_left;
            return _x;
        } else {
            _Link_type _y = _x->_parent;
            while (_y != NULL && _x == _y->_right) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }

    _Link_type _avl_decrement(_Link_type _x) throw() {
        if (_x->_left != NULL) {
            _x = _x->_left;
            while (_x->_right != NULL) _x = _x->_right;
            return _x;
        } else {
            _Link_type _y = _x->_parent;
            while (_y != NULL && _x == _y->_left) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }
};

template <typename _Tp>
struct _AVL_const_iterator {
    typedef _Tp value_type;
    typedef _Tp& reference;
    typedef _Tp* pointer;

    typedef _AVL_iterator<_Tp>* BIterator;

    typedef Bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef _AVL_const_iterator<_Tp> _Self;
    typedef _avl_node<_Tp>* _Link_type;

    _Link_type _node;

    _AVL_const_iterator() : _node() {}

    explicit _AVL_const_iterator(_Link_type _x) : _node(_x) {}

    // explicit _AVL_const_iterator(const BIterator& _it) : _node(_it._node) {}

    // BIterator _const_cast() const
    //{ return BIterator(const_cast<typename BIterator::_Link_type>(_node)); }

    reference operator*() const { return _node->_value_field; }

    pointer operator->() const { return __Addressof(_node->_value_field); }

    _Self& operator++() {
        _node = _avl_increment(_node);
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _node = _avl_increment(_node);
        return _tmp;
    }

    _Self& operator--() {
        _node = _avl_decrement(_node);
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _node = _avl_decrement(_node);
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _node == _x._node; }

    bool operator!=(const _Self& _x) const { return _node != _x._node; }

    _Link_type _avl_increment(_Link_type _x) throw() {
        if (_x->_right != NULL) {
            _x = _x->_right;
            while (_x->_left != NULL) _x = _x->_left;
            return _x;
        } else {
            _Link_type _y = _x->_parent;
            while (_y != NULL && _x == _y->_right) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }

    _Link_type _avl_decrement(_Link_type _x) throw() {
        if (_x->_left != NULL) {
            _x = _x->_left;
            while (_x->_right != NULL) _x = _x->_right;
            return _x;
        } else {
            _Link_type _y = _x->_parent;
            while (_y != NULL && _x == _y->_left) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }
};

template <typename _Val>
inline bool operator==(const _AVL_iterator<_Val>& _x,
                       const _AVL_iterator<_Val>& _y) {
    return _x._node == _y._node;
}

template <typename _Val>
inline bool operator!=(const _AVL_iterator<_Val>& _x,
                       const _AVL_iterator<_Val>& _y) {
    return _x._node != _y._node;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare>
class _AVL {
public:
    typedef _Key key_type;
    typedef _Val value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef _avl_node<_Val>* _Link_type;
    typedef const _avl_node<_Val>* _Const_Link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef _AVL_iterator<value_type> Iterator;
    typedef _AVL_const_iterator<value_type> Const_iterator;

private:
    size_type _node_count;
    _Link_type _root;
    _Compare key_comp;

protected:
    static const _Key& _S_key(_Const_Link_type _x) {
        return _KeyOfValue()(_S_value(_x));
    }

    static const_reference _S_value(_Const_Link_type _x) {
        return _x->_value_field;
    }

    int _height(_Const_Link_type _x) const {
        return _x == NULL ? -1 : _x->_height;
    }

    void _setHeight(_Link_type _x) {
        int _hl = _height(_x->_left);
        int _hr = _height(_x->_right);
        _x->_height = 1 + Max(_hl, _hr);
    }

    bool _isBalance(_Const_Link_type _x) const {
        int _bal = _height(_x->_left) - _height(_x->_right);
        return ((-1 <= _bal) && (_bal <= 1));
    }

    _Link_type _tallGrandchild(_Const_Link_type _x) const {
        if (_height(_x->_left) >= _height(_x->_right)) {
            if (_height(_x->_left->_left) >= _height(_x->_left->_right))
                return _x->_left->_left;
            else
                return _x->_left->_right;
        } else {
            if (_height(_x->_right->_right) >= _height(_x->_right->_left))
                return _x->_right->_right;
            else
                return _x->_right->_left;
        }
    }

    void _rebalance(const _Link_type& _x) {
        _Link_type _y = _x;
        while (_y != _root) {
            _y = _y->_parent;
            _setHeight(_y);
            if (!_isBalance(_y)) {
                _Link_type _z = _tallGrandchild(_y);
                _y = _restructure(_z);
                _setHeight(_y->_left);
                _setHeight(_y->_right);
                _setHeight(_y);
            }
        }
    }

    _Link_type _restructure(_Link_type& _x) {
        _Link_type left, middle, right;
        _Link_type t0, t1, t2, t3;
        _Link_type parent = _x->_parent;
        _Link_type gp = parent->_parent;

        if (_x == _x->_parent->_left && parent == parent->_parent->_left) {
            left = _x;
            middle = parent;
            right = gp;
            t0 = _x->_left;
            t1 = _x->_right;
            t2 = parent->_right;
            t3 = gp->_right;
        } else if (_x == _x->_parent->_left &&
                   parent == parent->_parent->_right) {
            left = gp;
            middle = _x;
            right = parent;
            t0 = gp->_left;
            t1 = _x->_left;
            t2 = _x->_right;
            t3 = parent->_right;
        } else if (_x == _x->_parent->_right &&
                   parent == parent->_parent->_left) {
            left = parent;
            middle = _x;
            right = gp;
            t0 = parent->_left;
            t1 = _x->_left;
            t2 = _x->_right;
            t3 = gp->_right;
        } else {
            left = gp;
            middle = parent;
            right = _x;
            t0 = gp->_left;
            t1 = parent->_left;
            t2 = _x->_left;
            t3 = _x->_right;
        }
        if (gp == _root)
            _root = middle;
        else if (gp == gp->_parent->_left)
            gp->_parent->_left = middle;
        else
            gp->_parent->_right = middle;
        middle->_parent = gp->_parent;
        return _connect34(left, middle, right, t0, t1, t2, t3);
    }

    _Link_type _connect34(_Link_type& left, _Link_type& middle,
                          _Link_type& right, _Link_type& t0, _Link_type& t1,
                          _Link_type& t2, _Link_type& t3) {
        left->_left = t0;
        if (t0) t0->_parent = left;
        left->_right = t1;
        if (t1) t1->_parent = left;

        right->_left = t2;
        if (t2) t2->_parent = right;
        right->_right = t3;
        if (t3) t3->_parent = right;

        middle->_left = left;
        left->_parent = middle;
        middle->_right = right;
        right->_parent = middle;
        return middle;
    }

    _Link_type _find(const key_type& _x) const {
        _Link_type _p = _root;
        while (_p != NULL && _KeyOfValue()(_x) != _S_key(_p)) {
            if (key_comp(_KeyOfValue()(_x), _S_key(_p)))
                _p = _p->_left;
            else
                _p = _p->_right;
        }
        return _p;
    }

    _Link_type _succ(_Link_type _x) {
        if (_x->_right != NULL) {
            _x = _x->_right;
            while (_x->_left != NULL) _x = _x->_left;
            return _x;
        } else {
            _Link_type _y = _x->_parent;
            while (_y != NULL && _x == _y->_right) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }

    Iterator _lower_bound(const _Key& _k)
    {
        _Link_type _x = _root;
        _Link_type _y = NULL;
        while (_x != NULL) {
            if (!key_comp(_S_key(_x), _k))
                _y = _x, _x = _x->_left;
            else
                _x = _x->_right;
        }
        return Iterator(_y);
    }

    Const_iterator _lower_bound(const _Key& _k) const
    {
        _Link_type _x = _root;
        _Link_type _y = NULL;
        while (_x != NULL) {
            if (!key_comp(_S_key(_x), _k))
                _y = _x, _x = _x->_left;
            else
                _x = _x->_right;
        }
        return Const_iterator(_y);
    }

    Iterator _upper_bound(const _Key& _k)
    {
        _Link_type _x = _root;
        _Link_type _y = NULL;
        while (_x != NULL) {
            if (key_comp(_k, _S_key(_x)))
                _y = _x, _x = _x->_left;
            else
                _x = _x->_right;
        }
        return Iterator(_y);
    }

    Const_iterator _upper_bound(const _Key& _k) const
    {
        _Link_type _x = _root;
        _Link_type _y = NULL;
        while (_x != NULL) {
            if (key_comp(_k, _S_key(_x)))
                _y = _x, _x = _x->_left;
            else
                _x = _x->_right;
        }
        return Const_iterator(_y);
    }


    void _destroy(_Link_type _r) {
        if (_r) {
            _destroy(_r->_left);
            _destroy(_r->_right);
            delete _r;
        }
        _r = NULL;
    }

public:
    _AVL() : _node_count(0), _root(NULL), key_comp(_Compare()) {}
    ~_AVL() { _destroy(_root); }

    _AVL(const _AVL& _rhs) {
        _node_count = 0;
        _root = NULL;
        key_comp = _rhs.key_comp;
        for (Const_iterator _it = _rhs.begin(); _it != _rhs.end(); ++_it)
            _insert_unique(*_it);
    }

    _AVL& operator=(const _AVL& _rhs) {
        _AVL _copy(_rhs);
        swap(_copy);
        return *this;
    }

    void swap(_AVL& _rhs) {
        using numb::Swap;
        Swap(_node_count, _rhs._node_count);
        Swap(_root, _rhs._root);
        Swap(key_comp, _rhs.key_comp);
    }

    template <typename _InputIterator>
    _AVL(_InputIterator _first, _InputIterator _last) {
        _node_count = 0;
        _root = NULL;
        for (; _first != _last; ++_first) _insert_unique(*_first);
    }

    _Compare key_compare() { return key_comp; }

    Iterator begin() throw() {
        _Link_type _leftmost = _root;
        while (_leftmost->_left != NULL) _leftmost = _leftmost->_left;
        return Iterator(_leftmost);
    }

    Iterator end() throw() { return Iterator(NULL); }

    Const_iterator begin() const throw() {
        _Link_type _leftmost = _root;
        while (_leftmost->_left != NULL) _leftmost = _leftmost->_left;
        return Const_iterator(_leftmost);
    }

    Const_iterator end() const throw() { return Const_iterator(NULL); }

    size_type size() const { return _node_count; }

    bool empty() const { return _node_count == 0; }

    Pair<Iterator, bool> _insert_unique(const value_type& _x) {
        _Link_type _hot = NULL;
        _Link_type _p = _root;
        while (_p != NULL) {
            _hot = _p;
            if (key_comp(_KeyOfValue()(_x), _S_key(_p)))
                _p = _p->_left;
            else if (key_comp(_S_key(_p), _KeyOfValue()(_x)))
                _p = _p->_right;
            else
                return Make_pair(Iterator(NULL), false);
        }
        _Link_type _cur = new _avl_node<value_type>(_x, _hot);
        if (_hot == NULL)
            _root = _cur;
        else {
            if (key_comp(_KeyOfValue()(_x), _S_key(_hot)))
                _hot->_left = _cur;
            else
                _hot->_right = _cur;
        }
        _setHeight(_cur);
        _rebalance(_cur);
        Iterator _iter(_cur);
        ++_node_count;
        return Make_pair(_iter, true);
    }

    Iterator _insert_unique(Const_iterator _pos, const value_type& _x) {
        // need impl
        return Iterator(NULL);
    }


    void erase(const key_type& _x) {
        _Link_type _del = _find(_x);
        if (_del == NULL) return;
        _Link_type _real;
        if (_del->_left == NULL || _del->_right == NULL)
            _real = _del;
        else
            _real = _succ(_del);

        if (_real != _del) _del->_value_field = _real->_value_field;

        _Link_type _child;
        if (_real->_left != NULL)
            _child = _real->_left;
        else
            _child = _real->_right;
        if (_child != NULL) _child->_parent = _real->_parent;

        if (_real->_parent == NULL)
            _root = _child;
        else {
            if (_real == _real->_parent->_left)
                _real->_parent->_left = _child;
            else
                _real->_parent->_right = _child;
            _setHeight(_real->_parent);
            _rebalance(_real->_parent);
        }

        delete _real;
        --_node_count;
    }

    Iterator find(const key_type& _x) { return Iterator(_find(_x)); }

    Iterator lower_bound(const key_type& _x)
    { return _lower_bound(_x); }

    Const_iterator lower_bound(const key_type& _x) const
    { return _lower_bound(_x); }

    Iterator upper_bound(const key_type& _x)
    { return _upper_bound(_x); }

    Const_iterator upper_bound(const key_type& _x) const
    { return _upper_bound(_x); }

    Iterator _insert_equal(const value_type& _x);
};
}

#endif
