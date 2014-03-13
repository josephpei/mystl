#ifndef _MYSTL_STACK_H
#define _MYSTL_STACK_H
#include "mystl_vector.hpp"

namespace numb {
template <typename _Tp, typename _Sequence = Vector<_Tp> >
class Stack {
public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
    typedef typename _Sequence::size_type size_type;
    typedef _Sequence container_type;

protected:
    _Sequence c;

public:
    Stack() {}

    template <typename _InputIterator>
    Stack(_InputIterator _first, _InputIterator _last)
    : c(_first, _last) { }

    bool empty() const { return c.empty(); }

    size_type size() const { return c.size(); }

    const_reference top() const { return c.back(); }

    void push(const value_type& _x) {
        c.push_back(_x);
    }

    value_type pop() {
        return c.pop_back();
    }

};
}

#endif
