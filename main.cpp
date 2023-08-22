#include <iostream>

using namespace std;
#include "BANK.h"

/*int main() {
    Bank bank;

    bank.loadFromFile("transactions.txt"); // Carica prima di visualizzare

    int choice;
    bool exit = false;

    while (!exit) {
        std::cout << "Bank Menu:" << std::endl;
        std::cout << "1. Add Transaction" << std::endl;
        std::cout << "2. Display Transactions" << std::endl;
        std::cout << "3. Calculate Balance" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                double amount;
                std::string date;
                std::cout << "Enter amount: ";
                std::cin >> amount;
                std::cout << "Enter date: ";
                std::cin >> date;
                bank.addTransaction(amount, date);
                bank.saveToFile("transactions.txt"); // Aggiungi al salvataggio
                break;
            }
            case 2:
                bank.displayTransactions();
                break;
            case 3: {
                double balance = bank.calculateBalance();
                std::cout << "Balance: " << balance << std::endl;
                break;
            }
            case 4:
                exit = true;
                break;
            default:
                std::cout << "Invalid choice." << std::endl;
        }
    }

    return 0;
}
*/


