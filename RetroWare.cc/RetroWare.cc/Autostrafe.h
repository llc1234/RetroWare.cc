#pragma once


class Autostrafe {
	uintptr_t dwClientState_ViewAngles = 0x4D90;


public:
	uintptr_t ForceLeft_ = 0;
	uintptr_t ForceRight_ = 0;
	uintptr_t ClientState_ = 0;

	float rot[2] = {0, 0};
	bool one_stop_space = false;

	void autostrafe(HANDLE process) {
		if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			uintptr_t ClientState;
			ReadProcessMemory(process, (void*)ClientState_, &ClientState, sizeof(ClientState), 0);

			float new_rot[2] = { 0, 0 };
			ReadProcessMemory(process, (void*)(ClientState + dwClientState_ViewAngles), &new_rot, sizeof(new_rot), 0);

			if (new_rot[1] > rot[1]) {
				int v = 1;
				WriteProcessMemory(process, (void*)(ForceLeft_), &v, sizeof(v), 0);
				v = 0;
				WriteProcessMemory(process, (void*)(ForceRight_), &v, sizeof(v), 0);

				rot[1] = new_rot[1];
				one_stop_space = true;

			} else if (new_rot[1] < rot[1]) {
				int v = 1;
				WriteProcessMemory(process, (void*)(ForceRight_), &v, sizeof(v), 0);
				v = 0;
				WriteProcessMemory(process, (void*)(ForceLeft_), &v, sizeof(v), 0);

				rot[1] = new_rot[1];
				one_stop_space = true;

			}
			
		} else {
			if (one_stop_space) {
				int v = 0;
				WriteProcessMemory(process, (void*)(ForceRight_), &v, sizeof(v), 0);
				v = 0;
				WriteProcessMemory(process, (void*)(ForceLeft_), &v, sizeof(v), 0);

				one_stop_space = false;
			}
		}
	}
};