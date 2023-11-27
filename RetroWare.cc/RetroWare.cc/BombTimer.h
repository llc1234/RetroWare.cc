#pragma once


class BombTimer {


public:
	uintptr_t BombTimer_ = 0;

	bool one = true;
	float start_time = 0;

	float map(float x, float in_min, float in_max, float out_min, float out_max) {
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

	void bombtimer(HANDLE process) {
		int is_planted = 0;
		ReadProcessMemory(process, (void*)BombTimer_, &is_planted, sizeof(is_planted), 0);

		if (is_planted) {
			// ImGui::SetNextWindowPos(ImVec2(30, 30));
			// ImGui::SetNextWindowSize(ImVec2(100, 50));
			// ImGui::Begin("Bomb Timer");

			float n = (clock() - start_time) / 1000;

			n = 40 - n;

			if (n <= 0) {
				n = 0;
			}

			float w = map(n, 0, 40, -1, 1);

			// std::string s = std::to_string(n);
			// ImGui::Text(s.c_str());
			// ImGui::End();
			glBegin(GL_QUADS);
			glColor3f(0.22, 0.67, 0);
			glVertex2f(w, 1);
			glVertex2f(-1, 1);
			glVertex2f(-1, 0.98);
			glVertex2f(w, 0.98);
			glEnd();

			if (one) {
				start_time = clock();
				one = false;
			}
		} else {
			one = true;
		}
	}
};