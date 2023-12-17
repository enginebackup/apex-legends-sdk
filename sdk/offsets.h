#pragma once

uint64_t base;

enum bone_id {
	head = 8,
	neck = 7,
	left_shoulder = 11,
	right_shoulder = 35,
	chest = 5,
	spine = 3,
	left_hand = 15,
	right_hand = 39,
	left_arm = 41,
	right_arm = 16,
	left_knee = 58,
	right_knee = 63,
	left_foot = 65,
	right_foot = 60,
	left_elbow_roll = 13,
	right_elbow_roll = 37,
};

namespace offsets
{
	constexpr auto LocalPlayer = 0x211fac8;
	constexpr auto cl_entitylist = 0x1d71858;
	constexpr auto ViewRender = 0x7389d40;
	constexpr auto ViewMatrix = 0x11a350;
	constexpr auto LevelName = 0x16966f0;
	constexpr auto m_iSignifierName = 0x04b0;
	constexpr auto m_vecAbsOrigin = 0x017c;
	constexpr auto m_iTeamNum = 0x037c;
	constexpr auto m_nForceBone = 0x0dd0 + 0x48;
	constexpr auto m_iHealth = 0x036c;
	constexpr auto m_iMaxHealth = 0x04a8;
	constexpr auto m_shieldHealth = 0x01a0;
	constexpr auto m_shieldHealthMax = 0x01a4;
	constexpr auto m_bleedoutState = 0x2710;
	constexpr auto m_customScriptInt = 0x1588;
	constexpr auto nameIndex = 0x38;
	constexpr auto nameList = 0xc275bf0;
	constexpr auto m_weaponNameIndex = 0x17a8;
	constexpr auto m_latestPrimaryWeapons = 0x1964;
	constexpr auto HighlightSettings = 0xb5cc530;
	constexpr auto HighlightServerActiveStates = 0x298;
	constexpr auto HighlightCurrentContextId = 0x294;
	constexpr auto HighlightVisibilityType = 0x278;
	constexpr auto m_hViewModels = 0x2d50;
	constexpr auto m_nSkin = 0x0d88;
	constexpr auto m_bZooming = 0x1c01;
	constexpr auto thirdperson_override = 0x01d00750;
	constexpr auto m_thirdPersonShoulderView = 0x36c0;
	constexpr auto vectorMin = 0x03f0 + 0x0010; //m_Collision + m_vecMins
	constexpr auto vectorMax = 0x03f0 + 0x001c; //m_Collision + m_vecMaxs
	constexpr auto aimpunch = 0x2468; // m_currentFrameLocalPlayer.m_vecPunchWeapon_Angle
	constexpr auto viewangles = 0x2564 - 0x14; // m_ammoPoolCapacity - 0x14
}