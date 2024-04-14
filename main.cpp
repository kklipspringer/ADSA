#include <iostream>
#include <string>  // 
#include <sstream> // for reading and processing the user input
#include <algorithm> 


using namespace std;

string getInput() {
    string userInput; 
    getline(cin, userInput);
    return (userInput);
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

        // Print out trees
        void preOrder() {

        }

        void inOrder() {

        }

        void postOrder() {

        }

        // Deletion
};

int main(void) {
    // Create blank tree
    AVL tree;
    // Get input from user
    string input = getInput();
    istringstream iss(input);
    string split;
    while(iss >> split) {
        
    }  

}