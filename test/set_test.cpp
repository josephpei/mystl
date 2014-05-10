/* ***************************************

* File Name : set_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/12 23:21:11

* Last Modified : 
 
**************************************** */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../mystl_set.hpp"

template<typename T>
void Shuffle(T *a, size_t sz)
{
    srand((unsigned)time(NULL));
    for (size_t i = 0; i < sz; ++i) {
        size_t r = i + rand() / (RAND_MAX / (sz - i) + 1);
        numb::Swap(a[i], a[r]);
    }
}

#define N 100

int main(int argc, char *argv[])
{
    int ia[100];
    for (int i = 0; i < N; ++i)
        ia[i] = i + 1;
    Shuffle(ia, 100);

    numb::Set<int> s1;
    for (int i = 0; i < N; ++i)
        s1.insert(ia[i]);
    std::cout << s1.find(6) << std::endl;
    numb::Set<int>::Iterator it = s1.begin();
    std::cout << "Set1: \n";
    for (; it != s1.end(); ++it)
        std::cout << *it << ", ";
    std::cout << std::endl;

    for (int i = 0; i < N/10; ++i)
        s1.erase((i+1) * 7);

    it = s1.lower_bound(7);
    std::cout << "7 lower bound: " << *it << std::endl;

    it = s1.upper_bound(14);
    std::cout << "14 upper bound: " << *it << std::endl;

    numb::Set<int> s2 = s1;
    numb::Set<int>::Iterator it2 = s2.begin();
    std::cout << "Set2: \n";
    for (; it2 != s2.end(); ++it2)
        std::cout << *it2 << ", ";
    std::cout << std::endl;
    return 0;
}
