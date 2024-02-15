#include "symtable.h"

using namespace std;

bool search1(SymEntry *&root, string k)
{
    if (root == nullptr)
    {
        return false;
    }
    else if (root->key == k)
    {
        return true;
    }
    else if (root->key > k)
    {
        return search1(root->left, k);
    }
    else
    {
        return search1(root->right, k);
    }
}

SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}

SymbolTable::~SymbolTable()
{
    if (root)
    {
        delete root;
    }
}

void insertRec(SymEntry *&root, string k, UnlimitedRational *v)
{
    if (root == NULL)
    {
        root = new SymEntry(k, v);
    }

    if (root->key > k)
    {
        insertRec(root->left, k, v);
    }
    else if (root->key < k)
    {
        insertRec(root->right, k, v);
    }
}

void SymbolTable::insert(string k, UnlimitedRational *v)
{
    insertRec(root, k, v);
    size++;
}

SymEntry *findSuccessor(SymEntry *&root)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    else if (root->right == nullptr)
    {
        return nullptr;
    }
    SymEntry *curr = root->right;
    while (curr != nullptr && curr->left != nullptr)
    {
        curr = curr->left;
    }
    return curr;
}

SymEntry *removeRec(SymEntry *&root, string k)
{
    if (root == nullptr)
    {
        return root;
    }

    if (k < root->key)
    {
        root->left = removeRec(root->left, k);
    }
    else if (k > root->key)
    {
        root->right = removeRec(root->right, k);
    }
    else
    {
        if (root->left == nullptr)
        {
            SymEntry *temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr)
        {
            SymEntry *temp = root->left;
            delete root;
            return temp;
        }

        SymEntry *temp = findSuccessor(root);
        root->key = temp->key;
        root->val = temp->val;
        root->right = removeRec(root->right, temp->key);
    }
    return root;
}

void SymbolTable::remove(string k)
{
    if (search1(root, k))
    {
        root = removeRec(root, k);
        size--;
    }
}

SymEntry *searchRec(SymEntry *root, string k)
{
    if (root == nullptr)
    {
        return nullptr;
    }

    if (root->key == k)
    {
        return root;
    }
    else if (root->key > k)
    {
        return searchRec(root->left, k);
    }
    else
    {
        return searchRec(root->right, k);
    }
}

UnlimitedRational *SymbolTable::search(string k)
{
    SymEntry *entry = searchRec(root, k);
    if (entry != nullptr)
    {
        return entry->val;
    }
    return nullptr;
}

int SymbolTable::get_size()
{
    return size;
}

SymEntry *SymbolTable::get_root()
{
    return root;
}
