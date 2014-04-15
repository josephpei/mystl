/* ***************************************

* File Name : set_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/12 23:21:11

* Last Modified : 
 
**************************************** */
#include <iostream>
#include "../mystl_set.hpp"

int main(int argc, char *argv[])
{
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    numb::Set<int> s1;
    for (int i = 0; i < 9; ++i)
        s1.insert(ia[i]);
    std::cout << s1.find(6) << std::endl;
    numb::Set<int>::Iterator it = s1.begin();
    std::cout << "Set1: \n";
    for (; it != s1.end(); ++it)
        std::cout << *it << std::endl;

    numb::Set<int> s2 = s1;
    numb::Set<int>::Iterator it2 = s2.begin();
    std::cout << "Set2: \n";
    for (; it2 != s2.end(); ++it2)
        std::cout << *it2 << std::endl;
    return 0;
}
