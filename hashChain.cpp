#include <iostream>
#include <string>
#include <vector>

#define HASH_GROUPS 100

using namespace std;

struct Entry{
    string fileName;
    int iNode;
    string fileType;
};

class HashTable{
    private:
        vector<Entry> table[HASH_GROUPS];

    public:
        int hashFunction(const string& fileName);
        void insertItem(Entry& newItem);
        void removeItem(const Entry& delItem);
        Entry searchItem(const string& itemName);
        void printTable();
};

int HashTable::hashFunction(const string& fileName){
    int hashValue = 0;
    for(const char& c : fileName){
        hashValue += static_cast<int>(c);
    }
    return hashValue % HASH_GROUPS;
}

void HashTable::insertItem(Entry& newItem){
    int hashValue = hashFunction(newItem.fileName);
    for(const Entry& item : table[hashValue]){
        if(item.fileName == newItem.fileName && item.fileType == newItem.fileType){
            return;
        }
    }
    table[hashValue].emplace_back(newItem);
}

void HashTable::removeItem(const Entry& delItem){
    int hashValue = hashFunction(delItem.fileName);
    vector<Entry>& hashGroup = table[hashValue];

    for (auto it = hashGroup.begin(); it != hashGroup.end(); ++it) {
        if (it->fileName == delItem.fileName && it->fileType == delItem.fileType) {
            hashGroup.erase(it);
            return;
        }
    }
}

Entry HashTable::searchItem(const string& itemName) {
    int hashValue = hashFunction(itemName);
    const vector<Entry>& hashGroup = table[hashValue];

    for (const Entry& item : hashGroup) {
        if (item.fileName == itemName) {
            return item;
        }
    }

    return {"", -1, ""};
}

void HashTable::printTable() {
    for (int i = 0; i < HASH_GROUPS; ++i) {
        const vector<Entry>& hashGroup = table[i];
        cout << "[" << i << "]: ";

        if (hashGroup.empty()) {
            cout << "---" << endl;
        } else {
            for (const Entry& item : hashGroup) {
                cout << "[" << item.fileName << ", " << item.iNode << ", " << item.fileType << "] --- ";
            }
            cout << endl;
        }
    }
}

int main(){
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