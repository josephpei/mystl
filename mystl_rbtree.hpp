#ifndef _MYSTL_RBTREE_H
#define _MYSTL_RBTREE_H

#include "mystl_algobase.hpp"
#include "mystl_iterator_base.hpp"
#include "mystl_pair.hpp"

namespace numb {

enum _RB_COLOR { RED, BLACK };

template <typename _Val>
struct _rb_node {
    typedef _rb_node* _Link_type;
    typedef const _rb_node* _Const_Link_type;
    static _Link_type _Nil;

    _Link_type _parent;
    _Link_type _left;
    _Link_type _right;
    _Val _value_field;
    _RB_COLOR _c;

    _rb_node() : _left(_Nil), _right(_Nil), _c(BLACK) {}
    explicit _rb_node(_Val _x, _RB_COLOR _co, _Link_type _p = NULL, _Link_type _l = _Nil,
                       _Link_type _r = _Nil)
        : _value_field(_x), _parent(_p), _left(_l), _right(_r), _c(_co) {}

    _Link_type _maximum()
    { return (_right == _Nil) ? this : _right->_maximum(); }

    _Link_type _minimum()
    { return (_left == _Nil) ? this : _left->_minimum(); }

    _Link_type _suuc()
    {
        if (_right != _Nil)
            return _right->_minimum();
        else {
            _Link_type _x = this;
            _Link_type _y = _x->_parent;
            while (_y != _Nil && _x == _y->_right) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }

    _Link_type _prev()
    {
        if (_left != _Nil)
            return _left->_maximum();
        else {
            _Link_type _x = this;
            _Link_type _y = _x->_parent;
            while (_y != _Nil && _x == _y->_left) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }
private:
    static _rb_node SENTINEL_OBJ;
};

template <typename _Val>
_rb_node<_Val> _rb_node<_Val>::SENTINEL_OBJ = _rb_node<_Val>();
template <typename _Val>
_rb_node<_Val>* _rb_node<_Val>::_Nil = &_rb_node<_Val>::SENTINEL_OBJ;

template <typename _Tp>
struct _RB_iterator {
    typedef _Tp value_type;
    typedef _Tp& reference;
    typedef _Tp* pointer;

    typedef Bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef _RB_iterator<_Tp> _Self;
    typedef _rb_node<_Tp>* _Link_type;

    _Link_type _node;

    _RB_iterator() : _node() {}

    explicit _RB_iterator(_Link_type _x) : _node(_x) {}

    reference operator*() const { return _node->_value_field; }

    pointer operator->() const { return __Addressof(_node->_value_field); }

    _Self& operator++() {
        _node = _node->_suuc();
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _node = _node->_suuc();
        return _tmp;
    }

    _Self& operator--() {
        _node = _node->_prev();
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _node = _node->_prev();
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _node == _x._node; }

    bool operator!=(const _Self& _x) const { return _node != _x._node; }
};

template <typename _Tp>
struct _RB_const_iterator {
    typedef _Tp value_type;
    typedef _Tp& reference;
    typedef _Tp* pointer;

    typedef _RB_iterator<_Tp>* BIterator;

    typedef Bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef _RB_const_iterator<_Tp> _Self;
    typedef _rb_node<_Tp>* _Link_type;

    _Link_type _node;

    _RB_const_iterator() : _node() {}

    explicit _RB_const_iterator(_Link_type _x) : _node(_x) {}

    // explicit _AVL_const_iterator(const BIterator& _it) : _node(_it._node) {}

    // BIterator _const_cast() const
    //{ return BIterator(const_cast<typename BIterator::_Link_type>(_node)); }

    reference operator*() const { return _node->_value_field; }

    pointer operator->() const { return __Addressof(_node->_value_field); }

    _Self& operator++() {
        _node = _node->_suuc();
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _node = _node->_suuc();
        return _tmp;
    }

    _Self& operator--() {
        _node = _node->_prev();
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _node = _node->_prev();
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _node == _x._node; }

    bool operator!=(const _Self& _x) const { return _node != _x._node; }
};

template <typename _Val>
inline bool operator==(const _RB_iterator<_Val>& _x,
                       const _RB_iterator<_Val>& _y) {
    return _x._node == _y._node;
}

template <typename _Val>
inline bool operator!=(const _RB_iterator<_Val>& _x,
                       const _RB_iterator<_Val>& _y) {
    return _x._node != _y._node;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare>
class _RBtree {
public:
    typedef _Key key_type;
    typedef _Val value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef _rb_node<_Val> _node_type;
    typedef _rb_node<_Val>* _Link_type;
    typedef const _rb_node<_Val>* _Const_Link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef _RB_iterator<value_type> Iterator;
    typedef _RB_const_iterator<value_type> Const_iterator;

    static _Link_type _Nil;

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

    _Link_type _find(const key_type& _x) const {
        _Link_type _p = _root;
        while (_p != _Nil && _x != _S_key(_p)) {
            if (key_comp(_x, _S_key(_p)))
                _p = _p->_left;
            else
                _p = _p->_right;
        }
        return _p;
    }

    _Link_type _succ(_Link_type _x) {
        if (_x->_right != _Nil) {
            _x = _x->_right;
            while (_x->_left != _Nil) _x = _x->_left;
            return _x;
        } else {
            _Link_type _y = _x->_parent;
            while (_y != _Nil && _x == _y->_right) {
                _x = _y;
                _y = _y->_parent;
            }
            return _y;
        }
    }

    void _left_rotate(_Link_type _x)
    {
        _Link_type _y = _x->_right;
        _x->_right = _y->_left;

        _y->_left->_parent = _x;
        _y->_parent = _x->_parent;

        if (_x->_parent == _Nil)
            _root = _y;
        else if (_x == _x->_parent->_left)
            _x->_parent->_left = _y;
        else
            _x->_parent->_right = _y;
        _y->_left = _x;
        _x->_parent = _y;
    }

    void _right_rotate(_Link_type _x)
    {
        _Link_type _y = _x->_left;
        _x->_left = _y->_right;

        _y->_right->_parent = _x;
        _y->_parent = _x->_parent;

        if (_x->_parent == _Nil)
            _root = _y;
        else
            if (_x == _x->_parent->_left)
                _x->_parent->_left = _y;
            else
                _x->_parent->_right = _y;

        _y->_right = _x;
        _x->_parent = _y;
    }

    void _rb_insert_fixup(_Link_type _x)
    {
        while (_x->_parent->_c == RED) {
            if (_x->_parent == _x->_parent->_parent->_left) {
                _Link_type _y = _x->_parent->_parent->_right;
                if (_y->_c == RED) {
                    _x->_parent->_c = BLACK;
                    _y->_c = BLACK;
                    _x->_parent->_parent->_c = RED;
                    _x = _x->_parent->_parent;
                }
                else {
                    if (_x == _x->_parent->_right) {
                        _x = _x->_parent;
                        _left_rotate(_x);
                    }
                    _x->_parent->_c = BLACK;
                    _x->_parent->_parent->_c = RED;
                    _right_rotate(_x->_parent->_parent);
                }
            }
            else {
                _Link_type _y = _x->_parent->_parent->_left;
                if (_y->_c == RED) {
                    _x->_parent->_c = BLACK;
                    _y->_c = BLACK;
                    _x->_parent->_parent->_c = RED;
                    _x = _x->_parent->_parent;
                }
                else {
                    if (_x == _x->_parent->_left) {
                        _x = _x->_parent;
                        _right_rotate(_x);
                    }
                    _x->_parent->_c = BLACK;
                    _x->_parent->_parent->_c = RED;
                    _left_rotate(_x->_parent->_parent);
                }
            }
        }
        _root->_c = BLACK;
    }

    void _rb_del_fixup(_Link_type _x)
    {
        while (_x != _root && _x->_c == BLACK) {
            if (_x == _x->_parent->_left) {
                _Link_type _w = _x->_parent->_right;
                if (_w->_c == RED) {
                    _x->_parent->_c = RED;
                    _w->_c = BLACK;
                    _left_rotate(_x->_parent);
                    _w = _x->_parent->_right;
                }
                if (_w->_left->_c == BLACK && _w->_right->_c == BLACK) {
                    _w->_c = RED;
                    _x = _x->_parent;
                }
                else if (_w->_right->_c == BLACK) {
                    _w->_left->_c = BLACK;
                    _w->_c = RED;
                    _right_rotate(_w);
                    _w = _x->_parent->_right;
                }
                _w->_c = _x->_parent->_c;
                _x->_parent->_c = BLACK;
                _w->_right->_c = BLACK;
                _left_rotate(_x->_parent);
                _x = _root;
            }
            else {
                _Link_type _w = _x->_parent->_left;
                if (_w->_c == RED) {
                    _x->_parent->_c = RED;
                    _w->_c = BLACK;
                    _right_rotate(_x->_parent);
                    _w = _x->_parent->_left;
                }
                if (_w->_left->_c == BLACK && _w->_right->_c == BLACK) {
                    _w->_c = RED;
                    _x = _x->_parent;
                }
                else if (_w->_left->_c == BLACK) {
                    _w->_right->_c = BLACK;
                    _w->_c = RED;
                    _left_rotate(_w);
                    _w = _x->_parent->_left;
                }
                _w->_c = _x->_parent->_c;
                _x->_parent->_c = BLACK;
                _w->_left->_c = BLACK;
                _right_rotate(_x->_parent);
                _x = _root;
            }
        }
        _x->_c = BLACK;
    }

    Iterator _lower_bound(const _Key& _k)
    {
        _Link_type _x = _root;
        _Link_type _y = _Nil;
        while (_x != _Nil) {
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
        _Link_type _y = _Nil;
        while (_x != _Nil) {
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
        _Link_type _y = _Nil;
        while (_x != _Nil) {
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
        _Link_type _y = _Nil;
        while (_x != _Nil) {
            if (key_comp(_k, _S_key(_x)))
                _y = _x, _x = _x->_left;
            else
                _x = _x->_right;
        }
        return Const_iterator(_y);
    }


    void _destroy(_Link_type _r) {
        if (_r == _Nil)
            return;

        _destroy(_r->_left);
        _destroy(_r->_right);
        delete _r;
    }

public:
    _RBtree() : _node_count(0), key_comp(_Compare()) {
        _root = _Nil;
    }
    ~_RBtree() { _destroy(_root); }

    _RBtree(const _RBtree& _rhs) {
        _node_count = 0;
        _root = _Nil;

        key_comp = _rhs.key_comp;
        for (Const_iterator _it = _rhs.begin(); _it != _rhs.end(); ++_it)
            _insert_unique(*_it);
    }

    _RBtree& operator=(const _RBtree& _rhs) {
        _RBtree _copy(_rhs);
        swap(_copy);
        return *this;
    }

    void swap(_RBtree& _rhs) {
        using numb::Swap;
        Swap(_node_count, _rhs._node_count);
        Swap(_root, _rhs._root);
        Swap(key_comp, _rhs.key_comp);
    }

    template <typename _InputIterator>
    _RBtree(_InputIterator _first, _InputIterator _last) {
        _node_count = 0;
        _root = _Nil;
        for (; _first != _last; ++_first) _insert_unique(*_first);
    }

    _Compare key_compare() { return key_comp; }

    Iterator begin() throw() {
        return Iterator(_root->_minimum());
    }

    Iterator end() throw() { return Iterator(_Nil); }

    Const_iterator begin() const throw() {
        return Const_iterator(_root->_minimum());
    }

    Const_iterator end() const throw() { return Const_iterator(_Nil); }

    size_type size() const { return _node_count; }

    bool empty() const { return _node_count == 0; }

    Pair<Iterator, bool> _insert_unique(const value_type& _x) {
        _Link_type _hot = _Nil;
        _Link_type _p = _root;
        while (_p != _Nil) {
            _hot = _p;
            if (key_comp(_KeyOfValue()(_x), _S_key(_p)))
                _p = _p->_left;
            else if (key_comp(_S_key(_p), _KeyOfValue()(_x)))
                _p = _p->_right;
            else
                return Make_pair(Iterator(_p), false);
        }
        _Link_type _cur = new _rb_node<value_type>(_x, RED, _hot, _Nil, _Nil);
        if (_hot == _Nil)
            _root = _cur;
        else {
            if (key_comp(_KeyOfValue()(_x), _S_key(_hot)))
                _hot->_left = _cur;
            else
                _hot->_right = _cur;
        }
        _rb_insert_fixup(_cur);
        Iterator _iter(_cur);
        ++_node_count;
        return Make_pair(_iter, true);
    }

    void erase(const key_type& _x) {
        _Link_type _del = _find(_x);
        if (_del == _Nil) return;
        _Link_type _real;
        if (_del->_left == _Nil || _del->_right == _Nil)
            _real = _del;
        else
            _real = _succ(_del);

        if (_real != _del) {
            key_type* _tmp = const_cast<key_type*>(&_del->_value_field.first);
            *_tmp = _real->_value_field.first;
            _del->_value_field.second = _real->_value_field.second;
        }

        _Link_type _child;
        if (_real->_left != _Nil)
            _child = _real->_left;
        else
            _child = _real->_right;
        _child->_parent = _real->_parent;

        if (_real->_parent == _Nil)
            _root = _child;
        else {
            if (_real == _real->_parent->_left)
                _real->_parent->_left = _child;
            else
                _real->_parent->_right = _child;
        }

        if (_real->_c == BLACK)
            _rb_del_fixup(_child);
        delete _real;
        --_node_count;
    }

    Iterator maximum() const
    { return (empty()) ? end() : Iterator(_root->_maximum()); }

    Iterator minimum() const
    { return (empty()) ? end() : Iterator(_root->_minimum()); }

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

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare>
typename _RBtree<_Key, _Val, _KeyOfValue, _Compare>::_Link_type
    _RBtree<_Key, _Val, _KeyOfValue, _Compare>::_Nil =
    _RBtree<_Key, _Val, _KeyOfValue, _Compare>::_node_type::_Nil;

}

#endif

