using namespace std;
#pragma once
#include <string>

class User {

    public:
        string username, password;
        bool isAdmin;

        User();
        User(const string& username, const string& password, bool isAdmin=false);

        string toLine() const;
        static User fromLine(const string& line);

};
