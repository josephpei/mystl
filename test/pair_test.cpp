/* ***************************************

* File Name : pair_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/4 20:23:39

* Last Modified : 
 
**************************************** */
#include <iostream>
#include "../mystl_pair.hpp"

int main(int argc, char *argv[])
{
    int n = 1;
    int a[5] = {1, 2, 3, 4, 5};

    Pair<int, int> p1 = Make_pair(n, a[1]);
    std::cout << "The value of p1 is"
              << "(" << p1.first << "," << p1.second << ")\n";
    return 0;
}
