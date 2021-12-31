#include <iostream>
#include <algorithm>
using namespace std;

const unsigned int size = 26;
struct node {
    struct node* pointer[size];
    bool star;
};

class Trie {
	public:
        struct node *root = new (struct node);
		Trie();
		struct node* makeNode(void);
        void insert(struct node *,string word);
        bool search(struct node *,string word);
        bool isEmpty(struct node *);
};

Trie::Trie(){
    root = Trie::makeNode();
}
struct node* Trie::makeNode(void){
    struct node *newNode = new (struct node);
    newNode->star = false;
    for (int i=0; i<size; i++)
        newNode->pointer[i] = NULL;
    return newNode;
}

void Trie::insert(struct node *root, string word) {
    struct node *temp = root;
    for (int i=0; i<word.length(); i++) {
        int index = word[i] - 'A'; // 'A' ascii code in 65, with this code we have 0 index for 'A' and 26 index for 'Z'
        if (!temp->pointer[index])
            temp->pointer[index] = makeNode();
        temp = temp->pointer[index];
    }
    temp->star= true;
}

bool Trie::search(struct node *root, string word) {
    struct node *temp = root;
    for (int i=0; i<word.length(); i++) {
        int index = word[i] - 'A'; // 'A' ascii code in 65, with this code we have 0 index for 'A' and 26 index for 'Z'
        if (!temp->pointer[index])
            return false;
        temp = temp->pointer[index];
    }
    if(temp == NULL or !temp->star) return false;
    return true;
}

bool Trie::isEmpty(node* root) {
    for (int i = 0; i < size; i++)
    if (root->pointer[i])
        return false;
    return true;
}

void toUpperCase(string& str){
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}



int main() {
    class Trie tree;
    int option;
    string word;
    while (true) {
    cout << "\nWelcome To Trie Tree Program !\n";
    cout << "Choose an option :\n";
    cout << "\t1- insert words.\n";
    cout << "\t2- search words.\n";
    cout << "\t3- exit app.\n";
    cout << "> ";
    cin >> option;
    switch(option){
        case 1 :
            cout << "\nPlease Give Me A Word To Insert : ";
            cin >> word;
            toUpperCase(word);
            if(tree.search(tree.root, word)) {
                cout << "\nalready exists !\n";
            } else {
                tree.insert(tree.root, word);
                cout << "\nWord successfuly added.\n";
            }
        break;
        
        case 2 :
            cout << "\nPlease Give Me A Word To Insert : ";
            cin >> word;
            toUpperCase(word);
            if(tree.search(tree.root, word))
                cout << "\nYES\n";
            else
                cout << "\nNo\n";
        break;
        case 3 :
            exit(0);
        break;
    }
    }
   return 0;
}