#include <iostream>

template <typename T>
struct List {
    struct Node {
        T data;
        Node *next = nullptr;
    };

    Node *head = nullptr;

    void Insert(T x) {
        Node *temp = new Node();
        temp->data = x;
        temp->next = head;
        head = temp;
    }

    void Print() {

        if (head == NULL)
            return;
        while (head != NULL) {
            std::cout << head->data;
            head = head->next;
        }
    }

    void Dup() {
        if (head == NULL || head->next == NULL)
            return;
        Node *prev;
        Node *current;
        prev = head;
        current = head->next;
        while (current != NULL) {
            if (prev->data == current->data) {
                prev->next = current->next;
                current = prev->next;
                continue;
            } else {
                current = current->next;
            }
        }
    }
};

int main() {
    List<int> list;
    //for (auto i : {1,9,8,9}) list.Insert(i); 
    for (auto i : {8,9,8,8}) list.Insert(i); 
    //for (auto i : {9,8,9,1}) list.Insert(i); 

    std::cout << "\n linked list is\t";
    std::cout << "\n before deletion: ";
    list.Print();

    list.Dup();

    std::cout << "\n after deletion: ";
    list.Print();
}
