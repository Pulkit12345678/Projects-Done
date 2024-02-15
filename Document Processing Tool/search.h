// Do NOT add any other includes
#include <string>
#include <vector>
#include <iostream>
#include "Node.h"
using namespace std;

// class Nod
// {
// public:
//     int bookcode;
//     int pageno;
//     int paragraph;
//     int sentenceno;
//     string sentencefromtext;
//     Nod(int a, int b, int c, int d, string s)
//     {
//         bookcode = a;
//         pageno = b;
//         paragraph = c;
//         sentenceno = d;
//         sentencefromtext = s;
//     }
// };

class Linkedlistnode
{
public:
    Linkedlistnode *nxt;
    int bookcode;
    int pageno;
    int paragraph;
    int sentenceno;
    string sentencefromtext;
    Linkedlistnode *prev;


    Linkedlistnode(int a, int b, int c, int d, string s)
    {
        bookcode = a;
        pageno = b;
        paragraph = c;
        sentenceno = d;
        sentencefromtext = s;
        nxt=nullptr;
        prev=nullptr;
    }
    // Linkedlistnode(Linkedlistnode *cur)
    // {
    //     nxt = NULL;
    //     curr = cur;
    // }
};

class singlylinkedlist
{
private:
    Linkedlistnode *root;
    Linkedlistnode *currptr;
    int size;

public:
    singlylinkedlist()
    {
        root = NULL;
        size = 0;
        currptr = root;
    }
    ~singlylinkedlist()
    {
        while (root != NULL)
        {
            Linkedlistnode *temp = root;
            root = root->nxt;
            delete temp;
        }
    }
    void insert(Linkedlistnode *nd)
    {
        if (size == 0)
        {
            Linkedlistnode *temp = nd;
            root = temp;
            currptr = temp;
        }
        else
        {
            Linkedlistnode *temp = nd;
            currptr->nxt = temp;
            currptr = currptr->nxt;
        }
        size++;
    }
    Linkedlistnode *get_root()
    {
        return root;
    }
};

class SearchEngine
{
private:
    // You can add attributes/helper functions here
    singlylinkedlist *my_linked_list;

public:
    /* Please do not touch the attributes and
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    SearchEngine();

    ~SearchEngine();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    Node *search(string pattern, int &n_matches);

    /* -----------------------------------------*/
};