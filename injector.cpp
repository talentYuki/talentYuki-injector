#include "injector.h"
#include "process.h"
#include "utils.h"

#include <iostream>

namespace Injector {

    bool InjectDLL(HANDLE hProcess, const std::string& dllPath) {
        // 1. Выделяем память в чужом процессе под путь к DLL
        SIZE_T pathSize = dllPath.size() + 1;
        LPVOID remoteMemory = VirtualAllocEx(
            hProcess,
            nullptr,
            pathSize,
            MEM_COMMIT | MEM_RESERVE,
            PAGE_READWRITE
        );

        if (!remoteMemory) {
            Utils::PrintError("VirtualAllocEx failed");
            return false;
        }
        Utils::PrintSuccess("Memory allocated in remote process");

        // 2. Записываем путь к DLL в чужой процесс
        SIZE_T bytesWritten = 0;
        if (!WriteProcessMemory(
            hProcess,
            remoteMemory,
            dllPath.c_str(),
            pathSize,
            &bytesWritten)) {
            Utils::PrintError("WriteProcessMemory failed");
            VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
            return false;
        }
        Utils::PrintSuccess("DLL path written to remote memory");

        // 3. Получаем адрес LoadLibraryA из kernel32.dll
        HMODULE hKernel32 = GetModuleHandleA("kernel32.dll");
        if (!hKernel32) {
            Utils::PrintError("GetModuleHandleA failed");
            VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
            return false;
        }

        LPTHREAD_START_ROUTINE loadLibraryAddr =
            reinterpret_cast<LPTHREAD_START_ROUTINE>(
                GetProcAddress(hKernel32, "LoadLibraryA"));

        if (!loadLibraryAddr) {
            Utils::PrintError("GetProcAddress failed");
            VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
            return false;
        }
        Utils::PrintSuccess("LoadLibraryA address resolved");

        // 4. Создаём удалённый поток, который вызовет LoadLibraryA
        HANDLE hThread = CreateRemoteThread(
            hProcess,
            nullptr,
            0,
            loadLibraryAddr,
            remoteMemory,
            0,
            nullptr
        );

        if (!hThread) {
            Utils::PrintError("CreateRemoteThread failed");
            VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);
            return false;
        }
        Utils::PrintSuccess("Remote thread created");

        // 5. Ждём завершения потока
        WaitForSingleObject(hThread, INFINITE);

        // 6. Очищаем
        CloseHandle(hThread);
        VirtualFreeEx(hProcess, remoteMemory, 0, MEM_RELEASE);

        return true;
    }

    bool InjectByName(const std::string& processName, const std::string& dllPath) {
        DWORD pid = Process::FindPID(processName);
        if (pid == 0) {
            Utils::PrintError("Process not found: " + processName);
            return false;
        }
        Utils::PrintInfo("PID: " + std::to_string(pid));

        HANDLE hProcess = Process::Open(pid);
        if (!hProcess) {
            Utils::PrintError("OpenProcess failed. Run as admin.");
            return false;
        }
        Utils::PrintSuccess("Process opened");

        bool result = InjectDLL(hProcess, dllPath);

        Process::Close(hProcess);
        return result;
    }

}