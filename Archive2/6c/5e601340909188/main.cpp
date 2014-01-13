#include <iostream>

struct ListElement {
    ListElement * next;
};

void joinLast1(ListElement *&l1, ListElement *&l2) {
    if (l1->next == nullptr) {
        l2 = l1;
        l1 = nullptr;
    } else {
        joinLast1(l1->next, l2);
    }
}

void joinLast2(ListElement *&l1, ListElement *&l2) {
    if (l1->next == nullptr) {
        l2 = l1;
        l1 = nullptr;
    } else {
        ListElement * help = l1;
        while (help->next->next != nullptr) {
            help = help->next;
        }
        l2 = help->next;
        help->next = nullptr;
    }
}

int main() {
    {
        ListElement help2{nullptr};
        ListElement help{&help2};
        ListElement * l1 = &help;
        ListElement * l2 = nullptr;
        std::cout << l1 << " " << l1->next << " : " << l2 << std::endl;
        joinLast1(l1, l2);
        std::cout << l1 << " " << l1->next << " : " << l2 << " " << l2->next << std::endl;
    }
    {
        ListElement help2{nullptr};
        ListElement help{&help2};
        ListElement * l1 = &help;
        ListElement * l2 = nullptr;
        std::cout << l1 << " " << l1->next << " : " << l2 << std::endl;
        joinLast2(l1, l2);
        std::cout << l1 << " " << l1->next << " : " << l2 << " " << l2->next << std::endl;
    }
}