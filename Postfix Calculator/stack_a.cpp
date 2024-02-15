#include <iostream>
#include "stack_a.h"
#include <sstream>
#include <stdexcept>

using namespace std;

Stack_A::Stack_A()
{
    size = -1;
}

void Stack_A::push(int data)
{
    if (size >= 1023)
    {
        throw runtime_error("Stack Full");
    }
    else
    {
        size++;
        stk[size] = data;
    }
}

int Stack_A::pop()
{
    if (size == -1)
    {
        throw runtime_error("Empty Stack");
    }
    else
    {
        return stk[size--];
    }
}

int Stack_A::get_element_from_top(int idx)
{
    if (size == -1)
    {
        throw runtime_error("Empty Stack");
    }
    else if (idx > size)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        return stk[size - idx ];
    }
}

int Stack_A::get_element_from_bottom(int idx)
{
    if (size == -1)
    {
        throw runtime_error("Empty Stack");
    }
    else if (idx > size)
    {
        throw runtime_error("Index out of range");
    }
    else
    {
        return stk[idx];
    }
}

void Stack_A::print_stack(bool top)
{
    if (top)
    {
        for (int i = size; i >= 0; i--)
        {
            cout << stk[i] << endl;
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            cout << stk[i] << endl;
        }
    }
}

int Stack_A::get_size()
{
    if (size == -1)
    {
        return 0;
    }
    else
    {
        return size + 1;
    }
}

int Stack_A::add()
{
    if (get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = stk[size];
    pop();
    int operand_2 = stk[size];
    pop();

    int value = operand_1 + operand_2;
    push(value);
    return value;
}

int Stack_A::subtract()
{
    if (get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = stk[size];
    pop();
    int operand_2 = stk[size];
    pop();

    int value = operand_2 - operand_1;
    push(value);
    return value;
}

int Stack_A::multiply()
{
    if (get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = stk[size];
    pop();
    int operand_2 = stk[size];
    pop();

    int value = operand_2 * operand_1;
    push(value);
    return value;
}

int Stack_A::divide()
{
    if (get_size() < 2)
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

int *Stack_A::get_stack()
{
    return stk;
}


