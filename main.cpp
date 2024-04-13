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
};

class AVL {
    public:
        // Balancing

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