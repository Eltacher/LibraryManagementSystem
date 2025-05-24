#pragma once
#include "../models/User.hpp"
#include <vector>
#include <string>

class AuthService {
    std::vector<User> users;
    const std::string path;
    User* current;
    void save() const;

public:
    AuthService(const std::string& userFile = "data/users.dat");
    bool registerUser(const std::string& uname, const std::string& pwd, bool admin = false);
    bool login(const std::string& uname, const std::string& pwd);
    void logout();
    bool isLogged() const;
    bool isAdmin() const;
    std::string who() const;
};
