#include "ulimitedrational.h"
#include <iostream>

UnlimitedInt *compare1(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_size() > i2->get_size())
    {
        return i1;
    }
    else if (i1->get_size() < i2->get_size())
    {
        return i2;
    }
    else
    {
        int *i_1 = i1->get_array();
        int *i_2 = i2->get_array();
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
}
UnlimitedInt *hcf(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->to_string() == "0" || i2->to_string() == "0")
    {
        return new UnlimitedInt("1");
    }
    if (compare1(i1, i2) == i1)
    {
        if(i1->to_string()==i2->to_string()){
            return new UnlimitedInt("1");
        }
        else if (UnlimitedInt::mod(i1, i2)->to_string() == "0")
        {
            return new UnlimitedInt(i2->to_string());
        }
        else
        {
            UnlimitedInt *i_1 = new UnlimitedInt(i1->to_string());
            UnlimitedInt *i_2 = new UnlimitedInt(i2->to_string());
            while (UnlimitedInt::mod(i_1, i_2)->to_string() != "0")
            {
                string s1 = i_1->to_string();
                string s2 = i_2->to_string();
                // delete i_1;
                // delete i_2;
                i_1 = new UnlimitedInt(s2);
                i_2 = new UnlimitedInt(UnlimitedInt::mod(new UnlimitedInt(s1), new UnlimitedInt(s2))->to_string());
            }
            return i_2;
        }
    }
    else
    {
        if (UnlimitedInt::mod(i2, i1)->to_string() == "0")
        {
            return new UnlimitedInt(i1->to_string());
        }
        else
        {
            UnlimitedInt *i_1 = new UnlimitedInt(i2->to_string());
            UnlimitedInt *i_2 = new UnlimitedInt(i1->to_string());
            while (UnlimitedInt::mod(i_1, i_2)->to_string() != "0")
            {
                string s1 = i_1->to_string();
                string s2 = i_2->to_string();
                // delete i_1;
                // delete i_2;
                i_1 = new UnlimitedInt(s2);
                i_2 = new UnlimitedInt(UnlimitedInt::mod(new UnlimitedInt(s1), new UnlimitedInt(s2))->to_string());
            }
            return i_2;
        }
    }
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    p = num;
    q = den;
}

UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt("0");
    q = new UnlimitedInt("1");
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str()
{
    if (p->to_string() == "0" && q->to_string() == "0")
    {
        return "0/0";
    }
    else if (q->to_string() == "0")
    {
        return "0/0";
    }
    else if (p->to_string() == "0")
    {
        return "0/" + q->to_string();
    }
    else
    {
        UnlimitedInt *q1 = UnlimitedInt::div(p, hcf(p, q));
        UnlimitedInt *q2 = UnlimitedInt::div(q, hcf(p, q));
        string s = "";
        s = q1->to_string();
        s = s + "/" + q2->to_string();
        return s;
    }
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if ((i1->get_q_str()) == "0" || (i2->get_q_str()) == "0")
    {
        return new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
    }
    UnlimitedInt *i1_num = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt *i2_num = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt *i1_den = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt *i2_den = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt *result_num = new UnlimitedInt(UnlimitedInt::add(UnlimitedInt::mul(i1_num, i2_den), UnlimitedInt::mul(i2_num, i1_den))->to_string());
    UnlimitedInt *result_den = new UnlimitedInt(UnlimitedInt::mul(i1_den, i2_den)->to_string());
    UnlimitedInt *HC = hcf(result_num, result_den);

    UnlimitedInt *den = new UnlimitedInt( UnlimitedInt::div(result_den, HC)->to_string());
    UnlimitedInt *num = new UnlimitedInt (UnlimitedInt::div(result_num, HC)->to_string());

    delete result_num;
    delete result_den;

    delete HC;
    delete i1_num;
    delete i1_den;
    delete i2_num;
    delete i2_den;
    return new UnlimitedRational(num, den);
}

UnlimitedRational *UnlimitedRational ::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if ((i1->get_q_str()) == "0" || (i2->get_q_str()) == "0")
    {
        return new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
    }
    UnlimitedInt *i1_num = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt *i2_num = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt *i1_den = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt *i2_den = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt *result_num = UnlimitedInt::sub(UnlimitedInt::mul(i1_num, i2_den), UnlimitedInt::mul(i2_num, i1_den));
    UnlimitedInt *result_den = UnlimitedInt::mul(i1_den, i2_den);
    UnlimitedInt *HC = hcf(result_num, result_den);

    UnlimitedInt *den = UnlimitedInt::div(result_den, HC);
    UnlimitedInt *num = UnlimitedInt::div(result_num, HC);

    delete result_num;
    delete result_den;
    delete HC;
    delete i1_num;
    delete i1_den;
    delete i2_num;
    delete i2_den;

    return new UnlimitedRational(num, den);
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if ((i1->get_q_str()) == "0" || (i2->get_q_str()) == "0")
    {
        return new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
    }
    UnlimitedInt *i1_num = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt *i2_num = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt *i1_den = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt *i2_den = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt *result_num = UnlimitedInt::mul(i1_num, i2_num);
    UnlimitedInt *result_den = UnlimitedInt::mul(i1_den, i2_den);
    UnlimitedInt *HC = hcf(result_num, result_den);

    UnlimitedInt *den = UnlimitedInt::div(result_den, HC);
    UnlimitedInt *num = UnlimitedInt::div(result_num, HC);

    delete result_num;
    delete result_den;
    delete HC;
    delete i1_num;
    delete i1_den;
    delete i2_num;
    delete i2_den;

    return new UnlimitedRational(num, den);
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    if ((i1->get_q_str()) == "0" || (i2->get_q_str()) == "0")
    {
        return new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
    }
    UnlimitedInt *i1_num = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt *i2_num = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt *i1_den = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt *i2_den = new UnlimitedInt(i2->get_q_str());

    UnlimitedInt *result_num = UnlimitedInt::mul(i1_num, i2_den);
    UnlimitedInt *result_den = UnlimitedInt::mul(i1_den, i2_num);
    UnlimitedInt *HC = hcf(result_num, result_den);
    UnlimitedInt *den = UnlimitedInt::div(result_den, HC);
    UnlimitedInt *num = UnlimitedInt::div(result_num, HC);

    delete HC;
    delete i1_num;
    delete i1_den;
    delete i2_num;
    delete i2_den;
    delete result_num;
    delete result_den;

    return new UnlimitedRational(num, den);
}

// // change hcf

// int main(){
//     UnlimitedRational* a = new UnlimitedRational(new UnlimitedInt("5"), new UnlimitedInt("6"));
//     UnlimitedRational* b = new UnlimitedRational(new UnlimitedInt("2"), new UnlimitedInt("4"));
//     cout<<a->get_frac_str()<<endl;
//     cout<<b->get_frac_str()<<endl;
//     cout<<hcf(new UnlimitedInt("16"), new UnlimitedInt("12"))->to_string()<<endl;
//     cout<<UnlimitedRational::add(a,b)->get_frac_str()<<endl;
//     cout<<UnlimitedRational::sub(a,b)->get_frac_str()<<endl;
//     cout<<UnlimitedRational::mul(a,b)->get_frac_str()<<endl;
//     cout<<UnlimitedRational::div(a,b)->get_frac_str()<<endl;
// }