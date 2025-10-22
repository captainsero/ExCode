#include<iostream>
#include<vector>
#include<string>
using namespace std;

bool validation(int number) {
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a number.\n";
        return false;
    } else if (number < 0) {
        cout << "Must be a positive number.\n";
        return false;
    } else {
        return true;
    }
}

class Inventory {
public:
    struct Item {
        int id = 0;
        string name;
        int quantity;
        float price;
    };

    vector<Item> items;

    void startItmes() {
        Item item1;
        Item item2;
        Item item3;
        Item item4;

        item1.name = "cola";
        item1.quantity = 20;
        item1.price = 3;
        items.push_back(item1);

        item2.name = "twist";
        item2.quantity = 5;
        item2.price = 10;
        items.push_back(item2);

        item3.name = "big cola";
        item3.quantity = 0;
        item3.price = 8;
        items.push_back(item3);

        item4.name = "burger";
        item4.quantity = 100;
        item4.price = 150;
        items.push_back(item4);

    }


    void addItem() {
        Item newItem;

        cout << "Enter Item Name: ";
        cin.ignore();
        getline(cin, newItem.name);

        while (true) {
            cout << "Enter Item Quantity(0 ot cancle): ";
            cin >> newItem.quantity;
            if (validation(newItem.quantity)) break;

            if (newItem.quantity == 0) {
                cout << "Cancelled.\n";
                return;
            }
        }

        while (true) {
            cout << "Enter Item Price: ";
            cin >> newItem.price;
            if (validation(newItem.price)) break;
        }

        newItem.id = items.size() + 1;
        items.push_back(newItem);
        cout << "Item Added Successfully\n";
    }

    void removeItem() {
        int number;
        while (true) {
            showItems();
            cout << "Enter the item ID to remove (0 to cancel): ";
            cin >> number;

            if (validation(number)) {
                bool found = false;
                for (int i = 0; i < items.size(); i++) {
                    if (items[i].id == number) {
                        items.erase(items.begin() + i);
                        cout << "Item removed successfully!\n";
                        return;
                    }
                }
                cout << "Item with ID " << number << " not found.\n";
            }

            if (number == 0) {
                cout << "Cancelled.\n";
                return;
            }

            
        }
    }

    void updateItme() {
        int number;
        while (true) {
            showItems();
            cout << "Enter the item ID to update (0 to cancel): ";
            cin >> number;

            if (validation(number)) {
                for (int i = 0; i < items.size(); i++) {
                    if (items[i].id == number) {
                        while (true) {
                            cout << "Enter Item Quantity: ";
                            cin >> items[i].quantity;
                            if (validation(items[i].quantity)) break;
                        }
                        while (true) {
                            cout << "Enter Item Price: ";
                            cin >> items[i].price;
                            if (validation(items[i].price)) break;

                        }
                        cout << "Item updated successfully.\n";
                        return;
                    }
                }
                cout << "Item with ID " << number << " not found.\n";
            }

            if (number == 0) {
                cout << "Cancelled.\n";
                return;
            }

            
        }
    }

    void showItems() {
        for (int i = 0; i < items.size(); i++) {
            items[i].id = i + 1;
        }
        cout << "====== Menu ======\n";
        for (auto &item : items) {
            cout << item.id << ". " << item.name;
            cout << " | Quantity: " << item.quantity;
            cout << " | Price: " << item.price << endl;
        }
        cout << "==================\n";
        itemNotification();
    }

    void itemNotification() {
        cout << "======= Low Stock =======\n";
        bool any = false;
        for (const Item& item : items) {
            if (item.quantity <= 5) {
                cout << "Item \"" << item.name << "\" is low on stock (Quantity: " << item.quantity << ")\n";
                any = true;
            }
        }
        if (!any) cout << "No low stock.\n";
        cout << "=========================\n";
    }

    void minusItemQuantity(string itemName, int quantity) {
        for (auto &item : items) {
            if (item.name == itemName) {
                item.quantity -= quantity;
                return;
            }
        }
        cout << "Error, no item found with name: " << itemName << endl;
    }

    void plusItemQuantity(string itemName, int quantity) {
        for (auto &item : items) {
            if (item.name == itemName) {
                item.quantity += quantity;
                return;
            }
        }
        cout << "Error, no item found with name: " << itemName << endl;
    }
};

class Table : public Inventory {
public:
    struct Order {
        int id;
        string itemName;
        int quantity;
    };

    struct TableInfo {
        int id;
        bool reserved;
        vector<Order> orders;
    };

    vector<TableInfo> tables;

    void startTables() {
        TableInfo t1{1, false, {}};
        TableInfo t2{2, false, {}};
        TableInfo t3{3, true, {}};
        tables.push_back(t1);
        tables.push_back(t2);
        tables.push_back(t3);
    }

    void AddTable() {
        TableInfo newTableInfo;
        newTableInfo.id = 0;
        newTableInfo.reserved = false;
        tables.push_back(newTableInfo);
        cout << "Table added successfully!\n";
        ShowTables();
    }

    void RemoveTable() {
        ShowTables();
        int tableId;
        cout << "Enter Table ID To Delete: ";
        cin >> tableId;
        if (cin.fail() || tableId <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid ID!\n";
            return;
        }
        for (int i = 0; i < tables.size(); i++) {
            if (tables[i].id == tableId) {
                tables.erase(tables.begin() + i); // Ask
                cout << "Table removed successfully!\n";
                return;
            }
        }
        cout << "Table not found!\n";
    }

    void ShowTables() {
        for (int i = 0; i < tables.size(); i++) {
            tables[i].id = i + 1;
        }
        cout << "===== Tables =====\n";
        for (auto &table : tables) {
            cout << "Table ID: " << table.id << " | ";
            cout << (table.reserved ? "Reserved\n" : "Free\n");
            showOrders(table);
            cout << "------------------\n";
        }
    }

    void addOrder() {
        int number;
        ShowTables();
        cout << "Enter table id (or 0 to cancel): ";
        cin >> number;
        if (!validation(number)) return;
        if (number == 0) return;

        for (auto &table : tables) {
            if (table.id == number) {
                while (true) {
                    if (items.empty()) {
                        cout << "No items in inventory.\n";
                        return;
                    }

                    showItems();
                    int id;
                    cout << "Enter item id to add (0 to finish): ";
                    cin >> id;

                    if (!validation(id)) {
                        // invalid input (non-number or negative)
                        continue;
                    }

                    if (id == 0) {
                        cout << "Finished adding orders.\n";
                        break;
                    }

                    

                    if (id < 1 || id > static_cast<int>(items.size())) { // Ask
                        cout << "Item id not found. Please choose a valid item id.\n";
                        continue;
                    }

                    Order ord;
                    cout << "Enter item quantity (0 to cancel this item): ";
                    cin >> ord.quantity;

                    if (!validation(ord.quantity)) {
                        // invalid quantity input
                        continue;
                    }

                    if (ord.quantity == 0) {
                        cout << "Cancelled this item.\n";
                        continue;
                    }

                    

                    if (ord.quantity > items[id - 1].quantity) {
                        cout << "Not enough stock. Available: " << items[id - 1].quantity << "\n";
                        continue;
                    }

                    ord.itemName = items[id - 1].name;
                    ord.id = 0;
                    table.orders.push_back(ord);
                    minusItemQuantity(ord.itemName, ord.quantity);
                    cout << "Order added successfully!\n";
                }
                return;
            }
        }

        cout << "Table not found.\n";
    }


    void deleteOrder() {
        int number;
        ShowTables();
        cout << "Enter table id (or 0 to cancel): ";
        cin >> number;
        if (!validation(number)) return;
        if (number == 0) return;
        for (auto &table : tables) {
            if (table.id == number) {
                showOrders(table);
                int id;
                cout << "Enter order number to delete: ";
                cin >> id;
                if (!validation(id) || id <= 0 || id > table.orders.size()) {
                    cout << "Invalid order number.\n";
                    return;
                }
                string itemName = table.orders[id - 1].itemName;
                int qty = table.orders[id - 1].quantity;
                table.orders.erase(table.orders.begin() + id - 1);
                plusItemQuantity(itemName, qty);
                cout << "Order deleted.\n";
                return;
            }
        }
        cout << "Table not found.\n";
    }

    void showOrders(TableInfo& table) {
        for (int i = 0; i < table.orders.size(); i++) {
            table.orders[i].id = i + 1;
        }
        if (table.orders.empty()) {
            cout << "No orders yet\n";
            return;
        }
        for (int i = 0; i < table.orders.size(); i++) {
            cout << i + 1 << ". " << table.orders[i].itemName;
            cout << " x(" << table.orders[i].quantity << ")\n";
        }
    }
};

class Bill{
public:
    struct BillPrice {
        int tableId;
        double total;
        string paymentMethod;
    };

    vector<BillPrice> bills;

    void calculateBill(Table& tab) {
        int tableId;
        cout << "Enter Table ID to calculate bill: ";
        cin >> tableId;
        if (cin.fail() || tableId <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid table ID\n";
            return;
        }

        for (auto &table : tab.tables) {
            if (table.id == tableId) {
                if (table.orders.empty()) {
                    cout << "No orders for this table.\n";
                    return;
                }

                double total = 0;
                for (auto &order : table.orders) {
                    for (auto &item : tab.items) {
                        if (item.name == order.itemName) {
                            total += item.price * order.quantity;
                        }
                    }
                }

                cout << "Bill for table " << tableId << ": " << total << "\n";

                // اختر طريقة الدفع
                int payChoice;
                string method;
                cout << "Choose Payment Method:\n";
                cout << "1. Cash\n";
                cout << "2. Credit Card\n";
                cout << "3. Mobile Wallet\n";
                cout << "Enter choice: ";
                cin >> payChoice;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input!\n";
                    return;
                }

                if (payChoice == 1) { // Cash
                    double payAmount;
                    while (true) {
                        cout << "Enter cash amount: ";
                        cin >> payAmount;

                        if (cin.fail() || payAmount <= 0) {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Invalid amount! Try again.\n";
                            continue;
                        }

                        if (payAmount < total) {
                            cout << "Low cash! You need at least " << total << "\n";
                        } else {
                            double change = payAmount - total;
                            if (change > 0) {
                                cout << "Payment successful! Change to return: " << change << "\n";
                            } else {
                                cout << "Payment successful! No change.\n";
                            }
                            method = "Cash";
                            break;
                        }
                    }
                } 
                else if (payChoice == 2) {
                    method = "Credit Card";
                    cout << "Payment successful using Credit Card.\n";
                } 
                else if (payChoice == 3) {
                    method = "Mobile Wallet";
                    cout << "Payment successful using Mobile Wallet.\n";
                } 
                else {
                    cout << "Invalid choice.\n";
                    return;
                }

                // احفظ الفاتورة
                bills.push_back({tableId, total, method});

                // مسح الطلبات بعد الدفع
                table.orders.clear();
                return;
            }
        }
        cout << "Table not found.\n";
    }



    void showBills() {
        cout << "===== Bills =====\n";
        if (bills.empty()) {
            cout << "No bills yet.\n";
            return;
        }
        for (auto &bill : bills) {
            cout << "Table " << bill.tableId 
                << " | Total: " << bill.total 
                << " | Payment: " << bill.paymentMethod << endl;
        }
    }
};

int main() {
    Table tab;
    Bill bil;
    tab.startItmes();
    tab.startTables();

    int choice;
    bool exit = false;

    while (!exit) {
        cout << "\n===== Main Dashboard =====\n";
        cout << "1. Admin Dashboard\n";
        cout << "2. Staff Dashboard\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (!validation(choice)) continue;

        switch (choice) {
        case 1: {
            // Admin Dashboard
            bool back = false;
            while (!back) {
                cout << "\n===== Admin Dashboard =====\n";
                cout << "1. Show Items\n";
                cout << "2. Add Item\n";
                cout << "3. Remove Item\n";
                cout << "4. Update Item\n";
                cout << "5. Show Tables\n";
                cout << "6. Add Table\n";
                cout << "7. Remove Table\n";
                cout << "0. Back\n";
                cout << "Enter choice: ";
                cin >> choice;

                if (!validation(choice)) continue;

                switch (choice) {
                case 1: tab.showItems(); break;
                case 2: tab.addItem(); break;
                case 3: tab.removeItem(); break;
                case 4: tab.updateItme(); break;
                case 5: tab.ShowTables(); break;
                case 6: tab.AddTable(); break;
                case 7: tab.RemoveTable(); break;
                case 0: back = true; break;
                default: cout << "Invalid choice.\n"; break;
                }
            }
            break;
        }
        case 2: {
            // Staff Dashboard
            bool back = false;
            while (!back) {
                cout << "\n===== Staff Dashboard =====\n";
                cout << "1. Add Order\n";
                cout << "2. Delete Order\n";
                cout << "3. Show Tables & Orders\n";
                cout << "4. Calculate Bill\n";
                cout << "5. Show Bills\n";
                cout << "0. Back\n";
                cout << "Enter choice: ";
                cin >> choice;

                if (!validation(choice)) continue;

                switch (choice) {
                case 1: tab.addOrder(); break;
                case 2: tab.deleteOrder(); break;
                case 3: tab.ShowTables(); break;
                case 4: bil.calculateBill(tab); break;
                case 5: bil.showBills(); break;
                case 0: back = true; break;
                default: cout << "Invalid choice.\n"; break;
                }
            }
            break;
        }
        case 0:
            cout << "Exit program.\n";
            exit = true;
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}
