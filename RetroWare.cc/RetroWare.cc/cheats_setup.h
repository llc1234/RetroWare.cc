#pragma once

class Cheats_setup {

public:
    HWND hWnd;
    DWORD PID;
    HANDLE process;
    uintptr_t client_DLL = 0;
    uintptr_t engine_DLL = 0;

    uintptr_t GetModuleBaseAddress(const char* modName) {
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, PID);
        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);
            if (Module32First(hSnap, &modEntry)) {
                do {
                    if (!strcmp(modEntry.szModule, modName)) {
                        CloseHandle(hSnap);
                        return (uintptr_t)modEntry.modBaseAddr;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
        }
    }

    void setup() {
        hWnd = FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9");
        GetWindowThreadProcessId(hWnd, &PID);
        process = OpenProcess(PROCESS_ALL_ACCESS, NULL, PID);

        client_DLL = GetModuleBaseAddress("client.dll");
        engine_DLL = GetModuleBaseAddress("engine.dll");

        // std::cout << "hWnd: " << hWnd << std::endl;
        // std::cout << "PID: " << PID << std::endl;
        // std::cout << "process: " << process << std::endl;

        // std::cout << "client_DLL: " << client_DLL << std::endl;
        // std::cout << "engine_DLL: " << engine_DLL << std::endl;
    }
};