using namespace std; 
#include "Book.hpp"
#include <sstream>

Book::Book() : available (true) {}

Book::Book(const string& id, const string& title, const string& author, const string& category, bool available) 
    : id(id), title(title), author(author), category(category), available(available) {}

string Book::toLine() const {

    ostringstream oss;
    oss << id << "|" << title << "|" << author << "|" << category << "|" << (available ? "1" : "0");
    return oss.str();
}

Book Book::fromLine(const string& line){
    
    istringstream iss(line);
    Book b;
    getline(iss, b.id, '|');
    getline(iss, b.title, '|');
    getline(iss, b.author, '|');
    getline(iss, b.category, '|');
    string avail;
    getline(iss, avail);
    b.available = (avail == "1");
    return b;
}
