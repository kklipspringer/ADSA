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
vector<string> getInput() {
    // tokenise and get input
}

struct Entry {
    string key; // Single letter
    string status; // Never Used, Occupied, Tombstone
    Entry() {
        key = "";
        status = "Never Used";
    }
};

class hashTable {
    private:
        vector<Entry> hTable; // Vector of Entries. 
    public:        
        // Initialise the hash table, with 26 "never used" entries
        hashTable() {
            for(int i = 0; i < 26; i++) {
                hTable.push_back(Entry());
            }
        }

        // Take word in. Use last letter. Convert letter to hash table index. 
        int hash(string key) {
            char lastChar = key.back(); // access last char. 
            return (lastChar - 'a')  % 26; 
        }

        // Start at the hashed entry. Then keep looking, and eventually wrap around. Do this 26 times.
        bool Search(string key) {
            int potentialIndex = hash(key);
            int maxIterations = 26 - hash(key);

            for(int i = 0; i < 26; i++) {
                // To be found, it must be marked occupied, and the keys must match. 
                if((hTable[potentialIndex].key == key) && (hTable[potentialIndex].status == "Occupied")) {
                    return true; 
                } else {
                    potentialIndex = (potentialIndex + 1) % 26; // to wrap around properly. 
                }
            }

            // If it's looked through 26 entries, then it doesn't exist, or it's been deleted.
            // Therefore, return false.  
            return false; 
        }

        void Insert(string key) {
            // If it exists, return. 
            if(Search(key)) {
                return;
            }

            int targetIndex = hash(key); // position in hash table, where you intend to store the key.  
            // Similar wrap around technique, to Search() function. 
            for(int i = 0; i < 26; i++) {
                if((hTable[targetIndex].status == "Never Used") || (hTable[targetIndex].status == "Tombstone")) {
                    hTable[targetIndex].key = key; 
                    hTable[targetIndex].status = "Occupied";
                    return;
                } 
                // If it's occupied, increase the index. Eventually wrap around. 
                if(hTable[targetIndex].status == "Occupied") {
                    targetIndex = (targetIndex + 1) % 26;  
                } 
            }
        }

        void Delete(string target) {}

        void printTable() {}
};

void executeInstructions(vector<string> instructions) {
    
}

int main(void) {
    // Read input

    // Call functions based on input

    // Print the table. 
    return 0;
}