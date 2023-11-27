#pragma once

class OutOfFovArrows {
	uintptr_t m_iTeamNum = 0xF4;
	uintptr_t m_vecOrigin = 0x138;
	uintptr_t m_iHealth = 0x100;
	uintptr_t m_bDormant = 0xED;
	uintptr_t dwClientState_ViewAngles = 0x4D90;
	
	float map(float x, float in_min, float in_max, float out_min, float out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

public:
	uintptr_t Entity_;
	uintptr_t ClientState_;

	void outoffovarrows(HANDLE handle, float color[3]) {
		uintptr_t local;
		ReadProcessMemory(handle, (void*) Entity_, &local, sizeof(local), 0);

		int local_Team;
		ReadProcessMemory(handle, (void*)(local + m_iTeamNum), &local_Team, sizeof(local_Team), 0);

		float local_pos[3];
		ReadProcessMemory(handle, (void*)(local + m_vecOrigin), &local_pos, sizeof(local_pos), 0);


		
		uintptr_t ClientState;
		ReadProcessMemory(handle, (void*)ClientState_, &ClientState, sizeof(ClientState), 0);

		float local_rot[2];
		ReadProcessMemory(handle, (void*)(ClientState + dwClientState_ViewAngles), &local_rot, sizeof(local_rot), 0);



		glBegin(GL_TRIANGLES);
		glColor3f(color[0], color[1], color[2]);

		for (int i = 0; i < 64; i++) {
			uintptr_t entity;
			ReadProcessMemory(handle, (void*)(Entity_ + i * 0x10), &entity, sizeof(entity), 0);

			if (entity == NULL) {
				continue;
			}

			int entity_Health;
			ReadProcessMemory(handle, (void*)(entity + m_iHealth), &entity_Health, sizeof(entity_Health), 0);

			if (!(entity_Health < 101 && entity_Health > 0)) {
				continue;
			}

			int entity_bDormant;
			ReadProcessMemory(handle, (void*)(entity + m_bDormant), &entity_bDormant, sizeof(entity_bDormant), 0);

			if (entity_bDormant) {
				continue;
			}

			int entity_Team;
			ReadProcessMemory(handle, (void*)(entity + m_iTeamNum), &entity_Team, sizeof(entity_Team), 0);
			
			if (local_Team != entity_Team) {
				float entity_pos[3];
				ReadProcessMemory(handle, (void*)(entity + m_vecOrigin), &entity_pos, sizeof(entity_pos), 0);

				float rot = atan2(entity_pos[0] - local_pos[0], entity_pos[1] - local_pos[1]);

				float rot_x = sin(rot + 1.5707 + map(local_rot[1], -180, 180, 0, 6.28318));
				float rot_y = cos(rot + 1.5707 + map(local_rot[1], -180, 180, 0, 6.28318));
				
				float x1 = 0 + rot_x * 0.3;
				float y1 = 0 + rot_y * 0.3;


				float rot_x2 = sin(rot + 1.5707 + map(local_rot[1] + 4, -180, 180, 0, 6.28318));
				float rot_y2 = cos(rot + 1.5707 + map(local_rot[1] + 4, -180, 180, 0, 6.28318));

				float x2 = 0 + rot_x2 * 0.25;
				float y2 = 0 + rot_y2 * 0.25;


				float rot_x3 = sin(rot + 1.5707 + map(local_rot[1] - 4, -180, 180, 0, 6.28318));
				float rot_y3 = cos(rot + 1.5707 + map(local_rot[1] - 4, -180, 180, 0, 6.28318));

				float x3 = 0 + rot_x3 * 0.25;
				float y3 = 0 + rot_y3 * 0.25;
				
				
				glVertex2f(x1, y1);
				glVertex2f(x2, y2);
				glVertex2f(x3, y3);

			}
		}

		glEnd();
	}
};