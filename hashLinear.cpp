#include <iostream>
#include <string>

#define HASH_GROUPS 100

using namespace std;

struct Entry {
    string fileName;
    int iNode;
    string fileType;
};

class HashTable {
    private:
        Entry table[HASH_GROUPS];
        bool occupied[HASH_GROUPS] = {false};

    public:
        int hashFunction(const string& fileName);
        void insertItem(const Entry& newItem);
        void removeItem(const Entry& delItem);
        Entry searchItem(const string& itemName);
        void printTable();
};

int HashTable::hashFunction(const string& fileName) {
    int hashValue = 0;
    for (const char& c : fileName) {
        hashValue += static_cast<int>(c);
    }
    return hashValue % HASH_GROUPS;
}

void HashTable::insertItem(const Entry& newItem) {
    int hashValue = hashFunction(newItem.fileName);
    int originalHashValue = hashValue;
    
    while (occupied[hashValue] && !(table[hashValue].fileName == newItem.fileName && table[hashValue].fileType == newItem.fileType)) {
        hashValue = (hashValue + 1) % HASH_GROUPS;
        if (hashValue == originalHashValue) {
            cout << "HashTable is full, cannot insert item." << endl;
            return;
        }
    }

    table[hashValue] = newItem;
    occupied[hashValue] = true;
}

void HashTable::removeItem(const Entry& delItem) {
    int hashValue = hashFunction(delItem.fileName);
    int originalHashValue = hashValue;

    while (occupied[hashValue]) {
        if (table[hashValue].fileName == delItem.fileName && table[hashValue].fileType == delItem.fileType) {
            occupied[hashValue] = false;
            return;
        }
        hashValue = (hashValue + 1) % HASH_GROUPS;
        if (hashValue == originalHashValue) {
            cout << "Item not found in the hash table." << endl;
            return;
        }
    }

    cout << "Item not found in the hash table." << endl;
}

Entry HashTable::searchItem(const string& itemName) {
    int hashValue = hashFunction(itemName);
    int originalHashValue = hashValue;

    while (occupied[hashValue]) {
        if (table[hashValue].fileName == itemName) {
            return table[hashValue];
        }
        hashValue = (hashValue + 1) % HASH_GROUPS;
        if (hashValue == originalHashValue) {
            return {"", -1, ""};
        }
    }

    return {"", -1, ""};
}

void HashTable::printTable() {
    for (int i = 0; i < HASH_GROUPS; ++i) {
        if (occupied[i]) {
            cout << "[" << i << "]: " << "[" << table[i].fileName << ", " << table[i].iNode << ", " << table[i].fileType << "] --- " << endl;
        } else {
            cout << "[" << i << "]: ---" << endl;
        }
    }
}

int main() {
    HashTable hashTable;

    while (true) {
        cout << "Menu:" << endl;
        cout << "1. Insert item" << endl;
        cout << "2. Remove item" << endl;
        cout << "3. Search item" << endl;
        cout << "4. Print table" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string fileName, fileType;
                int iNode;
                cout << "Enter file name: ";
                cin >> fileName;
                cout << "Enter iNode: ";
                cin >> iNode;
                cout << "Enter file type: ";
                cin >> fileType;

                Entry newItem = {fileName, iNode, fileType};
                hashTable.insertItem(newItem);
                cout << "Item inserted successfully." << endl;
                break;
            }
            case 2: {
                string fileName, fileType;
                cout << "Enter file name: ";
                cin >> fileName;
                cout << "Enter file type: ";
                cin >> fileType;

                Entry delItem = {fileName, -1, fileType};
                hashTable.removeItem(delItem);
                cout << "Item removed successfully." << endl;
                break;
            }
            case 3: {
                string itemName;
                cout << "Enter file name to search: ";
                cin >> itemName;

                Entry foundItem = hashTable.searchItem(itemName);
                if (foundItem.fileName != "") {
                    cout << "Item found: " << foundItem.fileName << ", " << foundItem.iNode << ", " << foundItem.fileType << endl;
                } else {
                    cout << "Item not found." << endl;
                }
                break;
            }
            case 4: {
                hashTable.printTable();
                break;
            }
            case 5: {
                cout << "Exiting program." << endl;
                return 0;
            }
            default: {
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
            }
        }
    }
}