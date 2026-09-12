#include <iostream>
#include <windows.h>
#include <string>

#include "injector.h"
#include "utils.h"

namespace {

    void PrintBanner() {
        std::cout << "========================================\n";
        std::cout << "         DLL INJECTOR v1.0.0            \n";
        std::cout << "========================================\n";
    }

}

int main() {
    SetConsoleTitleA("DLL Injector v1.0.0");
    system("cls");

    PrintBanner();

    // Запрашиваем имя процесса
    std::cout << "Process name (e.g. notepad.exe): ";
    std::string processName;
    std::cin >> processName;

    // Запрашиваем путь к DLL
    std::cout << "Path to DLL: ";
    std::string dllPath;
    std::cin >> dllPath;

    // Проверяем, существует ли DLL
    if (!Utils::FileExists(dllPath)) {
        Utils::PrintError("DLL not found: " + dllPath);
        system("pause");
        return 1;
    }

    // Преобразуем в абсолютный путь
    dllPath = Utils::GetAbsolutePath(dllPath);

    Utils::PrintInfo("Injecting: " + dllPath);
    Utils::PrintInfo("Into process: " + processName);

    // Запускаем инжект
    if (Injector::InjectByName(processName, dllPath)) {
        Utils::PrintSuccess("Injection successful!");
    }
    else {
        Utils::PrintError("Injection failed");
    }

    system("pause");
    return 0;
}