/* ***************************************

* File Name : list_test.cpp

* Copyright (C) 2014 Pei Yangwei<josephpei@gmail.com> 

* Purpose :

* Creation Date : 2014/3/4 18:07:22

* Last Modified : 
 
**************************************** */
#include "../mystl_list.hpp"
#include <iostream>
#include <iterator>

int main ()
{
    numb::List<int> IL;
    numb::List<int> IL2;
    IL.push_back(101);

    for (int i = 0; i != 50; i++)
    {
        IL.push_front(i);
        IL2.push_back(i);
    }
    IL.pop_front();
    IL2.pop_back();

    numb::List<int> IL3 = IL;

    std::ostream_iterator<int> out_it(std::cout, " ");

    std::cout << "list1:" << std::endl;
    numb::Copy(IL.begin(), IL.end(), out_it);
    std::cout << "\n\nlist2:\n";
    numb::Copy(IL2.begin(), IL2.end(), out_it);
    std::cout << "\n\nlist3:\n";
    numb::Copy(IL3.begin(), IL3.end(), out_it);


    return 0;
}

