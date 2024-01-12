#include <gtest/gtest.h>
#include "BANK.h"

// Test fixture per la classe Bank
class BankTest : public ::testing::Test {
protected:
    Bank bank;

    void SetUp() override {
        // Inizializza lo stato prima di ogni test (opzionale)
    }

    void TearDown() override {
        // Pulizia dopo ogni test (opzionale)
    }
};

// Test caso per l'aggiunta di transazioni e il calcolo del saldo
TEST_F(BankTest, AddTransactionAndCalculateBalance) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    double expectedBalance = 100.0 - 50.0 + 200.0;
    double actualBalance = bank.calculateBalance();

    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Altro test caso per il salvataggio e il caricamento delle transazioni
TEST_F(BankTest, SaveAndLoadTransactions) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    const std::string tempFileName = "test_transactions.tmp";
    bank.saveToFile(tempFileName);

    Bank loadedBank;
    loadedBank.loadFromFile(tempFileName);

    double expectedBalance = 100.0 - 50.0 + 200.0;
    double actualBalance = loadedBank.calculateBalance();

    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Test caso per il caricamento corretto delle transazioni da file
TEST_F(BankTest, LoadTransactionsFromFile) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    const std::string tempFileName = "test_transactions.tmp";
    bank.saveToFile(tempFileName);

    Bank loadedBank;
    loadedBank.loadFromFile(tempFileName);

    double expectedBalance = 100.0 - 50.0 + 200.0;
    double actualBalance = loadedBank.calculateBalance();

    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Test caso per l'aggiunta di transazioni con verifica della data
TEST_F(BankTest, AddTransactionWithValidDate) {
    bank.addTransaction("Transaction1", 100.0, "2023-08-01");
    bank.addTransaction("Transaction2", -50.0, "2023-08-02");
    bank.addTransaction("Transaction3", 200.0, "2023-08-03");

    // Aggiungi ulteriori transazioni con date valide
    bank.addTransaction("Transaction4", 50.0, "2023-08-04");
    bank.addTransaction("Transaction5", -20.0, "2023-08-05");
}

// Test caso per verificare la corretta funzionalità di isValid per date future
TEST_F(BankTest, IsValidWithFutureDate) {
    EXPECT_FALSE(bank.validateDate("2025-08-01"));
    EXPECT_FALSE(bank.validateDate("2025-08-02"));
    EXPECT_FALSE(bank.validateDate("2025-08-03"));
}

// Test caso per verificare la corretta funzionalità di isValid per date non valide
TEST_F(BankTest, IsValidWithInvalidDate) {
    EXPECT_FALSE(bank.validateDate("invalid_date"));
}

// Test caso per verificare la corretta funzionalità di isValid per date valide
TEST_F(BankTest, IsValidWithValidDate) {
    EXPECT_TRUE(bank.validateDate("2023-08-01"));
    EXPECT_TRUE(bank.validateDate("2023-08-02"));
    EXPECT_TRUE(bank.validateDate("2023-08-03"));
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
    double actualBalance = bank.calculateBalance();

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
    double actualBalance = bank.calculateBalance();

    // Confronta il saldo atteso con il saldo effettivo
    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
