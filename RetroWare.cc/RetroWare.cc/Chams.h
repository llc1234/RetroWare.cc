#pragma once


class Chams {
	uintptr_t m_iTeamNum = 0xF4;
	uintptr_t m_clrRender = 0x70;

	int is_Chams_enemy[3] = {0, 0, 0};
	int is_Chams_frendly[3] = {0, 0, 0};

public:
	uintptr_t localplayer_ = 0;
	uintptr_t Entity_ = 0;
	uintptr_t model_ambient_min_ = 0;

	int v_Chams_enemy[3] = {0, 0, 0};
	int v_Chams_frendly[3] = {0, 0, 0};

	float brightness = 0;
	
	
	void chams(HANDLE process, bool c_Enemy_chams, bool c_Team_chams) {
		uintptr_t localplayer;
		int localTeam;

		ReadProcessMemory(process, (void*)localplayer_, &localplayer, sizeof(localplayer), 0);
		ReadProcessMemory(process, (void*)(localplayer + m_iTeamNum), &localTeam, sizeof(localTeam), 0);
		
		// std::cout << localTeam << std::endl;

		for (int i = 0; i < 32; ++i) {
			uintptr_t entity;
			ReadProcessMemory(process, (void*)(Entity_ + i * 0x10), &entity, sizeof(entity), 0);

			int team;
			ReadProcessMemory(process, (void*)(entity + m_iTeamNum), &team, sizeof(team), 0);

			if (team == localTeam) {
				if (c_Team_chams) {
					WriteProcessMemory(process, (void*)(entity + m_clrRender), &v_Chams_frendly[0], sizeof(v_Chams_frendly[0]), 0);
					WriteProcessMemory(process, (void*)(entity + m_clrRender + 0x1), &v_Chams_frendly[1], sizeof(v_Chams_frendly[1]), 0);
					WriteProcessMemory(process, (void*)(entity + m_clrRender + 0x2), &v_Chams_frendly[2], sizeof(v_Chams_frendly[2]), 0);
					
				}

			} else {
				if (c_Enemy_chams) {
					WriteProcessMemory(process, (void*)(entity + m_clrRender), &v_Chams_enemy[0], sizeof(v_Chams_enemy[0]), 0);
					WriteProcessMemory(process, (void*)(entity + m_clrRender + 0x1), &v_Chams_enemy[1], sizeof(v_Chams_enemy[1]), 0);
					WriteProcessMemory(process, (void*)(entity + m_clrRender + 0x2), &v_Chams_enemy[2], sizeof(v_Chams_enemy[2]), 0);
					
				}
			}

			uintptr_t thisPtr;
			ReadProcessMemory(process, (void*)(model_ambient_min_ - 0x2c), &thisPtr, sizeof(thisPtr), 0);
			uintptr_t xored = *(uintptr_t*)&brightness ^ thisPtr;

			WriteProcessMemory(process, (void*)(model_ambient_min_), &xored, sizeof(xored), 0);
		}
	}
};