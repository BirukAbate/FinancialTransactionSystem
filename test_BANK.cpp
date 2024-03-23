#include <gtest/gtest.h>
#include "BANK.h"

// Test fixture per la classe Bank
class BankTest : public ::testing::Test {
protected:
    Bank bank;

    void SetUp() override {
        // Inizializza lo stato prima di ogni test
    }

    void TearDown() override {
        // Pulizia dopo ogni test
    }
};

// Test caso per l'aggiunta di una singola transazione e il calcolo del saldo
TEST_F(BankTest, AddSingleTransactionAndCalculateBalance) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");

    double expectedBalance = 100.0;
    double actualBalance = bank.getCurrentBalance();

    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Test caso per l'aggiunta di più transazioni e il calcolo del saldo
TEST_F(BankTest, AddMultipleTransactionsAndCalculateBalance) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    double expectedBalance = 100.0 - 50.0 + 200.0;
    double actualBalance = bank.getCurrentBalance();

    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Test caso per il salvataggio e il caricamento delle transazioni da file
TEST_F(BankTest, SaveAndLoadTransactions) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    const std::string tempFileName = "test_transactions.tmp";
    bank.saveToFile(tempFileName);

    Bank loadedBank;
    loadedBank.loadFromFile(tempFileName);

    double expectedBalance = 100.0 - 50.0 + 200.0;
    double actualBalance = loadedBank.getCurrentBalance();

    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Test caso per l'aggiunta di transazioni con date valide
TEST_F(BankTest, AddTransactionsWithValidDates) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");
    bank.addTransaction("Transaction4", 50.0, "2023-08-04");
    bank.addTransaction("Transaction5", -20.0, "2023-08-05");

    int totalTransactions = bank.getTotalTransactions();

    int expectedTotalTransactions = 5;

    // Verifica se il numero totale di transazioni corrisponde al valore atteso
    EXPECT_EQ(expectedTotalTransactions, totalTransactions);

}

// Test caso per la modifica di una transazione
TEST_F(BankTest, EditTransaction) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    // Modifica la transazione all'indice 1
    bank.editTransaction(1, "ModifiedTransaction", 150.0, "2023-08-15");

    // Calcola il saldo atteso dopo la modifica
    double expectedBalance = 100.0 + 150.0 + 200.0;

    // Calcola il saldo effettivo utilizzando il metodo della classe
    double actualBalance = bank.getCurrentBalance();

    // Confronta il saldo atteso con il saldo effettivo
    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Test caso per l'eliminazione di una transazione
TEST_F(BankTest, DeleteTransaction) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    // Elimina la transazione all'indice 1
    bank.deleteTransaction(1);

    // Calcola il saldo atteso dopo l'eliminazione
    double expectedBalance = 100.0 + 200.0;

    // Calcola il saldo effettivo utilizzando il metodo della classe
    double actualBalance = bank.getCurrentBalance();

    // Confronta il saldo atteso con il saldo effettivo
    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Test caso per la ricerca di transazioni per data
TEST_F(BankTest, SearchByDate) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    testing::internal::CaptureStdout();
    bank.searchByDate("2023-08-02");
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "Name: Transaction2 Amount: -50\n";
    EXPECT_EQ(output, expectedOutput);
}

// Test caso per la ricerca di transazioni per nome
TEST_F(BankTest, SearchByName) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    testing::internal::CaptureStdout();
    bank.searchByName("Transaction1");
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "Date: 2023-08-01 Amount: 100\n";
    EXPECT_EQ(output, expectedOutput);
}

// Test caso per la gestione di una transazione non valida
TEST_F(BankTest, AddInvalidTransaction) {
    EXPECT_THROW(bank.addTransaction("", 100.0, "2023-08-01"), std::invalid_argument);
    EXPECT_THROW(bank.addTransaction("Transaction1", 0.0, "2023-08-01"), std::invalid_argument);
    EXPECT_THROW(bank.addTransaction("Transaction1", 100.0, ""), std::invalid_argument);
    EXPECT_THROW(bank.addTransaction("Transaction1", 100.0, "invalid_date"), std::invalid_argument);
}

// Test caso per la modifica di una transazione inesistente
TEST_F(BankTest, EditNonExistentTransaction) {
    EXPECT_THROW(bank.editTransaction(10, "ModifiedTransaction", 150.0, "2023-08-15"), std::out_of_range);
}

// Test caso per l'eliminazione di una transazione inesistente
TEST_F(BankTest, DeleteNonExistentTransaction) {
    EXPECT_FALSE(bank.deleteTransaction(10));
}

// Test caso per la ricerca di transazioni per una data inesistente
TEST_F(BankTest, SearchByNonExistentDate) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    testing::internal::CaptureStdout();
    bank.searchByDate("2023-08-04"); // Cerca una data non presente nelle transazioni
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "No transactions found for date: 2023-08-04\n";
    EXPECT_EQ(output, expectedOutput);
}

// Test caso per la ricerca di transazioni per un nome inesistente
TEST_F(BankTest, SearchByNonExistentName) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    testing::internal::CaptureStdout();
    bank.searchByName("NonExistentTransaction");
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "No transactions found for name: NonExistentTransaction\n";
    EXPECT_EQ(output, expectedOutput);
}

// Test caso per la visualizzazione delle transazioni
TEST_F(BankTest, DisplayTransactions) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    testing::internal::CaptureStdout();
    bank.displayTransactions();
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput =
            "Index: 0 Name: Transaction1 Amount: 100 Date: 2023-08-01\n"
            "Index: 1 Name: Transaction2 Amount: -50 Date: 2023-08-02\n"
            "Index: 2 Name: Transaction3 Amount: 200 Date: 2023-08-03\n"
            "Total transactions: 3\n";

    EXPECT_EQ(output, expectedOutput);
}

// Test caso per la modifica di una transazione con un importo nullo
TEST_F(BankTest, EditTransactionWithZeroAmount) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    // Modifica la transazione all'indice 1 con un importo nullo
    EXPECT_THROW(bank.editTransaction(1, "ModifiedTransaction", 0.0, "2023-08-15"), std::invalid_argument);
}

// Test caso per la modifica di una transazione con una data non valida
TEST_F(BankTest, EditTransactionWithInvalidDate) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    // Modifica la transazione all'indice 1 con una data non valida
    EXPECT_THROW(bank.editTransaction(1, "ModifiedTransaction", 150.0, "invalid_date"), std::invalid_argument);
}

// Test caso per l'aggiunta di una transazione con un nome vuoto
TEST_F(BankTest, AddTransactionWithEmptyName) {
    EXPECT_THROW(bank.addTransaction("", 100.0, "2023-08-01"), std::invalid_argument);
}

// Test caso per la ricerca di transazioni per una data nulla
TEST_F(BankTest, SearchByNullDate) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    testing::internal::CaptureStdout();
    bank.searchByDate(""); // Cerca una data nulla
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "No transactions found for date: \n";
    EXPECT_EQ(output, expectedOutput);
}

// Test caso per la ricerca di transazioni per un nome vuoto
TEST_F(BankTest, SearchByEmptyName) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    testing::internal::CaptureStdout();
    bank.searchByName(""); // Cerca un nome vuoto
    std::string output = testing::internal::GetCapturedStdout();

    std::string expectedOutput = "No transactions found for name: \n";
    EXPECT_EQ(output, expectedOutput);
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
