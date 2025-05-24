#include "CatalogService.hpp"
#include "../utils/FileIO.hpp"
#include <algorithm>

CatalogService::CatalogService(const std::string& bookFile)
    : path(bookFile)
{
    books = FileIO::readAll<Book>(path, Book::fromLine);
}

void CatalogService::save() const {
    FileIO::writeAll<Book>(path, books, &Book::toLine);
}

bool CatalogService::add(const Book& b) {
    if (find(b.id)) return false;
    books.push_back(b);
    save();
    return true;
}

bool CatalogService::update(const std::string& id, const Book& b) {
    Book* ptr = find(id);
    if (!ptr) return false;
    *ptr = b;
    save();
    return true;
}

bool CatalogService::remove(const std::string& id) {
    auto oldSize = books.size();
    books.erase(std::remove_if(books.begin(), books.end(),
        [&](const Book& bk) { return bk.id == id; }), books.end());
    if (books.size() == oldSize) return false;
    save();
    return true;
}

const Book* CatalogService::find(const std::string& id) const {
    auto it = std::find_if(books.begin(), books.end(),
        [&](const Book& bk) { return bk.id == id; });
    return it == books.end() ? nullptr : &(*it);
}

Book* CatalogService::find(const std::string& id) {
    return const_cast<Book*>(static_cast<const CatalogService*>(this)->find(id));
}

std::vector<Book> CatalogService::search(const std::string& kw) const {
    std::vector<Book> res;
    for (const auto& b : books)
        if (b.title.find(kw) != std::string::npos ||
            b.author.find(kw) != std::string::npos)
            res.push_back(b);
    return res;
}

const std::vector<Book>& CatalogService::all() const { return books; }
