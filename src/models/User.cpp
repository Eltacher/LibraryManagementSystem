#include "User.hpp"
#include <sstream>

User::User() : isAdmin(false) {}

User::User(const string& username, const string& password, bool isAdmin)
    : username(username), password(password), isAdmin(isAdmin) {}

string User::toLine() const {

    ostringstream oss;
    oss << username << "|" << password << "|" << (isAdmin ? "1" : "0");
    return oss.str();
}

User User::fromLine(const string& line) {

    istringstream iss(line);
    User u;
    getline(iss, u.username, '|');
    getline(iss, u.password, '|');
    string adm;
    getline(iss, adm);
    u.isAdmin = (adm == "1");
    return u;
}