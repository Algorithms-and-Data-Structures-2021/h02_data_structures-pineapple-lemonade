#include <iostream>

#include "array_list.hpp"
#include "linked_list.hpp"

using namespace itis;

int main(int argc, char **argv) {
    std::cout << "Hello, stranger!" << std::endl;

    auto linked_list = new LinkedList();
//    linked_list->Add(Element::CHERRY_PIE);
//    linked_list->Add(Element::GRAVITY_GUN);
//    linked_list->Add(Element::DRAGON_BALL);
    linked_list->Insert(0,Element::BEAUTIFUL_FLOWERS);
    std::cout << linked_list[0] << linked_list->GetSize();
    return 0;
}