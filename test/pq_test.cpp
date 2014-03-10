/* ***************************************

* File Name : pq_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/10 16:13:19

* Last Modified : 
 
**************************************** */
#include "../mystl_queue.hpp"
#include <iostream>


int main(int argc, char *argv[])
{
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    numb::Priority_queue<int> ipq(ia, ia+9);
    std::cout << "size = " << ipq.size() << std::endl;

    for (int i = 0; i < ipq.size(); ++i)
        std::cout << ipq.top() << ' ';
    std::cout << std::endl;

    while (!ipq.empty()) {
        std::cout << ipq.pop() << ' ';
    }
    std::cout << std::endl;
    return 0;
}
