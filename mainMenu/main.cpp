#include <iostream>

#include "menu.hpp"

void task1(){
    std::cout << "task1\n";
}
void task2(){
    std::cout<<"task2\n";
}

int main()
{
    menu m{{{1,task1},{2,task2}}};
    m.run();
    return 0;
}
