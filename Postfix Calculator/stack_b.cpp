#include <iostream>
#include "stack_b.h"
#include <sstream>
#include <stdexcept>

using namespace std;

Stack_B ::Stack_B()
{
    stk = new int[1024];
    size = -1;
    capacity = 1024;
}

Stack_B ::~Stack_B()
{
    delete[] stk;
}

void Stack_B ::push(int data)
{
    if (size == capacity - 1)
    {
        int newcap = capacity * 2;
        try
        {
            int *newstk = new int[newcap];
            for (int i = 0; i <= size; i++)
            {
                newstk[i] = stk[i];
            }
            delete[] stk;
            stk = newstk;
            capacity = newcap;
        }
        catch (bad_alloc&)
        {
            throw runtime_error("Out of Memory");
        }
    }
    size++;
    stk[size] = data;
}

int Stack_B ::pop()
{
    if (size == -1)
    {
        throw runtime_error("Empty Stack");
    }
    else
    {
        int popvalue = stk[size];
        size--;
        if (size < capacity / 2 && capacity > 1024)
        {
            try
            {
                int newcap = max(1024, capacity / 2);
                int *newstk = new int[newcap];
                for (int i = 0; i <= size; i++)
                {
                    newstk[i] = stk[i];
                }
                delete[] stk;
                stk = newstk;
                capacity = newcap;
            }
            catch (bad_alloc&)
            {
                throw runtime_error("Out of Memory");
            }
        }
        if (size == -1)
        {
            capacity = 1024;
        }
        return popvalue;
    }
}

int Stack_B ::get_element_from_top(int idx)
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
        return stk[size - idx];
    }
}

int Stack_B ::get_element_from_bottom(int idx)
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

void Stack_B ::print_stack(bool top)
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

int Stack_B ::get_size()
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

int Stack_B ::add()
{
    if (get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = pop();
    // cout << operand_1 << endl;
    int operand_2 = pop();
    // cout << operand_2 << endl;
    int value = operand_1 + operand_2;
    push(value);
    return value;
}

int Stack_B::subtract()
{
    if (get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = pop();
    int operand_2 = pop();

    int value = operand_2 - operand_1;
    push(value);
    return value;
}

int Stack_B ::multiply()
{
    if (get_size() < 2)
    {
        throw runtime_error("Not Enough Arguments");
    }
    int operand_1 = pop();
    int operand_2 = pop();

    int value = operand_2 * operand_1;
    push(value);
    return value;
}

int Stack_B::divide()
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
    if (abs(operand_2) % abs(operand_1) == 0)
    {
        int a = operand_2 / operand_1;
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

int *Stack_B ::get_stack()
{
    return stk;
}