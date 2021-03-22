#include <iostream>

#include "array_list.hpp"
#include "linked_list.hpp"

using namespace itis;

int main(int argc, char **argv) {
    std::cout << "Hello, stranger!" << std::endl;

    auto array_list = new ArrayList();
    array_list->Add(Element::BEAUTIFUL_FLOWERS);
    array_list->Add(Element::GRAVITY_GUN);
    array_list->Add(Element::DRAGON_BALL);
    array_list->Insert(0,Element::CHERRY_PIE);
    std::cout << array_list[0];
    return 0;
}