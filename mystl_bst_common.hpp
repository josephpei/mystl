#ifndef _MYSTL_BST_COMMON_H
#define _MYSTL_BST_COMMON_H
#include "mystl_iterator_base.hpp"

namespace numb{
struct _btree_node_base {
    typedef _btree_node_base* _Base_ptr;
    typedef const _btree_node_base* _Const_Base_ptr;

    _Base_ptr _parent;
    _Base_ptr _left;
    _Base_ptr _right;

    static _Base_ptr _minimum(_Base_ptr _x)
    {
        while (_x->_left != NULL)
            _x = _x->_left;
        return _x;
    }

    static _Const_Base_ptr _minimum(_Const_Base_ptr _x)
    {
        while (_x->_left != NULL)
            _x = _x->_left;
        return _x;
    }

    static _Base_ptr _maximum(_Base_ptr _x)
    {
        while (_x->_right != NULL)
            _x = _x->_right;
        return _x;
    }

    static _Const_Base_ptr _maximum(_Const_Base_ptr _x)
    {
        while (_x->_right != NULL)
            _x = _x->_right;
        return _x;
    }
};


}

#endif
