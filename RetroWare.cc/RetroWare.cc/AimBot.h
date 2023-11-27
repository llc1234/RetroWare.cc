#pragma once


class AimBot {
	HANDLE han;

	uintptr_t m_vecOrigin = 0x138;
	uintptr_t m_iTeamNum = 0xF4;
	uintptr_t m_vecViewOffset = 0x108;
	uintptr_t dwClientState_GetLocalPlayer = 0x180;
	uintptr_t dwClientState_ViewAngles = 0x4D90;
	uintptr_t m_aimPunchAngle = 0x303C;
	uintptr_t m_bDormant = 0xED;
	uintptr_t m_lifeState = 0x25F;
	uintptr_t m_bSpottedByMask = 0x980;
	uintptr_t m_dwBoneMatrix = 0x26A8;
	uintptr_t m_iCrosshairId = 0x11838;

	// uintptr_t dwForceAttack = 0x322DDE8;

public:
	
	int v_aimFov = 10;
	float smoothing = 0;

	uintptr_t Entity_ = 0;
	uintptr_t localplayer_ = 0;
	uintptr_t ClientState_ = 0;
	uintptr_t ForceAttack_ = 0;

	struct Vector3
	{
		constexpr Vector3(
			const float x = 0.f,
			const float y = 0.f,
			const float z = 0.f) noexcept :
			x(x), y(y), z(z) { }

		constexpr const Vector3& operator-(const Vector3& other) const noexcept
		{
			return Vector3{ x - other.x, y - other.y, z - other.z };
		}

		constexpr const Vector3& operator+(const Vector3& other) const noexcept
		{
			return Vector3{ x + other.x, y + other.y, z + other.z };
		}

		constexpr const Vector3& operator/(const float factor) const noexcept
		{
			return Vector3{ x / factor, y / factor, z / factor };
		}

		constexpr const Vector3& operator*(const float factor) const noexcept
		{
			return Vector3{ x * factor, y * factor, z * factor };
		}

		constexpr const Vector3& ToAngle() const noexcept
		{
			return Vector3{
				std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
				std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
				0.0f };
		}

		constexpr const bool IsZero() const noexcept
		{
			return x == 0.f && y == 0.f && z == 0.f;
		}

		float x, y, z;
	};

	constexpr Vector3 CalculateAngle(
		const Vector3& localPosition,
		const Vector3& enemyPosition,
		const Vector3& viewAngles) noexcept
	{
		return ((enemyPosition - localPosition).ToAngle() - viewAngles);
	}

	template<typename T> T RRPM(SIZE_T address) {
		T buffer;
		ReadProcessMemory(han, (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}

	template<typename T> void WWPM(SIZE_T address, T buffer) {
		WriteProcessMemory(han, (LPVOID)address, &buffer, sizeof(buffer), NULL);
	}

	void aimBot(HANDLE handle, bool c_automatic_fire, bool c_aim_through_wall) {
		han = handle;
		
		const auto localPlayer = RRPM<uintptr_t>(localplayer_);
		const auto localTeam = RRPM<int32_t>(localPlayer + m_iTeamNum);

		const auto localEyePosition = RRPM<Vector3>(localPlayer + m_vecOrigin) + RRPM<Vector3>(localPlayer + m_vecViewOffset);

		const auto clientState = RRPM<uintptr_t>(ClientState_);

		const auto localPlayerId = RRPM<int32_t>(clientState + dwClientState_GetLocalPlayer);

		const auto viewAngles = RRPM<Vector3>(clientState + dwClientState_ViewAngles);
		const auto aimPunch = RRPM<Vector3>(localPlayer + m_aimPunchAngle) * 2;

		auto bestFov = v_aimFov;
		auto bestAngle = Vector3{ };

		for (auto i = 1; i <= 32; ++i) {
			const auto player = RRPM<std::uintptr_t>(Entity_ + i * 0x10);

			if (RRPM<std::int32_t>(player + m_iTeamNum) == localTeam)
				continue;

			if (RRPM<bool>(player + m_bDormant))
				continue;

			if (RRPM<std::int32_t>(player + m_lifeState))
				continue;


			int v;
			if (c_aim_through_wall) {
				v = 1;
			}
			else {
				v = RRPM<std::int32_t>(player + m_bSpottedByMask);
			}

			if (v & (1 << localPlayerId))
			{
				const auto boneMatrix = RRPM<std::uintptr_t>(player + m_dwBoneMatrix);

				const auto playerHeadPosition = Vector3{
					RRPM<float>(boneMatrix + 0x30 * 8 + 0x0C),
					RRPM<float>(boneMatrix + 0x30 * 8 + 0x1C),
					RRPM<float>(boneMatrix + 0x30 * 8 + 0x2C)
				};

				const auto angle = CalculateAngle(
					localEyePosition,
					playerHeadPosition,
					viewAngles + aimPunch
				);

				const auto fov = std::hypot(angle.x, angle.y);

				if (fov < bestFov)
				{
					bestFov = fov;
					bestAngle = angle;
				}

				if (c_automatic_fire && v) {
					int value;
					ReadProcessMemory(handle, (void*)(localPlayer + m_iCrosshairId), &value, sizeof(value), 0);

					if (value > 0 && value < 32) {
						int v = 6;
						WriteProcessMemory(handle, (void*)(ForceAttack_), &v, sizeof(v), 0);
					}
				}
				
				}
		}

		if (!bestAngle.IsZero()) {
			WWPM<Vector3>(clientState + dwClientState_ViewAngles, viewAngles + bestAngle / smoothing); // smoothing
		}

	}
};



/*

bool c_Enable_AimBot = false;
	bool c_automatic_fire = false;
	bool c_aim_through_wall = false;

	struct Vector3
	{
		constexpr Vector3(
			const float x = 0.f,
			const float y = 0.f,
			const float z = 0.f) noexcept :
			x(x), y(y), z(z) { }

		constexpr const Vector3& operator-(const Vector3& other) const noexcept
		{
			return Vector3{ x - other.x, y - other.y, z - other.z };
		}

		constexpr const Vector3& operator+(const Vector3& other) const noexcept
		{
			return Vector3{ x + other.x, y + other.y, z + other.z };
		}

		constexpr const Vector3& operator/(const float factor) const noexcept
		{
			return Vector3{ x / factor, y / factor, z / factor };
		}

		constexpr const Vector3& operator*(const float factor) const noexcept
		{
			return Vector3{ x * factor, y * factor, z * factor };
		}

		constexpr const Vector3& ToAngle() const noexcept
		{
			return Vector3{
				std::atan2(-z, std::hypot(x, y)) * (180.0f / std::numbers::pi_v<float>),
				std::atan2(y, x) * (180.0f / std::numbers::pi_v<float>),
				0.0f };
		}

		constexpr const bool IsZero() const noexcept
		{
			return x == 0.f && y == 0.f && z == 0.f;
		}

		float x, y, z;
	};

	constexpr Vector3 CalculateAngle(
		const Vector3& localPosition,
		const Vector3& enemyPosition,
		const Vector3& viewAngles) noexcept
	{
		return ((enemyPosition - localPosition).ToAngle() - viewAngles);
	}

	template<typename T> T RRPM(SIZE_T address) {
		T buffer;
		ReadProcessMemory(han, (LPCVOID)address, &buffer, sizeof(T), NULL);
		return buffer;
	}

	template<typename T> void WWPM(SIZE_T address, T buffer) {
		WriteProcessMemory(han, (LPVOID)address, &buffer, sizeof(buffer), NULL);
	}

	void aimBot(HANDLE handle, uintptr_t client_DLL, uintptr_t engine_DLL) {
		han = handle;

		if (c_Enable_AimBot) {
			const auto localPlayer = RRPM<uintptr_t>(client_DLL + dwLocalPlayer);
			const auto localTeam = RRPM<int32_t>(localPlayer + m_iTeamNum);

			const auto localEyePosition = RRPM<Vector3>(localPlayer + m_vecOrigin) + RRPM<Vector3>(localPlayer + m_vecViewOffset);

			const auto clientState = RRPM<uintptr_t>(engine_DLL + dwClientState);

			const auto localPlayerId = RRPM<int32_t>(clientState + dwClientState_GetLocalPlayer);

			const auto viewAngles = RRPM<Vector3>(clientState + dwClientState_ViewAngles);
			const auto aimPunch = RRPM<Vector3>(localPlayer + m_aimPunchAngle) * 2;

			auto bestFov = v_aimFov;
			auto bestAngle = Vector3{ };

			for (auto i = 1; i <= 32; ++i)
			{
				const auto player = RRPM<std::uintptr_t>(client_DLL + dwEntityList + i * 0x10);

				if (RRPM<std::int32_t>(player + m_iTeamNum) == localTeam)
					continue;

				if (RRPM<bool>(player + m_bDormant))
					continue;

				if (RRPM<std::int32_t>(player + m_lifeState))
					continue;

				int v;
				if (c_aim_through_wall) {
					v = 1;
				}
				else {
					v = RRPM<std::int32_t>(player + m_bSpottedByMask);
				}

				if (v & (1 << localPlayerId))
				{
					const auto boneMatrix = RRPM<std::uintptr_t>(player + m_dwBoneMatrix);

					const auto playerHeadPosition = Vector3{
						RRPM<float>(boneMatrix + 0x30 * 8 + 0x0C),
						RRPM<float>(boneMatrix + 0x30 * 8 + 0x1C),
						RRPM<float>(boneMatrix + 0x30 * 8 + 0x2C)
					};

					const auto angle = CalculateAngle(
						localEyePosition,
						playerHeadPosition,
						viewAngles + aimPunch
					);

					const auto fov = std::hypot(angle.x, angle.y);

					if (fov < bestFov)
					{
						bestFov = fov;
						bestAngle = angle;
					}

					if (c_automatic_fire && v) {
						int value;
						ReadProcessMemory(handle, (void*)(localPlayer + m_iCrosshairId), &value, sizeof(value), 0);

						if (value > 0 && value < 32) {
							int v = 6;
							WriteProcessMemory(handle, (void*)(client_DLL + dwForceAttack), &v, sizeof(v), 0);
						}
					}
				}
			}

			if (!bestAngle.IsZero())
				WWPM<Vector3>(clientState + dwClientState_ViewAngles, viewAngles + bestAngle / 3.f); // smoothing
		}
	}

*/