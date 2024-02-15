/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

// Write your code below this line

SymNode::SymNode(){
    this->height = 0;
    this->address = -1;
    this->key = "";
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
}

SymNode::SymNode(string k){
    this->key = k;
    this->par = NULL;
    this->left = NULL;
    this->right = NULL;
    this->address = -1;
    this->height = 1;
}

SymNode *SymNode::LeftLeftRotation()
{
    SymNode *temp = this->left;
    this->left = temp->right;
    if (temp->right != NULL)
    {
        temp->right->par = this;
    }
    temp->right = this;
    temp->par = this->par;
    this->par = temp;
    if (temp->par != NULL)
    {
        if (this->key < temp->par->key)
        {
            temp->par->left = temp;
        }
        else
        {
            temp->par->right = temp;
        }
    }

    int leftHeight;
    if (this->left != NULL)
    {
        leftHeight = this->left->height;
    }
    else
    {
        leftHeight = -1;
    }

    int rightHeight;
    if (this->right != NULL)
    {
        rightHeight = this->right->height;
    }
    else
    {
        rightHeight = -1;
    }

    this->height = 1 + max(leftHeight, rightHeight);

    int tempLeftHeight;
    if (temp->left != NULL)
    {
        tempLeftHeight = temp->left->height;
    }
    else
    {
        tempLeftHeight = -1;
    }

    int tempRightHeight;
    if (temp->right != NULL)
    {
        tempRightHeight = temp->right->height;
    }
    else
    {
        tempRightHeight = -1;
    }

    temp->height = 1 + max(tempLeftHeight, tempRightHeight);

    return temp;
}

SymNode *SymNode::RightRightRotation()
{
    SymNode *temp = this->right;
    this->right = temp->left;
    if (temp->left != NULL)
    {
        temp->left->par = this;
    }
    temp->left = this;
    temp->par = this->par;
    this->par = temp;
    if (temp->par != NULL)
    {
        if (this->key < temp->par->key)
        {
            temp->par->left = temp;
        }
        else
        {
            temp->par->right = temp;
        }
    }

    // Update height without ternary operators
    int leftHeight;
    if (this->left != NULL)
    {
        leftHeight = this->left->height;
    }
    else
    {
        leftHeight = -1;
    }

    int rightHeight;
    if (this->right != NULL)
    {
        rightHeight = this->right->height;
    }
    else
    {
        rightHeight = -1;
    }

    this->height = 1 + max(leftHeight, rightHeight);

    int tempLeftHeight;
    if (temp->left != NULL)
    {
        tempLeftHeight = temp->left->height;
    }
    else
    {
        tempLeftHeight = -1;
    }

    int tempRightHeight;
    if (temp->right != NULL)
    {
        tempRightHeight = temp->right->height;
    }
    else
    {
        tempRightHeight = -1;
    }

    temp->height = 1 + max(tempLeftHeight, tempRightHeight);

    return temp;
}

SymNode *SymNode::LeftRightRotation()
{
    this->left = this->left->RightRightRotation();
    return this->LeftLeftRotation();
}

SymNode *SymNode::RightLeftRotation()
{
    this->right = this->right->LeftLeftRotation();
    return this->RightRightRotation();
}

SymNode::~SymNode()
{
    delete this->left;
    delete this->right;
    this->left = NULL;
    this->right = NULL;
}