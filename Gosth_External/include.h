#pragma once
#include "memory.h"
#include "vector.h"
#include "../include/imgui/imgui.h"
#include "noclip.hpp"

uintptr_t ReplayInterface_ptr;
uintptr_t world_ptr;
uintptr_t viewport_ptr;
uintptr_t localplayer;


uintptr_t player_contry[256];
uintptr_t player_friend[256];

//aimbot
uintptr_t aimbot_locked[247];
bool aimbot_on;
bool aimbot_fov;
bool radar = false;
bool nazicroshair = true;
bool NoSpreaderBool = false;
bool crosshairn;
bool aimbot_showtarget;
bool aimbot_maxsensi;
float aimbot_fov_value = 40;
float aimbot_smooth = 0.1;
float aimbot_max_distance = 80;
int aimbot_bone;
bool TargetNpcs = false;
bool CrosshairDraw = false;
int CrosshairSize = 10;
int aimbot_currbone = 0;
int fov_segments = 40;

//trigger
uintptr_t trigger_locked[255];
bool trigger_on;
bool trigger_fov;
bool trigger_showtarget;
float trigger_fov_value = 40;
float trigger_max_distance = 80;
int trigger_type;


bool NoClipSpeed_bool;
//esp
bool esp_shieldbar = false;
bool armorbar = false;
bool esp_on = true;
bool esp_box;
bool esp_corner;
bool esp_shield;
bool esp_test;
bool Skeleton2;
bool filled_box;
bool esp_skeletons;
bool esp_drawnpcs = false;
bool esp_skeletons2;
bool esp_showdistance;
bool esp_hptext;
bool esp_lines;
bool esp_head;
bool esp_hpbar;
bool esp_hpbarhead;
bool esp_showid;
bool filledboxtest = false;
bool vehiclesnapline = false;
float esp_max_distance = 500;
bool gaybow = false;
//binds
int bind_menu;
int bind_menuVK;
int bind_aimbot;
int bind_trigger;
int bind_silent;

//exploits
float boostvalue = 1.f;
bool ex_godmode;
bool Veh_colour;
bool ex_invisible;
bool ex_fillammo;
bool ex_vehiclegravity;
float ex_vehiclegravity_value;
bool ex_norecoil;
bool ex_semigodmode;
bool ex_vehiclegodmode;
bool ex_nospread;
bool ex_noreaload;
bool ex_infammo;
bool infammo;
bool ex_NoRecoilTestBool;
bool ex_NoClipBool;
bool noclipmenu;
bool infstam;
bool ex_infstam;
bool ex_Explosive;
bool ex_runspeed_on;
float ex_runspeed_value = 1;
bool ex_vehicleaceleration;
float ex_vehicleaceleration_value;
bool ex_boostvehicle;
float ex_boostvehicle_value;
bool ex_vehiclebreak;
float ex_vehiclebreak_value;
inline int primary_color = 0;
inline int secondary_color = 0;
inline bool update_colors = false;

namespace Colors {

	ImColor skeleton_color_u32 = ImColor(255, 231, 94, 255);

	float ESPCorner_float[4] = { 255, 231, 94, 255 };
	ImColor ESPCorner = ImColor(255, 231, 94, 255);

	float ESPLines_float[4] = { 255, 231, 94, 255 };
	ImColor ESPLines = ImColor(255, 231, 94, 255);

	float ESPBox_float[4] = { 255, 231, 94, 255 };
	ImColor ESPBox = ImColor(255, 231, 94, 255);

	float ESPName_float[4] = { 255, 231, 94, 255 };
	ImColor ESPName = ImColor(255, 231, 94, 255);

	float ESPSkeleton_float[4] = { 255, 231, 94, 255 };
	ImColor ESPSkeleton = ImColor(255, 231, 94, 255);

	float ESPDistance_float[4] = { 255, 231, 94, 255 };
	ImColor ESPDistance = ImColor(255, 231, 94, 255);

	float ESPHpText_float[4] = { 255, 231, 94, 255 };
	ImColor ESPHpText = ImColor(255, 231, 94, 255);

	float FovCircle_float[4] = { 255, 231, 94, 255 };
	ImColor FovCircle = ImColor(255, 231, 94, 255);

	float Crosshair_float[4] = { 255, 231, 94, 255 };
	ImColor Crosshair = ImColor(255, 231, 94, 255);

	ImColor VehColour = ImColor(181, 0, 255, 255);
	ImColor CrosshairColour = ImColor(181, 0, 255, 255);
}
namespace Temp {
	static float Corner[4] = { 1.f, 1.f, 1.f, 255 };
	static float Box[4] = { 1.f, 1.f, 1.f, 255 };
	static float Distance[4] = { 1.f, 1.f, 1.f, 255 };
	static float HpText[4] = { 1.f, 1.f, 1.f , 255 };
	static float Lines[4] = { 1.0f, 1.0f, 1.0f, 255 };
	static float Skeleton[4] = { 1.f, 1.f, 1.f , 255 };
	static float VehicleColor[4] = { 1.f, 1.f, 1.f , 255 };
	static float Crosshair[4] = { 1.f, 1.f, 1.f , 255 };
	static float FovCircle[4] = { 1.f, 1.f, 1.f , 255 };
}

namespace Renderer_Defines {
	float Width;
	float Height;
}