#pragma once

#include <windows.h>
#include <string>

namespace Process {

    // Найти PID по имени процесса
    DWORD FindPID(const std::string& name);

    // Открыть процесс с правами на инжект
    HANDLE Open(DWORD pid);

    // Закрыть хендл процесса
    void Close(HANDLE hProcess);

}