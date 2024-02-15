// Do NOT add any other includes
#include "search.h"

string lower_(string &word)
{
    string k = "";
    for (int i = 0; i < word.length(); i++)
    {
        k += tolower(word[i]);
    }
    return k;
}

void computearray(string pattern, int m, int* lps){
    int j = 0;
    lps[0] = 0;
    int i = 1;
    while(i<m){
        if(pattern[i]==pattern[j]){
            j = j + 1;
            lps[i] = j;
            i++;
        }
        else{
            if(j!=0){
                j = lps[j-1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

vector<int> kmpsearchalgo(string pattern, string sentence){
    vector<int> to_be_returned;
    int lps[pattern.length()];
    computearray(pattern, pattern.length(), lps);
    int sentence_index = 0;
    int pattern_index = 0;
    while((sentence.length()-sentence_index)>=(pattern.length()-pattern_index)){
        if(pattern[pattern_index] == sentence[sentence_index]){
            pattern_index = pattern_index + 1;
            sentence_index = sentence_index + 1;
        }
        if(pattern_index==pattern.length()){
            to_be_returned.push_back(sentence_index-pattern_index);
            pattern_index = lps[pattern_index-1];
        }
        else if(sentence_index<sentence.length() && pattern[pattern_index]!=sentence[sentence_index]){
            if(pattern_index!=0){
                pattern_index = lps[pattern_index-1];
            }
            else{
                sentence_index = sentence_index + 1;
            }
        }
    } 
    return to_be_returned;
}

SearchEngine::SearchEngine()
{
    // Implement your function here
    my_linked_list = new singlylinkedlist();
}

SearchEngine::~SearchEngine()
{
    // Implement your function here
    delete my_linked_list;
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence)
{
    // Implement your function here
    sentence = lower_(sentence);
    Linkedlistnode* nd = new Linkedlistnode(book_code, page, paragraph, sentence_no, sentence);
    my_linked_list->insert(nd);
    return;
}

Node *SearchEngine::search(string pattern, int &n_matches)
{
    // Implement your function here
    // n_matches = 0;
    int cnt = 0;
    Node* root=nullptr;
    pattern = lower_(pattern);
    // root->right = NULL;
    Node* dummy = nullptr;
    Linkedlistnode* temp = my_linked_list->get_root();
    vector<int> vec;
    while(temp!=nullptr){
        vec.clear();
        vec = kmpsearchalgo(pattern, temp->sentencefromtext);
        for(int i = 0; i<vec.size(); i++){
            Node* newnode = new Node(temp->bookcode, temp->pageno, temp->paragraph, temp->sentenceno, vec[i]);
            if(root==nullptr){
                root = newnode;
                dummy = root;
                // n_matches++;
            }
            else{
                dummy->right = newnode;
                newnode->left = dummy;
                dummy = newnode;
                // n_matches++;
            }
        }
        cnt = cnt + vec.size();
        temp=temp->nxt;
    }
    n_matches = cnt;
    return root;
}




// int main(){
//     SearchEngine s;
//     s.insert_sentence(1,1,1,1,"I am the them the ravi");
//     s.insert_sentence(3,3,3,3,"I the hen them ravi");
//     string r="the";
//     int num=0;
//     s.search(r,num);
//     cout<<num<<endl;
//     return 0;
// }