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
    // Aggiungi transazioni positive e negative
    bank.addTransaction(100.0, "2023-08-01");
    bank.addTransaction(-50.0, "2023-08-02");
    bank.addTransaction(200.0, "2023-08-03");

    // Calcola il saldo atteso dopo le transazioni
    double expectedBalance = 100.0 - 50.0 + 200.0;

    // Calcola il saldo effettivo utilizzando il metodo della classe
    double actualBalance = bank.calculateBalance();

    // Confronta il saldo atteso con il saldo effettivo
    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

// Altro test caso per il salvataggio e il caricamento delle transazioni
TEST_F(BankTest, SaveAndLoadTransactions) {
    // Aggiungi transazioni positive e negative
    bank.addTransaction(100.0, "2023-08-01");
    bank.addTransaction(-50.0, "2023-08-02");
    bank.addTransaction(200.0, "2023-08-03");

    // Salva le transazioni su un file temporaneo
    const std::string tempFileName = "test_transactions.tmp";
    bank.saveToFile(tempFileName);

    // Crea una nuova istanza di Bank per caricare le transazioni
    Bank loadedBank;
    loadedBank.loadFromFile(tempFileName);

    // Calcola il saldo atteso dopo le transazioni
    double expectedBalance = 100.0 - 50.0 + 200.0;

    // Calcola il saldo effettivo utilizzando il metodo della classe caricata
    double actualBalance = loadedBank.calculateBalance();

    // Confronta il saldo atteso con il saldo effettivo
    EXPECT_DOUBLE_EQ(expectedBalance, actualBalance);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
