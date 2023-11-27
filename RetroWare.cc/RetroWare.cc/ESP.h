#pragma once


class ESP {
    uintptr_t m_vecOrigin = 0x138;
    uintptr_t m_iTeamNum = 0xF4;
    uintptr_t m_iHealth = 0x100;
    uintptr_t m_bDormant = 0xED;

    // uintptr_t client_DLL = 0x29780000;

    // uintptr_t dwEntityList = 0x4DFFF7C;

    // uintptr_t dwLocalPlayer = 0xDEA98C;

    // uintptr_t dwViewMatrix = 0x4DF0DC4;

    struct Vec2 {
        float X;
        float Y;
    };

    struct Vec3 {
        float X;
        float Y;
        float Z;
    };

    struct Matrix {
        float VMatrix[16];
    };

    void ConvertToRange(Vec2& Point) {
        Point.X /= 2560;
        Point.X *= 2.0f;
        Point.X -= 1.0f;

        Point.Y /= 1440;
        Point.Y *= 2.0f;
        Point.Y -= 1.0f;
    }

    bool WorldToScreen(const Vec3& VecOrigin, Vec2& VecScreen, float* Matrix) {
        VecScreen.X = VecOrigin.X * Matrix[0] + VecOrigin.Y * Matrix[1] + VecOrigin.Z * Matrix[2] + Matrix[3];
        VecScreen.Y = VecOrigin.X * Matrix[4] + VecOrigin.Y * Matrix[5] + VecOrigin.Z * Matrix[6] + Matrix[7];
        float W = VecOrigin.X * Matrix[12] + VecOrigin.Y * Matrix[13] + VecOrigin.Z * Matrix[14] + Matrix[15];

        if (W < 0.01f) {
            return false;
        }

        Vec2 NDC;
        NDC.X = VecScreen.X / W;
        NDC.Y = VecScreen.Y / W;

        VecScreen.X = (2560 / 2 * NDC.X) + (NDC.X + 2560 / 2);
        VecScreen.Y = (1440 / 2 * NDC.Y) + (NDC.Y + 1440 / 2);

        ConvertToRange(VecScreen);

        return true;
    }

public:
    float v_friendly_color[3] = {0, 0, 1};
    float v_enemy_color[3] = {1, 0, 0};
    float v_Health_color[3] = {0.22, 0.67, 0};

    bool c_box = false;
    bool c_line = false;
    bool c_Health = false;

    uintptr_t localplayer_ = 0; 
    uintptr_t Entity_ = 0;
    uintptr_t viewMatrix_ = 0;

	void Esp(HANDLE process, bool c_ESP_enemy, bool c_ESP_friendly) {
        Vec2 LineOrgin;
        LineOrgin.X = 0.0f;
        LineOrgin.Y = -1.0f;

        glBegin(GL_LINES);

        uintptr_t Player;
        ReadProcessMemory(process, (LPCVOID)(Entity_ + 0 * 0x10), &Player, sizeof(Player), NULL);

        Vec3 PlayerLocation;
        ReadProcessMemory(process, (LPCVOID)(Player + m_vecOrigin), &PlayerLocation, sizeof(PlayerLocation), NULL);


        Matrix ViewMatrix;
        uintptr_t EntityList;
        uintptr_t Localplayer;

        ReadProcessMemory(process, (LPCVOID)(viewMatrix_), &ViewMatrix, sizeof(ViewMatrix), NULL);
        ReadProcessMemory(process, (LPCVOID)(Entity_), &EntityList, sizeof(EntityList), NULL);
        ReadProcessMemory(process, (LPCVOID)(localplayer_), &Localplayer, sizeof(Localplayer), NULL);

        int Localplayer_Team;
        ReadProcessMemory(process, (LPCVOID)(EntityList + m_iTeamNum), &Localplayer_Team, sizeof(Localplayer_Team), NULL);

        

        for (short int i = 1; i < 64; ++i) {
            uintptr_t Entity;
            ReadProcessMemory(process, (LPCVOID)(Entity_ + i * 0x10), &Entity, sizeof(Entity), NULL);

            if (Entity == NULL) {
                continue;
            }

            int Dormant;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_bDormant), &Dormant, sizeof(Dormant), NULL);

            if (Dormant == 1) {
                continue;
            }

            int Health;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_iHealth), &Health, sizeof(Health), NULL);

            if (Health < 1 || Health > 100) {
                continue;
            }

            int team;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_iTeamNum), &team, sizeof(team), NULL);

            if (team == Localplayer_Team) {
                glColor3f(v_friendly_color[0], v_friendly_color[1], v_friendly_color[2]);
                if (!c_ESP_friendly) {
                    continue;
                }
            }
            else {
                glColor3f(v_enemy_color[0], v_enemy_color[1], v_enemy_color[2]);
                if (!c_ESP_enemy) {
                    continue;
                }
            }

            Vec3 EntityLocation;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_vecOrigin), &EntityLocation, sizeof(EntityLocation), NULL);

            Vec2 ScreenCoords;
            if (!WorldToScreen(EntityLocation, ScreenCoords, ViewMatrix.VMatrix)) {
                continue;
            }

            Vec2 HeadScreenCoords;
            EntityLocation.Z += 75;
            if (!WorldToScreen(EntityLocation, HeadScreenCoords, ViewMatrix.VMatrix)) {
                continue;
            }

            float w = (HeadScreenCoords.Y - ScreenCoords.Y) / 7;

            if (c_line) {
                glVertex2f(ScreenCoords.X, ScreenCoords.Y);
                glVertex2f(LineOrgin.X, LineOrgin.Y);
            }

            if (c_box) {
                glVertex2f(ScreenCoords.X, ScreenCoords.Y);
                glVertex2f(ScreenCoords.X + w, ScreenCoords.Y);

                glVertex2f(ScreenCoords.X, ScreenCoords.Y);
                glVertex2f(ScreenCoords.X - w, ScreenCoords.Y);

                // draw line at the top

                glVertex2f(HeadScreenCoords.X, HeadScreenCoords.Y);
                glVertex2f(HeadScreenCoords.X + w, HeadScreenCoords.Y);

                glVertex2f(HeadScreenCoords.X, HeadScreenCoords.Y);
                glVertex2f(HeadScreenCoords.X - w, HeadScreenCoords.Y);

                // draw line on rigth side

                glVertex2f(ScreenCoords.X + w, ScreenCoords.Y);
                glVertex2f(HeadScreenCoords.X + w, HeadScreenCoords.Y);

                // draw line on left side

                glVertex2f(ScreenCoords.X - w, ScreenCoords.Y);
                glVertex2f(HeadScreenCoords.X - w, HeadScreenCoords.Y);
            }

            if (c_Health) {
                EntityLocation.Z -= 75;

                Vec3 HealthBar;
                HealthBar.X = EntityLocation.X;
                HealthBar.Y = EntityLocation.Y;
                HealthBar.Z = EntityLocation.Z;

                HealthBar.Z += Health * 0.75;

                Vec2 screen_pos;
                WorldToScreen(HealthBar, screen_pos, ViewMatrix.VMatrix);

                glColor3f(v_Health_color[0], v_Health_color[1], v_Health_color[2]);
                glVertex2f(screen_pos.X + (w * 1.2), screen_pos.Y);
                glVertex2f(ScreenCoords.X + (w * 1.2), ScreenCoords.Y);
            }
        }

        glEnd();
	}
};

/*


void f_ESP(HANDLE process, uintptr_t client_DLL) {
    Vec2 LineOrgin;
        LineOrgin.X = 0.0f;
        LineOrgin.Y = -1.0f;

        glBegin(GL_LINES);

        uintptr_t Player;
        ReadProcessMemory(process, (LPCVOID)(client_DLL + dwEntityList + 0 * 0x10), &Player, sizeof(Player), NULL);

        Vec3 PlayerLocation;
        ReadProcessMemory(process, (LPCVOID)(Player + m_vecOrigin), &PlayerLocation, sizeof(PlayerLocation), NULL);


        Matrix ViewMatrix;
        uintptr_t EntityList;
        uintptr_t Localplayer;

        ReadProcessMemory(process, (LPCVOID)(client_DLL + dwViewMatrix), &ViewMatrix, sizeof(ViewMatrix), NULL);
        ReadProcessMemory(process, (LPCVOID)(client_DLL + dwEntityList), &EntityList, sizeof(EntityList), NULL);
        ReadProcessMemory(process, (LPCVOID)(client_DLL + dwLocalPlayer), &Localplayer, sizeof(Localplayer), NULL);

        int Localplayer_Team;
        ReadProcessMemory(process, (LPCVOID)(EntityList + m_iTeamNum), &Localplayer_Team, sizeof(Localplayer_Team), NULL);

        for (short int i = 1; i < 64; ++i) {
            uintptr_t Entity;
            ReadProcessMemory(process, (LPCVOID)(client_DLL + dwEntityList + i * 0x10), &Entity, sizeof(Entity), NULL);

            if (Entity == NULL) {
                continue;
            }

            int Dormant;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_bDormant), &Dormant, sizeof(Dormant), NULL);

            if (Dormant == 1) {
                continue;
            }

            int Health;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_iHealth), &Health, sizeof(Health), NULL);

            if (Health < 1 || Health > 100) {
                continue;
            }

            int team;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_iTeamNum), &team, sizeof(team), NULL);

            if (team == Localplayer_Team) {
                glColor3f(v_friendly_color[0], v_friendly_color[1], v_friendly_color[2]);
                if (!true) {
                    continue;
                }
            }
            else {
                glColor3f(v_enemy_color[0], v_enemy_color[1], v_enemy_color[2]);
                if (!true) {
                    continue;
                }
            }

            Vec3 EntityLocation;
            ReadProcessMemory(process, (LPCVOID)(Entity + m_vecOrigin), &EntityLocation, sizeof(EntityLocation), NULL);

            Vec2 ScreenCoords;
            if (!WorldToScreen(EntityLocation, ScreenCoords, ViewMatrix.VMatrix)) {
                continue;
            }

            Vec2 HeadScreenCoords;
            EntityLocation.Z += 75;
            if (!WorldToScreen(EntityLocation, HeadScreenCoords, ViewMatrix.VMatrix)) {
                continue;
            }

            float w = (HeadScreenCoords.Y - ScreenCoords.Y) / 7;


            glVertex2f(ScreenCoords.X, ScreenCoords.Y);
            glVertex2f(ScreenCoords.X + w, ScreenCoords.Y);

            glVertex2f(ScreenCoords.X, ScreenCoords.Y);
            glVertex2f(ScreenCoords.X - w, ScreenCoords.Y);

            // draw line at the top

            glVertex2f(HeadScreenCoords.X, HeadScreenCoords.Y);
            glVertex2f(HeadScreenCoords.X + w, HeadScreenCoords.Y);

            glVertex2f(HeadScreenCoords.X, HeadScreenCoords.Y);
            glVertex2f(HeadScreenCoords.X - w, HeadScreenCoords.Y);

            // draw line on rigth side

            glVertex2f(ScreenCoords.X + w, ScreenCoords.Y);
            glVertex2f(HeadScreenCoords.X + w, HeadScreenCoords.Y);

            // draw line on left side

            glVertex2f(ScreenCoords.X - w, ScreenCoords.Y);
            glVertex2f(HeadScreenCoords.X - w, HeadScreenCoords.Y);
            
        }

        glEnd();
}
*/