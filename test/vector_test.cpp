/* ***************************************

* File Name : Allocator_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com>

* Purpose :

* Creation Date : 2014/2/24 19:47:37

* Last Modified :

**************************************** */


#include "../mystl_vector.hpp"
#include <iostream>
#include <iterator>
int main ()
{
    numb::Vector<int> IV;

    for (int i = 0; i != 50; i++)
    {
        IV.push_back(i);
    }
    numb::Vector<int> IV2(IV);

    std::ostream_iterator<int> out_it(std::cout, " ");

    std::cout << "list:" << std::endl;
    numb::Copy(IV.begin(), IV.end(), out_it);
    std::cout << "\n\n\n";
    numb::Copy(IV2.begin(), IV2.end(), out_it);
    std::cout << "\n\n";


    return 0;
}

