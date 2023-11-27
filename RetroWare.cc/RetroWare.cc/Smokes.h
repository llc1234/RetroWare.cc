#pragma once

// x: 1284.16, y: -853.186, z: -167.969

class Smokes {
    uintptr_t m_vecOrigin = 0x138;
    uintptr_t m_iTeamNum = 0xF4;
    uintptr_t m_iHealth = 0x100;
    uintptr_t m_bDormant = 0xED;
    uintptr_t dwClientState_ViewAngles = 0x4D90;

    float smokeLocations[9][5] = { 
        {1284.16, -853.186, -167.969, -21.77, -144.135},
        {743.909, -1436.92, -260.272, -40.2659, -179.97},
        {1302.18, -183.096, -167.969, -47.291, -176.923},
        {-164.303, 534.36, -69.5491, -12, -156.712},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

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
    uintptr_t localplayer_ = 0;
    uintptr_t Entity_ = 0;
    uintptr_t viewMatrix_ = 0;
    uintptr_t ClientState_ = 0;
    uintptr_t ForceAttack_ = 0;
    uintptr_t ForceJump_ = 0;

    float v_color[3] = { 1, 1, 1 };

    void DrawLine(Matrix ViewMatrix, float x1, float y1, float z1, float x2, float y2, float z2) {
        Vec3 Line_1;
        Line_1.X = x1;
        Line_1.Y = y1;
        Line_1.Z = z1;

        Vec3 Line_2;
        Line_2.X = x2;
        Line_2.Y = y2;
        Line_2.Z = z2;

        Vec2 ScreenCoords_line1;
        Vec2 ScreenCoords_line2;

        WorldToScreen(Line_1, ScreenCoords_line1, ViewMatrix.VMatrix);
        WorldToScreen(Line_2, ScreenCoords_line2, ViewMatrix.VMatrix);

        glVertex2f(ScreenCoords_line1.X, ScreenCoords_line1.Y);
        glVertex2f(ScreenCoords_line2.X, ScreenCoords_line2.Y);
    }

    void DrawCircle(Matrix ViewMatrix, float x1, float y1, float z1, float size) {
        float rot = 0;

        for (int i = 0; i < 12; i++) {
            DrawLine(ViewMatrix, 
                x1 + sin(rot) * size, y1 + cos(rot) * size, z1,
                x1 + sin(rot + 30.41666 / 180 * 3.1415) * size, y1 + cos(rot + 30.41666 / 180 * 3.1415) * size, z1
            );

            rot += 30.41666 / 180 * 3.1415;
        }
    }

    void smokes(HANDLE process) {
        glBegin(GL_LINES);

        // uintptr_t Player;
        // ReadProcessMemory(process, (LPCVOID)(Entity_ + 0 * 0x10), &Player, sizeof(Player), NULL);

        // Vec3 PlayerLocation;
        // ReadProcessMemory(process, (LPCVOID)(Player + m_vecOrigin), &PlayerLocation, sizeof(PlayerLocation), NULL);


        Matrix ViewMatrix;
        uintptr_t EntityList;
        uintptr_t Localplayer;

        ReadProcessMemory(process, (LPCVOID)(viewMatrix_), &ViewMatrix, sizeof(ViewMatrix), NULL);
        ReadProcessMemory(process, (LPCVOID)(Entity_), &EntityList, sizeof(EntityList), NULL);
        ReadProcessMemory(process, (LPCVOID)(localplayer_), &Localplayer, sizeof(Localplayer), NULL);

        uintptr_t Player;
        ReadProcessMemory(process, (LPCVOID)(Entity_ + 0 * 0x10), &Player, sizeof(Player), NULL);

        Vec3 PlayerLocation;
        ReadProcessMemory(process, (LPCVOID)(Player + m_vecOrigin), &PlayerLocation, sizeof(PlayerLocation), NULL);

        // std::cout << "x: " << PlayerLocation.X << ", y: " << PlayerLocation.Y << ", z: " << PlayerLocation.Z << std::endl;
        
        float rot[2];
        uintptr_t ClientState;
        ReadProcessMemory(process, (LPCVOID)(ClientState_), &ClientState, sizeof(ClientState), NULL);
        ReadProcessMemory(process, (LPCVOID)(ClientState + dwClientState_ViewAngles), &rot, sizeof(rot), NULL);
        
        //std::cout << "rot: " << rot[0] << ", rot: " << rot[1] << std::endl;

        // std::cout << PlayerLocation.X << ", " << PlayerLocation.Y << ", " << PlayerLocation.Z << ", " << rot[0] << ", " << rot[1] << std::endl;

        glColor3f(v_color[0], v_color[1], v_color[2]);

        bool auto_bot = false;
        if (GetKeyState('P') & 0x8000) {
            auto_bot = true;
        }

        for (int i = 0; i < 9; i++) {
            DrawCircle(
                ViewMatrix,
                smokeLocations[i][0], smokeLocations[i][1], smokeLocations[i][2], 20
            );

            DrawLine(ViewMatrix,
                smokeLocations[i][0] + 20, smokeLocations[i][1], smokeLocations[i][2],
                smokeLocations[i][0] - 20, smokeLocations[i][1], smokeLocations[i][2]
            );

            DrawLine(ViewMatrix,
                smokeLocations[i][0], smokeLocations[i][1] + 20, smokeLocations[i][2],
                smokeLocations[i][0], smokeLocations[i][1] - 20, smokeLocations[i][2]
            );

            if (auto_bot) {
                float vor = hypot(PlayerLocation.X - smokeLocations[i][0], PlayerLocation.Y - smokeLocations[i][1]);

                

                if (vor < 20) {
                    float nr[2] = {smokeLocations[i][3], smokeLocations[i][4]};
                    WriteProcessMemory(process, (void*)(ClientState + dwClientState_ViewAngles), &nr, sizeof(nr), NULL);

                    int f = 5;
                    WriteProcessMemory(process, (void*)(ForceAttack_), &f, sizeof(f), NULL);
                    WriteProcessMemory(process, (void*)(ForceJump_), &f, sizeof(f), NULL);


                    f = 4;
                    WriteProcessMemory(process, (void*)(ForceAttack_), &f, sizeof(f), NULL);
                    f = 0;
                    WriteProcessMemory(process, (void*)(ForceJump_), &f, sizeof(f), NULL);
                }
            }
        }


        glEnd();
    }
};