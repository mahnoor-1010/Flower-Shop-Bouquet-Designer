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

int main(){

  cout << endl;
  cout << "=== Welcome to Flower Shop ===" << endl;
  mainMenu();

  while(true){
    if(optionMain == 1){
      bool loginSuccess = check_customer_login();
      if(loginSuccess){
        while(true){
          if(optionCustomer == 1){
            cout << endl;
            cout << "=== Bouquet Maker ===" << endl << endl;
            cout << "Name your Bouquet: ";
            cin >> bouquetName;
            available_flowers();
            create_bouquet();
            customerMenu();
          }
          else if(optionCustomer == 2){
            vieworders();
            customerMenu();
          }
          else if(optionCustomer == 3){
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
            customerMenu();
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

    }
    else if(optionMain == 3){

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

bool check_customer_login(){
  ifstream customerloginfile;
  customerloginfile.open("customerlogin.txt", ios::in);
  string customer_username;
  getline(customerloginfile, customer_username);
  string customer_password;
  getline(customerloginfile, customer_password);
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
    customerMenu();
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
    cout << "  " << flowerID[i] << " - " << flowerName[i] << " - Rs." << flowerPrice[i] << "   -   " << flowerStock[i] << endl;
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
    flowersfile << flowerID[i] << "," << flowerName[i] << "," << flowerPrice[i] << "," << flowerStock[i];
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
