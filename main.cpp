#include <iostream>
#include <string>  // 
#include <sstream> // for reading and processing the user input
#include <algorithm> 


using namespace std;

vector<string> getInput() {
    string in;
    getline(cin, in); 
    vector<string> tokens;
    string token;
    istringstream tokenStream(in);

    // Add every word (A3, I3, to vector), and return it
    while(tokenStream >> token) {
        tokens.push_back(token); 
    }

    return (tokens);
}

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int keyIn) {
        key = keyIn;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVL {
    public:
        Node* root = nullptr;
        // Balancing
        int height(Node* node) { // get height 
            if(!node) {
                return 0;
            }

            return (node->height);
        }

        int balanceFactor(Node* node) { // calculate balance factor. b(v) = h(Tl) - h(Tr)    (left - right)
            if(!node) {
                return 0;
            }

            return (height(node->left) - height(node->right)); 
        }

        Node* RR(Node* y) { // right rotate
            Node* x = y->left;
            Node* T2 = x->right;
            x->right = y;
            y->left = T2;
            y->height = (max(height(y->left), height(y->right))) + 1;
            x->height = (max(height(x->left), height(x->right))) + 1;
            return x;
        }

        Node* LR(Node* x) { // left rotate
            Node* y = x->right;
            Node* T2 = y->left;
            y->left = x;
            x->right = T2;
            x->height = (max(height(x->left), height(x->right))) + 1;
            y->height = (max(height(y->left), height(y->right))) + 1;
            return y;
        }

        // Insertion
        Node* insert(Node* node, int key) {}
        
        // Traverse and print out tree. Param tells it which method to use. 
        void traverse(Node* node, string method) {  
            if(method == "POSTORDER") {
                
            }

            if(method == "PREORDER") {

            } 

            if(method == "INORDER") {

            }
        }

        // Deletion
};

int main(void) {
    // Create blank tree
    AVL tree;
    // Get input from user
    vector<string> inputLine = getInput();
    size_t instructLen = inputLine.size();

    // Read the returned input string. Call necessary functions
    for(int i = 0; i < instructLen; i++) {
        if(inputLine[i][0] == 'A') {
            int num = stoi(inputLine[i].substr(1));
            tree.root = tree.insert(tree.root, num);
        } else if(inputLine[i][0] == 'D') {
            int num = stoi(inputLine[i].substr(1));
            tree.root = tree.insert(tree.root, num);
        } else {

        }
    }
}