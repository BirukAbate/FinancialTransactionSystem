//
// Created by Biruk Abate on 21/08/23.
//

#include "BANK.h"

#include <iostream>
#include <fstream>

void Bank::addTransaction(double amount, const std::string &date) {

    Transaction transaction;
    transaction.amount = amount;
    transaction.date = date;
    transactions.push_back(transaction);

}

void Bank::displayTransactions() const {
    for (const auto& transaction : transactions) {
        std::cout << "Amount: " << transaction.amount << " Date: " << transaction.date << std::endl;
    }
}

void Bank::loadFromFile(const std::string &filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        double amount;
        std::string date;
        while (inFile >> amount >> date) {
            Transaction transaction;
            transaction.amount = amount;
            transaction.date = date;
            transactions.push_back(transaction);
        }
        inFile.close();
        std::cout << "Transactions loaded from " << filename << std::endl;
    } else {
        std::cerr << "Error opening file for reading." << std::endl;
    }
}

void Bank::saveToFile(const std::string &filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& transaction : transactions) {
            outFile << transaction.amount << " " << transaction.date << std::endl;
        }
        outFile.close();
        std::cout << "Transactions saved to " << filename << std::endl;
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
    }
}

double Bank::calculateBalance() const {
    double balance = 0.0;
    for (const Transaction& transaction : transactions) {
        balance += transaction.amount;
    }
    return balance;
}