#include <iostream>
#include <vector>
#include <string>

using namespace std; 


// EACH SLOT HAS 2 COMPONENTS. STATUS, AND VALUE. 

// never used, tombstone, occupied
// table starts with 26 never used slots a-z. 
// length of key at most 10. Hash func uses last character. 


// Search: if key matches, then its been found. If never used, or tombstone, move onto next slot. 
//         Need to wrap around if its the last one. 

// Insertion: Check that key DOES NOT exist. If it exists, do nothing. 
//            Take last char as as key. If not used/tombstone, put key there. Try 
//            nxet slot if occupied. 

// Deletion: Search for it. Find key and change slot status to tombstone. 
// vector<string> getInput() {

// }

class hashTable {
    public:
        vector<string> hTable;
        // Initialise the hash table, with 26 "never used" entries
        hashTable() {
            for(int i = 0; i < 26; i++) {
                hTable.push_back("never used");
            }
        }

        // take a letter as input. Convert to an index. 
        int letterToIndex(string letter) {

        }

        void Search() {
            
        }
        void Insert() {
            return;
        }
        void Delete(string target) {
            if() {

            }
        }

        void printTable();
};

int main(void) {
    // Read input

    // Call functions based on input

    // Print the table. 
    return 0;
}