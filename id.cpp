#include<iostream>
#include<fstream>
using namespace std;

const int MAX_ORDERS = 100; 
const int MAX_USERS = 50; 
const int MAX_BOUQUET_TYPES = 5;
const int MAX_DAYS = 31; 

string orderIDs[MAX_ORDERS];     
string customerNames[MAX_ORDERS];
string bouquetTypes[MAX_ORDERS];  
int quantities[MAX_ORDERS];        
double prices[MAX_ORDERS];         
string orderDates[MAX_ORDERS];    
int totalOrders = 0;         

string customerUsernames[MAX_USERS];
string customerPasswords[MAX_USERS];
int totalCustomers = 0;

string floristUsernames[MAX_USERS];
string floristPasswords[MAX_USERS];
int totalFlorists = 0;

double salesReport[MAX_BOUQUET_TYPES][MAX_DAYS][2];

// Forward declarations
void viewAllOrders();
void generateSalesReport();
void deleteOrderHistory();
void manageUserAccounts();
void displayCustomerAccounts();
void displayFloristAccounts();
void addNewCustomer();
void addNewFlorist();
void deleteCustomer();
void deleteFlorist();
void clearScreen();
void pauseScreen();
void saveOrdersToFile();
void createSampleOrders();

void clearScreen() {
    // Print enough newlines to push content off screen
    for(int i = 0; i < 100; i++) {
        cout << "\n";
    }
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}

void Adminmenu(){
    int option; 
    bool exit = false;
    
    while(!exit) {
        clearScreen();
        cout<<"========================================"<<endl; 
        cout<<"          WELCOME TO ADMIN MENU         "<<endl; 
        cout<<"========================================"<<endl; 
        cout << "1. View all orders" << endl; 
        cout << "2. Generate sales report" << endl; 
        cout << "3. Delete or Reset order history" << endl; 
        cout << "4. Manage user accounts" << endl; 
        cout << "5. Exit Admin menu" << endl; 
        cout << "Enter your choice: "; 
        cin>> option; 
       
        switch(option){
            case 1 : 
                viewAllOrders(); 
                break;
            case 2 : 
                generateSalesReport(); 
                break;
            case 3 : 
                deleteOrderHistory(); 
                break;
            case 4 : 
                manageUserAccounts(); 
                break;
            case 5: 
                cout<<"Exiting from admin menu"<<endl; 
                exit = true;
                break;
            default: 
                cout<<"Invalid choice! Please enter a valid choice"<<endl; 
                pauseScreen();
                break;
        }
    }
}
void loadOrdersFromFile() {
   
    ifstream file;
    file.open("orders.txt");
    
    if (!file.is_open()) {
    	cout<<"No orders file found. Starting fresh."<<endl; 
        return; 
    }
    totalOrders = 0;
    
    while (totalOrders < MAX_ORDERS) {
        getline(file, orderIDs[totalOrders]);
        if (file.eof()) break;
        
        getline(file, customerNames[totalOrders]);
        getline(file, bouquetTypes[totalOrders]);
        file >> quantities[totalOrders];
        file >> prices[totalOrders];
        file.ignore(); 
        getline(file, orderDates[totalOrders]);
        totalOrders++; 
    }
    file.close();
    
}
void viewAllOrders() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "          ALL SAVED ORDERS             "<<endl;
    cout << "========================================"<<endl;
    
    if (totalOrders == 0) {
        cout << " No orders found in the system."<<endl;
    } else {
        cout << "Total Orders: " << totalOrders <<endl;
        
       
        for (int i = 0; i < totalOrders; i++) {
            cout << "Order #" << (i + 1) << endl;
            cout << "  Order ID: " << orderIDs[i] <<endl;
            cout << "  Customer: " << customerNames[i] <<endl;
            cout << "  Bouquet Type: " << bouquetTypes[i] << endl;
            cout << "  Quantity: " << quantities[i] <<endl;
            cout << "  Price: $" << prices[i] << endl;
            cout << "  Date: " << orderDates[i] <<endl;
            cout << "----------------------------------------"<<endl;
        }
    }
    
    pauseScreen();
}

void initializeSalesReport() {
    
    for (int i = 0; i < MAX_BOUQUET_TYPES; i++) {     
        for (int j = 0; j < MAX_DAYS; j++) {           
            salesReport[i][j][0] = 0;  
            salesReport[i][j][1] = 0;  
        }
    }
}

// Helper function to convert string to int (simple version)
int stringToInt(string str) {
    int result = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            result = result * 10 + (str[i] - '0');
        }
    }
    return result;
}

// Helper function to get substring
string getSubstring(string str, int start, int length) {
    string result = "";
    for (int i = start; i < start + length && i < str.length(); i++) {
        result += str[i];
    }
    return result;
}

void calculateSalesReport() {
   
    for (int i = 0; i < totalOrders; i++) {
        int bouquetIndex = -1;
        int day = 1; 
        
        
        if (bouquetTypes[i] == "Roses") 
            bouquetIndex = 0;
        else if (bouquetTypes[i] == "Tulips") 
            bouquetIndex = 1;
        else if (bouquetTypes[i] == "Sunflowers") 
            bouquetIndex = 2;
        else if (bouquetTypes[i] == "Lilies") 
            bouquetIndex = 3;
        else if (bouquetTypes[i] == "Mixed") 
            bouquetIndex = 4;
        
        
        if (orderDates[i].length() >= 2) {
            string dayStr = getSubstring(orderDates[i], 0, 2);
            day = stringToInt(dayStr); 
            
           
            if (day < 1 || day > 31) 
                day = 1;
        }
        
        // Add to 3D array if valid bouquet type
        if (bouquetIndex >= 0) {
            // Add quantity to [bouquetType][day][0]
            salesReport[bouquetIndex][day - 1][0] += quantities[i];
            
            // Add revenue to [bouquetType][day][1]
            salesReport[bouquetIndex][day - 1][1] += prices[i];
        }
    }
}


void generateSalesReport() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "      DAILY BOUQUET SALES REPORT       "<<endl;
    cout << "========================================"<<endl;
    
    // Check if orders exist
    if (totalOrders == 0) {
        cout << "[INFO] No orders available to generate report."<<endl;
        pauseScreen();
        return;
    }
    
    // Initialize and calculate report
    initializeSalesReport();
    calculateSalesReport();
    
    // Define bouquet names
    string bouquetNames[MAX_BOUQUET_TYPES] = {
        "Roses", "Tulips", "Sunflowers", "Lilies", "Mixed"
    };
    
    cout << "\n--- Sales Summary by Bouquet Type ---"<<endl;
    
    // Loop through each bouquet type
    for (int type = 0; type < MAX_BOUQUET_TYPES; type++) {
        double totalQty = 0;
        double totalRevenue = 0;
        
        // Sum up all days for this bouquet type
        for (int day = 0; day < MAX_DAYS; day++) {
            totalQty += salesReport[type][day][0];      // Sum quantities
            totalRevenue += salesReport[type][day][1];   // Sum revenues
        }
        
        // Only display if sales exist
        if (totalQty > 0) {
            cout << bouquetNames[type] << ": "<<endl;
            cout << "  Total Quantity Sold: " << (int)totalQty <<endl;
            cout << "  Total Revenue: $" << totalRevenue <<endl;
        }
    }
    
    // Calculate grand totals
    double grandTotalQty = 0;
    double grandTotalRevenue = 0;
    
    for (int i = 0; i < totalOrders; i++) {
        grandTotalQty += quantities[i];
        grandTotalRevenue += prices[i];
    }
    
    cout << "========================================"<<endl;
    cout << "GRAND TOTAL:\n";
    cout << "  Total Units Sold: " << (int)grandTotalQty <<endl;
    cout << "  Total Revenue: $" << grandTotalRevenue <<endl;
    cout << "========================================"<<endl;
    
    pauseScreen();
}
void deleteOrderHistory() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "       DELETE/RESET ORDER HISTORY      "<<endl;
    cout << "========================================"<<endl;
    
    cout << "\nCurrent total orders: " << totalOrders <<endl;
    
    
    if (totalOrders == 0) {
        cout << "[INFO] Order history is already empty."<<endl;
        pauseScreen();
        return;
    }
    
    // Ask for confirmation
    char confirm;
    cout << "Are you sure you want to delete ALL orders? (Y/N): ";
    cin >> confirm;
    
    // Use IF-ELSE to check confirmation
    if (confirm == 'Y' || confirm == 'y') {
        // STEP 1: Clear memory by resetting counter
        totalOrders = 0;
        
        // STEP 2: Clear file by opening in output mode
        ofstream file;
        file.open("orders.txt");
        file.close();
        
        cout << "[SUCCESS] All order history has been deleted!"<<endl;
    } else {
        cout << "[CANCELLED] Order history was not deleted."<<endl;
    }
    
    pauseScreen();
}

void displayCustomerAccounts() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "         CUSTOMER ACCOUNTS             "<<endl;
    cout << "========================================"<<endl;
    cout << "\nTotal Customers: " << totalCustomers << endl;
    
    for (int i = 0; i < totalCustomers; i++) {
        cout << (i + 1) << ". Username: " << customerUsernames[i] 
             << " | Password: " << customerPasswords[i] <<endl;
    }
    
    pauseScreen();
}

void addNewCustomer() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "         ADD NEW CUSTOMER              "<<endl;
    cout << "========================================"<<endl;
    
    
    if (totalCustomers >= MAX_USERS) {
        cout << "\n[ERROR] Maximum customer limit reached!"<<endl;
        pauseScreen();
        return;
    }
    
    
    string username, password;
    cout << "Enter new customer username: ";
    cin >> username;
    cout << "Enter new customer password: ";
    cin >> password;
    

    customerUsernames[totalCustomers] = username;
    customerPasswords[totalCustomers] = password;
    

    totalCustomers++;
    
    cout << "[SUCCESS] Customer account created! "<<endl;
    pauseScreen();
}

void deleteCustomer() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "         DELETE CUSTOMER               "<<endl;
    cout << "========================================"<<endl;
    
    // Check if customers exist
    if (totalCustomers == 0) {
        cout <<  "No customers to delete."<<endl;
        pauseScreen();
        return;
    }
    
    // Show all customers first
    displayCustomerAccounts();
    
    // Get index to delete
    int index;
    cout << "Enter customer number to delete (1-" << totalCustomers << "): ";
    cin >> index;
    
    // Validate input
    if (index < 1 || index > totalCustomers) {
        cout << "[ERROR] Invalid customer number!"<<endl;
        pauseScreen();
        return;
    }
    
   
    for (int i = index - 1; i < totalCustomers - 1; i++) {
        customerUsernames[i] = customerUsernames[i + 1];
        customerPasswords[i] = customerPasswords[i + 1];
    }
    

    totalCustomers--;
    
    cout << "[SUCCESS] Customer deleted!"<<endl;
    pauseScreen();
}

void displayFloristAccounts() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "         FLORIST ACCOUNTS              "<<endl;
    cout << "========================================"<<endl;
    cout << "\nTotal Florists: " << totalFlorists << endl;
    
    for (int i = 0; i < totalFlorists; i++) {
        cout << (i + 1) << ". Username: " << floristUsernames[i] 
             << " | Password: " << floristPasswords[i] <<endl;
    }
    
    pauseScreen();
}

void addNewFlorist() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "         ADD NEW FLORIST               "<<endl;
    cout << "========================================"<<endl;
    
    if (totalFlorists >= MAX_USERS) {
        cout << "\n[ERROR] Maximum florist limit reached!"<<endl;
        pauseScreen();
        return;
    }
    
    string username, password;
    cout << "Enter new florist username: ";
    cin >> username;
    cout << "Enter new florist password: ";
    cin >> password;
    
    floristUsernames[totalFlorists] = username;
    floristPasswords[totalFlorists] = password;
    totalFlorists++;
    
    cout << "[SUCCESS] Florist account created! "<<endl;
    pauseScreen();
}

void deleteFlorist() {
    clearScreen();
    cout << "========================================"<<endl;
    cout << "         DELETE FLORIST                "<<endl;
    cout << "========================================"<<endl;
    
    if (totalFlorists == 0) {
        cout << "No florists to delete."<<endl;
        pauseScreen();
        return;
    }
    
    displayFloristAccounts();
    
    int index;
    cout << "Enter florist number to delete (1-" << totalFlorists << "): ";
    cin >> index;
    
    if (index < 1 || index > totalFlorists) {
        cout << "[ERROR] Invalid florist number!"<<endl;
        pauseScreen();
        return;
    }
    
    for (int i = index - 1; i < totalFlorists - 1; i++) {
        floristUsernames[i] = floristUsernames[i + 1];
        floristPasswords[i] = floristPasswords[i + 1];
    }
    
    totalFlorists--;
    
    cout << "[SUCCESS] Florist deleted!"<<endl;
    pauseScreen();
}

void manageUserAccounts() {
    int choice;
    bool back = false;
    
    while (!back) {
        clearScreen();
        cout << "========================================\n";
        cout << "        MANAGE USER ACCOUNTS           \n";
        cout << "========================================\n";
        cout << "1. View All Customer Accounts\n";
        cout << "2. View All Florist Accounts\n";
        cout << "3. Add New Customer Account\n";
        cout << "4. Add New Florist Account\n";
        cout << "5. Delete Customer Account\n";
        cout << "6. Delete Florist Account\n";
        cout << "7. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                displayCustomerAccounts();
                break;
            case 2:
                displayFloristAccounts();
                break;
            case 3:
                addNewCustomer();
                break;
            case 4:
                addNewFlorist();
                break;
            case 5:
                deleteCustomer();
                break;
            case 6:
                deleteFlorist();
                break;
            case 7:
                back = true;
                break;
            default:
                cout << "[ERROR] Invalid choice!"<<endl;
                pauseScreen();
        }
    }
}

void saveOrdersToFile() {
    
    ofstream file;
    file.open("orders.txt");
    
    for (int i = 0; i < totalOrders; i++) {
        file << orderIDs[i] <<endl;
        file << customerNames[i] <<endl;
        file << bouquetTypes[i] <<endl;
        file << quantities[i] <<endl;
        file << prices[i] <<endl;
        file << orderDates[i] <<endl;
    }
    
    file.close();
}

void createSampleOrders() {
    // Create sample orders if none exist
    if (totalOrders == 0) {
        orderIDs[0] = "ORD001";
        customerNames[0] = "John Doe";
        bouquetTypes[0] = "Roses";
        quantities[0] = 5;
        prices[0] = 125.50;
        orderDates[0] = "01/12/2025";
        
        orderIDs[1] = "ORD002";
        customerNames[1] = "Jane Smith";
        bouquetTypes[1] = "Tulips";
        quantities[1] = 3;
        prices[1] = 75.00;
        orderDates[1] = "02/12/2025";
        
        orderIDs[2] = "ORD003";
        customerNames[2] = "Bob Wilson";
        bouquetTypes[2] = "Sunflowers";
        quantities[2] = 2;
        prices[2] = 50.00;
        orderDates[2] = "03/12/2025";
        
        orderIDs[3] = "ORD004";
        customerNames[3] = "Alice Brown";
        bouquetTypes[3] = "Lilies";
        quantities[3] = 4;
        prices[3] = 100.00;
        orderDates[3] = "04/12/2025";
        
        orderIDs[4] = "ORD005";
        customerNames[4] = "Charlie Green";
        bouquetTypes[4] = "Mixed";
        quantities[4] = 6;
        prices[4] = 150.00;
        orderDates[4] = "05/12/2025";
        
        totalOrders = 5;
        saveOrdersToFile();
        cout << "Sample orders created successfully!" << endl;
    }
}

void initializeSampleUsers() {
    
    customerUsernames[0] = "john_doe";
    customerPasswords[0] = "customer123";
    customerUsernames[1] = "jane_smith";
    customerPasswords[1] = "pass456";
    customerUsernames[2] = "bob_wilson";
    customerPasswords[2] = "bob789";
    totalCustomers = 3;
    

    floristUsernames[0] = "rose_expert";
    floristPasswords[0] = "florist123";
    floristUsernames[1] = "lily_master";
    floristPasswords[1] = "flower456";
    totalFlorists = 2;
}

int main(){
    initializeSampleUsers();
    loadOrdersFromFile();
    
    // Create sample orders if file doesn't exist or is empty
    if (totalOrders == 0) {
        createSampleOrders();
    }
    
    Adminmenu();
    
    return 0; 
}