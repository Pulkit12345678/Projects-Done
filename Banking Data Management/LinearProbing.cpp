#include "LinearProbing.h"
using namespace std;

vector<int> LinearProbing::BubbleSortDescendingorder(vector<int> &arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n - i - 1; ++j)
        {
            if (arr[j] < arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    return arr;
}

void LinearProbing::createAccount(std::string id, int count)
{
    Account a;
    a.id = id;
    a.balance = count;

    int idx = hash(id);
    bankStorage1d[idx] = a;
    v++;
}

std::vector<int> LinearProbing::getTopK(int k)
{
    vector<int> vs;
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].balance != -1)
        {
            vs.push_back(bankStorage1d[i].balance);
        }
    }

    BubbleSortDescendingorder(vs);

    vector<int> v;
    for (int i = 0; i < k && i < vs.size(); i++)
    {
        v.push_back(vs[i]);
    }

    return v;
}

int LinearProbing::getBalance(std::string id)
{
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].id == id)
        {
            return bankStorage1d[i].balance;
        }
    }
    return -1;
}

void LinearProbing::addTransaction(std::string id, int count)
{
    bool v = false;
    int z;
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].id == id)
        {
            z = i;
            v = true;
            break;
        }
    }
    if (v == true)
    {
        bankStorage1d[z].balance += count;
    }
    else
    {
        createAccount(id, count);
    }
}

bool LinearProbing::doesExist(std::string id)
{
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].id == id)
        {
            return true;
        }
    }
    return false;
}

bool LinearProbing::deleteAccount(std::string id)
{
    int z = -1;
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].id == id)
        {
            z = i;
        }
    }
    if (z != -1)
    {
        bankStorage1d.erase(bankStorage1d.begin() + z);
        v--;
        return true;
    }
    else
    {
        return false;
    }
}

int LinearProbing::databaseSize()
{
    return v;
}

int LinearProbing::hash(std::string id)
{
    unsigned long sum = 0;
    for (char c : id)
    {
        sum = ((sum * 63363) + c * 8521) * 8897;
    }
    int ip = sum % 83801;
    int index = ip;
    int orignalidx = index;
    while (bankStorage1d[index].balance != -1)
    {
        index = (index + 1) % 9973;
    }
    return index;
}

void LinearProbing::Printbank()
{
    for (int i = 0; i < bankStorage1d.size(); i++)
    {
        if (bankStorage1d[i].balance != -1)
        {
            cout << "Id: " << bankStorage1d[i].id << " :: Balance: " << bankStorage1d[i].balance <<" Position is: "<<i<< endl;
        }
    }
}