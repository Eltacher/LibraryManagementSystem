#pragma once
#include "../models/Transaction.hpp"
#include "CatalogService.hpp"
#include <vector>
#include <string>

class TransactionService {
    std::vector<Transaction> txns;
    const std::string path;
    CatalogService& catalog;
    void save() const;
    static std::string genId();

public:
    TransactionService(CatalogService& c, const std::string& txnFile = "data/transactions.dat");
    bool checkout(const std::string& user, const std::string& bookId);
    bool returnBook(const std::string& user, const std::string& bookId);
    void history(const std::string& user) const;
};
