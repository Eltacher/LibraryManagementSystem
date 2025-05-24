#include "AuthService.hpp"
#include "../utils/FileIO.hpp"
#include <algorithm>

AuthService::AuthService(const std::string& userFile)
    : path(userFile), current(nullptr)
{
    users = FileIO::readAll<User>(path, User::fromLine);
    if (users.empty()) {
        users.push_back(User("admin", "admin", true));
        save();
    }
}

void AuthService::save() const {
    FileIO::writeAll<User>(path, users, &User::toLine);
}

bool AuthService::registerUser(const std::string& uname, const std::string& pwd, bool admin) {
    auto it = std::find_if(users.begin(), users.end(),
        [&](const User& u) { return u.username == uname; });
    if (it != users.end()) return false;
    users.push_back(User(uname, pwd, admin));
    save();
    return true;
}

bool AuthService::login(const std::string& uname, const std::string& pwd) {
    auto it = std::find_if(users.begin(), users.end(),
        [&](User& u) { return u.username == uname && u.password == pwd; });
    if (it == users.end()) return false;
    current = &(*it);
    return true;
}

void AuthService::logout() { current = nullptr; }
bool AuthService::isLogged() const { return current != nullptr; }
bool AuthService::isAdmin() const { return current && current->isAdmin; }
std::string AuthService::who() const { return current ? current->username : ""; }
