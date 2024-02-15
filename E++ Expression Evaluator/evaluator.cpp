#include "evaluator.h"
#include<iostream>
using namespace std;

Evaluator::Evaluator()
{
    symtable = new SymbolTable();
}

Evaluator::~Evaluator()
{
    expr_trees.clear();
}

ExprTreeNode *maketree(vector<string> &tokens)
{
    if (tokens[0] == "(")
    {
        tokens.pop_back();
        tokens.erase(tokens.begin());
    }

    if (tokens.size() == 1)
    {
        string token = tokens[0];
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1])))
        {
            UnlimitedInt *nodetoinsert = new UnlimitedInt(token);
            ExprTreeNode *root = new ExprTreeNode("VAL", nodetoinsert);
            return root;
        }
        else
        {
            ExprTreeNode *root = new ExprTreeNode();
            root->type = "VAR";
            root->id = token;
            return root;
        }
    }

    else
    {
        vector<string> tokens_2;
        int index = 0;
        for (auto token:tokens)
        {
            if (token == "(")
            {
                tokens_2.push_back(token);
            }
            else if (token == ")")
            {
                tokens_2.pop_back();
            }
            else if (tokens_2.size() == 0)
            {
                if (token == "+" || token == "-" || token == "*" || token == "/")
                {
                    break;
                }
            }
            index++;
        }

        ExprTreeNode *newnode = new ExprTreeNode();
        vector<string> leftpart(tokens.begin(), tokens.begin() + index);
        vector<string> rightpart(tokens.begin() + index + 1, tokens.end());

        newnode->left = maketree(leftpart);
        newnode->right = maketree(rightpart);

        if (tokens[index] == "+")
        {
            newnode->type = "ADD";
        }
        if (tokens[index] == "-")
        {
            newnode->type = "SUB";
        }
        if (tokens[index] == "*")
        {
            newnode->type = "MUL";
        }
        if (tokens[index] == "/")
        {
            newnode->type = "DIV";
        }
        return newnode;
    }
    return nullptr;
}

void Evaluator::parse(vector<string> tokens)
{
    string variable = tokens[0];
    string equal = tokens[1];
    ExprTreeNode *root = new ExprTreeNode();
    ExprTreeNode *vari = new ExprTreeNode();

    vari->type = "VAR";
    vari->id = variable;

    root->left = vari;
    root->type = "Equal";
    root->id = equal;
    vector<string> tokens_2(tokens.begin() + 2, tokens.end());

    root->right = maketree(tokens_2);


    expr_trees.push_back(root);
}

UnlimitedRational *calculate(ExprTreeNode *root, SymbolTable *symtable)
{
    if (root->type == "VAL")
    {
        return root->val;
    }
    else if (root->type == "VAR")
    {
        UnlimitedRational *temp = symtable->search(root->id);
        root->evaluated_value = temp;
        return temp;
    }
    else if (root->type == "ADD")
    {
        UnlimitedRational *addi = UnlimitedRational::add(calculate(root->left, symtable), calculate(root->right, symtable));
        root->evaluated_value = addi;
        return addi;
    }
    else if (root->type == "SUB")
    {
        UnlimitedRational *addi = UnlimitedRational::sub(calculate(root->left, symtable), calculate(root->right, symtable));
        root->evaluated_value = addi;
        return addi;
    }
    else if (root->type == "MUL")
    {
        UnlimitedRational *addi = UnlimitedRational::mul(calculate(root->left, symtable), calculate(root->right, symtable));
        root->evaluated_value = addi;
        return addi;
    }
    else if (root->type == "DIV")
    {
        UnlimitedRational *addi = UnlimitedRational::div(calculate(root->left, symtable), calculate(root->right, symtable));
        root->evaluated_value = addi;
        return addi;
    }
    else
    {
        return nullptr;
    }
}

void Evaluator::eval()
{
    string variable = expr_trees.back()->left->id;

    ExprTreeNode* root = expr_trees.back()->right;

    UnlimitedRational* ans = calculate(root,symtable);
    symtable->insert(variable,ans);
}