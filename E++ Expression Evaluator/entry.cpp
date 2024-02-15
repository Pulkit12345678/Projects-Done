/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "entry.h"

SymEntry::SymEntry()
{
    val = new UnlimitedRational();

    this->left = NULL;
    this->right = NULL;
}

SymEntry::SymEntry(string k, UnlimitedRational *v)
{
    this->key = k;
    this->val = v;

    this->left = NULL;
    this->right = NULL;
}

SymEntry::~SymEntry()
{
    if(left)
    {
        delete this->left;
    }
    if(right)
    {
        delete this->right;
    }
    delete val;
}