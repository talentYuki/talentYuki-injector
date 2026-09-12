# talentYuki-injector

# DLL Injector

![C++](https://img.shields.io/badge/C%2B%2B-17-blue)
![Platform](https://img.shields.io/badge/Platform-Windows%2010%2F11-lightgrey)
![License](https://img.shields.io/badge/License-MIT-green)

A lightweight DLL injector for Windows, written in C++17 using WinAPI. It allows loading a custom DLL into a running process using the classic `CreateRemoteThread` + `LoadLibrary` technique.

## Features

- Find process by name
- Open process with full access rights
- Allocate memory in remote process
- Write DLL path into remote memory
- Resolve `LoadLibraryA` address from `kernel32.dll`
- Create remote thread to load the DLL
- Clean up allocated memory

## Requirements

- Windows 10/11
- C++17 compiler (MSVC / MinGW)
- CMake 3.15+
- Administrator privileges

## Build

### Using CMake
```bash
mkdir build && cd build
cmake ..
cmake --build . --config Release

Using MinGW
bash

g++ -std=c++17 src/*.cpp -I include -o injector.exe -ladvapi32
Usage

Run as Administrator:
bash

./injector.exe

Example:
text

========================================
         DLL INJECTOR v1.0.0
========================================
Process name (e.g. RustClient.exe): notepad.exe
Path to DLL: C:\cheats\test.dll
[*] Injecting C:\cheats\test.dll
[*] Into process: notepad.exe
[+] PID: 12345
[+] Process opened
[+] Injection successful!

Project Structure
text

dll-injector/
├── include/
│   ├── injector.h
│   ├── process.h
│   └── utils.h
├── src/
│   ├── main.cpp
│   ├── injector.cpp
│   ├── process.cpp
│   └── utils.cpp
├── CMakeLists.txt
├── README.md
└── LICENSE

Limitations

    Does not bypass anti-cheat. EAC, BattlEye and similar systems detect CreateRemoteThread and LoadLibrary calls.

    Requires matching architecture. x64 injector for x64 target, x86 for x86.

    Requires admin rights. Without them, OpenProcess will fail with ACCESS_DENIED.

Future Improvements

    □

    Manual mapping (no LoadLibrary)
    □

    Thread hijacking (no CreateRemoteThread)
    □

    Kernel-mode injection
    □

    SetWindowsHookEx injection
    □

    APC injection

Disclaimer

This tool is provided for educational purposes only. The author is not responsible for any misuse, including but not limited to cheating in online games, malware development, or violation of software licenses. Use at your own risk.
License

MIT License — see LICENSE for details.
text


---

## ЧТО ВАЖНО В ЭТОМ README:

| Блок | Зачем |
|---|---|
| **Бейджи** | Сразу видно: C++17, Windows, MIT |
| **Features** | Кратко: что умеет |
| **How it works** | ASCII-схема — **это выглядит профессионально** |
| **Requirements** | Что нужно для сборки |
| **Build** | Две команды: CMake и MinGW |
| **Usage** | Пример работы с выводом |
| **Structure** | Показывает, что проект модульный |
| **Limitations** | Честно: не обходит античит |
| **Future Improvements** | Показывает, что ты думаешь о развитии |
| **Disclaimer** | Юридическая защита |

---

## КАК ЗАЛИТЬ:

1. Открой репозиторий `dll-injector` на GitHub.
2. **Add file → Create new file**.
3. Имя: `README.md`.
4. Вставь весь текст выше.
5. **Commit new file**.

---
