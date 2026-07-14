#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include "Account.h"
#include <vector>
#include <string>

class BankSystem {
private:
    std::vector<Account> accounts;
    const std::string filename = "accounts.txt";

public:
    void loadAccountsFromFile();
    void saveAccountsToFile();
    
    void adminAddAccount();
    void adminRemoveAccount();
    void adminViewAllAccounts();

    Account* getAccountRef(size_t index);
    size_t getSystemSize() const;
};

// Global input verification helper declaration
double getValidDouble();

#endif // BANKSYSTEM_H