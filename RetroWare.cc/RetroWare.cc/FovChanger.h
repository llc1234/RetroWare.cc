#pragma once



class FovChanger {
	uintptr_t m_iDefaultFOV = 0x333C;
	uintptr_t m_iHealth = 0x100;

public:
	uintptr_t localplayer = 0;

	void changer_Fov(HANDLE process, int fov) {
		int Health;
		uintptr_t local;

		ReadProcessMemory(process, (void*)(localplayer), &local, sizeof(local), 0);
		
		WriteProcessMemory(process, (void*)(local + m_iDefaultFOV), &fov, sizeof(fov), 0);
	}
};