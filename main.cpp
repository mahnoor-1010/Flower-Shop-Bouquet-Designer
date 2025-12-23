#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void mainMenu();
void customerMenu();
void createabouquetMenu();
bool check_customer_login();
int get_inventory_index_by_id(int id);
void cancel();
void view_bouquet_details();
void available_flowers();
void add_flower();
void update_ordersfile(string order_id);
void checkout();
void create_bouquet();
void update_flowers();
string generate_order_id();
void vieworders();
void floristMenu();
bool check_admin_login();
void adminMenu();
void reset_file();
bool check_florist_login();
void update_stock();
void update_price();
void low_stock();
void customer_update_login();
void admin_update_login();
void florist_update_login();

int flowerID[50];
string flowerName[50];
int flowerPrice[50];
int flowerStock[50];
int flowerCount = 0;
string bouquetName;

int bouquetFlowerID[50];
string bouquetFlowerName[50];
int bouquetQuantity[50];
double bouquetTotalCost = 0.0;
int bouquetItemCount = 0;

int optionMain;
int optionCustomer;
int optioncreateabouquet;
int optionviewbouquet;
int optionplaceorder;
int optionFlorist;
int optionAdmin;
char delete_reset;
int account_option;

int main(){

  cout << endl;
  cout << "=== Welcome to Flower Shop ===" << endl;
  mainMenu();

  while(true){
    if(optionMain == 1){
      bool loginSuccess = check_customer_login();
      if(loginSuccess){
        while(true){
          customerMenu();
          if(optionCustomer == 1){
            cout << endl;
            cout << "=== Bouquet Maker ===" << endl << endl;
            cout << "Name your Bouquet: ";
            cin >> bouquetName;
            available_flowers();
            create_bouquet();
          }
          else if(optionCustomer == 2){
            vieworders();
          }
          else if(optionCustomer == 3){

            customer_update_login();
          }
          else if(optionCustomer == 4){
            cout << endl << "Logged out!" << endl;
            break;
          }
        }
      }
      mainMenu();
    }
    else if(optionMain == 2){
      bool loginSuccess = check_florist_login();
      if(loginSuccess){
        while(true){
          floristMenu();
          if(optionFlorist == 1){
            update_stock();
          }
          if(optionFlorist==2){
            update_price();
            
          }
          if(optionFlorist == 3){
            vieworders();
            

          }
          if(optionFlorist ==4){
            low_stock();
            
          }
          if(optionFlorist ==5 ){
            florist_update_login();
          }
          if(optionFlorist == 6){
            cout << endl << "Logged out!" << endl;
            break;
          }
        }
}
mainMenu();
    }
    else if(optionMain == 3){
      bool loginSuccess = check_admin_login();
      if(loginSuccess){
        while(true){
          adminMenu();
          if(optionAdmin == 1){
            vieworders(); 
          }
          else if(optionAdmin == 2){
            cout<<"Do you want to delete/reset order history? (Y/N): ";
            cin>> delete_reset; 
            if(delete_reset == 'Y'){
              reset_file();
            }
          }
          else if(optionAdmin == 3){
            cout<<"1.Customer"<<endl;
            cout<<"2.Admin"<<endl;
            cout<<"3.Florist"<<endl; 
            cout<<"Select an account to manage: "<<endl;
            cin>> account_option;
            if(account_option == 1){
              customer_update_login();
              adminMenu();
            }
            else if(account_option == 2){
              admin_update_login(); 
              adminMenu();

            }
            else if(account_option == 3){

              florist_update_login();
              adminMenu();

            }


          }    
          else if(optionAdmin==4){
            cout<<endl<<"Logged out!"<<endl;
            break; 
          }
        
        }
      }
      mainMenu();

    }
    else if(optionMain == 4){
      cout << "Program Exited." << endl;
      return 1;
    }
    else{
      cout << "Invalid option. Please try again." << endl;
      mainMenu();
    }
  }
  
  return 0;
}

void mainMenu(){
  cout << endl;
  cout << "=== MAIN MENU ===" << endl;
  cout << "1. Customer Login" << endl;
  cout << "2. Florist Login" << endl;
  cout << "3. Admin Login" << endl;
  cout << "4. Exit" << endl;
  cout << "Select an option: ";
  while(!(cin >> optionMain) || optionMain < 1 || optionMain > 4){
    cout << "Invalid input. Please enter a number between 1-4: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }
}

void customerMenu(){
  cout << endl;
  cout << "=== CUSTOMER MENU ===" << endl;
  cout << "1. Create a Bouquet" << endl;
  cout << "2. View Order History" << endl;
  cout <<  "3. Update Profile" << endl;
  cout << "4. Logout" << endl;
  cout << "Select an option: ";
  while(!(cin >> optionCustomer) || optionCustomer < 1 || optionCustomer > 4){
    cout << "Invalid input. Please enter a number between 1-4: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }
}

void createabouquetMenu(){
  cout << "1. Add Flower" << endl;
  cout << "2. View Bouquet" << endl;
  cout << "3. Checkout" << endl;
  cout << "4. Cancel" << endl;
  cout << "Select an option: ";
  while(!(cin >> optioncreateabouquet) || optioncreateabouquet < 1 || optioncreateabouquet > 4){
    cout << "Invalid input. Please enter a number between 1-4";
    cin.clear();
    cin.ignore(10000, '\n');
  }
}

void customer_update_login(){
            ofstream outfile;
            outfile.open("customerlogin.txt", ios::out);
            string new_customer_username;
            cout << "Enter new username";
            cin >> new_customer_username;
            outfile << new_customer_username << endl;
            string new_customer_password;
            cout << "Enter new password: ";
            cin >> new_customer_password;
            outfile << new_customer_password;
            outfile.close();
            cout << endl;
            cout << "Customer profile updated!";
            cout << endl;
}

void admin_update_login(){
            ofstream outfile;
            outfile.open("adminlogin.txt", ios::out);
            string new_admin_username;
            cout << "Enter new username";
            cin >> new_admin_username;
            outfile << new_admin_username << endl;
            string new_admin_password;
            cout << "Enter new password: ";
            cin >> new_admin_password;
            outfile << new_admin_password;
            outfile.close();
            cout << endl;
            cout << "Admin profile updated!";
            cout << endl;
}

void florist_update_login(){
            ofstream outfile;
            outfile.open("floristlogin.txt", ios::out);
            string new_florist_username;
            cout << "Enter new username";
            cin >> new_florist_username;
            outfile << new_florist_username << endl;
            string new_florist_password;
            cout << "Enter new password: ";
            cin >> new_florist_password;
            outfile << new_florist_password;
            outfile.close();
            cout << endl;
            cout << "Florist profile updated!";
            cout << endl;
}

bool check_customer_login(){
  ifstream customerloginfile;
  customerloginfile.open("customerlogin.txt", ios::in);
  string customer_username;
  getline(customerloginfile, customer_username);
  string customer_password;
  getline(customerloginfile, customer_password);
  customerloginfile.close();
  string customer_user_username;
  string customer_user_password;
  cout << endl;
  cout << "Please enter username for customer login: ";
  cin >> customer_user_username;
  cout << "Please enter password for customer login: ";
  cin >> customer_user_password;
  if(customer_user_username == customer_username && customer_user_password == customer_password){
    cout << endl;
    cout << "Successfully logged in as customer!" << endl;
    return true;
  }
  else{
    cout << endl;
    cout << "Incorrect username or password!" << endl;
    return false;
  }
}

int get_inventory_index_by_id(int id){
  for(int i = 0; i < flowerCount; i++){
    if(flowerID[i] == id){
      return i;
    }
  }
  return -1;
}

void cancel(){
  for(int i = 0; i < bouquetItemCount; i++){
    int flower_id = bouquetFlowerID[i];
    int qty_to_restore = bouquetQuantity[i];
    int index = get_inventory_index_by_id(flower_id);
    if(index != -1){
      flowerStock[index] += qty_to_restore;
    }
  }
  bouquetItemCount = 0;
  bouquetTotalCost = 0.0;
  bouquetName = "";
  cout << "Stock Restored. Bouquet Cancelled." << endl;
  update_flowers();
}

void view_bouquet_details(){
  cout << "Your Bouquet: " << endl;
  if(bouquetItemCount == 0){
    cout << "[Empty]" << endl;
    cout << "Total: 0.00 PKR" << endl;
  }
  else{
    for(int i = 0; i < bouquetItemCount; i++){
      int flower_id_in_bouquet = bouquetFlowerID[i];
      int index = get_inventory_index_by_id(flower_id_in_bouquet);
      int unit_price = flowerPrice[index];
      double subtotal = bouquetQuantity[i] * unit_price;
      cout << bouquetQuantity[i] << "x " << bouquetFlowerName[i] << " (" << flowerPrice[index] << " PKR each): " << subtotal << " PKR" << endl;
    }
    cout << "Total: " << bouquetTotalCost << " PKR" << endl;
  }
}

void available_flowers(){
  flowerCount = 0;
  ifstream flowersfile;
  flowersfile.open("flowers.txt", ios::in);
  while(flowersfile >> flowerID[flowerCount]){
    flowersfile.ignore();
    getline(flowersfile, flowerName[flowerCount], ',');
    flowersfile >> flowerPrice[flowerCount];
    flowersfile.ignore();
    flowersfile >> flowerStock[flowerCount];
    flowerCount++;
  }
  flowersfile.close();

  cout << "Avaiable Flowers:" << endl;
  cout << "Flower ID - Flower Name - Flower Price - Flower Stock" << endl;
  for(int i = 0; i < flowerCount; i++){
    cout << "  " << flowerID[i] << "     -  " << flowerName[i] << "  -     Rs." << flowerPrice[i] << "   -     " << flowerStock[i] << endl;
  }
}

void add_flower(){
  int id, qty;
  cout << endl;
  cout << "--- Add Flower ---" << endl;
  cout << "Enter Flower ID to add: ";
  while(!(cin >> id)){
    cout << "Invalid input. Please enter a valid number for Flower ID: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }
  cout << "Enter Quantity: ";
  while(!(cin >> qty)){
    cout << "Invalid input. Please enter a valid number for Quantity: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }

  int index = get_inventory_index_by_id(id);
  if(index == -1){
  cout << "Error: Flower ID" << id << " not found in inventory." << endl;
  cout << "Please try again." << endl;
  add_flower();
  return;
  }
  if(qty <= 0){
    cout << "Error: Quantity must be greater than zero." << endl;
    cout << "Please try again." << endl;
    add_flower();
    return;
  }

  if(flowerStock[index] < qty){
    cout << "Error: Not enough stock avaialble. Only " << flowerStock[index] << " left." << endl;
    cout << "Please try again." << endl;
    add_flower();
    return;
  }

  if(bouquetItemCount >= 50){
    cout << "Error: Bouquet limit reached." << endl;
    return;
  }

  bouquetFlowerID[bouquetItemCount] = id;
  bouquetFlowerName[bouquetItemCount] = flowerName[index];
  bouquetQuantity[bouquetItemCount] = qty;
  double itemCost = (double)flowerPrice[index] * qty;
  bouquetTotalCost += itemCost;
  flowerStock[index] -= qty;
  bouquetItemCount++;
  cout << qty << "x " << flowerName[index] << " added to bouquet. Subtotal: " << itemCost << " PKR." << endl;
  update_flowers();

}

void update_ordersfile(string order_id){
  ofstream ordersfile("orders.txt", ios::app);
  ordersfile << "--- NEW ORDER ---" << endl;
  ordersfile << "Order ID: " << order_id << endl;
  ordersfile << "Bouquet Name: " << bouquetName << endl;
  ordersfile << "Total Cost: " << bouquetTotalCost << " PKR" << endl;
  for(int i = 0; i < bouquetItemCount; i++){
    int index = get_inventory_index_by_id(bouquetFlowerID[i]);
    if(index != -1){
      double subtotal = bouquetQuantity[i] * flowerPrice[index];
      ordersfile << bouquetFlowerName[i] << " x" << bouquetQuantity[i] << " = " << subtotal << " PKR" << endl;
    }
  }
  ordersfile << "--- END ORDER ---" << endl << endl;
  ordersfile.close();
}

string generate_order_id(){
  ifstream infile;
  infile.open("order_id.txt", ios::in);
  int lastID = 0;
  infile >> lastID;
  infile.close();
  lastID++;
  ofstream outfile;
  outfile.open("order_id.txt", ios::out);
  outfile << lastID;
  outfile.close();
  return "ORD" + to_string(lastID);
}

void checkout(){
  cout << "Confirm Order: " << endl;
  view_bouquet_details();
  int optioncheckout;
  cout << "1. Confirm and Place Order" << endl;
  cout << "2. Cancel" << endl;
  cout << "Select an option: ";
  while(!(cin >> optioncheckout) || (optioncheckout != 1) && (optioncheckout != 2)){
    cout << "Invalid input. Please enter 1 or 2: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }
  if(optioncheckout == 1){
    string order_id = generate_order_id();
    cout << "Order Placed Successfully!" << endl;
    cout << "Order ID: " << order_id << endl;
    update_ordersfile(order_id);
    bouquetItemCount = 0;
    bouquetTotalCost = 0.0;
    bouquetName = "";
  }
  else if(optioncheckout == 2){
    cancel();
  }
}

void create_bouquet(){
  while(true){
    createabouquetMenu();
    if(optioncreateabouquet == 1){
      add_flower();
    }
    else if(optioncreateabouquet == 2){
      view_bouquet_details();
    }
    else if(optioncreateabouquet == 3){
      checkout();
      break;
    }
    else if(optioncreateabouquet == 4){
      cancel();
      break;
    }
  }
}

void update_flowers(){
  ofstream flowersfile;
  flowersfile.open("flowers.txt", ios::out);
  for(int i = 0; i < flowerCount; i++){
    flowersfile << flowerID[i] << ", " << flowerName[i] << ", " << flowerPrice[i] << ", " << flowerStock[i];
    if(i < flowerCount - 1){
      flowersfile << endl;
    }
  }
  flowersfile.close();
}

void vieworders(){
  ifstream ordersfile;
  ordersfile.open("orders.txt", ios::in);
  string s;
  while(getline(ordersfile, s)){
    cout << s << endl;
  }
  ordersfile.close();
}
bool check_admin_login(){
  
   ifstream adminloginfile;
  adminloginfile.open("adminlogin.txt", ios::in);
  string admin_username;
  getline(adminloginfile, admin_username);
  string admin_password;
  getline(adminloginfile, admin_password);
  adminloginfile.close();
  string admin_user_username;
  string admin_user_password;
  cout << endl;
  cout << "Please enter username for admin login: ";
  cin >> admin_user_username;
  cout << "Please enter password for admin login: ";
  cin >> admin_user_password;
  if(admin_user_username == admin_username && admin_user_password == admin_password){
    cout << endl;
    cout << "Successfully logged in as admin!" << endl;
    return true;
  }
  else{
    cout << endl;
    cout << "Incorrect username or password!" << endl;
    return false;
  }
}
bool check_florist_login(){
ifstream floristloginfile;
  floristloginfile.open("floristlogin.txt", ios::in);
  string florist_username;
  getline(floristloginfile, florist_username);
  string florist_password;
  getline(floristloginfile, florist_password);
  floristloginfile.close();
  string florist_user_username;
  string florist_user_password;
  cout << endl;
  cout << "Please enter username for florist login: ";
  cin >> florist_user_username;
  cout << "Please enter password for florist login: ";
  cin >> florist_user_password;
  if(florist_user_username == florist_username && florist_user_password == florist_password){
    cout << endl;
    cout << "Successfully logged in as florist!" << endl;
    return true;
  }
  else{
    cout << endl;
    cout << "Incorrect username or password!" << endl;
    return false;
  }
}

void update_stock(){
  flowerCount = 0;
  ifstream flowersfile;
  flowersfile.open("flowers.txt", ios::in);
  while(flowersfile >> flowerID[flowerCount]){
    flowersfile.ignore();
    getline(flowersfile, flowerName[flowerCount], ',');
    flowersfile >> flowerPrice[flowerCount];
    flowersfile.ignore();
    flowersfile >> flowerStock[flowerCount];
    flowerCount++;
  }
  flowersfile.close();

  cout << endl;
  cout << "=== UPDATE FLOWER STOCK ===" << endl;
  cout << "Current Inventory:" << endl;
  cout << "ID - Name - Price - Stock" << endl;
  for(int i = 0; i< flowerCount; i++){
    cout << flowerID[i] << " - " << flowerName[i] << " - Rs." << flowerPrice[i] << " - " << flowerStock[i] << endl;
  }

  int id;
  cout << endl << "Enter Flower ID to update stock: ";
  while(!(cin >> id)){
    cout << "Invalid input. Please enter a valid Flower ID: ";
    cin.clear();
    cin.ignore(10000, '\n');
  }

  int index = get_inventory_index_by_id(id);
  if(index == -1){
    cout << "Error: Flower ID" << id << " not found!" << endl;
    return;
  }
  
  int new_stock;
  cout << "Current stock for " << flowerName[index] << ": " << flowerStock[index] << endl;
  cout << "Enter new stock amount: ";
  while(!(cin>>new_stock) || new_stock < 0){
    cout << "Invalid input. Please enter a valid stock amount (0 or greater): ";
    cin.clear();
    cin.ignore(10000, '\n');
  }

  flowerStock[index] = new_stock;
  cout << "Stock updated successfully!" << endl;
  cout << flowerName[index] << " now has " << flowerStock[index] << " in stock." << endl;
  update_flowers();
}

void low_stock(){
    flowerCount = 0;
    ifstream flowersfile("flowers.txt");
    if(!flowersfile){
        cout << "Error opening flowers file!" << endl;
        return;
    }
    while(flowersfile >> flowerID[flowerCount]){
        flowersfile.ignore();
        getline(flowersfile, flowerName[flowerCount], ',');
        flowersfile >> flowerPrice[flowerCount];
        flowersfile.ignore();
        flowersfile >> flowerStock[flowerCount];
        flowerCount++;
    }
    flowersfile.close();
    
    bool no_low_stock = true;
    for(int i = 0; i < flowerCount; i++){
        if(flowerStock[i] < 15){
            no_low_stock = false;
            break;
        }
    }
    cout << endl;
    if(no_low_stock){
        cout << "All flowers are in stock!" << endl;
    } 
    else{
        cout << "=== LOW STOCK ALERTS ===" << endl;
        for(int i = 0; i < flowerCount; i++){
            if(flowerStock[i] < 15){
                cout << "Only " << flowerStock[i] << " " << flowerName[i] << " left!" << endl;
            }
        }
    }
}

void floristMenu(){
    cout << endl;
    cout << "1. Update Flower Stock" << endl;
    cout << "2. Update Flower Prices" << endl;
    cout << "3. View Orders" << endl;
    cout << "4. Low Stock Alerts" << endl;
    cout << "5. Update Profile" << endl;
    cout << "6. Logout" << endl;
    cout << "Select an option: ";
    while(!(cin >> optionFlorist) || optionFlorist < 1 || optionFlorist > 6){
        cout << "Invalid input. Please enter a number between 1-6: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void reset_file(){
    ofstream file;
    file.open("orders.txt", ios::out);
    file.close();
    cout << "File resetted successfully!" << endl;
}

void adminMenu(){
    cout << endl; 
    cout << "=== ADMIN MENU ===" << endl; 
    cout << "1. View all orders" << endl; 
    cout << "2. Delete or Reset order history" << endl; 
    cout << "3. Manage user accounts" << endl; 
    cout << "4. Exit Admin menu" << endl; 
    cout << "Enter your choice: ";
    while(!(cin >> optionAdmin) || optionAdmin < 1 || optionAdmin > 4){
        cout << "Invalid input. Please enter a number between 1-4: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
}

void update_price(){
    flowerCount = 0;
    ifstream flowersfile("flowers.txt");
    if(!flowersfile){
        cout << "Error opening flowers file!" << endl;
        return;
    }
    while(flowersfile >> flowerID[flowerCount]){
        flowersfile.ignore();
        getline(flowersfile, flowerName[flowerCount], ',');
        flowersfile >> flowerPrice[flowerCount];
        flowersfile.ignore();
        flowersfile >> flowerStock[flowerCount];
        flowerCount++;
    }
    flowersfile.close();
    
    cout << endl;
    cout << "=== UPDATE FLOWER PRICES ===" << endl;
    cout << "Current Inventory:" << endl;
    cout << "ID - Name - Price - Stock" << endl;
    for(int i = 0; i < flowerCount; i++){
        cout << flowerID[i] << " - " << flowerName[i] << " - Rs. " << flowerPrice[i] << " - " << flowerStock[i] << endl;
    }
    
    int id;
    cout << endl << "Enter Flower ID to update price: ";
    while(!(cin >> id)){
        cout << "Invalid input. Please enter a valid Flower ID: ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    int index = get_inventory_index_by_id(id);
    if(index == -1){
        cout << "Error: Flower ID " << id << " not found!" << endl;
        return;
    }
    
    int new_price;
    cout << "Current price for " << flowerName[index] << ": Rs. " << flowerPrice[index] << endl;
    cout << "Enter new price: ";
    while(!(cin >> new_price) || new_price < 0){
        cout << "Invalid input. Please enter a valid price (0 or greater): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }
    
    flowerPrice[index] = new_price;
    cout << "Price updated successfully!" << endl;
    cout << flowerName[index] << " now costs Rs. " << flowerPrice[index] << endl;
    update_flowers();
}