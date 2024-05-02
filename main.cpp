#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std; 


// Get and tokenise input. 
// Please note, that this function was reused from my A2 code.
vector<string> getInput() {
    string in;
    getline(cin, in); 
    vector<string> tokens;
    string token;
    istringstream tokenStream(in);

    while(tokenStream >> token) {
        tokens.push_back(token); 
    }

    return (tokens);
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
        int Search(string key) {
            int targetIndex = hash(key);
            //int maxIterations = 26 - hash(key);

            for(int i = 0; i < 26; i++) {
                // To be found, it must be marked occupied, and the keys must match. 
                if((hTable[targetIndex].key == key) && (hTable[targetIndex].status == "Occupied")) {
                    return targetIndex; 
                } else {
                    targetIndex = (targetIndex + 1) % 26; // to wrap around properly. 
                }
            }

            // If it's looked through 26 entries, then it doesn't exist, or it's been deleted.
            // Therefore, return false.  
            return -1; 
        }

        void Insert(string key) {
            // If it exists, return. 
            if(Search(key) != -1) {
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

        void Delete(string key) {
            int targetIndex = Search(key);
            // If it does exist. 
            if(targetIndex != -1) {
                hTable[targetIndex].status = "Tombstone";
            }   

            return;
        }

        void printTable() {
            bool firstPrinted = false;

            for(int i = 0; i < 26; i++) {
                // Entry must exist. 
                if(hTable[i].status == "Occupied") {
                    if(firstPrinted) {
                        cout << " ";
                    }
                    cout << hTable[i].key;
                    firstPrinted = true;
                }
            }
        }
};

void execute(vector<string> instructions) {
    // Create Hash Table.
    hashTable ht;

    for (size_t i = 0; i < instructions.size(); i++) {
        char action = instructions[i][0];
        string key = instructions[i].substr(1);

        if (action == 'A') {
            ht.Insert(key);
        } else if (action == 'D') {
            ht.Delete(key);
        }
    }

    // Finally, print table. 
    ht.printTable();
    return;
}

int main(void) {
    // Execute instructions that are received, from getInput. 
    execute(getInput()); 

    return 0;
}