/* ***************************************

* File Name : flist_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/10 18:31:58

* Last Modified : 
 
**************************************** */
#include <iostream>
#include <iterator>
#include "../mystl_forwardlist.hpp"

int main(int argc, char *argv[])
{
    numb::Forward_list<int> FL;
    for (int i = 0; i < 50; ++i)
        FL.push_front(i);

    std::ostream_iterator<int> out_it(std::cout, " ");
    std::cout << "Forwardlist:\n";

    numb::Copy(FL.begin(), FL.end(), out_it);

    return 0;
}
