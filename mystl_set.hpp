#ifndef _MYSTL_SET_H
#define _MYSTL_SET_H
#include "mystl_bst.hpp"

namespace numb {
template <typename _Key, typename _Compare = Less<_Key> >
class Set {
    public:
        typedef _Key key_type;
        typedef _Key value_type;
        typedef _Compare key_compare;
        typedef _Compare value_compare;

    private:
        typedef _BST<key_type, value_type, numb::_Identity<value_type>, key_compare> _Rep_type;
        _Rep_type _M_t;

    public:
        typedef _Key* pointer;
        typedef const _Key* const_pointer;
        typedef _Key& reference;
        typedef const _Key& const_reference;

        typedef typename _Rep_type::Iterator Iterator;
        typedef typename _Rep_type::Const_iterator Const_iterator;
        typedef typename _Rep_type::size_type size_type;
        typedef typename _Rep_type::difference_type difference_type;

        Set() : _M_t() { }

        Iterator begin()
        { return _M_t.begin(); }

        Iterator end()
        { return _M_t.end(); }

        bool empty() const
        { return _M_t.empty(); }

        size_type size() const
        { return _M_t.size(); }

        Pair<Iterator, bool> insert(const value_type& _x)
        {
            Pair<typename _Rep_type::Iterator, bool> _p = _M_t._insert_unique(_x);
            return Pair<Iterator, bool>(_p.first, _p.second);
        }

        value_type erase(const key_type& _x)
        {
            return _M_t.erase(_x);
        }

        bool find(const key_type& _x)
        {
            if (_M_t.find(_x) != end())
                return true;
            return false;
        }
};
}

#endif
