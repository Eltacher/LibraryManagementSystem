#include "Transaction.hpp"
#include <sstream>

Transaction::Transaction() : outDate(0), inDate(0) {}

Transaction::Transaction(const string& id, const string& username, const string& bookId,
                         time_t outDate, time_t inDate)
    : id(id), username(username), bookId(bookId), outDate(outDate), inDate(inDate) {}

string Transaction::toLine() const {
    ostringstream oss;
    oss << id << "|" << username << "|" << bookId << "|"
        << outDate << "|" << inDate;
    return oss.str();
}

Transaction Transaction::fromLine(const string& line) {
    stringstream iss(line);
    Transaction t;
    string tmp;
    getline(iss, t.id, '|');
    getline(iss, t.username, '|');
    getline(iss, t.bookId, '|');
    getline(iss, tmp, '|'); t.outDate = stoll(tmp);
    getline(iss, tmp); t.inDate = stoll(tmp);
    return t;
}

bool Transaction::isReturned() const {
    return inDate != 0;
}
