#pragma once

#include "PatternAddresses.h"


class Addresses {
    uintptr_t addr = 0;
    HANDLE process_handle = 0;

    PatternAddresses* pattern = new PatternAddresses();

public:
    uintptr_t Entity = 0;
    uintptr_t localplayer = 0;
    uintptr_t GlowObjectManager = 0;
    uintptr_t ViewMatrix = 0;
    uintptr_t model_ambient_min = 0;
    uintptr_t ClientState = 0;
    uintptr_t ForceAttack = 0;
    uintptr_t ForceJump = 0;
    uintptr_t ForceRight = 0;
    uintptr_t ForceLeft = 0;

    uintptr_t BombTimer = 0;

    /*
    void ScanMemoryRegion(HANDLE hProcess, LPCVOID startAddress, SIZE_T regionSize, const BYTE* pattern, const char* mask, size_t patternSize) {
        BYTE* buffer = new BYTE[regionSize];

        SIZE_T bytesRead;
        if (ReadProcessMemory(hProcess, startAddress, buffer, regionSize, &bytesRead)) {
            for (SIZE_T i = 0; i <= bytesRead - patternSize; i++) {
                bool found = true;
                for (SIZE_T j = 0; j < patternSize; j++) {
                    if (mask[j] == 'x' && buffer[i + j] != pattern[j]) {
                        found = false;
                        break;
                    }
                }

                // Pattern match found
                if (found) {
                    uintptr_t matchAddress = reinterpret_cast<uintptr_t>(startAddress) + i;
                    addr = matchAddress;
                }
            }
        }

        delete[] buffer;
    }

    void PerformAoBScan(DWORD targetProcessId, const BYTE* pattern, const char* mask, size_t patternSize) {
        // Open the target process
        HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_QUERY_INFORMATION, FALSE, targetProcessId);
        if (hProcess == NULL) {
            std::cout << "Failed to open the target process. Error code: " << GetLastError() << std::endl;
            return;
        }

        // Enumerate memory regions in the target process
        SYSTEM_INFO systemInfo;
        GetSystemInfo(&systemInfo);
        LPVOID minimumApplicationAddress = systemInfo.lpMinimumApplicationAddress;
        LPVOID maximumApplicationAddress = systemInfo.lpMaximumApplicationAddress;

        MEMORY_BASIC_INFORMATION memoryInfo;
        for (LPVOID address = minimumApplicationAddress; address < maximumApplicationAddress;) {
            if (VirtualQueryEx(hProcess, address, &memoryInfo, sizeof(memoryInfo)) == sizeof(memoryInfo)) {
                // Check if the memory region is accessible and not reserved
                if (memoryInfo.State == MEM_COMMIT && memoryInfo.Protect != PAGE_NOACCESS && !(memoryInfo.Type & MEM_PRIVATE)) {
                    // Scan the memory region
                    ScanMemoryRegion(hProcess, memoryInfo.BaseAddress, memoryInfo.RegionSize, pattern, mask, patternSize);
                }
                address = reinterpret_cast<LPVOID>(reinterpret_cast<char*>(address) + memoryInfo.RegionSize);
            }
            else {
                std::cout << "Failed to query memory information. Error code: " << GetLastError() << std::endl;
                break;
            }
        }

        // Close the target process handle
        CloseHandle(hProcess);
    }*/

    MODULEENTRY32 get_module(const char* modName, DWORD proc_id) {
        HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
        if (hSnap != INVALID_HANDLE_VALUE) {
            MODULEENTRY32 modEntry;
            modEntry.dwSize = sizeof(modEntry);
            if (Module32First(hSnap, &modEntry)) {
                do {
                    if (!strcmp(modEntry.szModule, modName)) {
                        CloseHandle(hSnap);
                        return modEntry;
                    }
                } while (Module32Next(hSnap, &modEntry));
            }
        }
        MODULEENTRY32 module = { -1 };
        return module;
    }

    uintptr_t find_pattern(MODULEENTRY32 module, uint8_t* arr, const char* pattern, int offset, int extra) {
        uintptr_t scan = 0x0;
        const char* pat = pattern;
        uintptr_t firstMatch = 0;

        for (uintptr_t pCur = (uintptr_t)arr; pCur < (uintptr_t)arr + module.modBaseSize; ++pCur) {
            if (!*pat) {
                scan = firstMatch; break;
            }

            if (*(uint8_t*)pat == '\?' || *(uint8_t*)pCur == ((((pat[0] & (~0x20)) >= 'A' && (pat[0] & (~0x20)) <= 'F') ? ((pat[0] & (~0x20)) - 'A' + 0xa) : ((pat[0] >= '0' && pat[0] <= '9') ? pat[0] - '0' : 0)) << 4 | (((pat[1] & (~0x20)) >= 'A' && (pat[1] & (~0x20)) <= 'F') ? ((pat[1] & (~0x20)) - 'A' + 0xa) : ((pat[1] >= '0' && pat[1] <= '9') ? pat[1] - '0' : 0)))) {
                if (!firstMatch) {
                    firstMatch = pCur;
                }

                if (!pat[2]) {
                    scan = firstMatch; break;
                }

                if (*(WORD*)pat == 16191 /*??*/ || *(uint8_t*)pat != '\?') {
                    pat += 3;
                }
                else {
                    pat += 2;
                }
            }

            else {
                pat = pattern; firstMatch = 0;
            }
        }
        if (!scan) return 0x0;
        uint32_t read;
        ReadProcessMemory(process_handle, (void*)(scan - (uintptr_t)arr + (uintptr_t)module.modBaseAddr + offset), &read, sizeof(read), NULL);
        return read + extra;
    }

	void scan(DWORD PID) {
        HWND hwnd = FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9");
        DWORD proc_id; 
        GetWindowThreadProcessId(hwnd, &proc_id);
        process_handle = OpenProcess(PROCESS_VM_READ | PROCESS_VM_OPERATION | PROCESS_VM_WRITE, false, proc_id);

        MODULEENTRY32 client = get_module("client.dll", proc_id);
        MODULEENTRY32 engine = get_module("engine.dll", proc_id);

        auto client_bytes = new uint8_t[client.modBaseSize];
        auto engine_bytes = new uint8_t[engine.modBaseSize];

        DWORD bytes_read;
        ReadProcessMemory(process_handle, client.modBaseAddr, client_bytes, client.modBaseSize, &bytes_read);
        ReadProcessMemory(process_handle, engine.modBaseAddr, engine_bytes, engine.modBaseSize, &bytes_read);
        // if (bytes_read != client.modBaseSize) throw;

        Entity =            find_pattern(client, client_bytes, pattern->Entity, 0x1, 0x0);
        localplayer =       find_pattern(client, client_bytes, pattern->localplayer, 0x3, 0x4);       
        GlowObjectManager = find_pattern(client, client_bytes, pattern->GlowObjectManager, 0x1, 0x4);        
        ViewMatrix =        find_pattern(client, client_bytes, pattern->ViewMatrix, 0x3, 0xB0);       
        model_ambient_min = find_pattern(client, client_bytes, pattern->model_ambient_min, 0x0, 0x0) + 0x6B6301A1;
        ClientState =       find_pattern(engine, engine_bytes, pattern->ClientState, 0x01, 0x0);
        ForceAttack =       find_pattern(client, client_bytes, pattern->ForceAttack, 0x02, 0x0);
        ForceJump =         find_pattern(client, client_bytes, pattern->ForceJump, 0x02, 0x0);
        ForceLeft =         find_pattern(client, client_bytes, pattern->ForceLeft, 465, 0x0);
        ForceRight =        find_pattern(client, client_bytes, pattern->ForceRight, 465, 0x0C);

        BombTimer =         find_pattern(client, client_bytes, pattern->BombTimer, 0x0, 0x0) - 0x10A6E0;

        delete[] client_bytes;
        delete[] engine_bytes;

        std::cout << std::endl;

        printf("[+] Found Entity @ 0x%X\n", Entity);
        printf("[+] Found localplayer @ 0x%X\n", localplayer);
        printf("[+] Found GlowObjectManager @ 0x%X\n", GlowObjectManager);
        printf("[+] Found ViewMatrix @ 0x%X\n", ViewMatrix);
        printf("[+] Found model_ambient_min @ 0x%X\n", model_ambient_min);
        printf("[+] Found ClientState @ 0x%X\n", ClientState);
        printf("[+] Found ForceAttack @ 0x%X\n", ForceAttack);
        printf("[+] Found ForceJump @ 0x%X\n", ForceJump);

        printf("[+] Found ForceLeft @ 0x%X\n", ForceLeft);
        printf("[+] Found ForceRight @ 0x%X\n", ForceRight);

        printf("[+] Found BombTimer @ 0x%X\n", BombTimer);

	}
};