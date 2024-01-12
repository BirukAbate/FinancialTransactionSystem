//
// Created by Biruk Abate on 21/08/23.
//

#include "BANK.h"

#include <iostream>
#include <fstream>
#include <ctime> // Per la manipolazione delle date e degli orari

bool Bank::isValidDate(const std::string& date) {
    std::tm parsedDate = {}; // Struttura per conservare la data

    if (std::sscanf(date.c_str(), "%d-%d-%d", &parsedDate.tm_year, &parsedDate.tm_mon, &parsedDate.tm_mday) != 3) {
        std::cerr << "Invalid date format: " << date << std::endl;
        return false;
    }

    parsedDate.tm_year -= 1900; // Adeguare l'anno
    parsedDate.tm_mon -= 1;
    // Ottenere l'orario corrente
    std::time_t currentTime = std::time(nullptr);
    std::tm currentTM = *std::localtime(&currentTime);

    // Confrontare la data inserita con l'orario corrente
    if (std::mktime(&parsedDate) > std::mktime(&currentTM)) {
        std::cerr << "Transaction date is in the future: " << date << std::endl;
        return false;
    }

    return true;
}


void Bank::addTransaction(const std::string &name, double amount, const std::string &date) {

    if (!isValidDate(date)) {
        return;
    }

    Transaction transaction;
    transaction.name = name;
    transaction.amount = amount;
    transaction.date = date;
    transactions.push_back(transaction);
    transactionCounter++;

}

void Bank::displayTransactions() const {
    for (size_t i = 0; i < transactions.size(); ++i) {
        const auto& transaction = transactions[i];
        std::cout << "Index: " << i << " Name: " << transaction.name << " Amount: " << transaction.amount << " Date: " << transaction.date << std::endl;
    }
    std::cout << "Total transactions: " << transactionCounter << std::endl;
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

void Bank::editTransaction(int index, const std::string &newName, double newAmount, const std::string &newDate) {
    if (index < 0 || index >= transactions.size()) {
        std::cerr << "Invalid index for transaction editing." << std::endl;
        return;
    }

    if (!isValidDate(newDate)) {
        std::cerr << "Invalid date format: " << newDate << ". Transaction not edited." << std::endl;
        return;
    }

    transactions[index].name = newName;
    transactions[index].amount = newAmount;
    transactions[index].date = newDate;

    std::cout << "Transaction at index " << index << " edited successfully." << std::endl;
}

void Bank::deleteTransaction(int index) {
    if (index < 0 || index >= transactions.size()) {
        std::cerr << "Invalid index for transaction deletion." << std::endl;
        return;
    }

    transactions.erase(transactions.begin() + index);
    transactionCounter--;

    std::cout << "Transaction at index " << index << " deleted successfully." << std::endl;
}