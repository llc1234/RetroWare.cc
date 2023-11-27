#pragma once

class Radar {
	uintptr_t m_bSpotted = 0x93D;

public:
	uintptr_t Entity_;

	void radar(HANDLE process) {
		bool spotted_true = true;

		for (int i = 0; i < 64; i++) {
			uintptr_t entity;
			ReadProcessMemory(process, (void*)(Entity_ + i * 0x10), &entity, sizeof(entity), 0);
			WriteProcessMemory(process, (void*)(entity + m_bSpotted), &spotted_true, sizeof(spotted_true), 0);
		}
	}
};