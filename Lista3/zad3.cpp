#include <iostream>

struct Link {
    int value;
    Link* next = nullptr;
};

void reverse(Link*& head) {
    Link* prev = nullptr;
    Link* current = head;
    Link* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
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
    push_front(head, 9);
    push_front(head, 5);
    push_front(head, 2);
    push_front(head, 1);
    std::cout << "Lista przed odwróceniem: ";
    print_list(head);
    reverse(head);
    std::cout << "Lista po odwróceniu: ";
    print_list(head);
    while (head != nullptr) {
        Link* temp = head;
        head = head->next;
        delete temp;
    }
    return 0;
}
