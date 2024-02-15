#include <iostream>
#include "node.h"
#include "list.h"
#include "stack_c.h"
#include "stdexcept"

using namespace std;

Stack_C::Stack_C()
{
    this->stk = new List();
}

Stack_C::~Stack_C()
{
    delete stk;
}

void Stack_C::push(int d)
{
    try{
    stk->insert(d);}
    catch(bad_alloc&)
    {
        throw runtime_error("Out of Memory");
    }
}

int Stack_C::pop()
{
    if(stk->get_size() == 0)
    {
        throw runtime_error("Empty Stack");
    }
    return stk->delete_tail();
}

int Stack_C::get_element_from_top(int idx)
{
    if (idx < 0 || idx >= stk->get_size())
    {
        throw runtime_error("Index out of range");
    }
    Node *curr = stk->get_head()->next;
    for (int i = 0; i < stk->get_size() - idx - 1; i++)
    {
        curr = curr->next;
    }
    return curr->get_value();
}

int Stack_C::get_element_from_bottom(int idx)
{
    if (idx < 0 || idx >= stk->get_size())
    {
        throw runtime_error("Index out of range");
    }
    Node *curr = stk->get_head()->next;
    for (int i = 0; i < idx; i++)
    {
        curr = curr->next;
    }
    return curr->get_value();
}

void Stack_C::print_stack(bool top)
{
    if (!top)
    {
        Node *curr = stk->get_head()->next;
        while (!curr->is_sentinel_node())
        {
            cout << curr->get_value() << endl;
            curr = curr->next;
        }
    }
    else
    {
        Node *curr = stk->get_head()->next;
        while (!curr->is_sentinel_node())
        {
            curr = curr->next;
        }

        curr = curr->prev;
        while (!curr->is_sentinel_node())
        {
            cout << curr->get_value() << endl;
            curr = curr->prev;
        }
    }
}

int Stack_C::add()
{
    if (stk->get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = pop();
    int operand_2 = pop();
    int value = operand_1 + operand_2;
    push(value);
    return operand_1 + operand_2;
}

int Stack_C::subtract()
{
    if (stk->get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = pop();
    int operand_2 = pop();
    int value = operand_2 - operand_1;
    push(value);
    return value;
}

int Stack_C::multiply()
{
    if (stk->get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = pop();
    int operand_2 = pop();
    int value = operand_1 * operand_2;
    push(value);
    return operand_1 * operand_2;
}

int Stack_C::divide()
{
    if (stk->get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = pop();
    int operand_2 = pop();

    if (operand_1 == 0)
    {
        throw runtime_error("Divide by Zero Error");
    }
    if(abs(operand_2) % abs(operand_1) == 0)
    {
        int a = operand_2/operand_1;
        push(a);
        return a;
    }

    int value = abs(operand_2) / abs(operand_1);

    if ((operand_2 < 0 && operand_1 > 0) || (operand_2 > 0 && operand_1 < 0))
    {
        value *= -1;
        value -= 1;
    }

    push(value);
    return value;
}

List *Stack_C::get_stack()
{
    return stk;
}

int Stack_C::get_size()
{
    return stk->get_size();
}
