/*
Student ID   : B1243
Student name : Soh Mei Yi Samantha
Description  : Car rental management system
*/

#define _WIN32_WINNT 0x0500
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <fstream>
#include <windows.h>
#include <string>
#include <iomanip>

using namespace std;

//Function prototypes
void populateData(int);
void mainMenu(int&);
void customer(char*, int, string);
void createAccount(char*, int, string);
void login(char*, int, string, bool&, int&);
bool checkUser(char*, int, string);
void adminMenu(bool&, int&);
void viewData(bool&, int&);
void displayData(bool&, int&);
void addCar(bool&, int&);
int linearSearch(int&);
int checkLinearSearch(bool&, int&);
void updateCar(bool&, int&);
void updateCar(int, bool&, int&);
void deleteCar(bool&, int&);
void customerMenu(char*, int, bool&, int&);
void rentCar(char*, int, bool&, int&);
void showInvoice(double, double, int, char*, int, bool&, int&);
void rentalRecord(char*, int, bool&, int&);
void termsAndConditions(int&);
void spacing();

ofstream newUser;
ifstream savedUser;

struct car {
    string carPlate, brand, model, colour, rentedBy;
    int capacity;
    double ratePerHour;
    bool isAvailable;
} cars[30];

int main() {

    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, 800, 600, TRUE);
    system("Color F0");

    int choice;
    int currentSize = 5;

    populateData(currentSize);
    mainMenu(currentSize);

    return 0;
}

//Function to populate data in car rental system
void populateData(int currentSize) {

    string carPlate[] = { "WVX3589", "WDP3194", "BSN5634", "WXS3529", "VDR7799" };
    string brand[] = { "Honda", "Proton", "Perodua", "BMW", "Renault" };
    string model[] = { "City", "X50" , "Bezza" , "M5", "Fluence" };
    string colour[] = { "Red", "Blue", "Black", "White", "Grey" };
    string rentedBy[] = { "Ray", "Henry", " ", " ", " " };
    int capacity[] = { 5, 5, 5, 5, 6 };
    double ratePerHour[] = { 10, 7, 7, 15, 20 };
    bool isAvailable[] = { false, false, true, true, true };

    for (int i = 0; i < currentSize; i++) {
        cars[i].carPlate = carPlate[i];
        cars[i].brand = brand[i];
        cars[i].model = model[i];
        cars[i].colour = colour[i];
        cars[i].rentedBy = rentedBy[i];
        cars[i].capacity = capacity[i];
        cars[i].ratePerHour = ratePerHour[i];
        cars[i].isAvailable = isAvailable[i];
    }
}

//Function to display main menu of the car rental system and get user input
void mainMenu(int &currentSize) {

    int choice;
    char username[50];
    string password;
    bool isAdmin = false;

    while (true) {
        system("cls");
        spacing();
        cout << setfill(' ') << setw(55) << "CAR RENTAL SYSTEM" << endl;
        cout << endl;
        cout << setfill(' ') << setw(45) << "1." << "Admin" << endl;
        cout << setfill(' ') << setw(45) << "2." << "Customer" << endl;
        cout << setfill(' ') << setw(45) << "3." << "T&C" << endl;
        cout << setfill(' ') << setw(45) << "4." << "Exit" << endl;
        cout << endl;
        cout << setfill(' ') << setw(55) << "Enter your choice: ";
        cin >> choice;

        //check if input is integer
        if (!cin.fail()) {
            if (choice >= 1 && choice <= 4) { //if input is within 1 to 4
                break;
            }
            else {
                cout << setfill(' ') << setw(65) << "You have entered wrong input.";
                Sleep(1000);
                system("cls");
                continue;
            }
        }

        //if input is not integer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << setfill(' ') << setw(65) << "You have entered wrong input.";
            Sleep(1000);
            system("cls");
            continue;
        }
    }

    system("cls");

    switch (choice) {
    case 1:
        isAdmin = true;
        savedUser.open("admin.txt"); // read admin.txt 
        login(username, 50, password, isAdmin, currentSize);
        break;
    case 2:
        isAdmin = false;
        customer(username, 50, password);
        login(username, 50, password, isAdmin, currentSize);
        break;
    case 3:
        termsAndConditions(currentSize);
        break;
    case 4:
        system("cls");
        spacing();
        cout << setfill(' ') << setw(65) << "THANK YOU FOR USING CAR RENTAL SYSTEM.";
        break;
    }
}

//Function to display menu for user to login as new or existing customer and get customer input
void customer(char* username, int size, string password) {

    int choice;

    while (true) {
        spacing();
        cout << setfill(' ') << setw(55) << "CAR RENTAL SYSTEM" << endl;
        cout << endl;
        cout << setfill(' ') << setw(45) << "1." << "New" << endl;
        cout << setfill(' ') << setw(45) << "2." << "Existing" << endl;
        cout << endl;
        cout << setfill(' ') << setw(55) << "Enter your choice: ";
        cin >> choice;

        //check if input is integer
        if (!cin.fail()) {
            if (choice == 1 || choice == 2) { //if input is 1 or 2
                break;
            }
            else {
                cout << setfill(' ') << setw(65) << "You have entered wrong input.";
                Sleep(1000);
                system("cls");
                continue;
            }
        }

        //if input is not integer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << setfill(' ') << setw(65) << "You have entered wrong input.";
            Sleep(1000);
            system("cls");
            continue;
        }
    }
    system("cls");

    //New customer has to create an account before logging in
    if (choice == 1) {
        createAccount(username, 50, password);
    }

    system("cls");
    savedUser.open("customer.txt"); //read customer.txt
}

//Function for new customer to create account
void createAccount(char* username, int size, string password) {

    spacing();
    cout << setfill(' ') << setw(55) << "Please create a username: ";
    cin.ignore();
    cin.getline(username, 50);
    cout << setfill(' ') << setw(55) << "Please create a password: ";
    cin >> password;

    newUser.open("customer.txt", ios::app); //write to customer.txt
    newUser << username << "\t" << password << endl;
    newUser.close();
    cout << setfill(' ') << setw(55) << "Account created!" << endl;
    Sleep(1000);
}

//Function to allow user(admin/customer) login
void login(char* username, int size, string password, bool &isAdmin, int &currentSize) {

    bool check;

    do {
        spacing();
        cout << setfill(' ') << setw(55) << "Enter your username: ";
        cin.ignore();
        cin.getline(username, 50);
        cout << setfill(' ') << setw(55) << "Enter your password: ";
        cin >> password;

        check = checkUser(username,50, password);
        if (check == true) {
            cout << setfill(' ') << setw(60) << "Login successful!" << endl;
        }
        else {
            cout << setfill(' ') << setw(60) << "ERROR! Login unsuccessful!" << endl;
        }
        Sleep(1000);
        system("cls");

    } while (check == false);
    savedUser.close();

    if (isAdmin == true) {
        adminMenu(isAdmin,currentSize);
    }
    else {
        customerMenu(username, 50, isAdmin, currentSize);
    }
}

//Function to verify username and password entered at login()
bool checkUser(char* username, int size, string password) {

    bool isMatch = false;
    char credential[50]; //to store data read from file
    savedUser.clear(); //reset all internal error flags or will still appear to be at the end of file
    savedUser.seekg(0, savedUser.beg); //move to the beginning of the file

    //check username
    while (savedUser >> credential) {
        if (strcmp(username, credential) == 0) {
            isMatch = true;
            break;
        }
        else {
            isMatch = false;
        }
    }

    //after username is true, check corresponding password
    if (isMatch == true) {
        while (savedUser >> credential) {
            if (password == credential) {
                isMatch = true;
            }
            else {
                isMatch = false;
            }
            break;
        }
    }
    return isMatch;
}

//Function to display menu for functions only accessible to admin
void adminMenu(bool &isAdmin, int &currentSize) {

    int choice;

    while (true) {
        spacing();
        cout << right << setfill(' ') << setw(55) << "CAR RENTAL SYSTEM" << endl;
        cout << endl;
        cout << right << setfill(' ') << setw(45) << "1." << "Show data" << endl;
        cout << right << setfill(' ') << setw(45) << "2." << "Add car" << endl;
        cout << right << setfill(' ') << setw(45) << "3." << "Update car" << endl;
        cout << right << setfill(' ') << setw(45) << "4." << "Delete car" << endl;
        cout << right << setfill(' ') << setw(45) << "5." << "Logout" << endl;
        cout << endl;
        cout << right << setfill(' ') << setw(55) << "Enter your choice: ";
        cin >> choice;

        //check if input is integer
        if (!cin.fail()) {
            if (choice >= 1 && choice <= 5) { //if input is within 1 to 5
                break;
            }
            else {
                cout << setfill(' ') << setw(65) << "You have entered wrong input.";
                Sleep(1000);
                system("cls");
                continue;
            }
        }

        //if input is not integer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << setfill(' ') << setw(65) << "You have entered wrong input.";
            Sleep(1000);
            system("cls");
            continue;
        }
    }
    system("cls");

    switch (choice) {
    case 1:
        viewData(isAdmin, currentSize);
        break;
    case 2:
        addCar(isAdmin, currentSize);
        break;
    case 3:
        updateCar(isAdmin, currentSize);
        break;
    case 4:
        deleteCar(isAdmin, currentSize);
        break;
    case 5:
        mainMenu(currentSize);
        break;
    }
}

void viewData(bool& isAdmin, int& currentSize) {

    spacing();
    cout << "Car plate" << setw(8) << "Brand" << setw(10) << "Model" << setw(10)
        << "Colour" << setw(12) << "Rented By" << setw(12) << "Capacity" << setw(15)
        << "Rate per hour" << endl;

    for (int i = 0; i < currentSize; i++) {

        cout << left << setw(12) << cars[i].carPlate << left << setw(10) << cars[i].brand << left << setw(9) << cars[i].model << left
            << setw(9) << cars[i].colour << left << setw(16) << cars[i].rentedBy << left << setw(12) << cars[i].capacity
            << left << setw(15) << cars[i].ratePerHour << endl;
    }
    cout << "\n";

    system("pause");
    system("cls");
    adminMenu(isAdmin, currentSize);
}

//Function to display data according to user type (admin/customer)
void displayData(bool &isAdmin, int &currentSize) {
   
    spacing();
    if (isAdmin == true) {
        cout << "Car plate" << setw(8) << "Brand" << setw(10) << "Model" << setw(10)
            << "Colour" << setw(12) << "Rented By" << setw(12) << "Capacity" << setw(15)
            << "Rate per hour" << endl;

        for (int i = 0; i < currentSize; i++) {

            cout << left << setw(12) << cars[i].carPlate << left << setw(10) << cars[i].brand << left << setw(9) << cars[i].model << left
                << setw(9) << cars[i].colour << left << setw(16) << cars[i].rentedBy << left << setw(12) << cars[i].capacity
                << left << setw(15) << cars[i].ratePerHour << endl;
        }
        cout << "\n";
    }
    else {
        cout << "Car plate" << setw(8) << "Brand" << setw(10) << "Model" << setw(10)
            << "Colour" << setw(12) << "Capacity" << setw(15)
            << "Rate per hour" << setw(12) << endl;

        for (int i = 0; i < currentSize; i++) {
            if (cars[i].isAvailable == true) {
                cout << left << setw(12) << cars[i].carPlate << left << setw(10) << cars[i].brand << left << setw(9) << cars[i].model << left
                    << setw(10) << cars[i].colour << left << setw(12) << cars[i].capacity
                    << left << setw(15) << cars[i].ratePerHour << endl;
            }
            else {
                continue;
            }
        }
        cout << "\n";
    }
}

//Function to add car by entering car data
void addCar(bool &isAdmin, int &currentSize) {

    cin.ignore(100, '\n');
    bool isDuplicate = false;
    string input;

    if (currentSize >= sizeof(cars)) {
        currentSize;
    }

    spacing();
    cout << setfill(' ') << setw(65) << "Please enter car data below: " << endl;
    cout << endl;

    //To ensure no duplicate car plate is in the data 
    do {
        cout << setfill(' ') << setw(45) << "Car plate number: ";
        getline(cin, cars[currentSize].carPlate);

        for (int i = 0; i < currentSize; i++) {
            if (cars[currentSize].carPlate == cars[i].carPlate) {
                cout << setfill(' ') << setw(55) << "The car plate is duplicate." << endl;
                isDuplicate = true;
                break;
            }
            else {
                isDuplicate = false;
            }
        }
    } while (isDuplicate == true);

    cout << setfill(' ') << setw(45) << "Car brand: ";
    getline(cin, cars[currentSize].brand);

    cout << setfill(' ') << setw(45) << "Car model: ";
    getline(cin, cars[currentSize].model);

    cout << setfill(' ') << setw(45) << "Car colour: ";
    getline(cin, cars[currentSize].colour);

    cout << setfill(' ') << setw(45) << "Car capacity: ";
    cin >> cars[currentSize].capacity;

    cout << setfill(' ') << setw(45) << "Rate per hour: ";
    cin >> cars[currentSize].ratePerHour;

    cout << setfill(' ') << setw(45) << "Saved successfully." << endl;
    currentSize++;
    Sleep(1000);
    system("cls");
    adminMenu(isAdmin, currentSize);
}

//Function to conduct linear search for car plate number
int linearSearch(int &currentSize) {

    cout << right << setfill(' ') << setw(55) << "Enter car plate number: ";
    getline(cin, cars[currentSize].carPlate);;

    for (int i = 0; i < currentSize; i++) {

        //If found return the index number
        if (cars[currentSize].carPlate == cars[i].carPlate) {
            return i;
        }

    }
    //If not found return -1
    return -1;
}

//Function to validate linear search and loop while element is not found
int checkLinearSearch(bool &isAdmin, int &currentSize) {

    cin.ignore(100, '\n');
    int index;
    bool isFound = false;

    //Loop while the car plate number input is not found and break when it is found and return its index
    do {
        index = linearSearch(currentSize);

        if (index == -1) {
            cout << setfill(' ') << setw(55) << "Element not found.";
            isFound = false;
            system("cls");
            displayData(isAdmin,currentSize);
        }
        else {
            isFound = true;
            break;
        }
    } while (!isFound);

    return index;
}

//Function to display update car menu
void updateCar(bool &isAdmin, int &currentSize) {

    int choice;

    while (true) {
        spacing();
        cout << setfill(' ') << setw(55) << "CAR RENTAL SYSTEM" << endl;
        cout << endl;
        cout << setfill(' ') << setw(40) << "1." << "Update car plate" << endl;
        cout << setfill(' ') << setw(40) << "2." << "Update car brand" << endl;
        cout << setfill(' ') << setw(40) << "3." << "Update car model" << endl;
        cout << setfill(' ') << setw(40) << "4." << "Update car colour" << endl;
        cout << setfill(' ') << setw(40) << "5." << "Update car capacity" << endl;
        cout << setfill(' ') << setw(40) << "6." << "Update car rate: " << endl;
        cout << endl;
        cout << setfill(' ') << setw(57) << "Enter your choice: ";
        cin >> choice;

        //check if input is integer
        if (!cin.fail()) {
            if (choice >= 1 && choice <= 6) { //if input is within 1 to 6
                break;
            }
            else {
                cout << setfill(' ') << setw(65) << "You have entered wrong input.";
                Sleep(1000);
                system("cls");
                continue;
            }
        }

        //if input is not integer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << setfill(' ') << setw(65) << "You have entered wrong input.";
            Sleep(1000);
            system("cls");
            continue;
        }
    }
    system("cls");
    updateCar(choice, isAdmin, currentSize);
}

//Function to get updated car details
void updateCar(int choice, bool &isAdmin, int &currentSize) {

    displayData(isAdmin, currentSize);

    int index = checkLinearSearch(isAdmin, currentSize);
    if (choice == 1) {
        cout << setfill(' ') << setw(55) << "New car plate number: ";
        getline(cin, cars[index].carPlate);
    }
    else if (choice == 2) {
        cout << setfill(' ') << setw(55) << "New brand: ";
        getline(cin, cars[index].brand);
    }
    else if (choice == 3) {
        cout << setfill(' ') << setw(55) << "New model: ";
        getline(cin, cars[index].model);
    }
    else if (choice == 4) {
        cout << setfill(' ') << setw(55) << "New colour: ";
        getline(cin, cars[index].colour);
    }
    else if (choice == 5) {
        cout << setfill(' ') << setw(55) << "New capacity: ";
        cin >> cars[index].capacity;
    }
    else {
        cout << setfill(' ') << setw(55) << "New rate: ";
        cin >> cars[index].ratePerHour;
    }
    cout << setfill(' ') << setw(55) << "Updated successfully." << endl;

    Sleep(1000);
    system("cls");
    adminMenu(isAdmin, currentSize);
}

//Function to delete car
void deleteCar(bool &isAdmin, int &currentSize) {

    displayData(isAdmin, currentSize);
    cout << "\n\n";

    int index = checkLinearSearch(isAdmin, currentSize);

    for (int i = index; i < currentSize - 1; i++) {
        cars[i] = cars[i + 1];
    }
    cout << setfill(' ') << setw(55) << "Deleted successfully." << endl;
    currentSize -= 1;
    Sleep(1000);
    system("cls");
    adminMenu(isAdmin, currentSize);
}

//Function to display menu for functions accessible to customer
void customerMenu(char* username, int size, bool &isAdmin,int &currentSize) {

    int choice;

    while (true) {
        spacing();
        cout << setfill(' ') << setw(55) << "CAR RENTAL SYSTEM" << endl;
        cout << endl;
        cout << right << setfill(' ') << setw(40) << "1." << "Rent car" << endl;
        cout << right << setfill(' ') << setw(40) << "2." << "View rental record" << endl;
        cout << right << setfill(' ') << setw(40) << "3." << "Logout" << endl;
        cout << endl;
        cout << setfill(' ') << setw(55) << "Enter your choice: ";
        cin >> choice;

        //check if input is integer
        if (!cin.fail()) {
            if (choice >= 1 && choice <= 3) { //if input is within 1 to 3
                break;
            }
            else {
                cout << setfill(' ') << setw(65) << "You have entered wrong input.";
                Sleep(1000);
                system("cls");
                continue;
            }
        }

        //if input is not integer
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << setfill(' ') << setw(65) << "You have entered wrong input.";
            Sleep(1000);
            system("cls");
            continue;
        }
    }

    system("cls");

    switch (choice) {
    case 1:
        rentCar(username,50,isAdmin, currentSize);
        break;
    case 2:
        rentalRecord(username,50,isAdmin, currentSize);
        break;
    case 3:
        mainMenu(currentSize);
        break;
    }
}

//Function to allow customer to rent cars
void rentCar(char* username, int size, bool &isAdmin, int &currentSize) {

    displayData(isAdmin, currentSize);
    int index = checkLinearSearch(isAdmin, currentSize);
    double hours, rate;

    cout << setfill(' ') << setw(55) << "Duration of rental (hours): ";
    cin >> hours;
    cars[index].rentedBy = username;
    cout << setfill(' ') << setw(55) << "Rented successfully." << endl;
    rate = cars[index].ratePerHour;

    Sleep(1000);
    system("cls");
    showInvoice(rate, hours, index, username,50, isAdmin, currentSize);
}

//Function to show invoice after customer rents car successfully
void showInvoice(double rate, double hours, int index, char* username, int size, bool& isAdmin, int &currentSize) {

    spacing();
    double total = 0.0;
    total = rate * hours;

    cout << setfill(' ') << setw(55) << "CAR RENTAL SYSTEM" << endl;
    cout << endl;
    cout << setfill(' ') << setw(50) << "Customer name: " << username << endl;
    cout << setfill(' ') << setw(50) << "Car plate no: " << cars[index].carPlate << endl;
    cout << setfill(' ') << setw(50) << "Car model: " << cars[index].model << endl;
    cout << setfill(' ') << setw(50) << "Rental rate: " << cars[index].ratePerHour << endl;
    cout << setfill(' ') << setw(50) << "Hours rented: " << hours << endl;
    cout << setfill(' ') << setw(50) << "-------------------------- " << endl;
    cout << setfill(' ') << setw(50) << "Total rental amount: " << total << endl;
    cout << setfill(' ') << setw(50) << "-------------------------- " << endl;
    cout << setfill(' ') << setw(90) << "# This is a computer generated invoice, it does not require an authorised signature #" << endl;

    system("pause");
    system("cls");
    customerMenu(username,50, isAdmin, currentSize);
}

//Function to show customer their rental record
void rentalRecord(char* username, int size, bool& isAdmin, int &currentSize) {

    spacing();
    for (int i = 0; i < currentSize; i++) {
        if (cars[i].rentedBy == username) {
            cout << "Car plate" << setw(8) << "Brand" << setw(10) << "Model" << setw(10)
                << "Colour" << setw(12) << "Capacity" << setw(15) << "Rate per hour" << endl;
            cout << left << setw(12) << cars[i].carPlate << left << setw(10) << cars[i].brand << left << setw(9) << cars[i].model << left
                << setw(10) << cars[i].colour << left << setw(12) << cars[i].capacity << left << setw(15) << cars[i].ratePerHour << endl;
        }
    }

    system("pause");
    system("cls");
    customerMenu(username, 50, isAdmin, currentSize);
}

//Function to display terms and conditions for car rental
void termsAndConditions(int &currentSize) {

    spacing();
    cout << setfill(' ') << setw(55) << "Terms & Conditions" << endl;
    cout << endl;
    cout << setfill(' ') << setw(30) << "1." << "No minimum rent" << endl;
    cout << setfill(' ') << setw(30) << "2." << "In cases of accidents, all costing" << endl;
    cout << setfill(' ') << setw(30) << "  " << "is paid by the driver" << endl;
    cout << setfill(' ') << setw(30) << "3." << "Prepare items below to make car rental booking" << endl;
    cout << setfill(' ') << setw(32) << "a)" << "Copy of IC and car license" << endl;
    cout << setfill(' ') << setw(32) << "b)" << "Deposit amount(Based on car type)" << endl;
    cout << setfill(' ') << setw(30) << "4." << "Safe drive" << endl;
    cout << "\n\n" << endl;

    system("pause");
    mainMenu(currentSize);
}

//Function to create 10 line spacings from the top before outputs are displayed
void spacing() {

    for (int i = 0; i < 10; i++) {
        cout << endl;
    }
}