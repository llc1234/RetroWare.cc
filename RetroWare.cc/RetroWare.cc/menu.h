#pragma once

class Menu {
public:
    bool c_Fov_changer = false;
    int v_Fov = 90;
    
    bool c_glow_enable = false;
    bool c_glow_enemy = false;
    bool c_glow_frendly = false;
    bool c_glow_spotted = false;

    float v_glow_enemy[3] = {1, 0, 0};
    float v_glow_frendly[3] = {0, 0, 1};
    float v_glow_spotted[3] = {1, 1, 1};

    bool c_ESP_enable = false;
    bool c_ESP_enemy = false;
    bool c_ESP_frendly = false;

    bool c_ESP_box = false;
    bool c_ESP_line = false;
    bool c_ESP_Health = false;

    float v_ESP_enemy[3] = {1, 0, 0};
    float v_ESP_frendly[3] = {0, 0, 1};

    bool c_Chams_enable = false;
    bool c_Chams_enemy = false;
    bool c_Chams_frendly = false;

    float v_Chams_enemy_color[3] = {1, 0, 0};
    float v_Chams_frendly_color[3] = {0, 0, 1};

    float v_Chams_brightness = 0;

    bool c_Enable_OutOfFovArrows = false;
    float v_OutOfFovArrows_color[3] = {1, 0, 0};

    bool c_Enable_Radar = false;

    bool c_Enable_TriggerBot = false;

    bool c_Enable_AimBot = false;
    bool c_AimBot_automatic_fire = false;
    bool c_AimBot_aim_through_wall = false;

    float AimBot_Fov = 0;
    float AimBot_smoothing = 1;

    bool c_Enable_Smokes = false;
    float v_Smokes_color[3] = {1, 1, 1};

    bool c_Enable_Bhop = false;
    bool c_Enable_AutoStrafe = false;
    bool c_Enable_NoFlash = false;
    bool c_Enable_BombTimer = false;

    bool c_Enable_Skin = false;
    int v_skin_id = 0;
    int v_skin_number = 0;

    const char* weapons_name[84] = { "WEAPON_DEAGLE","WEAPON_ELITE","WEAPON_FIVESEVEN","WEAPON_GLOCK","WEAPON_AK47","WEAPON_AUG","WEAPON_AWP","WEAPON_FAMAS","WEAPON_G3SG1","WEAPON_GALILAR","WEAPON_M249","WEAPON_M4A1","WEAPON_MAC10","WEAPON_P90","WEAPON_MP5SD","WEAPON_UMP45","WEAPON_XM1014","WEAPON_BIZON","WEAPON_MAG7","WEAPON_NEGEV","WEAPON_SAWEDOFF","WEAPON_TEC9","WEAPON_TASER","WEAPON_HKP2000","WEAPON_MP7","WEAPON_MP9","WEAPON_NOVA","WEAPON_P250","WEAPON_SHIELD","WEAPON_SCAR20","WEAPON_SG556","WEAPON_SSG08","WEAPON_KNIFEGG","WEAPON_KNIFE","WEAPON_FLASHBANG","WEAPON_HEGRENADE","WEAPON_SMOKEGRENADE","WEAPON_MOLOTOV","WEAPON_DECOY","WEAPON_INCGRENADE","WEAPON_C4","WEAPON_HEALTHSHOT","WEAPON_KNIFE_T","WEAPON_M4A1_SILENCER","WEAPON_USP_SILENCER","WEAPON_CZ75A","WEAPON_REVOLVER","WEAPON_TAGRENADE","WEAPON_FISTS","WEAPON_BREACHCHARGE","WEAPON_TABLET","WEAPON_MELEE","WEAPON_AXE","WEAPON_HAMMER","WEAPON_SPANNER","WEAPON_KNIFE_GHOST","WEAPON_FIREBOMB","WEAPON_DIVERSION","WEAPON_FRAG_GRENADE","WEAPON_SNOWBALL","WEAPON_BUMPMINE","WEAPON_BAYONET","WEAPON_KNIFE_FLIP","WEAPON_KNIFE_GUT","WEAPON_KNIFE_KARAMBIT","WEAPON_KNIFE_M9_BAYONET","WEAPON_KNIFE_TACTICAL","WEAPON_KNIFE_FALCHION","WEAPON_KNIFE_SURVIVAL_BOWIE","WEAPON_KNIFE_BUTTERFLY","WEAPON_KNIFE_PUSH","WEAPON_KNIFE_URSUS","WEAPON_KNIFE_GYPSY_JACKKNIFE","WEAPON_KNIFE_STILETTO","WEAPON_KNIFE_WIDOWMAKER","STUDDED_BLOODHOUND_GLOVES","T_GLOVES","CT_GLOVES","SPORTY_GLOVES","SLICK_GLOVES","LEATHER_HANDWRAPS","MOTORCYCLE_GLOVES","SPECIALIST_GLOVES","STUDDED_HYDRA_GLOVES" };
    

    void tab_Visuals() {
        ImGui::SetCursorPos(ImVec2(10, 50));
        ImGui::BeginChildFrame('1', ImVec2(310, 392), 0);

        ImGui::Checkbox("ESP", &c_ESP_enable);

        ImGui::Checkbox("ESP enemy                           ", &c_ESP_enemy);
        ImGui::SameLine();
        ImGui::ColorEdit3("ESP enemy color", v_ESP_enemy, ImGuiColorEditFlags_NoInputs);

        ImGui::Checkbox("ESP frendly                         ", &c_ESP_frendly);
        ImGui::SameLine();
        ImGui::ColorEdit3("ESP frendly color", v_ESP_frendly, ImGuiColorEditFlags_NoInputs);

        ImGui::Checkbox("ESP box", &c_ESP_box);
        ImGui::Checkbox("ESP line", &c_ESP_line);
        ImGui::Checkbox("ESP Health", &c_ESP_Health);


        ImGui::Text("");
        ImGui::Checkbox("Glow", &c_glow_enable);
        ImGui::Checkbox("Glow enemy                          ", &c_glow_enemy);
        ImGui::SameLine();
        ImGui::ColorEdit3("Glow enemy color", v_glow_enemy, ImGuiColorEditFlags_NoInputs);
        

        ImGui::Checkbox("Glow frendly                        ", &c_glow_frendly);
        ImGui::SameLine();
        ImGui::ColorEdit3("Glow frendly color", v_glow_frendly, ImGuiColorEditFlags_NoInputs);

        ImGui::Checkbox("Spotted color                       ", &c_glow_spotted);
        ImGui::SameLine();
        ImGui::ColorEdit3("Spotted color enemy color", v_glow_spotted, ImGuiColorEditFlags_NoInputs);

        
        ImGui::Text("");
        ImGui::Checkbox("Chams", &c_Chams_enable);
        ImGui::Checkbox("enemy                               ", &c_Chams_enemy);
        ImGui::SameLine();
        ImGui::ColorEdit3("enemy  ", v_Chams_enemy_color, ImGuiColorEditFlags_NoInputs);

        ImGui::Checkbox("frendly                             ", &c_Chams_frendly);
        ImGui::SameLine();
        ImGui::ColorEdit3("frendly  ", v_Chams_frendly_color, ImGuiColorEditFlags_NoInputs);

        ImGui::SliderFloat("brightness", &v_Chams_brightness, 0, 70);
        

        ImGui::EndChild();

        ImGui::SetCursorPos(ImVec2(310 + 20, 50));
        ImGui::BeginChildFrame('2', ImVec2(310, 392), 0);

        ImGui::Checkbox("Fov Changer", &c_Fov_changer);
        ImGui::SliderInt("Fov", &v_Fov, 40, 170);

        ImGui::Checkbox("Out Of Fov Arrows                   ", &c_Enable_OutOfFovArrows);
        ImGui::SameLine();
        ImGui::ColorEdit3("Out Of Fov Arrows color", v_OutOfFovArrows_color, ImGuiColorEditFlags_NoInputs);
        ImGui::Checkbox("Radar", &c_Enable_Radar);

        ImGui::EndChild();
    }

    void tab_Legit() {
        ImGui::SetCursorPos(ImVec2(10, 50));
        ImGui::BeginChildFrame('1', ImVec2(310, 392), 0);

        ImGui::Checkbox("TriggerBot", &c_Enable_TriggerBot);

        ImGui::Checkbox("AimBot", &c_Enable_AimBot);
        ImGui::Checkbox("Automatic fire", &c_AimBot_automatic_fire);
        ImGui::Checkbox("aim through wall", &c_AimBot_aim_through_wall);

        ImGui::SliderFloat("Fov", &AimBot_Fov, 0, 35);
        ImGui::SliderFloat("smoothing", &AimBot_smoothing, 1, 500);

        ImGui::EndChild();

        ImGui::SetCursorPos(ImVec2(310 + 20, 50));
        ImGui::BeginChildFrame('2', ImVec2(310, 392), 0);

        ImGui::EndChild();
    }

    void tab_Misc() {
        ImGui::SetCursorPos(ImVec2(10, 50));
        ImGui::BeginChildFrame('1', ImVec2(310, 392), 0);
        
        // ImGui::Checkbox("Smoke Locations                     ", &c_Enable_Smokes);
        // ImGui::SameLine();
        // ImGui::ColorEdit3("     ", v_Smokes_color, ImGuiColorEditFlags_NoInputs);

        ImGui::Checkbox("Bhop", &c_Enable_Bhop);
        ImGui::Checkbox("AutoStrafe", &c_Enable_AutoStrafe);
        ImGui::Checkbox("NoFlash", &c_Enable_NoFlash);
        ImGui::Checkbox("BombTimer", &c_Enable_BombTimer);

        ImGui::EndChild();

        ImGui::SetCursorPos(ImVec2(310 + 20, 50));
        ImGui::BeginChildFrame('2', ImVec2(310, 392), 0);

        ImGui::EndChild();
    }

    void tab_Skins() {
        ImGui::SetCursorPos(ImVec2(10, 50));
        ImGui::BeginChildFrame('1', ImVec2(310, 392), 0);

        ImGui::Checkbox("Enable SkinChanger", &c_Enable_Skin);
        
        static const char* current_item = "WEAPON_DEAGLE";

        if (ImGui::BeginCombo("weapon", current_item)) {
            for (int n = 0; n < IM_ARRAYSIZE(weapons_name); n++) {
                bool is_selected = (current_item == weapons_name[n]);
                if (ImGui::Selectable(weapons_name[n], is_selected))
                    current_item = weapons_name[n];
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }

        static int myIntValue = 0;
        ImGui::InputInt("skin ID", &myIntValue);

        if (ImGui::Button("change skin")) {
            for (int i = 0; i < IM_ARRAYSIZE(weapons_name); i++) {
                if (weapons_name[i] == current_item) {
                    v_skin_id = i;
                    v_skin_number = myIntValue;
                }
            }
        }

        ImGui::EndChild();

        ImGui::SetCursorPos(ImVec2(310 + 20, 50));
        ImGui::BeginChildFrame('2', ImVec2(310, 392), 0);

        ImGui::EndChild();
    }

    void menu_Tabs() {
        ImGui::BeginTabBar("Tabs");

        if (ImGui::BeginTabItem("Visuals")) {
            tab_Visuals();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Legit")) {
            tab_Legit();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Misc")) {
            tab_Misc();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Skins")) {
            tab_Skins();
            ImGui::EndTabItem();
        }
        
        ImGui::EndTabBar();
    }

    void main_menu() {
        ImGui::SetNextWindowSize(ImVec2(650, 450));
        ImGui::Begin("RetroWare V0.1.0", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

        menu_Tabs();

        ImGui::End();
    }

    void imgui_style() {
        ImVec4* colors = ImGui::GetStyle().Colors;

        colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
        colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

        ImGuiStyle& style = ImGui::GetStyle();

        style.WindowPadding = ImVec2(8.00f, 8.00f);
        style.FramePadding = ImVec2(5.00f, 2.00f);
        style.CellPadding = ImVec2(6.00f, 6.00f);
        style.ItemSpacing = ImVec2(6.00f, 6.00f);
        style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
        style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
        style.IndentSpacing = 25;
        style.ScrollbarSize = 15;
        style.GrabMinSize = 10;
        style.WindowBorderSize = 1;
        style.ChildBorderSize = 1;
        style.PopupBorderSize = 1;
        style.FrameBorderSize = 1;
        style.TabBorderSize = 3;
        style.WindowRounding = 7;
        style.ChildRounding = 4;
        style.FrameRounding = 3;
        style.PopupRounding = 4;
        style.ScrollbarRounding = 9;
        style.GrabRounding = 3;
        style.LogSliderDeadzone = 4;
        style.TabRounding = 3;
    }
};