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
void createabouquet(){
  cout << "1. Add Flower" << endl;
  cout << "2. View Bouquet" << endl;
  cout << "3. Checkout" << endl;
  cout << "4. Cancel" << endl;
  cout << "Select an option: ";
  cin >> optioncreateabouquet;
  
}
int optionviewbouquet;
void viewbouquet(){
  cout << "1. Remove a flower" << endl;
  cout << "2. Add a flower" << endl;
  cout << "3. Checkout" << endl;
  cout << "4. Cancel" << endl;
  cout << "Select an option: ";
  cin >> optionviewbouquet;
}

int optionplaceorder;
void placeorder(){
  cout << "1. Confirm Order" << endl;
  cout << "2. Edit Cart" << endl;
  cout << "3. Cancel" << endl;
  cout << "Select an option: ";
  cin >> optionplaceorder;
}

int main(){
string bouquetName;

 cout << endl;
    
    cout << "=== Welcome to Flower Shop ===" << endl;
    mainMenu();
    while(optionMain != 4){
       if(optionMain == 1){
        //open customerlogin.text
        // ask for user login and proceed
        
        if(optionCustomer == 1){
          cout << "Name your bouquet: ";
          cin >> bouquetName;
          cout << "Available Flowers: ";
          //open flowers.txt
        }

        if(optionCustomer == 2){
          cout << "--- Your Cart ---" << endl;
          // open cart.txt
        }

        if(optionCustomer == 3){
          cout << "--- Place Order ---" << endl;
          // make the user choose a bouquet
          // open bouquets.txt
          // display bouquet info
        }

        if(optionCustomer == 4){
          //open orderhistory.txt
        }

        if(optionCustomer == 5){
          //write to customerlogin.txt to change profile info
        }
        
        if(optionCustomer == 6){
          cout << "Logged out!";
          // repeat entire starting customer main code here
        }
    }

    
    }
   
  return 0;
}
