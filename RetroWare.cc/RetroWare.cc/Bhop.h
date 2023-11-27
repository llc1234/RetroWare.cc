#pragma once


class Bhop {
	uintptr_t m_fFlags = 0x104;

	
public:
	uintptr_t Entity_ = 0;
	uintptr_t ForceJump_ = 0;

	void bhop(HANDLE process) {
		uintptr_t local;
		ReadProcessMemory(process, (void*)Entity_, &local, sizeof(local), 0);
		
		int value;
		ReadProcessMemory(process, (void*)(local + m_fFlags), &value, sizeof(value), 0);
		
		uintptr_t buffer;
		
		if (value & 1) {
			buffer = 5;
		}
		else {
			buffer = 4;
		}

		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			WriteProcessMemory(process, (void*)(ForceJump_), &buffer, sizeof(buffer), 0);
		}
	}
};