#pragma once

#include <string>

namespace Utils {

    // Цветной вывод в консоль
    void PrintSuccess(const std::string& msg);
    void PrintError(const std::string& msg);
    void PrintInfo(const std::string& msg);

    // Проверка, существует ли файл
    bool FileExists(const std::string& path);

    // Получить абсолютный путь
    std::string GetAbsolutePath(const std::string& path);

}