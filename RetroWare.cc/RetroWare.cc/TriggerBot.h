#pragma once


class TriggerBot {
	uintptr_t m_iCrosshairId = 0x11838;
	uintptr_t m_iTeamNum = 0xF4;

	float start_time = clock();

public:
	uintptr_t Entity_ = 0;
	uintptr_t ForceAttack_ = 0;

	void triggerbot(HANDLE process) {
		uintptr_t localplayer;
		ReadProcessMemory(process, (void*)Entity_, &localplayer, sizeof(localplayer), 0);

		int Team;
		ReadProcessMemory(process, (void*)(localplayer + m_iTeamNum), &Team, sizeof(Team), 0);

		int value;
		ReadProcessMemory(process, (void*)(localplayer + m_iCrosshairId), &value, sizeof(value), 0);

		if (value < 32 && value > 0) {
			uintptr_t entity;
			ReadProcessMemory(process, (void*)(Entity_ + (value - 1) * 0x10), &entity, sizeof(entity), 0);

			int t;
			ReadProcessMemory(process, (void*)(entity + m_iTeamNum), &t, sizeof(t), 0);


			if (t != Team) {
				int v = 1;
				WriteProcessMemory(process, (void*)(ForceAttack_), &v, sizeof(v), 0);
				v = 0;
				WriteProcessMemory(process, (void*)(ForceAttack_), &v, sizeof(v), 0);
			}
		}
	}
};