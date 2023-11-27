#include <array>
#include <cmath>
#include <thread>
#include <numbers>
#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "addresses.h"
#include "cheats_setup.h"

#include "menu.h"
#include "StartMenu.h"

#include "ESP.h"
#include "Rage.h"
#include "Glow.h"
#include "Bhop.h"
#include "Radar.h"
#include "Chams.h"
#include "AimBot.h"
#include "Smokes.h"
#include "NoFlash.h"
#include "BombTimer.h"
#include "TriggerBot.h"
#include "Autostrafe.h"
#include "FovChanger.h"
#include "SkinChanger.h"
#include "OutOfFovArrows.h"

// mp_roundtime_defuse 60; mp_autoteambalance 0; mp_restartgame 1; mp_limitteams 0;
// sv_cheats 1; mp_drop_knife_enable 1; mp_items_prohibited 0; give weapon_knife_m9_bayonet; ent_fire weapon_knife addoutput "classname weapon_knifegg"
// sv_cheats 1; mp_drop_knife_enable 1; mp_items_prohibited 0; give weapon_knife_karambit; ent_fire weapon_knife addoutput "classname weapon_knifegg"
// sv_cheats 1; mp_drop_knife_enable 1; mp_items_prohibited 0; give weapon_knife_stiletto; ent_fire weapon_knife addoutput "classname weapon_knifegg"

// sv_cheats 1; mp_roundtime_defuse 60; bot_zombie 1; mp_restartgame 1;

class Window {
    GLFWwindow* window;

    GLFWmonitor* PrimaryMonitor;

    int window_width;
    int window_height;

    bool insert = false;

    bool menu_open = true;
    
    Menu* menu = new Menu();
    StartMenu* startmenu = new StartMenu();

    Addresses* addresses = new Addresses();
    Cheats_setup* cheat_setup = new Cheats_setup();
    
    ESP* esp = new ESP();
    Rage* rage = new Rage();
    Glow* glow = new Glow();
    Bhop* bhop = new Bhop();
    Radar* radar = new Radar();
    Chams* chams = new Chams();
    AimBot* aimbot = new AimBot();
    Smokes* smokes = new Smokes();
    NoFlash* noflash = new NoFlash();
    BombTimer* bombtimer = new BombTimer();
    TriggerBot* triggerbot = new TriggerBot();
    Autostrafe* autostrafe = new Autostrafe();
    FovChanger* fovchanger = new FovChanger();
    SkinChanger* skinchanger = new SkinChanger();
    OutOfFovArrows* outoffovarrows = new OutOfFovArrows();

public:
    void imgui_setup() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");

        menu->imgui_style();
    }

    bool ShouldCloseWindow() {
        return glfwWindowShouldClose(window);
    }

    void cheat_setup_addresses() {
        cheat_setup->setup();
        addresses->scan(cheat_setup->PID);

        autostrafe->ClientState_ = addresses->ClientState;
        autostrafe->ForceLeft_ = addresses->ForceLeft;
        autostrafe->ForceRight_ = addresses->ForceRight;

        bhop->Entity_ = addresses->Entity;
        bhop->ForceJump_ = addresses->ForceJump;

        noflash->Entity_ = addresses->Entity;

        aimbot->ClientState_ = addresses->ClientState;
        aimbot->Entity_ = addresses->Entity;
        aimbot->localplayer_ = addresses->localplayer;
        aimbot->ForceAttack_ = addresses->ForceAttack;

        fovchanger->localplayer = addresses->localplayer;

        chams->Entity_ = addresses->Entity;
        chams->localplayer_ = addresses->localplayer;
        chams->model_ambient_min_ = addresses->model_ambient_min;

        glow->llocalplayer = addresses->localplayer;
        glow->Entity = addresses->Entity;
        glow->GlowObjectManager = addresses->GlowObjectManager;

        esp->localplayer_ = addresses->localplayer;
        esp->Entity_ = addresses->Entity;
        esp->viewMatrix_ = addresses->ViewMatrix;

        smokes->localplayer_ = addresses->localplayer;
        smokes->Entity_ = addresses->Entity;
        smokes->viewMatrix_ = addresses->ViewMatrix;
        smokes->ClientState_ = addresses->ClientState;
        smokes->ForceAttack_ = addresses->ForceAttack;
        smokes->ForceJump_ = addresses->ForceJump;

        skinchanger->ClientState_ = addresses->ClientState;
        skinchanger->Entity_ = addresses->Entity;
        skinchanger->localplayer_ = addresses->localplayer;

        bombtimer->BombTimer_ = addresses->BombTimer;

        triggerbot->Entity_ = addresses->Entity;
        triggerbot->ForceAttack_ = addresses->ForceAttack;

        outoffovarrows->Entity_ = addresses->Entity;
        outoffovarrows->ClientState_ = addresses->ClientState;

        radar->Entity_ = addresses->Entity;

        rage->ClientState_ = addresses->ClientState;
        rage->EntityList_ = addresses->Entity;
    }

    void setup() {
        glfwInit();

        PrimaryMonitor = glfwGetPrimaryMonitor();

        window_width = glfwGetVideoMode(PrimaryMonitor)->width;
        window_height = glfwGetVideoMode(PrimaryMonitor)->height;

        glfwWindowHint(GLFW_FLOATING, true);
        glfwWindowHint(GLFW_RESIZABLE, false);
        // glfwWindowHint(GLFW_MAXIMIZED, true);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, true);

        window = glfwCreateWindow(window_width, window_height, "RetroWare.cc", NULL, NULL);
        // window = glfwCreateWindow(1176, 664, "RetroWare", NULL, NULL);

        glfwSetWindowAttrib(window, GLFW_DECORATED, false);
        glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, false);

        glfwMakeContextCurrent(window);

        // glfwSetWindowPos(window, 745, 376);
        glfwSetWindowPos(window, 0, 0);

        imgui_setup();

        std::thread([&]() {cheat_loop_thread_1();}).detach();
        std::thread([&]() {cheat_loop_thread_2();}).detach();
    }

    void imgui_newframe() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void imgui_render() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void imgui_watermark() {
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowSize(ImVec2(80, 15));
        ImGui::Begin("WaterMark", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);
        ImGui::Text("RetroWare");
        ImGui::End();
    }

    void display_menu() {
        if (menu_open) {
            glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, false);
            menu->main_menu();
            
        } else {
            glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, true);

        }

        imgui_watermark();
    }

    void open_close_menu() {
        display_menu();

        if (insert && (GetKeyState(VK_INSERT) & 0x8000)) {
            insert = false;
            menu_open = !menu_open;
        }

        if (!(GetKeyState(VK_INSERT) & 0x8000)) {
            insert = true;
        }
    }

    void cheat_loop_thread_1() {
        while (true) {
            if (menu->c_glow_enable) {
                glow->glow_Enemy_color[0] = menu->v_glow_enemy[0];
                glow->glow_Enemy_color[1] = menu->v_glow_enemy[1];
                glow->glow_Enemy_color[2] = menu->v_glow_enemy[2];

                glow->glow_Team_color[0] = menu->v_glow_frendly[0];
                glow->glow_Team_color[1] = menu->v_glow_frendly[1];
                glow->glow_Team_color[2] = menu->v_glow_frendly[2];

                glow->glow_Spotted_color[0] = menu->v_glow_spotted[0];
                glow->glow_Spotted_color[1] = menu->v_glow_spotted[1];
                glow->glow_Spotted_color[2] = menu->v_glow_spotted[2];

                glow->glow(cheat_setup->process, menu->c_glow_enemy, menu->c_glow_frendly, menu->c_glow_spotted);
            }

            if (menu->c_Enable_TriggerBot) {
                triggerbot->triggerbot(cheat_setup->process);
            }

            // rage->rage(cheat_setup->process);
        }
    }

    void cheat_loop_thread_2() {
        while (true) {
            if (menu->c_Fov_changer) {
                fovchanger->changer_Fov(cheat_setup->process, menu->v_Fov);
            }

            if (menu->c_Chams_enable) {
                chams->v_Chams_enemy[0] = menu->v_Chams_enemy_color[0] * 255;
                chams->v_Chams_enemy[1] = menu->v_Chams_enemy_color[1] * 255;
                chams->v_Chams_enemy[2] = menu->v_Chams_enemy_color[2] * 255;

                chams->v_Chams_frendly[0] = menu->v_Chams_frendly_color[0] * 255;
                chams->v_Chams_frendly[1] = menu->v_Chams_frendly_color[1] * 255;
                chams->v_Chams_frendly[2] = menu->v_Chams_frendly_color[2] * 255;

                chams->brightness = menu->v_Chams_brightness;

                chams->chams(cheat_setup->process, menu->c_Chams_enemy, menu->c_Chams_frendly);
            }

            if (menu->c_Enable_AimBot) {
                aimbot->smoothing = menu->AimBot_smoothing;
                aimbot->v_aimFov = menu->AimBot_Fov;

                aimbot->aimBot(cheat_setup->process, menu->c_AimBot_automatic_fire, menu->c_AimBot_aim_through_wall);
            }

            if (menu->c_Enable_Bhop) {
                bhop->bhop(cheat_setup->process);
            }

            if (menu->c_Enable_NoFlash) {
                noflash->noflash(cheat_setup->process);
            }

            if (menu->c_Enable_AutoStrafe) {
                autostrafe->autostrafe(cheat_setup->process);
            }

            if (menu->c_Enable_Skin) {
                skinchanger->skinchanger(cheat_setup->process, menu->v_skin_id, menu->v_skin_number);
            }

            if (menu->c_Enable_Radar) {
                radar->radar(cheat_setup->process);
            }
        }
    }

    void cheat_loop() {
        if (menu->c_ESP_enable) {
            esp->v_enemy_color[0] = menu->v_ESP_enemy[0];
            esp->v_enemy_color[1] = menu->v_ESP_enemy[1];
            esp->v_enemy_color[2] = menu->v_ESP_enemy[2];

            esp->v_friendly_color[0] = menu->v_ESP_frendly[0];
            esp->v_friendly_color[1] = menu->v_ESP_frendly[1];
            esp->v_friendly_color[2] = menu->v_ESP_frendly[2];

            esp->c_box = menu->c_ESP_box;
            esp->c_line = menu->c_ESP_line;
            esp->c_Health = menu->c_ESP_Health;

            esp->Esp(cheat_setup->process, menu->c_ESP_enemy, menu->c_ESP_frendly);
        }

        if (menu->c_Enable_Smokes) {
            smokes->v_color[0] = menu->v_Smokes_color[0];
            smokes->v_color[1] = menu->v_Smokes_color[1];
            smokes->v_color[2] = menu->v_Smokes_color[2];

            smokes->smokes(cheat_setup->process);
        }

        if (menu->c_Enable_BombTimer) {
            bombtimer->bombtimer(cheat_setup->process);
        }

        if (menu->c_Enable_OutOfFovArrows) {
            outoffovarrows->outoffovarrows(cheat_setup->process, menu->v_OutOfFovArrows_color);
        }
    }

    void update() {
        glClear(GL_COLOR_BUFFER_BIT);
        glLineWidth(2);

        
        imgui_newframe();
        if (startmenu->display_startmenu) {
            if (startmenu->one_time) {
                cheat_setup_addresses();
            }

            startmenu->startmenu();
        } else {
            open_close_menu();
        }
        imgui_render();
        cheat_loop();
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
        glfwSwapInterval(0);
    }
};


int main() {
    Window* window = new Window();
    
    window->setup();

    while (!window->ShouldCloseWindow()) {
        window->update();
    }

    return 0;
}