#ifndef _MYSTL_Pair_H
#define _MYSTL_Pair_H

template <typename _T1, typename _T2>
struct Pair {
    typedef _T1 first_type;
    typedef _T2 second_type;

    _T1 first;
    _T2 second;

    Pair() : first(), second() {}

    Pair(const _T1& _a, const _T2& _b) : first(_a), second(_b) {}

    template <typename _U1, typename _U2>
    Pair(const Pair<_U1, _U2>& _p)
        : first(_p.first), second(_p.second) {}
};

template <typename _T1, typename _T2>
inline bool operator==(const Pair<_T1, _T2>& _x, const Pair<_T1, _T2>& _y) {
    return _x.firt == _y.first && _x.second == _y.second;
}

template <typename _T1, typename _T2>
inline bool operator<(const Pair<_T1, _T2>& _x, const Pair<_T1, _T2>& _y) {
    return _x.first < _y.first ||
           (!(_y.first < _x.first) && _x.second < _y.second);
}

template <typename _T1, typename _T2>
inline bool operator!=(const Pair<_T1, _T2>& _x, const Pair<_T1, _T2>& _y) {
    return !(_x == _y);
}

template <typename _T1, typename _T2>
inline bool operator>(const Pair<_T1, _T2>& _x, const Pair<_T1, _T2>& _y) {
    return _y < _x;
}

template <typename _T1, typename _T2>
inline bool operator<=(const Pair<_T1, _T2>& _x, const Pair<_T1, _T2>& _y) {
    return !(_y < _x);
}

template <typename _T1, typename _T2>
inline bool operator>=(const Pair<_T1, _T2>& _x, const Pair<_T1, _T2>& _y) {
    return !(_x < _y);
}

template <typename _T1, typename _T2>
inline Pair<_T1, _T2> Make_pair(_T1 _x, _T2 _y) {
    return Pair<_T1, _T2>(_x, _y);
}

#endif
