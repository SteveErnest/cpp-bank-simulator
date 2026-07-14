#include "BankSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

double getValidDouble() {
    double value;
    while (true) {
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        } else {
            std::cout << "Error: Invalid input! Please enter a valid number: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void BankSystem::loadAccountsFromFile() {
    accounts.clear();
    std::ifstream inFile(filename);
    if (!inFile) return; 

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;
        
        std::stringstream ss(line);
        std::string indexStr, accNum, name, balStr;
        
        std::getline(ss, indexStr, ',');
        std::getline(ss, accNum, ',');
        std::getline(ss, name, ',');
        std::getline(ss, balStr, ',');

        if (!accNum.empty() && !name.empty()) {
            double bal = std::stod(balStr);
            accounts.push_back(Account(accNum, name, bal));
        }
    }
    inFile.close();
}

void BankSystem::saveAccountsToFile() {
    std::ofstream outFile(filename, std::ios::trunc); 
    if (!outFile) {
        std::cout << "Critical Error: Could not write to database file!\n";
        return;
    }

    for (size_t i = 0; i < accounts.size(); ++i) {
        outFile << (i + 1) << "," 
                << accounts[i].getAccountNumber() << "," 
                << accounts[i].getAccountHolderName() << "," 
                << accounts[i].getBalance() << "\n";
    }
    outFile.close();
}

void BankSystem::adminAddAccount() {
    std::string name;
    double initialBalance;
    std::cout << "\n--- [Admin] Create New Account ---\n";
    std::cout << "Enter Customer Full Name: ";
    std::getline(std::cin, name);
    std::cout << "Enter Initial Deposit Balance: ";
    initialBalance = getValidDouble();

    Account newAcc(name, initialBalance);
    accounts.push_back(newAcc);
    saveAccountsToFile(); 
    
    std::cout << "\u2514\u2500 Success! Account created at Index [" << accounts.size() << "]\n";
}

void BankSystem::adminRemoveAccount() {
    if (accounts.empty()) {
        std::cout << "No accounts available to remove.\n";
        return;
    }

    adminViewAllAccounts();
    std::cout << "\nEnter the Index number of the account you want to REMOVE: ";
    int targetIdx = static_cast<int>(getValidDouble());

    if (targetIdx < 1 || targetIdx > static_cast<int>(accounts.size())) {
        std::cout << "Error: Invalid index selection.\n";
        return;
    }

    std::string removedName = accounts[targetIdx - 1].getAccountHolderName();
    accounts.erase(accounts.begin() + (targetIdx - 1));
    
    saveAccountsToFile();
    std::cout << "Successfully removed " << removedName << ". Remaining index count shifted.\n";
}

void BankSystem::adminViewAllAccounts() {
    std::cout << "\n=========================================\n";
    std::cout << "        SYSTEM ACCOUNT DATABASE REGISTRY  \n";
    std::cout << "=========================================\n";
    if (accounts.empty()) {
        std::cout << " [Empty Registry - No Accounts Found] \n";
        return;
    }

    for (size_t i = 0; i < accounts.size(); ++i) {
        std::cout << "Index [" << (i + 1) << "] -> ";
        accounts[i].displayDetails();
    }
    std::cout << "=========================================\n";
    std::cout << "Total Active Accounts Registered: " << accounts.size() << "\n";
}

Account* BankSystem::getAccountRef(size_t index) {
    if (index > 0 && index <= accounts.size()) {
        return &accounts[index - 1];
    }
    return nullptr;
}

size_t BankSystem::getSystemSize() const { return accounts.size(); }