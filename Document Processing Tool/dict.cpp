// Do NOT add any other includes
#include "dict.h"

char char_converter(int i){
    char c = 'a';
    for(int j = 0; j<26; j++){
        if(j==i){
            return c;
        }
        c++;
    }
    if(i==26){
        return '#';
    }
    else if(i==27){
        return '$';
    }
    else if(i==28){
        return '%';
    }
    else if(i==29){
        return '&';
    }
    else if(i==30){
        return '*';
    }
    else if(i==31){
        return '+';
    }
    else if(i==32){
        return '/';
    }
    else if(i==33){
        return '0';
    }
    else if(i==34){
        return '1';
    }
    else if(i==35){
        return '2';
    }
    else if(i==36){
        return '3';
    }
    else if(i==37){
        return '4';
    }
    else if(i==38){
        return '5';
    }
    else if(i==39){
        return '6';
    }
    else if(i==40){
        return '7';
    }
    else if(i==41){
        return '8';
    }
    else if(i==42){
        return '9';
    }
    else if(i==43){
        return '<';
    }
    else if(i==44){
        return '=';
    }
    else if(i==45){
        return '>';
    }   
    else if(i==46){
        return '\\';
    }
    else if(i==47){
        return '^';
    }
    else if(i==48){
        return '_';
    }
    else if(i==49){
        return '`';
    }
    else if(i==50){
        return '|';
    }
    else if(i==51){
        return '~';
    }
}

int ascii(char ch){
    int i = 0;
    for(char c = 'a'; c<='z'; c++){
        if(c==ch){
            return i;
        }
        i++;
    }
    if(ch=='#'){
        return 26;
    }
    else if(ch=='$'){
        return 27;
    }
    else if(ch=='%'){
        return 28;
    }
    else if(ch=='&'){
        return 29;
    }
    else if(ch=='*'){
        return 30;
    }
    else if(ch=='+'){
        return 31;
    }
    else if(ch=='/'){
        return 32;
    }
    else if(ch=='0'){
        return 33;
    }
    else if(ch=='1'){
        return 34;
    }
    else if(ch=='2'){
        return 35;
    }
    else if(ch=='3'){
        return 36;
    }
    else if(ch=='4'){
        return 37;
    }
    else if(ch=='5'){
        return 38;
    }
    else if(ch=='6'){
        return 39;
    }
    else if(ch=='7'){
        return 40;
    }
    else if(ch=='8'){
        return 41;
    }
    else if(ch=='9'){
        return 42;
    }
    else if(ch=='<'){
        return 43;
    }
    else if(ch=='='){
        return 44;
    }
    else if(ch=='>'){
        return 45;
    }
    else if(ch=='\\'){
        return 46;
    }
    else if(ch=='^'){
        return 47;
    }
    else if(ch=='_'){
        return 48;
    }
    else if(ch=='`'){
        return 49;
    }
    else if(ch=='|'){
        return 50;
    }
    else if(ch=='~'){
        return 51;
    }
}

string lower(string &word)
{
    string k = "";
    for (int i = 0; i < word.length(); i++)
    {
        k += tolower(word[i]);
    }
    return k;
}

class TrieNode
{
public:
    char data;
    TrieNode *children[52];
    bool isterminal;
    int word_count;
    TrieNode(char ch)
    {
        data = ch;
        for (int i = 0; i < 52; i++)
        {
            children[i] = NULL;
        }
        isterminal = false;
        word_count = 0;
    }
};

class Trie
{
public:
    TrieNode *root;
    Trie()
    {
        root = new TrieNode('\0');
    }
    void insertUtil(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            root->isterminal = true;
            root->word_count++;
        }
        else
        {
            int index = ascii(word[0]);
            TrieNode *child;
            if (root->children[index] != NULL)
            {
                child = root->children[index];
            }
            else
            {
                child = new TrieNode(word[0]);
                root->children[index] = child;
            }
            insertUtil(child, word.substr(1));
        }
    }

    void insertword(string word)
    {
        insertUtil(root, word);
    }

    bool searchUtil(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            return root->isterminal;
        }
        int index = ascii(word[0]);
        TrieNode *child;
        if (root->children[index] != NULL)
        {
            child = root->children[index];
        }
        else
        {
            return false;
        }
        return searchUtil(child, word.substr(1));
    }

    bool search(string word)
    {
        return searchUtil(root, word);
    }

    TrieNode *get_to_terminalUtil(TrieNode *root, string word)
    {
        if (word.length() == 0)
        {
            return root;
        }
        int index = ascii(word[0]);
        TrieNode *child;
        if (root->children[index] != NULL)
        {
            child = root->children[index];
            return get_to_terminalUtil(child, word.substr(1));
        }
        else
        {
            return root;
        }
    }
    TrieNode *get_to_terminal(string word)
    {
        return get_to_terminalUtil(root, word);
    }
};

Dict::Dict()
{
    // Implement your function here
    t = new Trie();
}

Dict::~Dict()
{
    // Implement your function here
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    sentence = lower(sentence);
    string k = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        if (sentence[i] == ' ')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '!')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '"')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '\'')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '(')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == ')')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == ',')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '-')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '.')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == ':')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == ';')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '?')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '@')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '[')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == ']')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '{')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else if (sentence[i] == '}')
        {
            if (k.length() != 0)
            {
                t->insertword(k);
            }
            k = "";
        }
        else
        {
            k = k + sentence[i];
        }
    }
    if (k.length() != 0)
    {
        t->insertword(k);
    }
    return;
}

int Dict::get_word_count(string word)
{
    // Implement your function here
    if (t->search(word) == false)
    {
        return 0;
    }
    else
    {
        return t->get_to_terminal(word)->word_count;
    }
}

void dumpTrieToFile(TrieNode *node, string currentWord, ofstream &outfile)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->isterminal)
    {
        outfile << currentWord << ", " << node->word_count << "\n";
    }

    for (int i = 0; i < 26; i++)
    {
        if (node->children[i] != nullptr)
        {
            char nextChar = 'a' + i;
            dumpTrieToFile(node->children[i], currentWord + nextChar, outfile);
        }
    }
}

void dump_helper(TrieNode* root, string p, string filename){
    ofstream dumper(filename, ios::app);
    if(root->isterminal==true){
        dumper<<p<<","<<root->word_count<<endl;
    }
    string p1 = p;
    for(int i = 0; i<52; i++){
        if(root->children[i]){
            p1+=char_converter(i);
            dump_helper(root->children[i], p1, filename);
        }
        p1 = p;
    }
}

void Dict::dump_dictionary(string filename)
{
    // Implement your function here

    ofstream dumper(filename, ios::app);
    dumper.clear();
    string p = "";
    dump_helper(t->root, p, filename);
    dumper.close();

    // Recursively traverse the Trie to dump words and their counts
    return;
}

