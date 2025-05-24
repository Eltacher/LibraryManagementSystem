#include "TransactionService.hpp"
#include "../utils/FileIO.hpp"
#include <ctime>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <sstream>

TransactionService::TransactionService(CatalogService& c, const std::string& txnFile)
    : path(txnFile), catalog(c)
{
    txns = FileIO::readAll<Transaction>(path, Transaction::fromLine);
}

void TransactionService::save() const {
    FileIO::writeAll<Transaction>(path, txns, &Transaction::toLine);
}

std::string TransactionService::genId() {
    std::ostringstream oss;
    oss << "TX" << std::time(nullptr);
    return oss.str();
}

bool TransactionService::checkout(const std::string& user, const std::string& bookId) {
    Book* b = catalog.find(bookId);
    if (!b || !b->available) return false;
    b->available = false;
    catalog.update(bookId, *b);
    txns.push_back(Transaction(genId(), user, bookId, std::time(nullptr), 0));
    save();
    return true;
}

bool TransactionService::returnBook(const std::string& user, const std::string& bookId) {
    auto it = std::find_if(txns.begin(), txns.end(),
        [&](Transaction& t) { return t.bookId == bookId && t.username == user && !t.isReturned(); });
    if (it == txns.end()) return false;
    it->inDate = std::time(nullptr);
    save();
    Book* b = catalog.find(bookId);
    if (b) {
        b->available = true;
        catalog.update(bookId, *b);
    }
    return true;
}

void TransactionService::history(const std::string& user) const {
    for (const auto& t : txns) {
        if (t.username == user) {
            std::cout << "#" << t.id << " " << t.bookId
                      << " out: " << std::put_time(std::localtime(&t.outDate), "%F")
                      << " in: ";
            if (t.isReturned())
                std::cout << std::put_time(std::localtime(&t.inDate), "%F");
            else
                std::cout << '-';
            std::cout << "\n";
        }
    }
}
