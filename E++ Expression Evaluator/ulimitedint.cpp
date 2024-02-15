/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedint.h"
#include <iostream>

UnlimitedInt::UnlimitedInt()
{
    size = 0;
    sign = 1;
    capacity = 2;
    unlimited_int = new int[capacity];
    unlimited_int[0] = sign;
    unlimited_int[1] = 0;
}

UnlimitedInt::UnlimitedInt(string s)
{
    capacity = 2 * s.length();
    unlimited_int = new int[capacity];
    if (s[0] == '+')
    {
        sign = 1;
        size = s.length() - 1;
        unlimited_int[0] = sign;
        for (int i = s.length() - 1; i > 0; i--)
        {
            unlimited_int[size + 1 - i] = stoi(s.substr(i, 1));
        }
    }
    else if (s[0] == '-')
    {
        sign = -1;
        size = s.length() - 1;
        unlimited_int[0] = sign;
        for (int i = s.length() - 1; i > 0; i--)
        {
            unlimited_int[size + 1 - i] = stoi(s.substr(i, 1));
        }
    }
    else
    {
        sign = 1;
        size = s.length();
        unlimited_int[0] = sign;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            unlimited_int[size - i] = stoi(s.substr(i, 1));
        }
    }
}

string UnlimitedInt::to_string()
{
    string s = "";
    if (sign == -1)
    {
        s = s + "-";
    }
    for (int i = size; i > 0; i--)
    {
        s = s + std::to_string(unlimited_int[i]);
    }
    return s;
}

UnlimitedInt::UnlimitedInt(int num)
{
    string s = std::to_string(num);
    capacity = 2 * s.length();
    unlimited_int = new int[capacity];
    if (s[0] == '+')
    {
        sign = 1;
        size = s.length() - 1;
        unlimited_int[0] = sign;
        for (int i = s.length() - 1; i > 0; i--)
        {
            unlimited_int[size + 1 - i] = stoi(s.substr(i, 1));
        }
    }
    else if (s[0] == '-')
    {
        sign = -1;
        size = s.length() - 1;
        unlimited_int[0] = sign;
        for (int i = s.length() - 1; i > 0; i--)
        {
            unlimited_int[size + 1 - i] = stoi(s.substr(i, 1));
        }
    }
    else
    {
        sign = 1;
        size = s.length();
        unlimited_int[0] = sign;
        for (int i = s.length() - 1; i >= 0; i--)
        {
            unlimited_int[size - i] = stoi(s.substr(i, 1));
        }
    }
}

UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{
    unlimited_int = ulimited_int;
    capacity = cap;
    sign = sgn;
    size = sz;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

int UnlimitedInt::get_size()
{
    return size;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}

UnlimitedInt *compare(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int *i_1 = i1->get_array();
    int *i_2 = i2->get_array();
    if (i1->get_size() == i2->get_size())
    {
        for (int i = i1->get_size(); i >= 1; i--)
        {
            if (i_1[i] > i_2[i])
            {
                return i1;
            }
            if (i_1[i] < i_2[i])
            {
                return i2;
            }
        }
        return i1;
    }
    if (i1->get_size() > i2->get_size())
    {
        return i1;
    }
    else
    {
        return i2;
    }
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_sign() == i2->get_sign())
    {
        int i_1 = i1->get_size();
        int i_2 = i2->get_size();
        UnlimitedInt *result = new UnlimitedInt();
        result->sign = i1->sign;
        int max_size = max(i_1, i_2);

        result->capacity = max_size + 2;
        result->unlimited_int = new int[result->capacity];
        int carry = 0;
        for (int i = 1; i <= max_size; i++)
        {
            int i_11 = 0;
            if (i <= i_1)
            {
                i_11 = i1->unlimited_int[i];
            }

            int i_22 = 0;
            if (i <= i_2)
            {
                i_22 = i2->unlimited_int[i];
            }

            int sum = i_11 + i_22 + carry;
            int input = sum % 10;
            carry = sum / 10;
            result->unlimited_int[i] = input;
        }
        if (carry != 0)
        {
            result->size = max_size + 1;
            result->unlimited_int[max_size + 1] = carry;
        }
        else
        {
            result->size = max_size;
        }
        if (result->get_sign() == -1)
        {
            result->unlimited_int[0] = -1;
            result->sign = -1;
        }
        return result;
    }
    else
    {
        if (i1->get_sign() == 1)
        {
            UnlimitedInt *temp = new UnlimitedInt(i2->to_string());
            temp->unlimited_int[0] = 1;
            temp->sign = 1;
            return sub(i1, temp);
        }

        else
        {
            UnlimitedInt *temp = new UnlimitedInt(i1->to_string());
            temp->unlimited_int[0] = 1;
            temp->sign = 1;
            return sub(i2, temp);
        }
    }
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1 == i2)
    {
        UnlimitedInt *result = new UnlimitedInt("0");
        return result;
    }
    if (i1->get_sign() == i2->get_sign())
    {
        if (i1->get_sign() == 1)
        {
            UnlimitedInt *result = new UnlimitedInt();
            UnlimitedInt *larger = compare(i1, i2);
            if (larger == i1)
            {
                int max_size = larger->get_size();
                result->capacity = max_size + 2;
                result->sign = 1;
                result->unlimited_int = new int[result->capacity];
                int borrow = 0;
                for (int i = 1; i <= max_size; i++)
                {
                    int i_11 = 0;
                    if (i <= i1->get_size())
                    {
                        i_11 = i1->unlimited_int[i];
                    }

                    int i_22 = 0;
                    if (i <= i2->get_size())
                    {
                        i_22 = i2->unlimited_int[i];
                    }

                    int diff = i_11 - i_22 - borrow;

                    if (diff < 0)
                    {
                        diff += 10;
                        borrow = 1;
                    }
                    else
                    {
                        borrow = 0;
                    }
                    result->unlimited_int[i] = diff;
                }
                while (max_size > 0 && result->unlimited_int[max_size] == 0)
                {
                    max_size--;
                }
                result->size = max_size;
                result->unlimited_int[0] = 1;
                if(result->size == 0){
                    delete result;
                    result = new UnlimitedInt("0");
                }
                return result;
            }
            else
            {
                int max_size = larger->get_size();
                result->capacity = max_size + 2;
                result->sign = -1;
                result->unlimited_int = new int[result->capacity];
                int borrow = 0;
                for (int i = 1; i <= max_size; i++)
                {
                    int i_11 = 0;
                    if (i <= i1->get_size())
                    {
                        i_11 = i1->unlimited_int[i];
                    }

                    int i_22 = 0;
                    if (i <= i2->get_size())
                    {
                        i_22 = i2->unlimited_int[i];
                    }

                    int diff = i_22 - i_11 - borrow;

                    if (diff < 0)
                    {
                        diff += 10;
                        borrow = 1;
                    }
                    else
                    {
                        borrow = 0;
                    }
                    result->unlimited_int[i] = diff;
                }
                while (max_size > 0 && result->unlimited_int[max_size] == 0)
                {
                    max_size--;
                }
                result->size = max_size;
                result->unlimited_int[0] = -1;
                if(result->size == 0){
                    delete result;
                    result = new UnlimitedInt("0");
                }
                return result;
            }
        }
        else
        {
            UnlimitedInt *temp = new UnlimitedInt(i2->to_string());
            temp->sign = 1;
            temp->unlimited_int[0] = 1;
            UnlimitedInt *temp2 = new UnlimitedInt(i1->to_string());
            temp2->sign = 1;
            temp2->unlimited_int[0] = 1;
            return sub(temp, temp2);
        }
    }
    else
    {
        if (i1->get_sign() == -1)
        {
            UnlimitedInt *temp = new UnlimitedInt(i2->to_string());
            temp->sign = -1;
            temp->unlimited_int[0] = -1;
            return add(i1, temp);
        }
        else
        {
            UnlimitedInt *temp = new UnlimitedInt(i2->to_string());
            temp->sign = 1;
            temp->unlimited_int[0] = 1;
            return add(i1, temp);
        }
    }
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->to_string() == "0" || i2->to_string() == "0")
    {
        UnlimitedInt *result = new UnlimitedInt("0");
        return result;
    }

    UnlimitedInt *result = new UnlimitedInt();
    result->sign = i1->get_sign() * i2->get_sign();
    result->capacity = i1->get_size() + i2->get_size() + 2;
    result->unlimited_int = new int[result->capacity];
    result->unlimited_int[0] = i1->get_sign() * i2->get_sign();

    int *directmultiply = new int[result->capacity];
    int *carry = new int[result->capacity];

    for (int i = 0; i < result->capacity; i++)
    {
        carry[i] = 0;
        directmultiply[i] = 0;
    }

    for (int i = 1; i <= i1->get_size(); i++)
    {
        for (int j = 1; j <= i2->get_size(); j++)
        {
            int product = i1->unlimited_int[i] * i2->unlimited_int[j];
            directmultiply[i + j - 1] += product;
            if (directmultiply[i + j - 1] >= 10)
            {
                carry[i + j] += directmultiply[i + j - 1] / 10;
                directmultiply[i + j - 1] %= 10;
            }
        }
    }

    for (int i = 1; i < result->capacity; i++)
    {
        result->unlimited_int[i] = directmultiply[i] + carry[i];
        if (result->unlimited_int[i] >= 10)
        {
            carry[i + 1] += result->unlimited_int[i] / 10;
            result->unlimited_int[i] %= 10;
        }
        if (result->unlimited_int[i] != 0)
        {
            result->size = i;
        }
    }

    delete[] directmultiply;
    delete[] carry;

    return result;
}

UnlimitedInt *UnlimitedInt ::div(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if(i1->to_string()=="0"){
        return new UnlimitedInt("0");
    }
    if(i1->to_string()==i2->to_string()){
        return new UnlimitedInt("1");
    }
    if (compare(i1, i2) == i2)
    {
        return (new UnlimitedInt("0"));
    }
    UnlimitedInt *i = new UnlimitedInt();
    i->size = i1->size - i2->size + 1;
    i->capacity = i1->size - i2->size + 2;
    i->unlimited_int = new int[i->capacity];
    i->sign = i1->sign * i2->sign;
    i->unlimited_int[0] = i->sign;
    for (int j = 1; j <= i->size; j++)
    {
        i->unlimited_int[j] = 0;
    }
    for (int k = i->size; k >= 1; k--)
    {
        while (compare(mul(i, i2), i1) == i1)
        {
            i->unlimited_int[k] = i->unlimited_int[k] + 1;
        }
        if (mul(i, i2)->to_string() != i1->to_string())
        {
            i->unlimited_int[k] = i->unlimited_int[k] - 1;
        }
    }
    while (i->unlimited_int[i->size] == 0 && i->size > 0)
    {
        i->size = i->size - 1;
    }
    if (i1->sign != i2->sign)
    {
        if (mul(i, i2)->to_string() == i1->to_string())
        {
            return i;
        }
        else
        {
            return sub(i, new UnlimitedInt(1));
        }
    }
    return i;
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->sign == i2->sign)
    {
        return sub(i1, mul(div(i1, i2), i2));
    }
    else if (i1->sign == -1)
    {
        return sub(i1, mul(div(i1, i2), i2));
    }
    else
    {
        return sub(mul(div(i1, i2), i2),i1);
    }
}


// int main(){
//     UnlimitedInt* temp = new UnlimitedInt("0");
//     UnlimitedInt* dummy = new UnlimitedInt("5");
//     cout<<compare(temp, dummy)->to_string()<<endl;
//     cout<<UnlimitedInt::div(temp, dummy)->to_string()<<endl;
//     cout<<UnlimitedInt::mod(temp, dummy)->to_string()<<endl;
// }