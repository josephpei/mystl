/* ***************************************

* File Name : map_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/5/10 23:00:02

* Last Modified : 
 
**************************************** */
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../mystl_map.hpp"

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
    numb::Map<int, char> m;

    int ia[100];
    for (int i = 0; i < N; ++i)
        ia[i] = i;
    Shuffle(ia, 100);

    for (int i = 0; i < N; ++i)
        m[ia[i]] = (char)i;

    for (int i = 0; i < N; ++i)
        std::cout << m[i] << ' ';

    std::cout << std::endl;
    return 0;
}
