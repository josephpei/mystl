#ifndef _MYSTL_BST_H
#define _MYSTL_BST_H
#include "mystl_algobase.hpp"
#include "mystl_iterator_base.hpp"
#include "mystl_pair.hpp"

namespace numb {

template <typename _Val>
struct _bst_node {
    typedef _bst_node* _Link_type;
    typedef const _bst_node* _Const_Link_type;

    _Link_type _parent;
    _Link_type _left;
    _Link_type _right;
    _Val _value_field;

    _bst_node() {}
    explicit _bst_node(_Val _x, _Link_type _p = NULL, _Link_type _l = NULL,
                       _Link_type _r = NULL)
        : _value_field(_x), _parent(_p), _left(_l), _right(_r) {}
};

template <typename _Tp>
struct _BST_iterator {
    typedef _Tp value_type;
    typedef _Tp& reference;
    typedef _Tp* pointer;

    typedef Bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef _BST_iterator<_Tp> _Self;
    typedef _bst_node<_Tp>* _Link_type;

    _Link_type _node;

    _BST_iterator() : _node() {}

    explicit _BST_iterator(_Link_type _x) : _node(_x) {}

    reference operator*() const { return _node->_value_field; }

    pointer operator->() const { return __Addressof(_node->_value_field); }

    _Self& operator++() {
        _node = _bst_increment(_node);
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _node = _bst_increment(_node);
        return _tmp;
    }

    _Self& operator--() {
        _node = _bst_decrement(_node);
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _node = _bst_decrement(_node);
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _node == _x._node; }

    bool operator!=(const _Self& _x) const { return _node != _x._node; }

    _Link_type _bst_increment(_Link_type _x) throw() {
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

    _Link_type _bst_decrement(_Link_type _x) throw() {
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
struct _BST_const_iterator {
    typedef _Tp value_type;
    typedef _Tp& reference;
    typedef _Tp* pointer;

    typedef _BST_iterator<_Tp>* BIterator;

    typedef Bidirectional_iterator_tag iterator_category;
    typedef ptrdiff_t difference_type;

    typedef _BST_const_iterator<_Tp> _Self;
    typedef _bst_node<_Tp>* _Link_type;

    _Link_type _node;

    _BST_const_iterator() : _node() {}

    explicit _BST_const_iterator(_Link_type _x) : _node(_x) {}

    //explicit _BST_const_iterator(const BIterator& _it) : _node(_it._node) {}

    //BIterator _const_cast() const
    //{ return BIterator(const_cast<typename BIterator::_Link_type>(_node)); }

    reference operator*() const { return _node->_value_field; }

    pointer operator->() const { return __Addressof(_node->_value_field); }

    _Self& operator++() {
        _node = _bst_increment(_node);
        return *this;
    }

    _Self operator++(int) {
        _Self _tmp = *this;
        _node = _bst_increment(_node);
        return _tmp;
    }

    _Self& operator--() {
        _node = _bst_decrement(_node);
        return *this;
    }

    _Self operator--(int) {
        _Self _tmp = *this;
        _node = _bst_decrement(_node);
        return _tmp;
    }

    bool operator==(const _Self& _x) const { return _node == _x._node; }

    bool operator!=(const _Self& _x) const { return _node != _x._node; }

    _Link_type _bst_increment(_Link_type _x) throw() {
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

    _Link_type _bst_decrement(_Link_type _x) throw() {
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
inline bool operator==(const _BST_iterator<_Val>& _x,
                       const _BST_iterator<_Val>& _y) {
    return _x._node == _y._node;
}

template <typename _Val>
inline bool operator!=(const _BST_iterator<_Val>& _x,
                       const _BST_iterator<_Val>& _y) {
    return _x._node != _y._node;
}

template <typename _Key, typename _Val, typename _KeyOfValue, typename _Compare>
class _BST {
public:
    typedef _Key key_type;
    typedef _Val value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef _bst_node<_Val>* _Link_type;
    typedef const _bst_node<_Val>* _Const_Link_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;

    typedef _BST_iterator<value_type> Iterator;
    typedef _BST_const_iterator<value_type> Const_iterator;

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

    _Link_type _find(const key_type& _x)
    {
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


    void _destroy(_Link_type _r) {
        if (_r) {
            _destroy(_r->_left);
            _destroy(_r->_right);
            delete _r;
        }
        _r = NULL;
    }

public:
    _BST()
        : _node_count(0),
          _root(NULL),
          key_comp(_Compare()) {}
    ~_BST() { _destroy(_root); }

    _BST(const _BST& _rhs);
    _BST& operator=(const _BST& _rhs);

    Iterator begin() throw() {
        _Link_type _leftmost = _root;
        while (_leftmost->_left != NULL)
            _leftmost = _leftmost->_left;
        return Iterator(_leftmost);
    }

    Iterator end() throw() { return Iterator(NULL); }

    Const_iterator begin() const throw() {
        _Link_type _leftmost = _root;
        while (_leftmost->_left != NULL)
            _leftmost = _leftmost->_left;
        return Const_iterator(static_cast<_Const_Link_type>(_leftmost));
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
        _Link_type _cur = new _bst_node<value_type>(_x, _hot);
        if (_hot == NULL)
            _root = _cur;
        else {
            if (key_comp(_KeyOfValue()(_x), _S_key(_hot)))
                _hot->_left = _cur;
            else
                _hot->_right = _cur;
        }
        Iterator _iter(_cur);
        ++_node_count;
        return Make_pair(_iter, true);
    }

    size_type erase(const key_type& _x)
    {
        _Link_type _del = _find(_x);
        if (_del == NULL)
            throw;
        _Link_type _real;
        if (_del->_left == NULL || _del->_right == NULL)
            _real = _del;
        else
            _real = _succ(_del);

        _Link_type _child;
        if (_real->_left != NULL)
            _child = _real->_left;
        else
            _child = _real->_right;
        if (_child != NULL)
            _child->_parent = _real->_parent;

        if (_real->_parent == NULL)
            _root = _child;
        else {
            if (_real == _real->_parent->_left)
                _real->_parent->_left = _child;
            else
                _real->_parent->_right = _child;
        }

        if (_real != _del)
            _del->_value_field = _real->_value_field;

        delete _real;
        return _S_value(_del);
    }

    Iterator find(const key_type& _x)
    {
        return Iterator(_find(_x));
    }


    Iterator _insert_equal(const value_type& _x);
};
}
#endif
