#pragma once

class StartMenu {
public:
	
	bool display_startmenu = true;

	bool main_display = true;

	bool one_time = false;

	void startmenu() {
		ImGui::SetNextWindowSize(ImVec2(250, 150));
		ImGui::Begin("RetroWare", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
		
		if (one_time) {
			display_startmenu = false;
		}

		if (main_display) {
			ImGui::Text("Version: 0.1.0");
			ImGui::Text("Release date: 30.7.2023");

			ImGui::SetCursorPos(ImVec2(10, 110));
			if (ImGui::Button("Load Cheat", ImVec2(232, 30))) {
				main_display = false;
			}
		} else {
			ImGui::SetCursorPos(ImVec2(10, 110));
			ImGui::Text("Waiting for CSGO...");

			if (FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9") == 0) {
				exit(-1);
			} else {
				Sleep(1000);
				one_time = true;
			}
		}
		
		ImGui::End();
	}
};