//
// Created by Biruk Abate on 21/08/23.
//

#ifndef FINANCIALTRANSACTIONSYSTEM_BANK_H
#define FINANCIALTRANSACTIONSYSTEM_BANK_H

#endif //FINANCIALTRANSACTIONSYSTEM_BANK_H

#include <vector>
#include <string>
#include "TRANSACTION.h"

class Bank {

private:
    std::vector<Transaction> transactions;
    bool isValidDate(const std::string& date);
public:
    void addTransaction(double amount, const std::string& date);
    void displayTransactions() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    double calculateBalance() const;
    bool validateDate(const std::string& date){ // mi serve per eseguire le fasi di test
        return isValidDate(date);
    }

};


