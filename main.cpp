
#include "BankSystem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    BankSystem bank;
    bank.loadAccountsFromFile(); 

    const std::string ADMIN_USER = "admin";
    const std::string ADMIN_PASS = "admin123";

    int identityChoice = 0;
    
    std::cout << "=== Welcome to the Automated Secure Banking Hub ===\n";
    std::cout << "Select Portal Access Mode:\n";
    std::cout << "1. Administrator Portal\n";
    std::cout << "2. General Customer Simulation\n";
    std::cout << "Enter choice: ";
    identityChoice = static_cast<int>(getValidDouble());

    if (identityChoice == 1) {
        std::string user, pass;
        std::cout << "\n--- Secure Admin Verification Required ---\n";
        std::cout << "Username: ";
        std::cin >> user;
        std::cout << "Password: ";
        std::cin >> pass;

        if (user == ADMIN_USER && pass == ADMIN_PASS) {
            int adminChoice = 0;
            do {
                std::cout << "\n=== Management Panel ===\n";
                std::cout << "1. View All Registered Accounts\n";
                std::cout << "2. Add New Account\n";
                std::cout << "3. Remove Existing Account\n";
                std::cout << "4. Exit Terminal\n";
                std::cout << "Enter Action: ";
                adminChoice = static_cast<int>(getValidDouble());

                switch (adminChoice) {
                    case 1: bank.adminViewAllAccounts(); break;
                    case 2: bank.adminAddAccount(); break;
                    case 3: bank.adminRemoveAccount(); break;
                    case 4: std::cout << "Closing Admin session. System states safely exported.\n"; break;
                    default: std::cout << "Invalid Option selected.\n";
                }
            } while (adminChoice != 4);
        } else {
            std::cout << "Authentication Failed! Unauthorized terminal shutdown.\n";
        }
    } else {
        if (bank.getSystemSize() == 0) {
            std::cout << "\nNotice: No database records found. Let's register a default user first.\n";
        }

// TODO: Create a Account class with the following attributes: account number,
// account holder name, and balance. Implement methods to deposit and withdraw money,
// as well as a method to display account details.

// Class account should have encapsulation, with private member variables and public methods
// to access and modify them. The deposit method should add a specified amount to the balance,
// while the withdraw method should subtract a specified amount from the balance,
// ensuring that the balance does not go negative. The display method should print the account
// number, account holder name, and current balance.

// TODO: Create components to seperate classes and main.cpp. Files need to be modularized to separate the Account class,
// BankSystem class, and main program logic into different files. This will improve code organization and maintainability.


