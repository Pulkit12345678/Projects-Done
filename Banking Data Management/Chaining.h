#ifndef CHAINING_H
#define CHAINING_H

#include "BaseClass.h"
#include <iostream>
#include <vector>

class Chaining : public BaseClass
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
    std::vector<int> BubbleSortDescendingorder(std::vector<int> &arr);
    Chaining()
    {
        bankStorage2d.resize(initailsize);
    }


private:
    const int initailsize = 100000;
};

#endif // CHAINING_H
