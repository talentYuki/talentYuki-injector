#pragma once

#include <windows.h>
#include <string>

namespace Injector {

    // Заинжектить DLL в процесс по хендлу
    bool InjectDLL(HANDLE hProcess, const std::string& dllPath);

    // Найти процесс по имени и заинжектить DLL
    bool InjectByName(const std::string& processName, const std::string& dllPath);

}