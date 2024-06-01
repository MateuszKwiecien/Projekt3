#include <iostream>
#include <string>

#define HASH_GROUPS 100

using namespace std;

constexpr bool isPrime(int num) {
    if (num <= 1) return false;
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) return false;
    }
    return true;
}

constexpr int largestPrimeLessThan(int num) {
    for (int i = num - 1; i > 1; --i) {
        if (isPrime(i)) return i;
    }
    return 2; // Fallback to the smallest prime number
}

constexpr int R = largestPrimeLessThan(HASH_GROUPS);

struct Entry {
    string fileName;
    int iNode;
    string fileType;
};

class HashTable {
    private:
        Entry table[HASH_GROUPS];
        bool occupied[HASH_GROUPS] = {false}; // To track occupied slots

    public:
        int hashFunction1(const string& fileName);
        int hashFunction2(const string& fileName);
        void insertItem(const Entry& newItem);
        void removeItem(const Entry& delItem);
        Entry searchItem(const string& itemName);
        void printTable();
};

int HashTable::hashFunction1(const string& fileName) {
    int hashValue = 0;
    for (const char& c : fileName) {
        hashValue += static_cast<int>(c);
    }
    return hashValue % HASH_GROUPS;
}

int HashTable::hashFunction2(const string& fileName) {
    int hashValue = 0;
    for (const char& c : fileName) {
        hashValue += static_cast<int>(c);
    }
    return R - (hashValue % R);
}

void HashTable::insertItem(const Entry& newItem) {
    int hashValue1 = hashFunction1(newItem.fileName);
    int hashValue2 = hashFunction2(newItem.fileName);
    int i = 0;

    while (occupied[(hashValue1 + i * hashValue2) % HASH_GROUPS] && !(table[(hashValue1 + i * hashValue2) % HASH_GROUPS].fileName == newItem.fileName && table[(hashValue1 + i * hashValue2) % HASH_GROUPS].fileType == newItem.fileType)) {
        i++;
        if (i == HASH_GROUPS) {
            cout << "HashTable is full, cannot insert item." << endl;
            return;
        }
    }

    int index = (hashValue1 + i * hashValue2) % HASH_GROUPS;
    table[index] = newItem;
    occupied[index] = true;
}

void HashTable::removeItem(const Entry& delItem) {
    int hashValue1 = hashFunction1(delItem.fileName);
    int hashValue2 = hashFunction2(delItem.fileName);
    int i = 0;

    while (occupied[(hashValue1 + i * hashValue2) % HASH_GROUPS]) {
        int index = (hashValue1 + i * hashValue2) % HASH_GROUPS;
        if (table[index].fileName == delItem.fileName && table[index].fileType == delItem.fileType) {
            occupied[index] = false;
            return;
        }
        i++;
        if (i == HASH_GROUPS) {
            cout << "Item not found in the hash table." << endl;
            return;
        }
    }

    cout << "Item not found in the hash table." << endl;
}

Entry HashTable::searchItem(const string& itemName) {
    int hashValue1 = hashFunction1(itemName);
    int hashValue2 = hashFunction2(itemName);
    int i = 0;

    while (occupied[(hashValue1 + i * hashValue2) % HASH_GROUPS]) {
        int index = (hashValue1 + i * hashValue2) % HASH_GROUPS;
        if (table[index].fileName == itemName) {
            return table[index];
        }
        i++;
        if (i == HASH_GROUPS) {
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
