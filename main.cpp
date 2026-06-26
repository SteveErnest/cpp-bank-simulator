
// TODO: Create a Account class with the following attributes: account number,
// account holder name, and balance. Implement methods to deposit and withdraw money,
// as well as a method to display account details.

// Class account should have encapsulation, with private member variables and public methods
// to access and modify them. The deposit method should add a specified amount to the balance,
// while the withdraw method should subtract a specified amount from the balance,
// ensuring that the balance does not go negative. The display method should print the account
// number, account holder name, and current balance.

#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <cstdlib>
#include <ctime>

using namespace std; // Global namespace directive

class Account {
private:
    string accountNumber;
    string accountHolderName;
    double balance;

    // Helper to generate a random 8-digit account number string
    string generateAccountNumber() {
        string accNum = "";
        for (int i = 0; i < 8; ++i) {
            accNum += to_string(rand() % 10);
        }
        return accNum;
    }

public:
    // Constructor
    Account(string name, double initialBalance) {
        accountHolderName = name;
        accountNumber = generateAccountNumber();
        
        if (initialBalance >= 0.0) {
            balance = initialBalance;
        } else {
            balance = 0.0;
            cout << "Notice: Initial balance cannot be negative. Set to $0.0.\n";
        }
    }

    // Getters
    string getAccountNumber() const { return accountNumber; }
    string getAccountHolderName() const { return accountHolderName; }
    double getBalance() const { return balance; }

    // Deposit method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Successfully deposited $" << amount << " to Account " << accountNumber << "\n";
        } else {
            cout << "Error: Deposit amount must be positive!\n";
        }
    }

    // Withdraw method with safety check
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Error: Withdrawal amount must be positive!\n";
            return false;
        } else if (amount > balance) {
            cout << "Error: Insufficient funds! Withdrawal denied.\n";
            return false;
        } else {
            balance -= amount;
            cout << "Successfully withdrew $" << amount << " from Account " << accountNumber << "\n";
            return true;
        }
    }

    // Simplified Transfer Method: No pointers, no references, no "this->"
    // It only handles withdrawing from the current account.
    bool transferOut(double amount) {
        cout << "\nInitiating transfer of $" << amount << "...\n";
        
        if (withdraw(amount)) {
            return true;
        } else {
            cout << "Transfer failed due to underlying account restrictions.\n";
            return false;
        }
    }

    // Display account details
    void displayDetails() const {
        cout << "\n--- Account Details ---" << "\n";
        cout << "Account Holder : " << accountHolderName << "\n";
        cout << "Account Number : " << accountNumber << "\n";
        cout << "Current Balance: $" << balance << "\n";
        cout << "-----------------------\n";
    }
};

// --- Helper Functions ---

// Simplified password strength checker (Only checks length now)
bool isPasswordStrong(string password) {
    if (password.length() >= 8) {
        return true;
    }

    cout << "\n❌ Weak Password! It must be at least 8 characters long.\n\n";
    return false;
}

// Robust input validation helper for doubles
double getValidDouble() {
    double value;
    while (true) {
        if (cin >> value) {
            return value;
        } else {
            cout << "Error: Invalid input! Please enter a valid number: ";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }
    }
}

int main(int argc, char *argv[]) {
    srand(time(0)); 

    string name, password;
    double initialBalance;

    cout << "=== Welcome to the Automated Banking Registration ===\n";
    cout << "Enter Account Holder Full Name: ";
    getline(cin, name);

    // Registration Loop for Password Strength
    do {
        cout << "Set a strong account password: ";
        cin >> password;
    } while (!isPasswordStrong(password));

    cout << "✔ Password accepted.\n";
    cout << "Enter Initial Deposit Balance: ";
    initialBalance = getValidDouble();

    // Create primary user account
    Account userAccount(name, initialBalance);
    cout << "\n🎉 Account created successfully!";
    userAccount.displayDetails();

    // Create a dummy secondary account for testing transfers
    Account testAccount("Ayesha (External Savings)", 500.00);
    cout << "Notice: A secondary default account was auto-generated for testing wire transfers:\n";
    cout << " * Target Name: " << testAccount.getAccountHolderName() << "\n";
    cout << " * Target Account #: " << testAccount.getAccountNumber() << "\n";

    int choice = 0;
    do {
        cout << "\n=== Interactive Banking Menu ===\n";
        cout << "1. Deposit Funds\n";
        cout << "2. Withdraw Funds\n";
        cout << "3. Secure Fund Transfer\n";
        cout << "4. Display Account Information\n";
        cout << "5. Exit\n";
        cout << "Enter option: ";
        
        double choiceInput = getValidDouble();
        choice = static_cast<int>(choiceInput);

        switch (choice) {
            case 1: {
                cout << "Enter amount to deposit: ";
                double amt = getValidDouble();
                userAccount.deposit(amt);
                break;
            }
            case 2: {
                cout << "Enter amount to withdraw: ";
                double amt = getValidDouble();
                userAccount.withdraw(amt);
                break;
            }
            case 3: {
                cout << "Enter transfer amount to send to " << testAccount.getAccountHolderName() << ": ";
                double amt = getValidDouble();
                
                // If the withdrawal succeeds from the sender, deposit directly into the recipient
                if (userAccount.transferOut(amt)) {
                    testAccount.deposit(amt);
                    cout << "Transfer complete!\n";
                }
                break;
            }
            case 4:
                userAccount.displayDetails();
                cout << "Secondary Test Account Status: Balance is $" << testAccount.getBalance() << "\n";
                break;
            case 5:
                cout << "Thank you for banking with us. Goodbye!\n";
                break;
            default:
                cout << "Invalid menu index selection. Range is [1-5].\n";
        }
    } while (choice != 5);

    return 0;
}
