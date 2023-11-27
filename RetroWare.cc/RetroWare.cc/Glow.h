#pragma once


class Glow {
	// uintptr_t dwGlowObjectManager = 0x535AA08;
	uintptr_t m_iTeamNum = 0xF4;
	uintptr_t m_iGlowIndex = 0x10488;
	uintptr_t m_bSpottedByMask = 0x980;

public:

	float glow_Team_color[3] = {1, 1, 1};
	float glow_Enemy_color[3] = { 1, 1, 1 };
	float glow_Spotted_color[3] = { 1, 1, 1 };

	uintptr_t llocalplayer = 0; 
	uintptr_t Entity = 0;
	uintptr_t GlowObjectManager = 0;

	void glow(HANDLE process, bool c_Enemy_Glow, bool c_Team_Glow, bool c_Spotted) {
		if (c_Enemy_Glow || c_Team_Glow) {
			uintptr_t localplayer;
			ReadProcessMemory(process, (LPCVOID)(llocalplayer), &localplayer, sizeof(localplayer), NULL);

			uintptr_t glowObjectManager;
			ReadProcessMemory(process, (LPCVOID)(GlowObjectManager), &glowObjectManager, sizeof(glowObjectManager), NULL);

			int me_team;
			ReadProcessMemory(process, (LPCVOID)(localplayer + m_iTeamNum), &me_team, sizeof(me_team), NULL);

			for (auto i = 1; i < 64; ++i) {
				uintptr_t entity;
				ReadProcessMemory(process, (LPCVOID)(Entity + i * 0x10), &entity, sizeof(entity), NULL);

				int getteam;
				ReadProcessMemory(process, (LPCVOID)(entity + m_iTeamNum), &getteam, sizeof(getteam), NULL);

				int32_t glowIndex;
				ReadProcessMemory(process, (LPCVOID)(entity + m_iGlowIndex), &glowIndex, sizeof(glowIndex), NULL);

				if (getteam == me_team) {
					if (c_Team_Glow) {
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x8), &glow_Team_color[0], sizeof(glow_Team_color[0]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0xC), &glow_Team_color[1], sizeof(glow_Team_color[1]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x10), &glow_Team_color[2], sizeof(glow_Team_color[2]), NULL);

						float r = 1.0;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x14), &r, sizeof(r), NULL);

						bool p = true;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x27), &p, sizeof(p), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x28), &p, sizeof(p), NULL);
					}
				}
				else {
					if (c_Enemy_Glow) {
						int32_t spotted;
						ReadProcessMemory(process, (LPCVOID)(entity + m_bSpottedByMask), &spotted, sizeof(spotted), NULL);

						float first_color[3] = {glow_Enemy_color[0], glow_Enemy_color[1], glow_Enemy_color[2]};

						if (spotted && c_Spotted) {
							first_color[0] = glow_Spotted_color[0];
							first_color[1] = glow_Spotted_color[1];
							first_color[2] = glow_Spotted_color[2];
						} 
						
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x8), &first_color[0], sizeof(first_color[0]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0xC), &first_color[1], sizeof(first_color[1]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x10), &first_color[2], sizeof(first_color[2]), NULL);

						float r = 1.0;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x14), &r, sizeof(r), NULL);

						bool p = true;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x27), &p, sizeof(p), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x28), &p, sizeof(p), NULL);
						
					}
				}
			}
		}
	}
};


/*
if (true || true) {
			uintptr_t localplayer;
			ReadProcessMemory(process, (LPCVOID)(0x2DB90000 + 0xDEA98C), &localplayer, sizeof(localplayer), NULL);

			uintptr_t glowObjectManager;
			ReadProcessMemory(process, (LPCVOID)(0x2DB90000 + dwGlowObjectManager), &glowObjectManager, sizeof(glowObjectManager), NULL);

			int me_team;
			ReadProcessMemory(process, (LPCVOID)(localplayer + m_iTeamNum), &me_team, sizeof(me_team), NULL);

			for (auto i = 1; i < 64; ++i) {
				uintptr_t entity;
				ReadProcessMemory(process, (LPCVOID)(0x2DB90000 + 0x4DFFF7C + i * 0x10), &entity, sizeof(entity), NULL);

				int getteam;
				ReadProcessMemory(process, (LPCVOID)(entity + m_iTeamNum), &getteam, sizeof(getteam), NULL);

				int32_t glowIndex;
				ReadProcessMemory(process, (LPCVOID)(entity + m_iGlowIndex), &glowIndex, sizeof(glowIndex), NULL);

				if (getteam == me_team) {
					if (c_Team_Glow) {
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x8), &glow_Team_color[0], sizeof(glow_Team_color[0]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0xC), &glow_Team_color[1], sizeof(glow_Team_color[1]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x10), &glow_Team_color[2], sizeof(glow_Team_color[2]), NULL);

						float r = 1.0;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x14), &r, sizeof(r), NULL);

						bool p = true;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x27), &p, sizeof(p), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x28), &p, sizeof(p), NULL);
					}
				}
				else {
					if (c_Enemy_Glow) {
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x8), &glow_Enemy_color[0], sizeof(glow_Enemy_color[0]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0xC), &glow_Enemy_color[1], sizeof(glow_Enemy_color[1]), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x10), &glow_Enemy_color[2], sizeof(glow_Enemy_color[2]), NULL);

						float r = 1.0;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x14), &r, sizeof(r), NULL);

						bool p = true;
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x27), &p, sizeof(p), NULL);
						WriteProcessMemory(process, (void*)(glowObjectManager + (glowIndex * 0x38) + 0x28), &p, sizeof(p), NULL);
					}
				}
			}
		}
*/