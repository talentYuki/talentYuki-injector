#include "utils.h"

#include <iostream>
#include <windows.h>
#include <filesystem>

namespace fs = std::filesystem;

namespace Utils {

    void PrintSuccess(const std::string& msg) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 10); // зелёный
        std::cout << "[+] " << msg << std::endl;
        SetConsoleTextAttribute(h, 7);
    }

    void PrintError(const std::string& msg) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 12); // красный
        std::cout << "[!] " << msg << std::endl;
        SetConsoleTextAttribute(h, 7);
    }

    void PrintInfo(const std::string& msg) {
        HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(h, 11); // голубой
        std::cout << "[*] " << msg << std::endl;
        SetConsoleTextAttribute(h, 7);
    }

    bool FileExists(const std::string& path) {
        return fs::exists(path) && fs::is_regular_file(path);
    }

    std::string GetAbsolutePath(const std::string& path) {
        return fs::absolute(path).string();
    }

}