#pragma once

class PatternAddresses {
public:
	const char* Entity =            "BB ? ? ? ? 83 FF 01 0F 8C ? ? ? ? 3B F8";
	const char* localplayer =       "8D 34 85 ? ? ? ? 89 15 ? ? ? ? 8B 41 08 8B 48 04 83 F9 FF";
	const char* GlowObjectManager = "A1 ? ? ? ? A8 01 75 4B";
	const char* ViewMatrix =        "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9";
	const char* model_ambient_min = "F3 0F 10 0D ? ? ? ? F3 0F 11 4C 24 ? 8B 44 24 20 35 ? ? ? ? 89 44 24 0C";
	const char* ClientState =       "A1 ? ? ? ? 33 D2 6A 00 6A 00 33 C9 89 B0";
	const char* ForceAttack =       "89 0D ? ? ? ? 8B 0D ? ? ? ? 8B F2 8B C1 83 CE 04";
	const char* ForceJump =         "8B 0D ? ? ? ? 8B D6 8B C1 83 CA 02";
	const char* ForceLeft =         "55 8B EC 51 53 8A 5D 08";
	const char* ForceRight =        "55 8B EC 51 53 8A 5D 08";

	// my addresses
	const char* BombTimer =         "CC 28 ? ? 02 00 00 00";
};