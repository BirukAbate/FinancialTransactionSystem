#include <iostream>

#include "Bank.h"

int main() {
    Bank bank;

    bank.addTransaction(100.0, "2023-08-18");
    bank.addTransaction(-50.0, "2023-08-19");

    bank.displayTransactions();
    bank.saveToFile("transaction.txt");
    bank.loadFromFile("transactions.txt");
    bank.displayTransactions();

    return 0;
}

