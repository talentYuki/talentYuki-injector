#include "process.h"

#include <tlhelp32.h>

namespace Process {

    DWORD FindPID(const std::string& name) {
        HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (snap == INVALID_HANDLE_VALUE) return 0;

        PROCESSENTRY32 pe;
        pe.dwSize = sizeof(pe);

        if (Process32First(snap, &pe)) {
            do {
                if (name == pe.szExeFile) {
                    CloseHandle(snap);
                    return pe.th32ProcessID;
                }
            } while (Process32Next(snap, &pe));
        }

        CloseHandle(snap);
        return 0;
    }

    HANDLE Open(DWORD pid) {
        return OpenProcess(
            PROCESS_CREATE_THREAD |
            PROCESS_QUERY_INFORMATION |
            PROCESS_VM_OPERATION |
            PROCESS_VM_WRITE |
            PROCESS_VM_READ,
            FALSE,
            pid
        );
    }

    void Close(HANDLE hProcess) {
        if (hProcess) {
            CloseHandle(hProcess);
        }
    }

}