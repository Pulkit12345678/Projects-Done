#include"parser.h"

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
            int sto = stoi(token);
            return new ExprTreeNode("VAL", sto);
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
        for (const auto &token : tokens)
        {
            if (token == "(")
            {
                tokens_2.push_back(token);
            }
            else if (token == ")")
            {
                tokens_2.pop_back();
            }
            else if (tokens_2.empty() && (token == "+" || token == "-" || token == "*" || token == "/"))
            {
                break;
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
        else if (tokens[index] == "-")
        {
            newnode->type = "SUB";
        }
        else if (tokens[index] == "*")
        {
            newnode->type = "MUL";
        }
        else if (tokens[index] == "/")
        {
            newnode->type = "DIV";
        }
        return newnode;
    }

    return nullptr;
}

Parser::Parser() : symtable(new SymbolTable()) {}

void Parser::parse(const vector<string> tokens)
{
    string variable = tokens[0];
    string equal = tokens[1];
    ExprTreeNode *root = new ExprTreeNode();
    ExprTreeNode *vari = new ExprTreeNode();
    vector<string> tokens_2(tokens.begin() + 2, tokens.end());
    root->right = maketree(tokens_2);

    if (tokens[0] == "del")
    {
        vari->type = "DEL";
    }
    else if (tokens[0] == "ret")
    {
        vari->type = "RET";
    }
    else
    {
        vari->type = "VAR";
        vari->id = variable;
    }

    root->left = vari;
    root->type = "Equal";
    root->id = equal;

    expr_trees.push_back(root);
}

Parser::~Parser()
{
    expr_trees.clear();
    delete symtable;
}