#include <iostream>
#include <string>
#include <limits>
#include <sstream>
using namespace std;

const int MAX_ITEMS = 100;

class Item {
public:
    string name;

    Item(const string &itemName) : name(itemName) {}
};

class InventoryItem : public Item {
public:
    int quantity;

    InventoryItem(const string &itemName = "", int itemQuantity = 0) : Item(itemName), quantity(itemQuantity) {}
};

class InventorySystem {
private:
    InventoryItem inventory[MAX_ITEMS];
    int itemCount = 0;
    stringstream memoryStream;

public:
    InventorySystem() : itemCount(0) {
        for (int i = 0; i < MAX_ITEMS; ++i) {
            inventory[i] = InventoryItem();
        }
    }

    void addItem(const string &itemName, int quantity);

    void removeItem(const string &itemName, int quantity);

    void displayInventory() ;
};

void InventorySystem::addItem(const string &itemName, int quantity) {
    if (itemCount < MAX_ITEMS) {
        for (int i = 0; i < itemCount; ++i) {
            if (inventory[i].name == itemName) {
                inventory[i].quantity += quantity;
                memoryStream << quantity << " " << itemName << "(s) added to the inventory." << endl << endl;
                return;
            }
        }

        inventory[itemCount++] = InventoryItem(itemName, quantity);
        memoryStream << quantity << " " << itemName << "(s) added to the inventory." << endl << endl;
        string result;
        while (getline(memoryStream, result)) {
                cout << result << std::endl;
            }
    } else {
        cout << "Inventory is full. Cannot add " << itemName << "." << endl;
    }
}

void InventorySystem::removeItem(const string &itemName, int quantity) {
    for (int i = 0; i < itemCount; ++i) {
        if (inventory[i].name == itemName) {
            if (inventory[i].quantity >= quantity) {
                inventory[i].quantity -= quantity;
                cout << quantity << " " << itemName << "(s) removed from the inventory." << endl;
            } else {
                cout << "Not enough " << itemName << " in the inventory." << endl;
            }
            return;
        }
    }

    // If the loop completes without finding the item
    cout << "Error: No such item '" << itemName << "' in the inventory." << endl;
}

void InventorySystem::displayInventory()  {
    
    if (itemCount == 0) {
        cout << "Inventory is empty." << endl;
    } else {
        cout << "Current Inventory:" << endl;
        for (int i = 0; i < itemCount; ++i) {
            cout << inventory[i].name << ": " << inventory[i].quantity << endl;
        }
    }

    // Display the contents of the stringstream
}

int main() {
    InventorySystem inventorySystem;
    int ch, quantity;
    string newItem;

    while (true) {
        try {
            cout << "Enter a choice: " << endl;
            cout << "1. Add item to inventory" << endl;
            cout << "2. Remove an item from inventory" << endl;
            cout << "3. Display inventory" << endl;
            cout << "4. EXIT!" << endl;

            while (!(cin >> ch)) {
                throw runtime_error("Invalid input. Please enter a number.");
            }

            switch (ch) {
                case 1:
                    cout << "Enter item to be added and its quantity: ";
                    cin >> newItem;

                    while (!(cin >> quantity)) {
                        throw runtime_error("Invalid input for quantity. Please enter a number.");
                    }

                    inventorySystem.addItem(newItem, quantity);
                    break;

                case 2:
                    cout << "Enter item to be removed and its quantity: ";
                    cin >> newItem;

                    while (!(cin >> quantity)) {
                        throw runtime_error("Invalid input for quantity. Please enter a number.");
                    }

                    inventorySystem.removeItem(newItem, quantity);
                    break;

                case 3:
                    inventorySystem.displayInventory();
                    break;
                    
            }
            if(ch > 4)
                cout << "invalid input entered !" << endl;
        } catch (exception &e) {
            cerr << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (ch == 4)
            break;
    }

    return 0;
}
