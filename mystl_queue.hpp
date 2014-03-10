#ifndef _MYSTL_QUEUE_H
#define _MYSTL_QUEUE_H
#include "mystl_list.hpp"
#include "mystl_vector.hpp"
#include "mystl_heap.hpp"

namespace numb {
template <typename _Tp, typename _Sequence = List<_Tp> >
class Queue {

    template <typename _Tp1, typename _Seq1>
    friend bool operator==(const Queue<_Tp1, _Seq1>&,
                           const Queue<_Tp1, _Seq1>&);

    template <typename _Tp1, typename _Seq1>
    friend bool operator<(const Queue<_Tp1, _Seq1>&, const Queue<_Tp1, _Seq1>&);

public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
    typedef typename _Sequence::size_type size_type;

protected:
    _Sequence c;

public:
    explicit Queue(const _Sequence& _c = _Sequence()) : c(_c) {}

    bool empty() const { return c.empty(); }

    size_type size() const { return c.size(); }

    reference front() { return c.front(); }

    const_reference front() const { return c.front(); }

    reference back() { return c.back(); }

    const_reference back() const { return c.back(); }

    void push(const value_type& _x) { c.push_back(_x); }

    value_type pop() { return c.pop_front(); }
};

template <typename _Tp, typename _Seq>
inline bool operator==(const Queue<_Tp, _Seq>& __x,
                       const Queue<_Tp, _Seq>& __y) {
    return __x.c == __y.c;
}

template <typename _Tp, typename _Seq>
inline bool operator<(const Queue<_Tp, _Seq>& __x,
                      const Queue<_Tp, _Seq>& __y) {
    return __x.c < __y.c;
}

/// Based on operator==
template <typename _Tp, typename _Seq>
inline bool operator!=(const Queue<_Tp, _Seq>& __x,
                       const Queue<_Tp, _Seq>& __y) {
    return !(__x == __y);
}

/// Based on operator<
template <typename _Tp, typename _Seq>
inline bool operator>(const Queue<_Tp, _Seq>& __x,
                      const Queue<_Tp, _Seq>& __y) {
    return __y < __x;
}

/// Based on operator<
template <typename _Tp, typename _Seq>
inline bool operator<=(const Queue<_Tp, _Seq>& __x,
                       const Queue<_Tp, _Seq>& __y) {
    return !(__y < __x);
}

/// Based on operator<
template <typename _Tp, typename _Seq>
inline bool operator>=(const Queue<_Tp, _Seq>& __x,
                       const Queue<_Tp, _Seq>& __y) {
    return !(__x < __y);
}

template <typename _Tp, typename _Sequence = Vector<_Tp>,
          typename _Compare = Less<typename _Sequence::value_type> >
class Priority_queue {
public:
    typedef typename _Sequence::value_type value_type;
    typedef typename _Sequence::reference reference;
    typedef typename _Sequence::const_reference const_reference;
    typedef typename _Sequence::size_type size_type;
    typedef _Sequence container_type;

protected:
    _Sequence c;
    _Compare comp;

public:
    Priority_queue(const _Compare& _x = _Compare(),
                   const _Sequence& _s = _Sequence())
        : c(_s), comp(_x) {
        Make_heap(c.begin(), c.end(), comp);
    }

    template <typename _InputIterator>
    Priority_queue(_InputIterator _first, _InputIterator _last, const _Compare& _x = _Compare())
    : c(_first, _last), comp(_x)
    { Make_heap(c.begin(), c.end(), comp); }

    bool empty() const { return c.empty(); }

    size_type size() const { return c.size(); }

    const_reference top() const { return c.front(); }

    void push(const value_type& _x) {
        c.push_back(_x);
        Push_heap(c.begin(), c.end(), comp);
    }

    value_type pop() {
        Pop_heap(c.begin(), c.end(), comp);
        return c.pop_back();
    }
};
}

#endif
