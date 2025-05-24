using namespace std;
#pragma once
#include <string>

class Book {
    public:
        string id, title, author, category;
        bool available;

        Book();
        Book(const string& id, const string& title, const string& author, const string& category, bool available = true);

        string toLine() const;
        static Book fromLine(const string& line);
};