#pragma once

class Rage {
	uintptr_t m_iHealth = 0x100;
	uintptr_t m_iTeamNum = 0xF4;
	uintptr_t m_bDormant = 0xED;
	uintptr_t m_vecOrigin = 0x138;
	uintptr_t dwClientState_ViewAngles = 0x4D90;

public:
	uintptr_t EntityList_;
	uintptr_t ClientState_;

	float map(float x, float in_min, float in_max, float out_min, float out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	void rage(HANDLE hprocess) {
		uintptr_t ClientState;
		ReadProcessMemory(hprocess, (void*)ClientState_, &ClientState, sizeof(ClientState), 0);

		uintptr_t local;
		ReadProcessMemory(hprocess, (void*)EntityList_, &local, sizeof(local), 0);

		float local_pos[3];
		ReadProcessMemory(hprocess, (void*)(local + m_vecOrigin), &local_pos, sizeof(local_pos), 0);


		for (int i = 1; i < 64; i++) {
			uintptr_t entity;
			ReadProcessMemory(hprocess, (void*)(EntityList_ + i * 0x10), &entity, sizeof(entity), 0);


			int entity_bDormant;
			ReadProcessMemory(hprocess, (void*)(entity + m_bDormant), &entity_bDormant, sizeof(entity_bDormant), 0);

			if (entity_bDormant) {
				continue;
			}

			int entity_Health;
			ReadProcessMemory(hprocess, (void*)(entity + m_iHealth), &entity_Health, sizeof(entity_Health), 0);

			if (!(entity_Health < 101 && entity_Health > 0)) {
				continue;
			}
			
			float entity_pos[3];
			ReadProcessMemory(hprocess, (void*)(entity + m_vecOrigin), &entity_pos, sizeof(entity_pos), 0);


			float rot_x = atan2(entity_pos[0] - local_pos[0], entity_pos[1] - local_pos[1]);
			float r_x = map(rot_x + 1.5707, 0, 6.28, 180, -180);

			float rot_y = atan2(entity_pos[0] - local_pos[0], entity_pos[2] - local_pos[2]);
			float r_y = map(rot_y, -3.1415, 3.1415, -89, 89);


			// WriteProcessMemory(hprocess, (void*)(ClientState + dwClientState_ViewAngles), &r_y, sizeof(r_y), 0);
			// WriteProcessMemory(hprocess, (void*)(ClientState + dwClientState_ViewAngles + 0x4), &r_x, sizeof(r_x), 0);

			// std::cout << rot_y << std::endl;
		}
	}
};