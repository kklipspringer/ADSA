#include <iostream> // for printing out traversed tree
#include <string>  // for user input
#include <sstream> // for reading and processing the user input
#include <algorithm> // for max() function. Used in my rotation functions

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
        Node* insert(Node* node, int key) {
            if (node == nullptr) {
                return new Node(key);
            }
            if (key < node->key) {
                node->left = insert(node->left, key);
            } else if (key > node->key) {
                node->right = insert(node->right, key);
            } else {
                return node;  // Cannot insert same key. 
            }

            node->height = 1 + (max(height(node->left), height(node->right)));

            int balance = balanceFactor(node);
            // left left
            if(balance > 1 && key < node->left->key) {
                return RR(node);
            }
            // right right
            if(balance < -1 && key > node->right->key) {
                return LR(node);
            }
            // left right
            if(balance > 1 && key > node->left->key) {
                node->left = LR(node->left);
                return RR(node);
            }
            // right left
            if(balance < -1 && key < node->right->key) {
                node->right = RR(node->right);
                return LR(node);
            }

            return node;
        }

        // Traverse and print out tree. Param tells it which method to use. 
        void traverse(Node* node, string method) {
            if(node == nullptr) {
                return;
            }
            // PREORDER TRAVERSAL
            if(method == "PER") {
                cout << node->key << " ";
                traverse(node->left, method);
                traverse(node->right, method);
            } 
            //INORDER TRAVERSAL
            if(method == "IN") {
                traverse(node->left, method);
                cout << node->key << " ";
                traverse(node->right, method);
            } 
            // POSTORDER TRAVERSAL
            if(method == "POST") {
                traverse(node->left, method);
                traverse(node->right, method);
                cout << node->key << " ";
            }
        }
        // Deletion
        Node* del(Node* node, int key) {
            if (node == nullptr) {
                return node;  // Cant find node with that key. Just returns 
            }

            // does bst deletion first, then gets balance factor, and balances it
            if(key < node->key) {
                node->left = del(node->left, key);
            } else if(key > node->key) {
                node->right = del(node->right, key);
            } else {
                // node with only one child or no child
                if((node->left == nullptr) || (node->right == nullptr)) {
                    Node* temp = node->left ? node->left : node->right;
                    if(temp == nullptr) { // has no child
                        temp = node;
                        node = nullptr;
                    } else { // only one child
                        *node = *temp; 
                    }
                    delete temp;
                } else {
                    Node* temp = node->right;
                    while (temp && temp->left != nullptr) {
                        temp = temp->left;
                    }
                    node->key = temp->key;
                    node->right = del(node->right, temp->key);
                }
            }

            // tree only has root
            if(node == nullptr) {
                return node;
            }

            node->height = 1 + (max(height(node->left), height(node->right)));
            int bf = balanceFactor(node);

            // left left
            if(bf > 1 && balanceFactor(node->left) >= 0) {
                return RR(node);
            }
            // left right
            if(bf > 1 && balanceFactor(node->left) < 0) {
                node->left = LR(node->left);
                return RR(node);
            }
            // right right
            if(bf < -1 && balanceFactor(node->right) <= 0) {
                return LR(node);
            }
            // right left
            if(bf < -1 && balanceFactor(node->right) > 0) {
                node->right = RR(node->right);
                return LR(node);
            }

            return node;
        }
};

int main(void) {
    // Create blank tree
    AVL tree;
    // Get input from user
    vector<string> inputLine = getInput();
    int instructLen = inputLine.size();

    // Read the returned input string. Call necessary functions. 
    // I'm making the assumption, that inputs will be valid. 
    for(int i = 0; i < instructLen; i++) {
        if(inputLine[i][0] == 'A') {
            int num = stoi(inputLine[i].substr(1));
            tree.root = tree.insert(tree.root, num);
        } else if(inputLine[i][0] == 'D') {
            int num = stoi(inputLine[i].substr(1));
            tree.root = tree.del(tree.root, num);
        } else { // if its not an A or D instruction, it must want traversal. Also specify the method.  
            tree.traverse(tree.root, (inputLine[i])); 
        }
    }

    return 0; 
}