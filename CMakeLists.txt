cmake_minimum_required(VERSION 3.21)
project(FinancialTransactionSystem)

set(CMAKE_CXX_STANDARD 14)

add_executable(FinancialTransactionSystem BANK.cpp BANK.h test_BANK.cpp)

# Aggiungi le directory di inclusione per Google Test
include_directories(googletest/include)

# Aggiungi le librerie di Google Test
add_subdirectory(googletest)

target_link_libraries(FinancialTransactionSystem gtest gtest_main)


