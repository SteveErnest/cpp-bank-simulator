#include "Account.h"
#include <iostream>
#include <cstdlib>

// Generates an 8-digit random account string
std::string Account::generateAccountNumber() {
    std::string accNum = "";
    for (int i = 0; i < 8; ++i) {
        accNum += std::to_string(std::rand() % 10);
    }
    return accNum;
}

Account::Account(std::string name, double initialBalance) {
    accountHolderName = name;
    accountNumber = generateAccountNumber();
    balance = (initialBalance >= 0.0) ? initialBalance : 0.0;
}

Account::Account(std::string accNum, std::string name, double bal) {
    accountNumber = accNum;
    accountHolderName = name;
    balance = bal;
}

std::string Account::getAccountNumber() const { return accountNumber; }
std::string Account::getAccountHolderName() const { return accountHolderName; }
double Account::getBalance() const { return balance; }

void Account::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
        std::cout << "Successfully deposited $" << amount << " to Account " << accountNumber << "\n";
    } else {
        std::cout << "Error: Deposit amount must be positive!\n";
    }
}

bool Account::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Error: Withdrawal amount must be positive!\n";
        return false;
    } else if (amount > balance) {
        std::cout << "Error: Insufficient funds!\n";
        return false;
    } else {
        balance -= amount;
        std::cout << "Successfully withdrew $" << amount << " from Account " << accountNumber << "\n";
        return true;
    }
}

void Account::displayDetails() const {
    std::cout << "Account Holder : " << accountHolderName << " | Acc #: " << accountNumber << " | Balance: $" << balance << "\n";
}