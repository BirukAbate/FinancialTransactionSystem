//
// Created by Biruk Abate
//

#include "BANK.h"

#include <iostream>
#include <fstream>


void Bank::addTransaction(const std::string &name, double amount, const std::string &date) {

    Transaction transaction(name, amount, date);
    transactions.push_back(transaction);
    currentBalance += amount;
}

void Bank::displayTransactions() const {
    for (size_t i = 0; i < transactions.size(); ++i) {
        const auto& transaction = transactions[i];
        std::cout << "Index: " << i << " Name: " << transaction.getName() << " Amount: " << transaction.getAmount() << " Date: " << transaction.getDate() << std::endl;
    }
    std::cout << "Total transactions: " << transactions.size() << std::endl;
}

void Bank::loadFromFile(const std::string &filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string name;
        double amount;
        std::string date;
        while (inFile >> name >> amount >> date) {
            Transaction transaction(name, amount, date);
            transactions.push_back(transaction);
            currentBalance += amount;
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
            outFile << transaction.getName() << " " << transaction.getAmount() << " " << transaction.getDate() << std::endl;
        }
        outFile.close();
        std::cout << "Transactions saved to " << filename << std::endl;
    } else {
        std::cerr << "Error opening file for writing." << std::endl;
    }
}


void Bank::editTransaction(int index, const std::string &newName, double newAmount, const std::string &newDate) {
    if (index < 0 || index >= transactions.size()) {
        throw std::out_of_range("Index out of range.");
    }
    if (newAmount == 0.0) {
        throw std::invalid_argument("Amount cannot be zero");
    }

    /*if (!validateDate(newDate)) {
        throw std::invalid_argument("Invalid date format");
    }
     */

    std::tm parsedDate = {}; // Struttura per conservare la data

    if (std::sscanf(newDate.c_str(), "%d-%d-%d", &parsedDate.tm_year, &parsedDate.tm_mon, &parsedDate.tm_mday) != 3) {
        throw std::invalid_argument("Invalid date format");
    }

    parsedDate.tm_year -= 1900; // Adeguare l'anno
    parsedDate.tm_mon -= 1;
    // Ottenere l'orario corrente
    std::time_t currentTime = std::time(nullptr);
    std::tm currentTM = *std::localtime(&currentTime);

    if (parsedDate.tm_year < 0 || parsedDate.tm_mon < 0 || parsedDate.tm_mon > 11 || parsedDate.tm_mday < 1 || parsedDate.tm_mday > 31) {
        throw std::invalid_argument("Invalid date format");
    }
    // Confrontare la data inserita con l'orario corrente
    if (std::mktime(&parsedDate) > std::mktime(&currentTM)) {
        throw std::invalid_argument("Invalid date format");
    }

    currentBalance = currentBalance + newAmount - transactions[index].getAmount();
    transactions[index].setName(newName);
    transactions[index].setAmount(newAmount);
    transactions[index].setDate(newDate);

    std::cout << "Transaction at index " << index << " edited successfully." << std::endl;
}

bool Bank::deleteTransaction(int index) {
    if (index < 0 || index >= transactions.size()) {
        std::cerr << "Invalid index for transaction deletion." << std::endl;
        return false;
    }
    currentBalance = currentBalance - transactions[index].getAmount();
    transactions.erase(transactions.begin() + index);

    std::cout << "Transaction at index " << index << " deleted successfully." << std::endl;
    return true;
}

void Bank::searchByDate(const std::string &date) {
    bool found = false;
    for (const auto& transaction : transactions) {
        if (transaction.getDate() == date) {
            std::cout << "Name: " << transaction.getName() << " Amount: " << transaction.getAmount() << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No transactions found for date: " << date << std::endl;
    }
}

void Bank::searchByName(const std::string &name) {
    bool found = false;
    for (const auto& transaction : transactions) {
        if (transaction.getName() == name) {
            std::cout << "Date: " << transaction.getDate() << " Amount: " << transaction.getAmount() << std::endl;
            found = true;
        }
    }
    if (!found) {
        std::cout << "No transactions found for name: " << name << std::endl;
    }
}

