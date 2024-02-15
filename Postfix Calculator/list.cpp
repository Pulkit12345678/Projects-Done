#include <iostream>
#include "node.h"
#include "list.h"

using namespace std;

List::List() {
    this->size = 0;
    this->sentinel_head = new Node(true);
    this->sentinel_tail = new Node(true);
    this->sentinel_head->next = this->sentinel_tail;
    this->sentinel_tail->prev = this->sentinel_head;
}

List::~List() {
    Node* curr = this->sentinel_head->next;
    while (curr != this->sentinel_tail) {
        Node* next = curr->next;
        delete curr;
        curr = next;
    }
    delete this->sentinel_head;
    delete this->sentinel_tail;
}

void List::insert(int v) {
    Node* nodetoinsert = new Node(v, this->sentinel_tail, this->sentinel_tail->prev);
    this->sentinel_tail->prev->next = nodetoinsert;
    this->sentinel_tail->prev = nodetoinsert;
    size++;
}

int List::delete_tail() {
    if (size == 0) {
        throw runtime_error("Empty Stack");
    }
    Node* nodetodelete = sentinel_tail->prev;
    int value = nodetodelete->get_value();
    nodetodelete->prev->next = sentinel_tail;
    sentinel_tail->prev = nodetodelete->prev;
    delete nodetodelete;
    size--;
    return value;
}

int List::get_size() {
    return size;
}

Node* List::get_head() {
    return sentinel_head;
}