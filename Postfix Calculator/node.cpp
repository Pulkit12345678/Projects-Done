#include <iostream>
#include "node.h"

Node::Node(bool sentinel)
{
    this->value = 0;
    this->is_sentinel = sentinel;
    this->next = nullptr;
    this->prev = nullptr;
}

Node::Node(int v, Node *nxt, Node *prv)
{
    this->value = v;
    this->next = nxt;
    this->prev = prv;
}

bool Node::is_sentinel_node()
{
    return is_sentinel;
}

int Node::get_value()
{
    return value;
}