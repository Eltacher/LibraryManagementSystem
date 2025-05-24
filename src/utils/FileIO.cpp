#include "FileIO.hpp"
#include <fstream>
#include <filesystem>

namespace FileIO {

template<typename T>
std::vector<T> readAll(const std::string& path, T(*parser)(const std::string&)) {
    std::vector<T> vec;
    std::ifstream fin(path);
    std::string line;
    while (std::getline(fin, line)) {
        if (!line.empty())
            vec.push_back(parser(line));
    }
    return vec;
}

template<typename T>
void writeAll(const std::string& path, const std::vector<T>& data, std::string(T::*serializer)() const) {
    std::filesystem::create_directories(std::filesystem::path(path).parent_path());
    std::ofstream fout(path, std::ios::trunc);
    for (const auto& item : data)
        fout << (item.*serializer)() << '\n';
}

// Explicit instantiation for linker
#include "../models/Book.hpp"
#include "../models/User.hpp"
#include "../models/Transaction.hpp"
template std::vector<Book> FileIO::readAll(const std::string&, Book(*)(const std::string&));
template std::vector<User> FileIO::readAll(const std::string&, User(*)(const std::string&));
template std::vector<Transaction> FileIO::readAll(const std::string&, Transaction(*)(const std::string&));
template void FileIO::writeAll<Book>(const std::string&, const std::vector<Book>&, std::string(Book::*)() const);
template void FileIO::writeAll<User>(const std::string&, const std::vector<User>&, std::string(User::*)() const);
template void FileIO::writeAll<Transaction>(const std::string&, const std::vector<Transaction>&, std::string(Transaction::*)() const);

} // namespace FileIO
