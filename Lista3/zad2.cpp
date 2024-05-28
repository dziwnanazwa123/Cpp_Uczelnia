#include <iostream>

struct Link {
    int value;
    Link* next = nullptr;
};

void release(Link** phead) {
    if (*phead == nullptr) {
        return;
    }

    Link* next = (*phead)->next;

    delete *phead;

    *phead = next;

    release(phead);
}

void push_front(Link*& head, int value) {
    Link* new_link = new Link;
    new_link->value = value;
    new_link->next = head;
    head = new_link;
}

void print_list(const Link* head) {
    const Link* current = head;
    while (current != nullptr) {
        std::cout << current->value << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

int main() {
    Link* head = nullptr;
    push_front (head, 5);
    push_front (head, 10);
    push_front (head, 15);

    std::cout << "Lista: ";
    print_list(head);

    release(&head);

    std::cout << "Lista po zwolnieniu pamięci: ";
    print_list(head);

    return 0;
}
