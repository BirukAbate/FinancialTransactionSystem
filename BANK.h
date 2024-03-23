//
// Created by Biruk Abate on 21/08/23.
//
#ifndef FINANCIALTRANSACTIONSYSTEM_BANK_H
#define FINANCIALTRANSACTIONSYSTEM_BANK_H

#include <vector>
#include <string>

class Bank {

private:
    class Transaction {
    private:
        std::string name;
        std::string date;
        double amount;

    public:
        Transaction(const std::string& name, double amount, const std::string& date)
                : name(name), amount(amount), date(date) {
            if (name.empty() || amount == 0.0 || date.empty()) {
                throw std::invalid_argument("name, amount and date must be provided.");
            }

            std::tm parsedDate = {}; // Struttura per conservare la data

            if (std::sscanf(date.c_str(), "%d-%d-%d", &parsedDate.tm_year, &parsedDate.tm_mon, &parsedDate.tm_mday) != 3) {
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
        }




        std::string getName() const {
            return name;
        }

        void setName(const std::string& newName) {
            name = newName;
        }

        std::string getDate() const {
            return date;
        }

        void setDate(const std::string& newDate) {
            date = newDate;
        }

        double getAmount() const {
            return amount;
        }

        void setAmount(double newAmount) {
            amount = newAmount;
        }
    };

    std::vector<Transaction> transactions;
    double currentBalance = 0;

public:
    double getCurrentBalance() const {
        return currentBalance;
    };
    int getTotalTransactions() const {
        return transactions.size();
    }

    void addTransaction(const std::string& name, double amount, const std::string& date);
    void displayTransactions() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    bool deleteTransaction(int index);
    void editTransaction(int index, const std::string& newName, double newAmount, const std::string& newDate);
    void searchByName(const std::string& name) const;
    void searchByDate(const std::string& date) const;

};

#endif //FINANCIALTRANSACTIONSYSTEM_BANK_H


