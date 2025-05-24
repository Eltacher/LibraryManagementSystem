using namespace std;
#pragma once
#include <string>
#include <ctime>

class Transaction {
public:
    string id, username, bookId;
    time_t outDate, inDate;

    Transaction();
    Transaction(const string& id, const string& username, const string& bookId,
                time_t outDate, time_t inDate);

    string toLine() const;
    static Transaction fromLine(const string& line);
    bool isReturned() const;
};
