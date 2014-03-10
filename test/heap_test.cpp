/* ***************************************

* File Name : heap_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/10 15:20:52

* Last Modified : 
 
**************************************** */
#include "../mystl_heap.hpp"
#include "../mystl_vector.hpp"
#include "../mystl_algobase.hpp"
#include <iostream>
#include <iterator>

int main(int argc, char *argv[])
{
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    numb::Vector<int> ivec(ia, ia + 9);
    std::ostream_iterator<int> out_it(std::cout, " ");
    numb::Copy(ivec.begin(), ivec.end(), out_it);
    std::cout << std::endl;

    numb::Make_heap(ivec.begin(), ivec.end());
    numb::Copy(ivec.begin(), ivec.end(), out_it);
    std::cout << std::endl;

    ivec.push_back(7);
    numb::Push_heap(ivec.begin(), ivec.end());
    numb::Copy(ivec.begin(), ivec.end(), out_it);
    std::cout << std::endl;

    numb::Pop_heap(ivec.begin(), ivec.end());
    std::cout << ivec.back() << std::endl;
    ivec.pop_back();

    numb::Copy(ivec.begin(), ivec.end(), out_it);
    std::cout << std::endl;

    numb::Sort_heap(ivec.begin(), ivec.end());
    numb::Copy(ivec.begin(), ivec.end(), out_it);
    std::cout << std::endl;
    return 0;
}
