#pragma once
#include <vector>
#include <string>
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

}
