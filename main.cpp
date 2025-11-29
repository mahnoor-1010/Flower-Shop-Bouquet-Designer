#include <iostream>
#include <fstream>
using namespace std;

int optionMain;
void mainMenu(){
  cout << endl;   
  cout << "1. Customer Login" << endl;
  cout << "2. Florist Login" << endl;
  cout << "3. Admin Login" << endl;
  cout << "4. Exit" << endl;
  cout << "Select an option: ";
  cin >> optionMain;
}

int optionCustomer;
void customerMenu(){
  cout << endl;
  cout << "1. Create a Bouquet" << endl;
  cout << "2. View Cart" << endl;
  cout << "3. Place Order" << endl;
  cout << "4. View Order History" << endl;
  cout << "5. Update Profile" << endl;
  cout << "6. Logout" << endl;
  cout << "Select an option: ";
  cin >> optionCustomer;
}
int optioncreateabouquet;
void optioncreateabouquet(){
  cout << "1. Add Flower" << endl;
  cout << "2. View Bouquet" << endl;
  cout << "3. Checkout" << endl;
  cout << "4. Cancel" << endl;
  cin >> optioncreateabouquet;
  
}

void optionviewbouquet(){
  cout << "1. Remove a flower" << endl;
  cout << "2. Add a flower" << endl;
  cout << "3. Checkout" << endl;
  cout << "4. Cancel" << endl;
  cin >> optionviewbouquet;
}
int main(){
string bouquetName;

 cout << endl;
    cout << "=== Welcome to Flower Shop ===" << endl;
    mainMenu();
    if(optionMain == 1){
        
        if(optionCustomer == 1){
          cout << "Name your bouquet: ";
          cin >> bouquetName;
          cout << "Available Flowers: ";
            
        }
    }

  return 0;
}
