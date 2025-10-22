#include<iostream>
#include<vector>
#include<string>

using namespace std;

bool validation(int number){
    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input! Please enter a number.\n";
        return false;
    }
    else if (number < 0) {
        cout << "ID must be a positive number.\n";
        return false;
    }else{
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

    void startItmes(){
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

        // item4.name = "burger";
        // item4.quantity = 100;
        // item4.price = 150;
        // items.push_back(item4);

    }

    void addItem(){
        Item newItem;
        
        cout << "Enter Item Name: ";
        cin >> newItem.name;

        while (true) {
        cout << "Enter Item Quantity: ";
        cin >> newItem.quantity;
        if (newItem.quantity == 0)
        {
            cout << "Cancled.\n";
            return;
        }
        if (validation(newItem.quantity)) { 
            break;
        } 
    }

    while (true) {
        cout << "Enter Item Price: ";
        cin >> newItem.price;
        if (cin.fail() || newItem.price < 0 || newItem.quantity == 0) {
            cout << "Invalid input! Price must be a positive number.\n";
            cin.clear();
            cin.ignore(1000, '\n');
        } else {
            break;
        }
    }


        newItem.id = 0;
        items.push_back(newItem);
        cout << "Item Added Successfully\n";
    }

    void removeItem() {
        int number;

        while (true) {
            showItems();

            cout << "Enter the item ID to remove (0 to cancel): ";
            cin >> number;

            if (number == 0){
                cout << "Cancled.\n";
                return;
            }
            

            if (validation(number))
            {
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
            
        }
    }


    void updateItme(){
        int number;
        while (true) {
            showItems();

            cout << "Enter the item ID to remove (0 to cancel): ";
            cin >> number;

            if (number == 0)
            {
                cout << "Cancled.\n";
                return;
            }
            

            if (validation(number))
            {
               bool found = false;
                for (int i = 0; i < items.size(); i++) {
                    if (items[i].id == number) {
                        while (true) {

                        cout << "Enter Item Quantity: ";
                        cin >> items[i].quantity;
                        if (validation(items[i].quantity)){
                            break;
                        }
            }

                    while (true) {
                        cout << "Enter Item Price: ";
                        cin >> items[i].price;
                        if (cin.fail() || items[i].price < 0 || items[i].quantity == 0) {
                            cout << "Invalid input! Price must be a positive number.\n";
                            cin.clear();
                            cin.ignore(1000, '\n');
                        } else {
                            break;
                        }
                    }
                        return; // done
                    }
                }
                cout << "Item with ID " << number << " not found.\n";
            }
        }
    }


    void showItems(){
        for (int i = 0; i < items.size(); i++){
            items[i].id = i + 1;
        }

        for (int i = 0; i < items.size(); i++)
        {
            cout  << items[i].id << "." << items[i].name;
            cout << " _quantity: " << items[i].quantity;
            cout << " _price: " << items[i].price << endl;
            cout << "==========\n";
        }


        itemNotification();

    }

    void itemNotification() {
        int count = 0;
        cout << "=======LowStock=======\n";


        for (const Item& item : items) {
            if (item.quantity <= 5) {
                cout << " Item \"" << item.name << "\" is low stock 5 (Quantity: " << item.quantity << ")\n";
                count++;
            }
        }

        if (count == 0) {
            cout << " No low stock.\n";
        }
        cout << "=======LowStock=======\n";

    }

    void minusItemQuantity(string itemName, int quantity) {

        for (int i = 0; i < items.size(); i++)
        {
            if (items[i].name == itemName)
            {
                items[i].quantity -= quantity;
                return;
            }
        }
        cout << "Error, There is no item with the name: " << itemName << endl;
        
    }

    void plusItemQuantity(string itemName, int quantity){
        for (int i = 0; i < items.size(); i++)
            {
                if (items[i].name == itemName)
                {
                    items[i].quantity += quantity;
                    return;
                }
            }
        cout << "Error, There is no item with the name: " << itemName << endl;
    }

};



class Table : public Inventory{
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
        TableInfo t1;
        TableInfo t2;
        TableInfo t3;

        t1.id = 1;
        t1.reserved = false;  // free table
        tables.push_back(t1);

        t2.id = 2;
        t2.reserved = false;
        tables.push_back(t2);

        t3.id = 3;
        t3.reserved = true;   // example reserved
        tables.push_back(t3);

        cout << "Tables initialized successfully!\n";
    }
    

    void addOrder(){
        int number;
        while (true)
        {
            showTables();

            cout << "Enter table id (or 0 to cancel)";
            cin >> number;

            if (number == 0)
            {
                cout << "Cancled.\n";
                return;
            }
            

            if (validation(number))
            {
                bool found = false;
                for (int i = 0; i < tables.size(); i++) {
                    if (tables[i].id == number) {
                        Order ord;
                        int id;

                        while (true)
                        {
                            showItems();
                            cout << "Enter item id to add: ";
                            cin >> id;

                            if (validation(id) && id != 0)
                            {
                                cout << "Enter item quantity: ";
                                cin >> ord.quantity;

                                if (validation(ord.quantity) && id != 0)
                                {
                                    ord.id = 0;
                                    ord.itemName = items[id - 1].name;
                                    tables[i].orders.push_back(ord);
                                    return;
                                }
                                
                            }
                        }

                        return; // done
                    }
                }
                cout << "Item with ID " << number << " not found.\n";  
            }

        }
        
    }

    void showTables(){
        for (int i = 0; i < tables.size(); i++){
            tables[i].id = i + 1;
        }

        for (int i = 0; i < tables.size(); i++)
        {
            cout << "table id : " << tables[i].id << endl;
            cout << tables[i].reserved << endl;
            cout << "==========\n";

        }
    }

    void showOrder(TableInfo table){
        vector<Order> ord = table.orders;
        for (int i = 0; i < ord.size(); i++)
        {
            cout << table.id << endl;
            cout << ord[i].itemName << endl;
        }
        cout << "=========";
        
    }

    void deleteOrder() {
    int number;
        showTables();

        cout << "Enter table id (or 0 to cancel)";
        cin >> number;

        if (number == 0)
        {
            cout << "Cancled.\n";
            return;
        }
        
        if (validation(number))
        {
             for (int i = 0; i < tables.size(); i++) {
                if (tables[i].id == number) {
                    int id;
                    showOrders(tables[i]);

                    cout << "Enter the order id(or 0 to cancle): ";
                    cin >> id;

                    if (validation(id))
                    {
                        for (int j = 0; j < tables[i].orders.size(); j++)
                        {
                            if (tables[i].orders[j].id == id)
                            {
                                tables[i].orders.erase(tables[i].orders.begin() + j);
                                return;
                            } 
                        }
                        cout << "There is no order with this id\n";
                    }
                }
            }
            cout << "There is no Table with this number\n";
        
    }

}

    void showOrders(TableInfo& table) {

        for (int i = 0; i < table.orders.size(); i++){
            table.orders[i].id = i + 1;
        }

        vector<Order> ord = table.orders;

        for (int i = 0; i < table.orders.size(); i++){
            cout << ord[i].id << "." << ord[i].itemName << endl;
            cout << "quantity: " << ord[i].quantity << endl;
            cout << "===============\n";
        }
        
        
    }

};

class Bill : public Table{
    public:
    struct BillPrice {
        int tableId;
        double total;
    };

    vector<BillPrice> bills;
};

int main(){
    Table tab;
    Bill bil;

    

    tab.startItmes();
    tab.startTables();
    int number;
    bool exit = false;
    while (!exit)
    {
        cout << "1.Show Items\n2.Add Item\n3.Remove Item\n4.Update Itme\n5.Add Order\n0.Exit\n";
        cout << "Enter your choice: ";
        cin >> number;
        cout << "===============\n";
        switch (number)
        {
        case 1:
            tab.showItems();
            break;
        case 2:
            tab.addItem();
            break;
        case 3:
            tab.removeItem();
            break;
        case 4:
            tab.updateItme();
            break;
        case 5:
            tab.addOrder();
            break;
        case 0 :
            cout << "Exit";
            exit = true;
            break;
        default:
            cout << "invalid number";
            break;
        }  
    }
    
    
    return 0;
}