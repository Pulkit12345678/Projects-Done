#include"eppcompiler.h"

EPPCompiler::EPPCompiler() {
    output_file = "";
    memory_size = 0;
}

EPPCompiler::EPPCompiler(string out_file, int mem_limit)
    : output_file(out_file), memory_size(mem_limit)
{
    for (int i = memory_size - 1; i >= 0; i--)
    {
        mem_loc.push_back(i);
    }
}

void EPPCompiler::compile(const vector<vector<string>> code)
{
    for (const auto &line : code)
    {
        targ.parse(line);
        ExprTreeNode *exprTree = targ.expr_trees.back();

        if (exprTree->left->type == "VAR")
        {
            const string &varId = exprTree->left->id;
            if (targ.symtable->search(varId) == -2)
            {
                int mem = mem_loc.back();
                mem_loc.pop_back();
                targ.symtable->insert(varId);
                targ.symtable->assign_address(varId, mem);
            }
        }
        else if (exprTree->left->type == "DEL")
        {
            const string &varId = exprTree->right->id;
            int mem = targ.symtable->search(varId);
            mem_loc.push_back(mem);
            targ.last_deleted = mem;
            targ.symtable->remove(varId);
        }

        vector<string> commands = generate_targ_commands();
        write_to_file(commands);
    }
}


void command_maker(ExprTreeNode *node, SymbolTable *table, vector<string> &commands)
{
    if (node->type == "VAL")
    {
        string address = to_string(node->num);
        commands.push_back("PUSH " + address);
    }
    else if (node->type == "VAR")
    {
        const string &varId = node->id;
        int address = table->search(varId);
        commands.push_back("PUSH mem[" + to_string(address) + "]");
    }
    else
    {
        command_maker(node->right, table, commands);
        command_maker(node->left, table, commands);
        commands.push_back(node->type);
    }
}

vector<string> EPPCompiler::generate_targ_commands()
{
    vector<string> commands;
    ExprTreeNode *exprTree = targ.expr_trees.back();

    if (exprTree->left->type == "VAR")
    {
        command_maker(exprTree->right, targ.symtable, commands);
        const string &varId = exprTree->left->id;
        int address = targ.symtable->search(varId);
        commands.push_back("mem[" + to_string(address) + "] = POP");
    }
    else if (exprTree->left->type == "DEL")
    {
        int mem = targ.last_deleted;
        commands.push_back("DEL = mem[" + to_string(mem) + "]");
    }
    else if (exprTree->left->type == "RET")
    {
        command_maker(exprTree->right, targ.symtable, commands);
        commands.push_back("RET = POP");
    }

    return commands;
}

void EPPCompiler::write_to_file(vector<string> commands)
{
    ofstream file(output_file, std::ios::app);
    for (const string &command : commands)
    {
        file << command << endl;
    }
    file.close();
}

EPPCompiler::~EPPCompiler() {
    delete targ.symtable;
    targ.expr_trees.clear();
}
