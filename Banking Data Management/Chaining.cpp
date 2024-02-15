#include "Chaining.h"
using namespace std;

vector<int> Chaining::BubbleSortDescendingorder(vector<int> &arr)
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

void Chaining::createAccount(std::string id, int count)
{
    Account a;
    a.id = id;
    a.balance = count;

    int index = hash(id);
    bankStorage2d[index].push_back(a);
}

std::vector<int> Chaining::getTopK(int k)
{
    std::vector<int> vs;

    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            vs.push_back(bankStorage2d[i][j].balance);
        }
    }

    std::vector<int> v;
    for (int i = 0; i < k && i < vs.size(); i++)
    {
        v.push_back(vs[i]);
    }

    for (int i = k; i < vs.size(); i++)
    {
        int minValue = INT16_MAX;
        int minIndex = -1;
        for (int j = 0; j < k; j++)
        {
            if (v[j] < minValue)
            {
                minValue = v[j];
                minIndex = j;
            }
        }
        if (vs[i] > minValue && minIndex != -1)
        {
            v[minIndex] = vs[i];
        }
    }
    BubbleSortDescendingorder(v);
    return v;
}

int Chaining::getBalance(std::string id)
{
    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            if (bankStorage2d[i][j].id == id)
            {
                return bankStorage2d[i][j].balance;
            }
        }
    }
    return -1;
}

void Chaining::addTransaction(std::string id, int count)
{
    bool v = false;
    int z = -1;
    int k = -1;
    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            if (bankStorage2d[i][j].id == id)
            {
                z = i;
                k = j;
                v = true;
                break;
            }
            if(v)
            {
                break;
            }
        }
    }
    if (v == true)
    {
        bankStorage2d[z][k].balance += count;
    }
    else
    {
        createAccount(id, count);
    }
}

bool Chaining::doesExist(std::string id)
{
    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            if (bankStorage2d[i][j].id == id)
            {
                return true;
            }
        }
    }
    return false;
}

bool Chaining::deleteAccount(std::string id)
{
    bool v = false;
    int z = -1;
    int k = -1;
    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        for (int j = 0; j < bankStorage2d[i].size(); j++)
        {
            if (bankStorage2d[i][j].id == id)
            {
                z = i;
                k = j;
                v = true;
                break;
            }
        }
        if(v)
        {
            break;
        }
    }
    if (z != -1 && k != -1)
    {
        bankStorage2d[z].erase(bankStorage2d[z].begin() + k);
        return true;
    }
    else
    {
        return false;
    }
}

int Chaining::databaseSize()
{
    int cnt = 0;
    for (int i = 0; i < bankStorage2d.size(); i++)
    {
        cnt = cnt + bankStorage2d[i].size();
    }
    return cnt;
}

int Chaining::hash(std::string id)
{
    unsigned long sum = 0;
    for (char c : id)
    {
        sum = ((sum * 63363) + c * 8521) * 8897;
    }
    int ip = sum % 83801;
    return ip;
}