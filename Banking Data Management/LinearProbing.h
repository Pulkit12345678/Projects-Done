#ifndef LINEARPROBING_H
#define LINEARPROBING_H

#include "BaseClass.h"
#include <iostream>

class LinearProbing : public BaseClass
{
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    void Printbank();
    LinearProbing()
    {
        v = 0;
        bankStorage1d.resize(Table_Size);
        for (int i = 0; i < bankStorage1d.size(); i++)
        {
            bankStorage1d[i].balance = -1;
        }
    }
    std::vector<int> BubbleSortDescendingorder(std::vector<int> &arr);
private:
    std::vector<std::pair<std::string,int>> vss;
    const int Table_Size = 100000;
    int v;
};

#endif // LINEARPROBING_H
