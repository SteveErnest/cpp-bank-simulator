<<<<<<< HEAD
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
=======

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

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std;

// --- Account Class ---
class Account
{
private:
    string accountNumber;
    string accountHolderName;
    double balance;

    string generateAccountNumber()
    {
        string accNum = "";
        for (int i = 0; i < 8; ++i)
        {
            accNum += to_string(rand() % 10);
        }
        return accNum;
    }

public:
    // Regular Constructor
    Account(string name, double initialBalance)
    {
        accountHolderName = name;
        accountNumber = generateAccountNumber();
        balance = (initialBalance >= 0.0) ? initialBalance : 0.0;
    }

    // Constructor used when loading existing data from the text file
    Account(string accNum, string name, double bal)
    {
        accountNumber = accNum;
        accountHolderName = name;
        balance = bal;
    }

    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Successfully deposited $" << amount << " to Account " << accountNumber << "\n";
        }
        else
        {
            cout << "Error: Deposit amount must be positive!\n";
        }
    }

    bool withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Error: Withdrawal amount must be positive!\n";
            return false;
        }
        else if (amount > balance)
        {
            cout << "Error: Insufficient funds!\n";
            return false;
        }
        else
        {
            balance -= amount;
            cout << "Successfully withdrew $" << amount << " from Account " << accountNumber << "\n";
            return true;
        }
    }

    void displayDetails() const
    {
        cout << "Account Holder : " << accountHolderName << " | Acc #: " << accountNumber << " | Balance: $" << balance << "\n";
    }
};

// --- Input Validation Helper ---
double getValidDouble()
{
    double value;
    while (true)
    {
        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear trailing newlines
            return value;
        }
        else
        {
            cout << "Error: Invalid input! Please enter a valid number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// --- Bank System Manager (Handles File Database & Admin Features) ---
class BankSystem
{
private:
    vector<Account> accounts;
    const string filename = "accounts.txt";

public:
    // Load accounts from text file on startup
    void loadAccountsFromFile()
    {
        accounts.clear();
        ifstream inFile(filename);
        if (!inFile)
            return; // File doesn't exist yet, which is fine

        string line;
        while (getline(inFile, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);
            string indexStr, accNum, name, balStr;

            // Parse custom text database layout: Index | AccNum | Name | Balance
            getline(ss, indexStr, ',');
            getline(ss, accNum, ',');
            getline(ss, name, ',');
            getline(ss, balStr, ',');

            if (!accNum.empty() && !name.empty())
            {
                double bal = stod(balStr);
                accounts.push_back(Account(accNum, name, bal));
            }
        }
        inFile.close();
    }

    // Save/Sync dynamic array changes back to accounts.txt
    void saveAccountsToFile()
    {
        ofstream outFile(filename, ios::trunc); // Overwrite with fresh index alignment
        if (!outFile)
        {
            cout << "Critical Error: Could not write to database file!\n";
            return;
        }

        // The index increments dynamically based on its position in the loop
        for (size_t i = 0; i < accounts.size(); ++i)
        {
            outFile << (i + 1) << ","
                    << accounts[i].getAccountNumber() << ","
                    << accounts[i].getAccountHolderName() << ","
                    << accounts[i].getBalance() << "\n";
        }
        outFile.close();
    }

    // Admin Feature: Add Account
    void adminAddAccount()
    {
        string name;
        double initialBalance;
        cout << "\n--- [Admin] Create New Account ---\n";
        cout << "Enter Customer Full Name: ";
        getline(cin, name);
        cout << "Enter Initial Deposit Balance: ";
        initialBalance = getValidDouble();

        Account newAcc(name, initialBalance);
        accounts.push_back(newAcc);
        saveAccountsToFile(); // Sync file system

        cout << "🎉 Success! Account created at Index [" << accounts.size() << "]\n";
    }

    // Admin Feature: Remove Account (Decrements index automatically)
    void adminRemoveAccount()
    {
        if (accounts.empty())
        {
            cout << "No accounts available to remove.\n";
            return;
        }

        adminViewAllAccounts();
        cout << "\nEnter the Index number of the account you want to REMOVE: ";
        int targetIdx = static_cast<int>(getValidDouble());

        if (targetIdx < 1 || targetIdx > static_cast<int>(accounts.size()))
        {
            cout << "❌ Error: Invalid index selection.\n";
            return;
        }

        // Remove element from vector (translates 1-based index to 0-based vector index)
        string removedName = accounts[targetIdx - 1].getAccountHolderName();
        accounts.erase(accounts.begin() + (targetIdx - 1));

        // Re-write database file to naturally shift indices downwards
        saveAccountsToFile();
        cout << "🗑️ Successfully removed " << removedName << ". Remaining index count shifted.\n";
    }

    // Admin Feature: View All Records
    void adminViewAllAccounts()
    {
        cout << "\n=========================================\n";
        cout << "       SYSTEM ACCOUNT DATABASE REGISTRY  \n";
        cout << "=========================================\n";
        if (accounts.empty())
        {
            cout << " [Empty Registry - No Accounts Found] \n";
            return;
        }

        for (size_t i = 0; i < accounts.size(); ++i)
        {
            cout << "Index [" << (i + 1) << "] -> ";
            accounts[i].displayDetails();
        }
        cout << "=========================================\n";
        cout << "Total Active Accounts Registered: " << accounts.size() << "\n";
    }

    // Helper to find account by index pointer safely for standard workflows
    Account *getAccountRef(size_t index)
    {
        if (index > 0 && index <= accounts.size())
        {
            return &accounts[index - 1];
        }
        return nullptr;
    }

    size_t getSystemSize() const { return accounts.size(); }
};

// --- Main Program Workflow ---
int main()
{
    srand(time(0));
    BankSystem bank;
    bank.loadAccountsFromFile(); // Hydrate the storage array from text file

    const string ADMIN_USER = "admin";
    const string ADMIN_PASS = "admin123";

    int identityChoice = 0;

    cout << "=== Welcome to the Automated Secure Banking Hub ===\n";
    cout << "Select Portal Access Mode:\n";
    cout << "1. Administrator Portal\n";
    cout << "2. General Customer Simulation\n";
    cout << "Enter choice: ";
    identityChoice = static_cast<int>(getValidDouble());

    if (identityChoice == 1)
    {
        // --- ADMIN SYSTEM RUNTIME ---
        string user, pass;
        cout << "\n--- Secure Admin Verification Required ---\n";
        cout << "Username: ";
        cin >> user;
        cout << "Password: ";
        cin >> pass;

        if (user == ADMIN_USER && pass == ADMIN_PASS)
        {
            int adminChoice = 0;
            do
            {
                cout << "\n=== 🛠️ Administrator Management Panel ===\n";
                cout << "1. View All Registered Accounts (With Auto-Index)\n";
                cout << "2. Add New Account (Increments Index)\n";
                cout << "3. Remove Existing Account (Decrements Index)\n";
                cout << "4. Exit Terminal\n";
                cout << "Enter Action: ";
                adminChoice = static_cast<int>(getValidDouble());

                switch (adminChoice)
                {
                case 1:
                    bank.adminViewAllAccounts();
                    break;
                case 2:
                    bank.adminAddAccount();
                    break;
                case 3:
                    bank.adminRemoveAccount();
                    break;
                case 4:
                    cout << "Closing Admin session. System states safely exported.\n";
                    break;
                default:
                    cout << "Invalid Option selected.\n";
                }
            } while (adminChoice != 4);
        }
        else
        {
            cout << "❌ Authentication Failed! Unauthorized terminal shutdown.\n";
        }
    }
    else
    {
        // --- CUSTOMER PORTAL DEMO ---
        if (bank.getSystemSize() == 0)
        {
            cout << "\nNotice: No database records found. Let's register a default user first.\n";
>>>>>>> 23c2fb4ef50aaf6197b589c0dd693206ae70d585
            bank.adminAddAccount();
        }

        int choice = 0;
<<<<<<< HEAD
        do {
            std::cout << "\n=== Interactive User Banking Menu ===\n";
            std::cout << "1. Deposit Funds (Modifies First Database Record)\n";
            std::cout << "2. Display My Account Info\n";
            std::cout << "3. Exit System\n";
            std::cout << "Enter option: ";
            choice = static_cast<int>(getValidDouble());

            Account* primaryUser = bank.getAccountRef(1); 

            switch (choice) {
                case 1: {
                    if (primaryUser) {
                        std::cout << "Enter amount to deposit: ";
                        double amt = getValidDouble();
                        primaryUser->deposit(amt);
                        bank.saveAccountsToFile(); 
                    }
                    break;
                }
                case 2:
                    if (primaryUser) {
                        std::cout << "\n--- Your Account Details ---\n";
                        primaryUser->displayDetails();
                    }
                    break;
                case 3:
                    std::cout << "Thank you for using our system. Goodbye!\n";
                    break;
                default:
                    std::cout << "Invalid choice.\n";
=======
        do
        {
            cout << "\n=== Interactive User Banking Menu ===\n";
            cout << "1. Deposit Funds (Modifies First Database Record)\n";
            cout << "2. Display My Account Info\n";
            cout << "3. Exit System\n";
            cout << "Enter option: ";
            choice = static_cast<int>(getValidDouble());

            Account *primaryUser = bank.getAccountRef(1); // Interact with first indexed account

            switch (choice)
            {
            case 1:
            {
                if (primaryUser)
                {
                    cout << "Enter amount to deposit: ";
                    double amt = getValidDouble();
                    primaryUser->deposit(amt);
                    bank.saveAccountsToFile(); // Save balance change back to txt file
                }
                break;
            }
            case 2:
                if (primaryUser)
                {
                    cout << "\n--- Your Account Details ---\n";
                    primaryUser->displayDetails();
                }
                break;
            case 3:
                cout << "Thank you for using our system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice.\n";
>>>>>>> 23c2fb4ef50aaf6197b589c0dd693206ae70d585
            }
        } while (choice != 3);
    }

    return 0;
<<<<<<< HEAD
}
=======
}
>>>>>>> 23c2fb4ef50aaf6197b589c0dd693206ae70d585
