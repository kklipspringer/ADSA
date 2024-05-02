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
            if(key.empty()) {
                return (-1);
            }

            char lastChar = key.back(); // access last char. 
            return (lastChar - 'a')  % 26; 
        }

        bool Search(string key) {
            int potentialIndex = hash(key);
            //.... go to index. is it there? no? increase index. Is it there? no? increase index.
            // If you've reached the end, return. 
        }

        void Insert() {}

        void Delete(string target) {}

        void printTable() {}
};

int main(void) {
    // Read input

    // Call functions based on input

    // Print the table. 
    return 0;
}