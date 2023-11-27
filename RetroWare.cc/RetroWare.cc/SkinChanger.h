#pragma once

// deagle 711
// glock 38
// ak 490
// awp 344
// usp 653

enum WeaponIds {
    WEAPON_DEAGLE = 1,
    WEAPON_ELITE = 2,
    WEAPON_FIVESEVEN = 3,
    WEAPON_GLOCK = 4,
    WEAPON_AK47 = 7,
    WEAPON_AUG = 8,
    WEAPON_AWP = 9,
    WEAPON_FAMAS = 10,
    WEAPON_G3SG1 = 11,
    WEAPON_GALILAR = 13,
    WEAPON_M249 = 14,
    WEAPON_M4A1 = 16,
    WEAPON_MAC10 = 17,
    WEAPON_P90 = 19,
    WEAPON_MP5SD = 23,
    WEAPON_UMP45 = 24,
    WEAPON_XM1014 = 25,
    WEAPON_BIZON = 26,
    WEAPON_MAG7 = 27,
    WEAPON_NEGEV = 28,
    WEAPON_SAWEDOFF = 29,
    WEAPON_TEC9 = 30,
    WEAPON_TASER = 31,
    WEAPON_HKP2000 = 32,
    WEAPON_MP7 = 33,
    WEAPON_MP9 = 34,
    WEAPON_NOVA = 35,
    WEAPON_P250 = 36,
    WEAPON_SHIELD = 37,
    WEAPON_SCAR20 = 38,
    WEAPON_SG556 = 39,
    WEAPON_SSG08 = 40,
    WEAPON_KNIFEGG = 41,
    WEAPON_KNIFE = 42,
    WEAPON_FLASHBANG = 43,
    WEAPON_HEGRENADE = 44,
    WEAPON_SMOKEGRENADE = 45,
    WEAPON_MOLOTOV = 46,
    WEAPON_DECOY = 47,
    WEAPON_INCGRENADE = 48,
    WEAPON_C4 = 49,
    WEAPON_HEALTHSHOT = 57,
    WEAPON_KNIFE_T = 59,
    WEAPON_M4A1_SILENCER = 60,
    WEAPON_USP_SILENCER = 61,
    WEAPON_CZ75A = 63,
    WEAPON_REVOLVER = 64,
    WEAPON_TAGRENADE = 68,
    WEAPON_FISTS = 69,
    WEAPON_BREACHCHARGE = 70,
    WEAPON_TABLET = 72,
    WEAPON_MELEE = 74,
    WEAPON_AXE = 75,
    WEAPON_HAMMER = 76,
    WEAPON_SPANNER = 78,
    WEAPON_KNIFE_GHOST = 80,
    WEAPON_FIREBOMB = 81,
    WEAPON_DIVERSION = 82,
    WEAPON_FRAG_GRENADE = 83,
    WEAPON_SNOWBALL = 84,
    WEAPON_BUMPMINE = 85,
    WEAPON_BAYONET = 500,
    WEAPON_KNIFE_FLIP = 505,
    WEAPON_KNIFE_GUT = 506,
    WEAPON_KNIFE_KARAMBIT = 507,
    WEAPON_KNIFE_M9_BAYONET = 508,
    WEAPON_KNIFE_TACTICAL = 509,
    WEAPON_KNIFE_FALCHION = 512,
    WEAPON_KNIFE_SURVIVAL_BOWIE = 514,
    WEAPON_KNIFE_BUTTERFLY = 515,
    WEAPON_KNIFE_PUSH = 516,
    WEAPON_KNIFE_URSUS = 519,
    WEAPON_KNIFE_GYPSY_JACKKNIFE = 520,
    WEAPON_KNIFE_STILETTO = 522,
    WEAPON_KNIFE_WIDOWMAKER = 523,
    STUDDED_BLOODHOUND_GLOVES = 5027,
    T_GLOVES = 5028,
    CT_GLOVES = 5029,
    SPORTY_GLOVES = 5030,
    SLICK_GLOVES = 5031,
    LEATHER_HANDWRAPS = 5032,
    MOTORCYCLE_GLOVES = 5033,
    SPECIALIST_GLOVES = 5034,
    STUDDED_HYDRA_GLOVES = 5035,
};

class SkinChanger {

public:
    int waepon_number[84][2] = {
    {1, 0}, // WEAPON_DEAGLE
    {2, 0}, // WEAPON_ELITE
    {3, 0}, // WEAPON_FIVESEVEN
    {4, 0}, // WEAPON_GLOCK
    {7, 0}, // 
    {8, 0}, // 
    {9, 0}, // 
    {10, 0}, // 
    {11, 0}, // 
    {13, 0}, // 
    {14, 0}, // 
    {16, 0}, // 
    {17, 0}, // 
    {19, 0}, // 
    {23, 0}, // 
    {24, 0}, // 
    {25, 0}, // 
    {26, 0}, // 
    {27, 0}, // 
    {28, 0}, // 
    {29, 0}, // 
    {30, 0}, // 
    {31, 0}, // 
    {32, 0}, // 
    {33, 0}, // 
    {34, 0}, // 
    {35, 0}, // 
    {36, 0}, // 
    {37, 0}, // 
    {38, 0}, // 
    {39, 0}, // 
    {40, 0}, // 
    {41, 0}, // 
    {42, 0}, // 
    {43, 0}, // 
    {44, 0}, // 
    {45, 0}, // 
    {46, 0}, // 
    {47, 0}, // 
    {48, 0}, // 
    {49, 0}, // 
    {57, 0}, // 
    {59, 0}, // 
    {60, 0}, // 
    {61, 0}, // 
    {63, 0}, // 
    {64, 0}, // 
    {68, 0}, // 
    {69, 0}, // 
    {70, 0}, // 
    {72, 0}, // 
    {74, 0}, // 
    {75, 0}, // 
    {76, 0}, // 
    {78, 0}, // 
    {80, 0}, // 
    {81, 0}, // 
    {82, 0}, // 
    {83, 0}, // 
    {84, 0}, // 
    {85, 0}, // 
    {500, 0}, // 
    {505, 0}, // 
    {506, 0}, // 
    {507, 0}, // 
    {508, 0}, // 
    {509, 0}, // 
    {512, 0}, // 
    {514, 0}, // 
    {515, 0}, // 
    {516, 0}, // 
    {519, 0}, // 
    {520, 0}, // 
    {522, 0}, // 
    {523, 0}, // 
    {5027, 0}, // 
    {5028, 0}, // 
    {5029, 0}, // 
    {5030, 0}, // 
    {5031, 0}, // 
    {5032, 0}, // 
    {5033, 0}, // 
    {5034, 0}, // 
    {5035, 0}  // 
    };

	uintptr_t m_hMyWeapons = 0x2E08;

	uintptr_t m_flFallbackWear = 0x31E0;;
	uintptr_t m_nFallbackPaintKit = 0x31D8;
	uintptr_t m_nFallbackSeed = 0x31DC;
	uintptr_t m_nFallbackStatTrak = 0x31E4;
	uintptr_t m_iItemDefinitionIndex = 0x2FBA;
	uintptr_t m_iItemIDHigh = 0x2FD0;
	uintptr_t m_iEntityQuality = 0x2FBC;
	uintptr_t m_iAccountID = 0x2FD8;
	uintptr_t m_OriginalOwnerXuidLow = 0x31D0;

	uintptr_t Entity_ = 0;
	uintptr_t localplayer_ = 0;
	uintptr_t ClientState_ = 0;

	HANDLE h;

	constexpr const int GetWeaponPaint(const short& itemDefinition) {
        for (int i = 0; i < 85; i++) {
            if (waepon_number[i][0] == itemDefinition) {
                return waepon_number[i][1];
            }
        }

        return 0;
	}

	template<typename T> T RPM(SIZE_T address) {
		T buffer;
		ReadProcessMemory(h, (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}

	template<typename T> void WPM(SIZE_T address, T buffer) {
		WriteProcessMemory(h, (LPVOID)address, &buffer, sizeof(buffer), NULL);
	}


	void skinchanger(HANDLE process, int v_skin_id, int v_skin_number) {
		h = process;

        waepon_number[v_skin_id][1] = v_skin_number;

		uintptr_t localplayer;
		ReadProcessMemory(process, (void*) localplayer_, &localplayer, sizeof(localplayer), 0);
		
		const auto& weapons = RPM<std::array<unsigned long, 8>>(localplayer + m_hMyWeapons);

		for (const auto& handle : weapons) {
			uintptr_t weapon;
			ReadProcessMemory(process, (void*)((Entity_ + (handle & 0xFFF) * 0x10) - 0x10), &weapon, sizeof(weapon), 0);
			
			if (!weapon) {
				continue;
			}

			if (const auto paint = GetWeaponPaint(RPM<short>(weapon + m_iItemDefinitionIndex))) {
				
				const bool shouldUpdate = RPM<std::int32_t>(weapon + m_nFallbackPaintKit) != paint;

				WPM<std::int32_t>(weapon + m_iItemIDHigh, -1);

				WPM<std::int32_t>(weapon + m_nFallbackPaintKit, paint);
				WPM<float>(weapon + m_flFallbackWear, 0.1);

				if (shouldUpdate) {
					WPM<std::int32_t>(RPM<std::uintptr_t>(ClientState_) + 0x174, -1);
				}
			}
		}
	}
};