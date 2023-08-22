#include <iostream>

using namespace std;
#include "BANK.h"

int main() {
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


/*int main(){

        Bank bank;
        bank.loadFromFile("transactions.txt");
        bank.addTransaction(100.0, "2023-08-01");
        bank.addTransaction(-50.0, "2023-08-02");
        bank.addTransaction(200.0, "2023-08-03");

        std::cout << "Transactions after adding:" << std::endl;
        bank.displayTransactions();
        cout<<endl;
        double balance = bank.calculateBalance();
        std::cout << "Balance after adding: " << balance << std::endl;

        bank.saveToFile("transactions.txt");
        std::cout << "Transactions saved to file." << std::endl;

        bank.addTransaction(-30.0, "2023-08-04");
        std::cout << "Transactions after adding another:" << std::endl;
        bank.saveToFile("transactions.txt");
        std::cout << "Transactions saved to file." << std::endl;

        bank.displayTransactions();

        balance = bank.calculateBalance();
        std::cout << "Balance after adding another: " << balance << std::endl;


        bank.displayTransactions();

        balance = bank.calculateBalance();
        std::cout << "Balance after loading: " << balance << std::endl;

        return 0;
    }
*/
