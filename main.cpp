#include <iostream>

using namespace std;
#include "BANK.h"

int main() {
    Bank bank;

    bank.addTransaction(100.0, "2023-08-18");
    bank.addTransaction(-50.0, "2023-08-19");
    bank.displayTransactions();
    bank.saveToFile("transactions.txt");
    bank.loadFromFile("transactions.txt");
    bank.addTransaction(-34.57, "2023-08-19");
    cout<<"transaction from file"<<endl;
    bank.displayTransactions();
    double balance = bank.calculateBalance();
    std::cout << "Balance: " << balance << std::endl;

    return 0;
}

