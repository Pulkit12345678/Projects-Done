/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
    this->left = NULL;
    this->right = NULL;
}

ExprTreeNode::ExprTreeNode(string t, int v)
{
    this->type = t;
    this->left = nullptr;
    this->right = nullptr;
    this->num = v;
}

ExprTreeNode::~ExprTreeNode()
{
    if (left != nullptr)
    {
        delete left;
    }
    if (right != nullptr)
    {
        delete right;
    }
}
