#include <iostream>
#include <map>
#include <set>
#include <string>
#include <iomanip>
using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
};

int main() {
    map<int, Product> inventory;
    set<int> lowStock;

    inventory[101] = {"Keyboard", 1200, 10};
    inventory[102] = {"Mouse", 500, 5};
    inventory[103] = {"Monitor", 8500, 3};

    int choice;

    do {
        cout << "\n===== INVENTORY SYSTEM =====\n";
        cout << "1. Display Inventory\n";
        cout << "2. Add Stock\n";
        cout << "3. Sell Product\n";
        cout << "4. Search Product\n";
        cout << "5. Display Low Stock\n";
        cout << "6. Calculate Inventory Value\n";
        cout << "7. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) {
            for (const auto &entry : inventory) {
                const Product &p = entry.second;

                cout << entry.first << " | " << p.name
                     << " | Price: Rs." << p.price
                     << " | Quantity: " << p.quantity << endl;
            }
        }
        else if (choice == 2 || choice == 3) {
            int id, qty;
            cout << "Enter product ID: ";
            cin >> id;
            cout << "Enter quantity: ";
            cin >> qty;

            auto it = inventory.find(id);

            if (it == inventory.end() || qty <= 0) {
                cout << "Invalid product or quantity.\n";
            }
            else if (choice == 2) {
                it->second.quantity += qty;
                cout << "Stock updated successfully.\n";
            }
            else if (it->second.quantity >= qty) {
                it->second.quantity -= qty;
                cout << "Sale completed. Amount: Rs."
                     << it->second.price * qty << endl;
            }
            else {
                cout << "Insufficient stock.\n";
            }
        }
        else if (choice == 4) {
            int id;
            cout << "Enter product ID: ";
            cin >> id;

            auto it = inventory.find(id);

            if (it != inventory.end()) {
                cout << "Name: " << it->second.name << endl;
                cout << "Price: Rs." << it->second.price << endl;
                cout << "Stock: " << it->second.quantity << endl;
            } else {
                cout << "Product not found.\n";
            }
        }
        else if (choice == 5) {
            lowStock.clear();

            for (const auto &entry : inventory) {
                if (entry.second.quantity <= 5)
                    lowStock.insert(entry.first);
            }

            cout << "Products with stock <= 5:\n";

            for (int id : lowStock)
                cout << id << " - " << inventory[id].name
                     << " (" << inventory[id].quantity << ")\n";
        }
        else if (choice == 6) {
            double total = 0;

            for (const auto &entry : inventory) {
                total += entry.second.price *
                         entry.second.quantity;
            }

            cout << fixed << setprecision(2);
            cout << "Total inventory value: Rs."
                 << total << endl;
        }

    } while (choice != 7);

    return 0;
}
