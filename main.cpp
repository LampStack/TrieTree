#include <iostream>
#include <algorithm>
#include <fstream>
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
        void insert(string word);
        bool search(string word);
        string readFile(string path);
        void insert_to_file(string content, char chr);
        void toUpperCase(string& str);
        bool isEmpty();
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

void Trie::insert(string word) {
    struct node *temp = root;
    for (int i=0; i<word.length(); i++) {
        int index = word[i] - 'A'; // 'A' ascii code in 65, with this code we have 0 index for 'A' and 26 index for 'Z'
        if (!temp->pointer[index])
            temp->pointer[index] = makeNode();
        temp = temp->pointer[index];
    }
    temp->star= true;
}

bool Trie::search(string word) {
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

string Trie::readFile(string path){
    fstream myFile(path, ios::in );
    string content;
    getline(myFile, content, '\0');
    myFile.close();
    return content;
}

void Trie::insert_to_file(string path, char chr){
    string content = readFile(path);
    string temp = "";
    for (int i=0; i<(int)content.size(); i++){
        if (content[i] != chr){
            temp += content[i];
        }else{
            toUpperCase(temp);
            insert(temp);
            temp = "";
        }
    }
}

void Trie::toUpperCase(string& str){
    transform(str.begin(), str.end(), str.begin(), ::toupper);
}

bool Trie::isEmpty() {
    for (int i = 0; i < size; i++)
    if (root->pointer[i])
        return false;
    return true;
}

int main() {
    class Trie tree;
    int option;
    string word, path;
    system("cls");
    while (true) {
        cout << "Choose an option :\n";
        cout << "\t1- add a word\n";
        cout << "\t2- search a word\n";
        cout << "\t3- add words from a file\n";
        cout << "\t4- exit app\n";
        cout << "> ";
        cin >> option;
        system("cls");
        switch(option){
            case 1 :
                cout << "\n> Please Give Me A Word To Insert : ";
                cin >> word;
                tree.toUpperCase(word);
                if(tree.search(word)) {
                    system("cls");
                    cout << "\n***This word already exists in the tree***\n";
                } else {
                    tree.insert(word);
                    system("cls");
                    cout << "\n***The word was successfully added to the tree***\n";
                }
            break;
            case 2 :
                cout << "\n> Please Give Me A Word To Insert : ";
                cin >> word;
                tree.toUpperCase(word);
                if(tree.search(word)){
                    system("cls");
                    cout << "\n***The word was found in the tree***\n";
                }else{
                    system("cls");
                    cout << "\n***This word does not exist in the tree***\n";
                }
            break;
            case 3 :
                cout << "\n> Please enter the file name : ";
                cin >> path;
                tree.insert_to_file(path, ' ');
                system("cls");
                cout << "\n***All words in the file were added to the tree***\n";
            break;
            case 4 :
                exit(0);
            break;
            }
    }
   return 0;
}
