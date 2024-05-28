#include <iostream>

struct Link {
    int value;
    Link* next = nullptr;
};

size_t size(const Link* head) {
    size_t count = 0;
    const Link* current = head;
    while (current != nullptr) {
        ++count;
        current = current->next;
    }
    return count;
}

size_t sum(const Link* head) {
    size_t total = 0;
    const Link* current = head;
    while (current != nullptr) {
        total += current->value;
        current = current->next;
    }
    return total;
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

    std::cout << "Liczba elementów: " << size(head) << std::endl;

    std::cout << "Suma wartości: " << sum(head) << std::endl;

    while (head != nullptr) {
        Link* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}
