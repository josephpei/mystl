#ifndef _MYSTL_MAP_H
#define _MYSTL_MAP_H
#include "mystl_avl.hpp"
#include "mystl_rbtree.hpp"
#include "mystl_algobase.hpp"
#include "mystl_pair.hpp"

namespace numb {
template<typename _Key, typename _Tp, typename _Compare = Less<_Key> >
class Map {
    public:
        typedef _Key key_type;
        typedef _Tp mapped_type;
        typedef Pair<const _Key, _Tp> value_type;
        typedef _Compare key_compare;

    public:
        class value_compare : public Binary_function<value_type, value_type, bool> {
            friend class Map<_Key, _Tp, _Compare>;
            protected:
            _Compare comp;

            value_compare(_Compare _c) : comp(_c) { }

            public:
            bool operator()(const value_type& _x, const value_type& _y) const
            { return comp(_x.first, _y.first); }
        };

    private:
        //typedef _AVL<key_type, value_type, _Select1st<value_type>, key_compare> _Rep_type;
        typedef _RBtree<key_type, value_type, _Select1st<value_type>, key_compare> _Rep_type;
        _Rep_type _M_t;

    public:
        typedef typename _Rep_type::Iterator Iterator;
        typedef typename _Rep_type::Const_iterator Const_iterator;
        typedef typename _Rep_type::size_type size_type;
        typedef typename _Rep_type::difference_type difference_type;

        Map() : _M_t() { }

        Map(const Map& _x) : _M_t(_x._M_t) { }

        Map& operator=(const Map& _x)
        { _M_t = _x._M_t; return *this; }

        Iterator begin() throw()
        { return _M_t.begin(); }

        Const_iterator begin() const throw()
        { return _M_t.begin(); }

        Iterator end() throw()
        { return _M_t.end(); }

        Const_iterator end() const throw()
        { return _M_t.end(); }

        bool empty() const throw()
        { return _M_t.empty(); }

        size_type size() const throw()
        { return _M_t.size(); }

        mapped_type& operator[](const key_type& _k)
        {
            Pair<Iterator, bool> _j = insert(value_type(_k, mapped_type()));
            return (*(_j.first)).second;
        }

        Iterator lower_bound(const key_type& _k)
        { return _M_t.lower_bound(_k); }

        Const_iterator lower_bound(const key_type& _k) const
        { return _M_t.lower_bound(_k); }

        mapped_type& at(const key_type& _k)
        {
            Iterator _i = lower_bound(_k);
            if (_i == end() || key_comp()(_k, (*_i).first))
                throw;
            return (*_i).second;
        }

        const mapped_type& at(const key_type& _k) const
        {
            Const_iterator _i = lower_bound(_k);
            if (_i == end() || key_comp()(_k, (*_i).first))
                throw;
            return (*_i).second;
        }

        Pair<Iterator, bool> insert(const value_type& _x)
        { return _M_t._insert_unique(_x); }

        void erase(const key_type& _x)
        { return _M_t.erase(_x); }

        key_compare key_comp() const
        { return key_compare(); }

        value_compare value_comp() const
        { return key_compare(); }
};
}

#endif
