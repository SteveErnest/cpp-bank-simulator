#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

class Account {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

    std::string generateAccountNumber();

public:
    // Regular Constructor
    Account(std::string name, double initialBalance);

    // File-load Constructor
    Account(std::string accNum, std::string name, double bal);

    // Getters
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;

    // Core Actions
    void deposit(double amount);
    bool withdraw(double amount);
    void displayDetails() const;
};

#endif // ACCOUNT_H