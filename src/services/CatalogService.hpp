#pragma once
#include "../models/Book.hpp"
#include <vector>
#include <string>

class CatalogService {
    std::vector<Book> books;
    const std::string path;
    void save() const;

public:
    CatalogService(const std::string& bookFile = "data/books.dat");
    bool add(const Book& b);
    bool update(const std::string& id, const Book& b);
    bool remove(const std::string& id);
    const Book* find(const std::string& id) const;
    Book* find(const std::string& id);
    std::vector<Book> search(const std::string& kw) const;
    const std::vector<Book>& all() const;
};
