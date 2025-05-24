#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include "services/AuthService.hpp"
#include "services/CatalogService.hpp"
#include "services/TransactionService.hpp"

using namespace std;

// Yıldızlı/gizli şifre girişi
string getPassword(const string& prompt = "Password: ") {
    cout << prompt << flush;
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    string password;
    char ch = 0;
    while (true) {
        ch = getchar();
        if (ch == '\n' || ch == '\r') break;
        else if (ch == 127 || ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b" << flush;
            }
        }
        else if (isprint(ch)) {
            password += ch;
            cout << '*' << flush;
        }
    }
    cout << endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return password;
}

// "Press ENTER..." fonksiyonu (pause ismini kullanma, çakışır!)
void waitForEnter() {
    cout << "Press ENTER...";
    cin.ignore();
}

int main() {
    AuthService auth;
    CatalogService catalog;
    TransactionService tx(catalog);

    while (true) {
        if (!auth.isLogged()) {
            cout << "\n1) Login\n2) Register\n0) Exit\nChoice: ";
            int c; cin >> c; cin.ignore();
            if (c == 0) break;
            string u, p;
            cout << "Username:"; getline(cin, u);
            p = getPassword("Password: ");
            if (c == 1) {
                if (auth.login(u, p)) cout << "Logged in!\n";
                else cout << "Wrong creds!\n";
            }
            else if (c == 2) {
                if (auth.registerUser(u, p)) cout << "Registered!\n";
                else cout << "User exists!\n";
            }
            continue;
        }

        cout << "\n--- MENU (" << auth.who() << (auth.isAdmin() ? " | admin" : "") << ") ---\n";
        if (auth.isAdmin())
            cout << "1) Add 2) Update 3) Remove 4) List All 5) Logout 0) Exit\n";
        else
            cout << "1) Search 2) Checkout 3) Return 4) My History 5) Logout 0) Exit\n";
        int ch; cin >> ch; cin.ignore();

        if (ch == 0) { auth.logout(); break; }
        if (ch == 5) { auth.logout(); continue; }

        if (auth.isAdmin()) {
            if (ch == 1) {
                Book b;
                cout << "ID:"; getline(cin, b.id);
                cout << "Title:"; getline(cin, b.title);
                cout << "Author:"; getline(cin, b.author);
                cout << "Category:"; getline(cin, b.category);
                b.available = true;
                if (catalog.add(b)) cout << "Added!\n";
                else cout << "ID exists!\n";
            }
            else if (ch == 2) {
                string id; cout << "ID:"; getline(cin, id);
                const Book* old = catalog.find(id);
                if (!old) { cout << "Not found\n"; continue; }
                Book b = *old;
                cout << "New title (" << b.title << "):"; getline(cin, b.title);
                if (b.title.empty()) b.title = old->title;
                if (catalog.update(id, b)) cout << "Updated!\n";
            }
            else if (ch == 3) {
                string id; cout << "ID:"; getline(cin, id);
                if (catalog.remove(id)) cout << "Removed\n"; else cout << "Not found\n";
            }
            else if (ch == 4) {
                for (const auto& b : catalog.all())
                    cout << b.id << " | " << b.title << " | " << (b.available ? "OK" : "OUT") << "\n";
            }
        }
        else {
            if (ch == 1) {
                string kw; cout << "Keyword:"; getline(cin, kw);
                auto res = catalog.search(kw);
                for (const auto& b : res)
                    cout << b.id << " | " << b.title << " | " << (b.available ? "OK" : "OUT") << "\n";
            }
            else if (ch == 2) {
                string id; cout << "Book ID:"; getline(cin, id);
                if (tx.checkout(auth.who(), id)) cout << "Enjoy reading!\n";
                else cout << "Cannot checkout\n";
            }
            else if (ch == 3) {
                string id; cout << "Book ID:"; getline(cin, id);
                if (tx.returnBook(auth.who(), id)) cout << "Thanks!\n";
                else cout << "Cannot return\n";
            }
            else if (ch == 4) {
                tx.history(auth.who());
            }
        }
        waitForEnter();
    }
    cout << "Bye!\n";
    return 0;
}
