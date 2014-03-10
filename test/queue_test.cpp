/* ***************************************

* File Name : queue_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/9 21:11:32

* Last Modified : 
 
**************************************** */
#include "../mystl_queue.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
    numb::Queue<int> Q1;
    for (int i = 0; i < 50; i++)
        Q1.push(i);

    for (int i = 0; i < 50; i++)
        std::cout << Q1.pop() << ' ';
    std::cout << std::endl;
    return 0;
}
