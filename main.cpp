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

        // Insertion

        // Traverse and print out tree. Param tells it which method to use. 
        void traverse() {  
            
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
            //tree.root = tree.insert(tree.root, num);
        } else if(inputLine[i][0] == 'D') {
            int num = stoi(inputLine[i].substr(1));
            //tree.root = tree.insert(tree.root, num);
        } else {

        }
    }
}