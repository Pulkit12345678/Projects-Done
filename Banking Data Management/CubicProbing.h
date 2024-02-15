#ifndef CUBICPROBING_H
#define CUBICPROBING_H

#include "BaseClass.h"
#include <iostream>

class CubicProbing : public BaseClass {
public:
    void createAccount(std::string id, int count) override;
    std::vector<int> getTopK(int k) override;
    int getBalance(std::string id) override;
    void addTransaction(std::string id, int count) override;
    bool doesExist(std::string id) override;
    bool deleteAccount(std::string id) override;
    int databaseSize() override;
    int hash(std::string id) override;
    CubicProbing()
    {
        bankStorage1d.resize(Table_Size);
        for (int i = 0; i < bankStorage1d.size(); i++)
        {
            bankStorage1d[i].balance = -1;
        }
    }
    std::vector<int> BubbleSortDescendingorder(std::vector<int> &arr);

private:
    const int Table_Size = 100000;
};

#endif // CUBICPROBING_H
