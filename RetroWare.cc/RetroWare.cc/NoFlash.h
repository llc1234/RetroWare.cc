#pragma once


class NoFlash {
	uintptr_t m_flFlashMaxAlpha = 0x1046C;
	

public:
	uintptr_t Entity_ = 0;

	void noflash(HANDLE handle) {
		int value;
		uintptr_t localplayer;

		ReadProcessMemory(handle, (void*)(Entity_), &localplayer, sizeof(localplayer), 0);
		ReadProcessMemory(handle, (void*)(localplayer + m_flFlashMaxAlpha), &value, sizeof(value), 0);

		int v = 0;
		if (value > 0) {
			WriteProcessMemory(handle, (void*)(localplayer + m_flFlashMaxAlpha), &v, sizeof(v), 0);
		}
	}
};