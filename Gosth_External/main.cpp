#include "main.hpp"
#include "include.h"
#include "esp.hpp"
#include "aimbot.hpp"
#include "memory.h"
#include "offsets.h"
#include "exploit.h"
#include "xor.hpp"
#include <Windows.h>
#include <string>
#include "skStr.h"
#include <urlmon.h>
#include "color.hpp"
#include "user_interface.h"
#include "imgui/imgui_impl_win32.h"
#include "trigger.hpp"
#include "nav_elements.h"
#include "Console.h"
#include "fa_solid_900.h"
#include "Fonts.hpp"
#include <Windows.h>
#include <iostream>
#include "natives.hpp"
#include "Snowflake.hpp"

std::string tm_to_readable_time(tm ctx);
static std::time_t string_to_timet(std::string timestamp);
static std::tm timet_to_tm(time_t timestamp);

std::string username;
std::string password;
std::string key;
std::string logg;
using namespace std;
bool visual = true;
bool aimbot = true;
bool espkkkk = false;
enum heads {
	rage, antiaim, visuals, settings, skins, configs, scripts
};

enum sub_heads {
	general, accuracy, exploits, _general, advanced
};


void panel();


bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height) {

	// Load from file
	int image_width = 0;
	int image_height = 0;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
	if (image_data == NULL)
		return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}
#define M_PI 3.14159265358979323846264338327950288419716939937510

float BOG_TO_GRD(float BOG) {
	return (180 / M_PI) * BOG;
}

float GRD_TO_BOG(float GRD) {
	return (M_PI / 180) * GRD;
}
int faken_rot = 0;
void Nazi()
{

	POINT Screen; int oodofdfo, jbjfdbdsf;
	Screen.x = GetSystemMetrics(0);
	Screen.y = GetSystemMetrics(1);
	//Middle POINT
	POINT Middle; Middle.x = (int)(Screen.x / 2); Middle.y = (int)(Screen.y / 2);
	int a = (int)(Screen.y / 2 / 30);
	float gamma = atan(a / a);
	faken_rot++;
	int Drehungswinkel = faken_rot;

	int i = 0;
	while (i < 4)
	{
		std::vector <int> p;
		p.push_back(a * sin(GRD_TO_BOG(Drehungswinkel + (i * 90))));                                    //p[0]        p0_A.x
		p.push_back(a * cos(GRD_TO_BOG(Drehungswinkel + (i * 90))));                                    //p[1]        p0_A.y
		p.push_back((a / cos(gamma)) * sin(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));    //p[2]        p0_B.x
		p.push_back((a / cos(gamma)) * cos(GRD_TO_BOG(Drehungswinkel + (i * 90) + BOG_TO_GRD(gamma))));    //p[3]        p0_B.y

		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Middle.x, Middle.y), ImVec2(Middle.x + p[0], Middle.y - p[1]), ImColor(255, 0, 0));
		ImGui::GetOverlayDrawList()->AddLine(ImVec2(Middle.x + p[0], Middle.y - p[1]), ImVec2(Middle.x + p[2], Middle.y - p[3]), ImColor(255, 0, 0));

		i++;
	}
}

void FovAimbot() {
	int screen_x = GetSystemMetrics(SM_CXSCREEN);
	int screen_y = GetSystemMetrics(SM_CYSCREEN);
	auto draw = ImGui::GetOverlayDrawList();
	draw->AddCircle(ImVec2(screen_x / 2, screen_y / 2), aimbot_fov_value, Colors::FovCircle, fov_segments, 2.0f);
}




void radar2D()
{
	//RADAR
	auto Actors = localplayer;
	const float radarWidth = 200.0f;
	const float radarHeight = 200.0f;
	const ImU32 backgroundColor = IM_COL32(95, 95, 95, 95);
	const ImU32 radarColor = IM_COL32(0, 0, 0, 255);
	ImGuiIO& io = ImGui::GetIO();
	auto BackgroundDrawList = ImGui::GetBackgroundDrawList();
	// Obtenir la taille de l'écran
	ImVec2 displaySize = io.DisplaySize;
	// Position en haut à droite
	float margin = 100.0f; // Ajoutez une marge pour éviter que le radar ne soit collé au bord de l'écran
	float radarPosX = displaySize.x - radarWidth - margin;
	float radarPosY = margin;
	const ImVec2 cursorPos = ImVec2(radarPosX, radarPosY);
	const float centerX = cursorPos.x + 100.0f;
	const float centerY = cursorPos.y + 100.0f;
	const ImVec2 center = ImVec2(centerX, centerY);
	BackgroundDrawList->AddRectFilled(cursorPos, ImVec2(cursorPos.x + radarWidth, cursorPos.y + radarHeight), backgroundColor); // Draw the background rectangle
	BackgroundDrawList->AddRect(cursorPos, ImVec2(cursorPos.x + radarWidth, cursorPos.y + radarHeight), radarColor); // Draw the outer rectangle of the radar
	BackgroundDrawList->AddLine(ImVec2(center.x, cursorPos.y), ImVec2(center.x, cursorPos.y + radarHeight), radarColor); // Draw the cross lines at the center of the radar
	BackgroundDrawList->AddLine(ImVec2(cursorPos.x, center.y), ImVec2(cursorPos.x + radarWidth, center.y), radarColor);
}
void CrosshairNormal()
{

		int screen_x = GetSystemMetrics(SM_CXSCREEN);
		int screen_y = GetSystemMetrics(SM_CYSCREEN);

		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(screen_x / 2, screen_y / 2), ImVec2(screen_x / 2, screen_y / 2), ImColor(255, 255, 255, 255), 1);
		ImGui::GetBackgroundDrawList()->AddLine(ImVec2(screen_x / 2, screen_y / 2), ImVec2(screen_x / 2, screen_y / 2), ImColor(255, 255, 255, 255), 1);

}

float color_red = 1.;
float color_green = 0;
float color_blue = 0;
float color_random = 0.0;
float color_speed = -10.0;

void ColorChange()
{
	static float Color[3];
	static DWORD Tickcount = 0;
	static DWORD Tickcheck = 0;
	ImGui::ColorConvertRGBtoHSV(color_red, color_green, color_blue, Color[0], Color[1], Color[2]);
	if (GetTickCount() - Tickcount >= 1)
	{
		if (Tickcheck != Tickcount)
		{
			Color[0] += 0.001f * color_speed;
			Tickcheck = Tickcount;
		}
		Tickcount = GetTickCount();
	}
	if (Color[0] < 0.0f) Color[0] += 1.0f;
	ImGui::ColorConvertHSVtoRGB(Color[0], Color[1], Color[2], color_red, color_green, color_blue);
}


void GPlayerList() {
	uintptr_t PedReplayInterface = read_mem<uintptr_t>(ReplayInterface_ptr + 0x18);
	uintptr_t PedList = read_mem<uintptr_t>(PedReplayInterface + 0x100);
	for (int i = 0; i < 256; i++) {
		if (PedList) {
			uintptr_t Ped = read_mem<uintptr_t>(PedList + (i * 0x10));
			if (Ped) {
				if (localplayer != 0) {
					if (Ped != localplayer) {

						player_contry[i] = Ped;

					}
				}
			}
		}
	}
}

void PlayerList() {
	GPlayerList();
	for (int i = 0; i < 256; i++) {
		if (player_contry[i] != 0) {
			string layer = std::to_string(i);
			if (player_friend[i] == 0) {
				if (ImGui::Button(("Add Friend ID: " + layer).c_str(), { 199, 22 })) {
					player_friend[i] = player_contry[i];
				}
			}
			else {
				if (ImGui::Button(("Rem Friend ID: " + layer).c_str(), { 199, 22 })) {
					player_friend[i] = 0;
				}
			}
		}
	}
}

namespace var {
	bool checkbox = true;
	bool checkboxIn = false;
	bool esp = false;
	bool box = false;
	bool name = false;
	bool hp = false;
	bool ar = false;
	bool am = false;
	bool esp1 = false;
	bool box1 = false;
	bool name1 = false;
	bool hp1 = false;
	bool ar1 = false;
	bool am1 = false;
	int slider_intager = 50;
	float slider_float = 0.5f;

	bool boundbox1 = false;
	bool boundbox = false;
	bool bindbox = false;

	float slider_float1 = 0.0f;
	float slider_float2 = 1.0f;
	float slider_float3 = 90.0f;
	int selectedItem3 = 0;
	const char* items3_eng[] = { "Selected 0", "Selected 1", "Selected 2", "Selected 3" };
	bool multi_items_count[5];
	const char* multi_items[5] = { "One", "Two", "Three", "Four", "Five" };
	float color_edit0[4] = { 0.70f, 0.80f, 0.90f, 1.000f };
	float color_edit1[4] = { 0.70f, 0.80f, 0.90f, 1.000f };
	float color_edit2[4] = { 218 / 255.f, 96 / 255.f, 21 / 255.f, 255 / 255.f };
	float color_edit3[4] = { 0.70f, 0.80f, 0.90f, 1.000f };
	float color_edit4[4] = { 0.70f, 0.80f, 0.90f, 1.000f };

	static const char* items[]{ "Default", "Triangles", "3D Box" };
	int selectedItem = 0;
	static char input[64] = { "" };
	char input2[64] = { "" };
	int key0;
	int key1;
	int key2;
}

namespace colors {

	inline ImVec4 general_color = ImColor(195, 105, 48, 255);
	inline ImVec4 main_color = ImColor(16, 16, 16, 255);
	inline ImVec4 lite_color = ImColor(20, 20, 20, 255);
	inline ImVec4 gray_color = ImColor(43, 43, 43, 255);
	inline ImVec4 Tab_Child = ImColor(15, 15, 15, 255);
	inline ImVec4 Tab_Border = ImColor(26, 26, 26, 255);

	inline ImVec4 Tab_Selected = ImColor(223, 99, 25, 255);
	inline ImVec4 Tab_Hovered = ImColor(130, 130, 130, 255);
	inline ImVec4 Tab = ImColor(80, 80, 80, 255);

	inline ImVec4 Checkbox = ImColor(14, 14, 14, 255);
	inline ImVec4 Checkbox_Hovered = ImColor(12, 12, 12, 255);
	inline ImVec4 Checkbox_Active = ImColor(218, 96, 21, 255);

	inline ImVec4 Car_Slider = ImColor(221, 97, 23, 255);
	inline ImVec4 Car_Slider_Hovered = ImColor(223, 99, 25, 255);
	inline ImVec4 Car_Slider_Active = ImColor(223, 99, 25, 255);

	inline ImVec4 Slider = ImColor(16, 16, 16, 255);
	inline ImVec4 Slider_Hovered = ImColor(18, 18, 18, 255);
	inline ImVec4 Slider_Active = ImColor(18, 18, 18, 255);

	inline ImVec4 Circle_Slider = ImColor(255, 255, 255, 255);
	inline ImVec4 Circle_SliderHovered = ImColor(255, 255, 255, 255);
	inline ImVec4 Circle_SliderActive = ImColor(255, 255, 255, 255);

	inline ImVec4 Combo = ImColor(26, 26, 26, 255);
	inline ImVec4 Combo_Hovered = ImColor(26, 26, 26, 255);
	inline ImVec4 Combo_Active = ImColor(26, 26, 26, 255);

	inline ImVec4 InputText = ImColor(16, 16, 16, 255);
	inline ImVec4 InputText_Hovered = ImColor(18, 18, 18, 255);
	inline ImVec4 InputText_Active = ImColor(18, 18, 18, 255);

	inline ImVec4 Button = ImColor(26, 26, 26, 255);
	inline ImVec4 Button_Hovered = ImColor(30, 30, 30, 255);
	inline ImVec4 Button_Active = ImColor(33, 33, 33, 255);

	inline ImVec4 Selectable_Hovered = ImColor(150, 150, 150, 255);
	inline ImVec4 Selectable_Active = ImColor(250, 250, 250, 255);

	inline ImVec4 Picker_Active = ImColor(20, 20, 20, 255);

	inline ImVec4 Text = ImColor(71, 71, 71, 255);
	inline ImVec4 Text_Hovered = ImColor(200, 200, 200, 255);
	inline ImVec4 Text_Active = ImColor(235, 245, 255, 255);

	inline ImVec4 CheckMark = ImColor(255, 255, 255, 255);

	inline ImVec4 Transparent = ImColor(0, 0, 0, 0);

	inline ImVec4 tab_tooltip = ImColor(180, 180, 180, 255);

	inline ImVec4 keybind_background = ImColor(17, 17, 17, 255);
	inline ImVec4 keybind_border = ImColor(28, 28, 28, 255);
}
static bool animated_background;
inline ImColor main_color(218, 96, 21, 255);
inline ImVec4 color_particle(0.7f, 0.f, 0.f, 1.f);
inline ImColor background_color(24, 24, 24, 255);

inline ImVec4 second_color(0.09f, 0.09f, 0.09f, 1.f);


inline ImVec2 frame_size = ImVec2(605, 65);


void Particles()
{
	ImVec2 screen_size = { (float)GetSystemMetrics(SM_CXSCREEN), (float)GetSystemMetrics(SM_CYSCREEN) };

	static ImVec2 partile_pos[100];
	static ImVec2 partile_target_pos[100];
	static float partile_speed[100];
	static float partile_radius[100];

	for (int i = 1; i < 50; i++)
	{
		if (partile_pos[i].x == 0 || partile_pos[i].y == 0)
		{
			partile_pos[i].x = rand() % (int)screen_size.x + 1;
			partile_pos[i].y = 15.f;
			partile_speed[i] = 1 + rand() % 25;
			partile_radius[i] = rand() % 4;

			partile_target_pos[i].x = rand() % (int)screen_size.x;
			partile_target_pos[i].y = screen_size.y * 2;
		}

		partile_pos[i] = ImLerp(partile_pos[i], partile_target_pos[i], ImGui::GetIO().DeltaTime * (partile_speed[i] / 60));

		if (partile_pos[i].y > screen_size.y)
		{
			partile_pos[i].x = 0;
			partile_pos[i].y = 0;
		}

		ImGui::GetWindowDrawList()->AddCircleFilled(partile_pos[i], partile_radius[i], ImColor(255, 255, 255, 255));
	}

}




#define TITLE "Snowflake.cpp"
#define TITLEW TEXT(TITLE)

// you need those for snowflake
#define WINDOW_WIDTH  1920
#define WINDOW_HEIGHT 1080

#define SNOW_LIMIT 5

bool Snowflakenable = false;
std::vector<Snowflake::Snowflake> snow;

void loginpanel();
int valueI;
bool the_bool;
bool damageboost;
bool isNoclipWorking = false;
static float noclipspeed = 1.00001f;
static bool speed = false;
bool noclipworks = false;
int damageamount = 50;
bool customfov;
int fovvalue = 50;
bool watermark = true;
bool watermark2 = true;
bool watermarkrgb = true;
bool crosshair = false;
bool userinfo = true;
bool Explosy;
bool god;
bool nspeed;
bool fillammo;
bool VehBool;
bool invis;
bool nrec;
bool nreload;
bool nrecoilzero;
bool npread;
bool VehSp;
bool vehicleboostbool;
bool VehBrk;
bool VehGod;
bool ex_freezeplayer;
int freeze = 0;
bool VehGravity;
int tabb = 0;
bool overlay = false;
bool Skeleton = false;
int Skeletonthinkness = 0;
inline ImVec4 particleColour = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


const char* menu_bind[] = { ("Insert"), ("F8"), ("Delete"), ("F4") };
const char* aimbot_bind[] = { ("Right Button") ,("Left Button") , ("Page Backward Button"), ("Page Forward Button"),("Shift"),("Menu"),("E") };
const char* trigger_bind[] = { ("Right Button") ,("Left Button"), ("Page Backward Button"), ("Page Forward Button"),("Shift"),("Menu"),("E") };
static int selected = 0;
static int sub_selected = 0;

static bool bullying = false;
static bool bullythosemfs = false;
static bool stopbullythemyoushitters = false;
static bool stop = false;
static bool niggas = false;
static bool hihihi = false;
static bool bro = false;
static int sliderinc = 0;
//static int combo = 0;
const char* hitbox_items[] = { "Head", "Neck", "Pelvis", "Right Hand", "Left Hand", "Right Foot", "Left Foot" };
static float color[4] = { 1.f, 1.f, 1.f, 1.f };


static heads tab{ rage };
static sub_heads subtab{ general };

const char* tab_name = tab == rage ? "Ragebot" : tab == antiaim ? "Anti-aim" : tab == visuals ? "Visuals" : tab == settings ? "Settings" : tab == skins ? "Skins" : tab == configs ? "Configs" : tab == scripts ? "Scripts" : 0;
const char* tab_icon = tab == rage ? "B" : tab == antiaim ? "C" : tab == visuals ? "D" : tab == settings ? "E" : tab == skins ? "F" : tab == configs ? "G" : tab == scripts ? "H" : 0;
void Render() {

	glfwPollEvents();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();


	





	if (customfov)
	{
		DWORD64 cameraaddr = read_mem<DWORD64>(offset::b2372::i_camera_ptr);
		uintptr_t CameraData = read_mem<uintptr_t>(cameraaddr + 0x10);
		write_mem<float>(CameraData + 0x30, fovvalue);
	}

	//if (noclipworks)
	//{
	//	D3DXVECTOR3 pos = read_mem<D3DXVECTOR3>(localplayer + 0x90);
	//	uintptr_t navig = read_mem<uintptr_t>(localplayer + 0x30);
	//	write_mem<D3DXVECTOR3>(navig + 0x30, D3DXVECTOR3(0, 0, 0));

	//	if (GetAsyncKeyState(0x57) & 0x8000) {
	//		write_mem<D3DXVECTOR3>(localplayer + 0x320, D3DXVECTOR3(0, 0, 0));
	//		uint64_t camera = read_mem<uintptr_t>(offset::b2372::i_camera_ptr + 0x0);
	//		D3DXVECTOR3 angles = read_mem<D3DXVECTOR3>(camera + 0x03D0);
	//		if (angles == D3DXVECTOR3(0, 0, 0))
	//			angles = read_mem<D3DXVECTOR3>(camera + 0x40);
	//		D3DXVECTOR3 npos = pos;
	//		npos.x += (angles.x * 2);
	//		npos.y += (angles.y * 2);
	//		npos.z += (angles.z * 2);
	//		write_mem<D3DXVECTOR3>(localplayer + 0x90, npos);
	//		write_mem<D3DXVECTOR3>(navig + 0x50, npos);


	//	}

	//}




	if (Snowflakenable)
	{
		Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 1.f/*minimum size*/, 5.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, WINDOW_WIDTH, WINDOW_HEIGHT, Snowflake::vec3(0.f, 0.005f)/*gravity*/, IM_COL32(222, 0, 180, 100)/*color*/);

	}

	if (ex_infammo)
	{
		uintptr_t WeaponManager = read_mem<uintptr_t>(localplayer + 0x10D8);
		uintptr_t weaponinfo = read_mem<uintptr_t>(WeaponManager + 0x20);

		uintptr_t AmmoInfo = read_mem<uintptr_t>(weaponinfo + 0x60);
		uintptr_t AmmoCount = read_mem<uintptr_t>(AmmoInfo + 0x8d);
		uintptr_t LastCount = read_mem<uintptr_t>(AmmoCount + 0x0);
		write_mem<uint32_t>(AmmoCount + 0x18, 9999);
	}


	if (damageboost)
	{
		DWORD64 weaponmanager = read_mem<DWORD64>(localplayer + 0x10D8);
		weaponmanager = read_mem<DWORD64>(weaponmanager + 0x20);
		write_mem<float>(weaponmanager + 0xB0, damageamount);
	}

	if (watermark)
	{
		/*auto draw_list = ImGui::GetBackgroundDrawList();*/
		auto RGB = ImGui::GetColorU32({ color_red, color_green, color_blue, 255 });
#define xorstr_
		auto draw_list = ImGui::GetBackgroundDrawList();

		auto watermark = xorstr_("Input Text Here");
		auto watermark_size = ImGui::CalcTextSize(watermark);

		auto yOffset = 0;
		auto offset = 4;

		draw_list->AddRectFilled(ImVec2(6, 4 + yOffset), ImVec2((4 * 2) + watermark_size.x + 6, 6 + yOffset), ImColor(1.0f, 0.0f, 1.0f));
		draw_list->AddRectFilled(ImVec2(6, 6 + yOffset), ImVec2((4 * 2) + watermark_size.x + 6, 25 + yOffset), ImColor(0.2117647081613541f, 0.2235294133424759f, 0.2470588237047195f, 1.0f));
		draw_list->AddText(ImVec2(10, 6 + yOffset), ImColor(255, 255, 255, 255), watermark);




	}
	//if (watermarkrgb)
	//{
	//	auto draw_list = ImGui::GetBackgroundDrawList();
	//	auto RGB = ImGui::GetColorU32({ color_red, color_green, color_blue, 255 });

	//	ImGui::GetOverlayDrawList()->AddText(ImVec2(32, 20), ImColor(RGB), ("Rainbow Mode"));
	//}

	
	void annoyingshit(ImGuiWindow & window); {
		auto RGB = ImGui::GetColorU32({ color_red, color_green, color_blue, 255 });
		/*ImGui::GetOverlayDrawList()->AddText(ImVec2(32, 20), ImColor(RGB), ("Rainbow Mode"));*/
	}

	if (watermark2)
	{

		auto RGB = ImGui::GetColorU32({ color_red, color_green, color_blue, 255 });
		#define xorstr_
		auto draw_list = ImGui::GetBackgroundDrawList();

		auto watermark2 = xorstr_("Input Text Here");
		auto watermark_size2 = ImGui::CalcTextSize(watermark2);

		auto yOffset = 26;
		auto offset = 2;

		draw_list->AddRectFilled(ImVec2(6, 4 + yOffset), ImVec2((4 * 2) + watermark_size2.x + 6, 6 + yOffset), ImColor(1.0f, 0.0f, 1.0f));
		draw_list->AddRectFilled(ImVec2(6, 6 + yOffset), ImVec2((4 * 2) + watermark_size2.x + 6, 25 + yOffset), ImColor(0.2117647081613541f, 0.2235294133424759f, 0.2470588237047195f, 1.0f));
		draw_list->AddText(ImVec2(10, 7 + yOffset), ImColor(255, 255, 255, 255), watermark2);

	}



	if (bind_menu == 0) { bind_menuVK = VK_INSERT; }
	else if (bind_menu == 1) { bind_menuVK = VK_F8; }
	else if (bind_menu == 2) { bind_menuVK = VK_DELETE; }
	else if (bind_menu == 3) { bind_menuVK = VK_F4; }

	__try {
		if (aimbot_fov) { FovAimbot(); }

		if (radar) {
			radar2D();
		}
		
		if (nazicroshair)
		{
			Nazi();
		}

		if (esp_on) { DrawEsp(); }

		if (aimbot_on) { bindaimbot(); Aimbot(); }

		if (trigger_on) {
			bindtrigger();
			if (trigger_type == 0 || trigger_type == 1) {
				RageTriggerbot();
			}
			else if (trigger_type == 2) {
				LegitTriggerbot();
			}
		}

		if (ex_runspeed_on) { Player::SpeedWalk(true, ex_runspeed_value); nspeed = true; }
		else { if (nspeed) { Player::SpeedWalk(false, 0); }nspeed = false; }

		if (ex_runspeed_on) { Player::SpeedWalk(true, ex_runspeed_value); nspeed = true; }
		else { if (nspeed) { Player::SpeedWalk(false, 0); }nspeed = false; }

		if (ex_norecoil) { Weapons::NoRecoil(true); nrec = true; }
		else { if (nrec) { Weapons::NoRecoil(false); }nrec = false; }

		if (ex_Explosive) { Weapons::SetAmmoExplosiveType(true); Explosy = true; }
		else { if (Explosy) { Weapons::SetAmmoExplosiveType(false); }Explosy = false; }

		if (ex_noreaload) { Weapons::NoReaload(true); nreload = true; }
		else { if (nreload) { Weapons::NoReaload(false); }nreload = false; }

		//if (ex_infammo) { Weapons::InfiniteAmmo(true); infammo = true; }
		//else { if (infammo) { Weapons::InfiniteAmmo(false); }infammo = false; }

		if (ex_NoClipBool) { Weapons::NoRecoilTest(true); noclipmenu = true; }
		else { if (noclipmenu) { Weapons::NoRecoilTest(false); }noclipmenu = false; }


		if (ex_nospread) { Weapons::NoSpread(true); npread = true; }
		else { if (npread) { Weapons::NoSpread(false); }npread = false; }

		if (ex_godmode) { Player::Godmode(true); god = true; }
		else { if (god) { Player::Godmode(false); }god = false; }


		if (ex_freezeplayer) { Player::FreezePlayer(true); freeze = true; }
		else { if (freeze) { Player::FreezePlayer(false); }freeze = false; }

		if (ex_invisible) { Player::Invisible(true); invis = true; }
		else { if (invis) { Player::Invisible(false); }invis = false; }

		if (ex_infstam) { Player::InfStam(true); infstam = true; }
		else { if (infstam) { Player::InfStam(false); }infstam = false; }

		if (ex_fillammo) { Weapons::FillAmmo(true); fillammo = true; }
		else { if (fillammo) { Weapons::FillAmmo(false); } fillammo = false; }

		if (ex_semigodmode) {
			if (Player::GetHealth() <= 200) {
				Player::SetHealth(Player::GetMaxHealth());
			}
		}

		if (ex_vehicleaceleration) { Vehicle::VehicleAceleration(true, ex_vehicleaceleration_value); VehSp = true; }
		else { if (VehSp) { Vehicle::VehicleAceleration(false, ex_vehicleaceleration_value); }VehSp = false; }

		if (ex_boostvehicle) { Vehicle::VehicleAceleration(true, ex_vehicleaceleration_value); vehicleboostbool = true; }
		else { if (vehicleboostbool) { Vehicle::VehicleAceleration(false, ex_vehicleaceleration_value); }vehicleboostbool = false; }

		if (ex_vehiclebreak) { Vehicle::VehicleBrakeForce(true, ex_vehiclebreak_value); VehBrk = true; }
		else { if (VehBrk) { Vehicle::VehicleBrakeForce(false, ex_vehiclebreak_value); }VehBrk = false; }

		if (ex_vehiclegodmode) { Vehicle::GodModeVehicle(true); VehGod = true; }
		else { if (VehGod) { Vehicle::GodModeVehicle(false); }VehGod = false; }

		if (ex_vehiclegravity) { Vehicle::VehicleGravity(true); ex_vehiclegravity_value = true; }
		else { if (VehGravity) { Vehicle::VehicleGravity(false); }ex_vehiclegravity_value = false; }
	}
	__except ((GetExceptionCode() == EXCEPTION_ACCESS_VIOLATION) ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {}
	ColorChange();

	
	if (menu_visible) {


		ImGui::SetNextWindowSize(ImVec2(520, 395));


		ImGui::Begin("Text", nullptr, ImGuiWindowFlags_NoDecoration);

		auto draw = ImGui::GetWindowDrawList();
		ImVec2 pos = ImGui::GetWindowPos();
		ImVec2 size = ImGui::GetWindowSize();
		//draw->AddRectFilled(pos, ImVec2(size.x + 2, size.y + 2), ImColor(255, 10, 10, 255), 0.2f);
		draw->AddRectFilled(pos, ImVec2(pos.x + 55, pos.y + size.y), ImColor(20, 20, 20, 255)); // left rect
		draw->AddRectFilled(ImVec2(pos.x + 55, pos.y), ImVec2(pos.x + size.x, pos.y + 35), ImColor(20, 20, 20, 255)); // upper rect
				
		draw->AddLine(ImVec2(pos.x + 55, pos.y + 35), ImVec2(pos.x + size.x, pos.y + 35), ImColor(255, 255, 255, 15)); // upper line
		draw->AddLine(ImVec2(pos.x + 55, pos.y), ImVec2(pos.x + 55, pos.y + size.y), ImColor(255, 255, 255, 15)); // left line
		POINT mouse;
		RECT rc = { 0 };
		GetCursorPos(&mouse);

		ImDrawList* drawList = ImGui::GetWindowDrawList();

		static const int numParticles = 115;
		static ImVec2 particlePositions[numParticles];
		static ImVec2 particleDistance;
		static ImVec2 particleVelocities[numParticles];

		static bool initialized = false;
		if (!initialized)
		{
			for (int i = 0; i < numParticles; ++i)
			{
				particlePositions[i] = ImVec2(
					ImGui::GetWindowPos().x + ImGui::GetWindowSize().x * static_cast<float>(rand()) / RAND_MAX,
					ImGui::GetWindowPos().y + ImGui::GetWindowSize().y * static_cast<float>(rand()) / RAND_MAX
				);

				particleVelocities[i] = ImVec2(
					static_cast<float>((rand() % 11) - 5),
					static_cast<float>((rand() % 11) - 5)
				);

			}

			initialized = true;
		}

		ImVec2 cursorPos = ImGui::GetIO().MousePos;
		for (int i = 0; i < numParticles; ++i)
		{
			//draw lines to particles
			for (int j = i + 1; j < numParticles; ++j)
			{
				float distance = std::hypotf(particlePositions[j].x - particlePositions[i].x, particlePositions[j].y - particlePositions[i].y);
				float opacity = 1.0f - (distance / 55.0f);  // opacity cahnge

				if (opacity > 0.0f)
				{
					ImU32 lineColor = ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 1.0f, opacity));
					drawList->AddLine(particlePositions[i], particlePositions[j], lineColor);
				}
			}

			//draw lines to cursor
			float distanceToCursor = std::hypotf(cursorPos.x - particlePositions[i].x, cursorPos.y - particlePositions[i].y);
			float opacityToCursor = 1.0f - (distanceToCursor / 52.0f);  // Adjust the divisor to control the opacity change

			if (opacityToCursor > 0.0f)
			{
				ImU32 lineColorToCursor = ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 1.0f, opacityToCursor));
				drawList->AddLine(cursorPos, particlePositions[i], lineColorToCursor);
			}
		}

		//update and render particles
		float deltaTime = ImGui::GetIO().DeltaTime;
		for (int i = 0; i < numParticles; ++i)
		{
			particlePositions[i].x += particleVelocities[i].x * deltaTime;
			particlePositions[i].y += particleVelocities[i].y * deltaTime;

			// Stay in window
			if (particlePositions[i].x < ImGui::GetWindowPos().x)
				particlePositions[i].x = ImGui::GetWindowPos().x + ImGui::GetWindowSize().x;
			else if (particlePositions[i].x > ImGui::GetWindowPos().x + ImGui::GetWindowSize().x)
				particlePositions[i].x = ImGui::GetWindowPos().x;

			if (particlePositions[i].y < ImGui::GetWindowPos().y)
				particlePositions[i].y = ImGui::GetWindowPos().y + ImGui::GetWindowSize().y;
			else if (particlePositions[i].y > ImGui::GetWindowPos().y + ImGui::GetWindowSize().y)
				particlePositions[i].y = ImGui::GetWindowPos().y;

			//ImU32 particleColour = ImGui::ColorConvertFloat4ToU32(particleColour);

			////render particles behind components
			//drawList->AddCircleFilled(particlePositions[i], 1.5f, particleColour);
		}



		//Snowflake::CreateSnowFlakes(snow, SNOW_LIMIT, 1.f/*minimum size*/, 5.f/*maximum size*/, 0/*imgui window x position*/, 0/*imgui window y position*/, WINDOW_WIDTH, WINDOW_HEIGHT, Snowflake::vec3(0.f, 0.005f)/*gravity*/, IM_COL32(255, 0, 255, 100)/*color*/);
		Snowflake::Update(snow, Snowflake::vec3(mouse.x, mouse.y)/*mouse x and y*/, Snowflake::vec3(rc.left, rc.top)/*hWnd x and y positions*/); // you can change a few things inside the update function

		ImGui::SetCursorPos(ImVec2(13, 11));
		ImGui::BeginGroup();
		if (elements::tab("B", tab == rage)) {
			tab = rage; sub_selected = 0;
		}
		if (elements::tab("D", tab == antiaim)) {
			tab = antiaim; sub_selected = 2;
		}
		if (elements::tab("C", tab == visuals)) {
			tab = visuals; sub_selected = 184;
		}
		if (elements::tab("F", tab == skins)) {
			tab = skins; sub_selected = 222;
		}
		if (elements::tab("E", tab == settings)) {
			tab = settings; sub_selected = 456;
		}
		ImGui::EndGroup();

		if (tab == rage) {
			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Aimbot", 0 == sub_selected)) {
				sub_selected = 0;
			}
			ImGui::SameLine();
			if (custom_interface::subtab("TriggerBot", 16 == sub_selected)) {
				sub_selected = 16;
			}
			ImGui::SameLine();
			if (custom_interface::subtab("Add Friend", 87 == sub_selected)) {
				sub_selected = 87;
			}

			ImGui::EndGroup();

			if (sub_selected == 0) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Aim Assistance", ImVec2(219, 342));
				{
					ImGui::Checkbox("Crosshair", &nazicroshair);
					ImGui::Checkbox("Lock Aimbot", &aimbot_on);
					ImGui::Checkbox("Show Fov", &aimbot_fov);
					ImGui::Checkbox("Target Npcs", &TargetNpcs);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Fov Colour").c_str(), Temp::FovCircle, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::FovCircle.Value.x = Temp::FovCircle[0]; Colors::FovCircle.Value.y = Temp::FovCircle[1]; Colors::FovCircle.Value.z = Temp::FovCircle[2]; Colors::FovCircle.Value.w = Temp::FovCircle[3];
					//ImGui::Spacing();
					//ImGui::ColorEdit4("Crosshair Color", Temp::Crosshair, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					//Colors::CrosshairColour.Value.x = Temp::Crosshair[0];
					//Colors::CrosshairColour.Value.y = Temp::Crosshair[1];
					//Colors::CrosshairColour.Value.z = Temp::Crosshair[2];
					//Colors::CrosshairColour.Value.w = Temp::Crosshair[3];
				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(291, 44));
				ImGui::BeginChild("Config", ImVec2(219, 342));
				{
					ImGui::Combo("Aimbot Bone", &aimbot_bone, hitbox_items, IM_ARRAYSIZE(hitbox_items));
					ImGui::SliderFloat("Aimbot Smoothing", &aimbot_smooth, 0.f, 50.f, "% .2f");
					ImGui::SliderFloat("Aimbot Distance", &aimbot_max_distance, 20.f, 1000.f, "% .2f");
					ImGui::SliderFloat("Aimbot Fov", &aimbot_fov_value, 20.f, 800.f, "% .2f");
					ImGui::SliderInt("Fov Segments", &fov_segments, 1, 100);
				}
				ImGui::EndChild();

			}

			if (sub_selected == 16) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("TriggerBot", ImVec2(219, 342));
				{
					ImGui::Checkbox("TriggerBot", &trigger_on);
					ImGui::Checkbox("TriggerBot Fov", &trigger_fov);

				}
				ImGui::EndChild();

				ImGui::SetCursorPos(ImVec2(291, 44));
				ImGui::BeginChild("Config", ImVec2(219, 342));
				{
					//ImGui::Combo("Aimbot Bone", &combo, combo_items, 4);
					ImGui::SliderFloat("TriggerBot Fov Value", &trigger_fov_value, 0.f, 50.f, "% .2f");
					ImGui::SliderFloat("TriggerBot Distance", &aimbot_max_distance, 20.f, 500.f, "% .2f");
				}
				ImGui::EndChild();
			}

			if (sub_selected == 87) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Friend List", ImVec2(219, 342));
				{
					PlayerList();
				}
				ImGui::EndChild();
			}
		}

		if (tab == antiaim) {
			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Visuals", 2 == sub_selected)) {
				sub_selected = 2;
			}
			ImGui::EndGroup();

			if (sub_selected == 2) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Visuals", ImVec2(219, 342));
				{

					ImGui::Checkbox(XorStr("Box").c_str(), &esp_box);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Box Color").c_str(), Temp::Box, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPBox.Value.x = Temp::Box[0]; Colors::ESPBox.Value.y = Temp::Box[1]; Colors::ESPBox.Value.z = Temp::Box[2]; Colors::ESPBox.Value.w = Temp::Box[3];
						
					ImGui::Checkbox(XorStr("Box Corner").c_str(), &esp_corner);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Box Corner Color").c_str(), Temp::Corner, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPCorner.Value.x = Temp::Corner[0]; Colors::ESPCorner.Value.y = Temp::Corner[1]; Colors::ESPCorner.Value.z = Temp::Corner[2]; Colors::ESPCorner.Value.w = Temp::Corner[3];

					ImGui::Checkbox(XorStr("Skeleton").c_str(), &esp_skeletons);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Skeleton Color").c_str(), Temp::Skeleton, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPSkeleton.Value.x = Temp::Skeleton[0]; Colors::ESPSkeleton.Value.y = Temp::Skeleton[1]; Colors::ESPSkeleton.Value.z = Temp::Skeleton[2]; Colors::ESPSkeleton.Value.w = Temp::Skeleton[3];

					ImGui::Checkbox(XorStr("Distance").c_str(), &esp_showdistance);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Text Distance Color").c_str(), Temp::Distance, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPDistance.Value.x = Temp::Distance[0]; Colors::ESPDistance.Value.y = Temp::Distance[1]; Colors::ESPDistance.Value.z = Temp::Distance[2]; Colors::ESPDistance.Value.w = Temp::Distance[3];

					ImGui::Checkbox(XorStr("Health Text").c_str(), &esp_hptext);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Text Health Color").c_str(), Temp::HpText, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPHpText.Value.x = Temp::HpText[0]; Colors::ESPHpText.Value.y = Temp::HpText[1]; Colors::ESPHpText.Value.z = Temp::HpText[2]; Colors::ESPHpText.Value.w = Temp::HpText[3];

					ImGui::Checkbox(XorStr("Lines").c_str(), &esp_lines);
					ImGui::SameLine();
					ImGui::SetCursorPosX(200);
					ImGui::ColorEdit4(XorStr("Lines Color").c_str(), Temp::Lines, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
					Colors::ESPLines.Value.x = Temp::Lines[0]; Colors::ESPLines.Value.y = Temp::Lines[1]; Colors::ESPLines.Value.z = Temp::Lines[2]; Colors::ESPLines.Value.w = Temp::Lines[3];


					ImGui::Checkbox(XorStr("Draw NPCS").c_str(), &esp_drawnpcs);

					ImGui::Checkbox(XorStr("Filled Box").c_str(), &filled_box);

					ImGui::Checkbox(XorStr("Hp Bar").c_str(), &esp_hpbar);

					ImGui::Checkbox(XorStr("Armor Bar").c_str(), &esp_shieldbar);

					ImGui::Checkbox(XorStr("Head").c_str(), &esp_head);

					ImGui::Checkbox(XorStr("Show ID").c_str(), &esp_showid);

					ImGui::Checkbox(XorStr("Rainbow Everything").c_str(), &gaybow);

					ImGui::SliderFloat(XorStr("Esp Distance").c_str(), &esp_max_distance, 20, 500, "% .2f");
				}
				ImGui::EndChild();


			}
		}

		if (tab == visuals) {
			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Self", 184 == sub_selected)) {
				sub_selected = 184;
			}
			ImGui::EndGroup();

			//armasex
			if (sub_selected == 184) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Player", ImVec2(219, 342));
				{
					ImGui::Checkbox("Freeze Player", &ex_freezeplayer);
					ImGui::Checkbox("Invisible", &ex_invisible);
					ImGui::Checkbox("God Mode", &ex_godmode);
					ImGui::Checkbox("Semi GodMode", &ex_semigodmode);
					ImGui::Checkbox("Run Speed", &ex_runspeed_on);
					ImGui::Checkbox("Inf Stamina", &ex_infstam);
					ImGui::Checkbox(skCrypt("Fov Changer (GLITCHY)"), &customfov);
					if (customfov)
					{

						ImGui::SliderInt(skCrypt(("Fov")), &fovvalue, 0.0f, 150);
					}
					ImGui::SliderFloat(XorStr("Run Speed").c_str(), &ex_runspeed_value, 0.f, 10.f, "% .1f");
				}
				ImGui::EndChild();
			}


				ImGui::SetCursorPos(ImVec2(291, 44));
				ImGui::BeginChild("Vehicle", ImVec2(219, 342));
				{
					//ImGui::Checkbox("Vehicle Gravity", &ex_vehiclegravity);
					ImGui::Checkbox("Vehicle Booster", &ex_boostvehicle);
					ImGui::Checkbox("Vehicle Acceleration", &ex_vehicleaceleration);
					ImGui::Checkbox("Vehicle Brake Force", &ex_vehiclebreak);
					ImGui::Checkbox("Vehicle GodMode", &ex_vehiclegodmode);
					ImGui::Checkbox("Fix Engine", &the_bool);
					if (ImGui::Button("Fix Engine", ImVec2(192, 22))) {
						Vehicle::FixEngine(1000.f);
					}
					ImGui::SliderFloat(XorStr("Vehicle Acceleration").c_str(), &ex_vehicleaceleration_value, 0.f, 20000.f, "% .2f");
					ImGui::Spacing();
					ImGui::SliderFloat(XorStr("Vehicle Brake Force").c_str(), &ex_vehiclebreak_value, 0.f, 20000.f, "% .2f");
					ImGui::Spacing();
					ImGui::SliderFloat(XorStr("Vehicle Booster").c_str(), &ex_boostvehicle_value, 0.f, 20000.f, "% .2f");
					ImGui::Spacing();
					//ImGui::SliderFloat(XorStr("Vehicle Gravity").c_str(), &ex_vehiclegravity_value, 0.f, 200.f, "% .2f");
				}
				ImGui::EndChild();

			}




		if (tab == skins) {

			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Weapons", 222 == sub_selected)) {
				sub_selected = 222; 
			}
			ImGui::EndGroup();

			//armas
			if (sub_selected == 222) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Weapons", ImVec2(219, 342));
				{
					ImGui::Checkbox("Infinite Ammo", &ex_infammo);
					ImGui::Checkbox("No Recoil", &ex_norecoil);
					ImGui::Checkbox("No Reload", &ex_noreaload);
					ImGui::Checkbox("No Spread", &ex_nospread);
					ImGui::Checkbox("Move To Teleport", &noclipworks);
					ImGui::Checkbox(skCrypt("Damage Boost"), &damageboost);
					if (damageboost)
					{

						ImGui::SliderInt(skCrypt("Damage Amount"), &damageamount, 0.0f, 200);
					}
				}

				ImGui::EndChild();


			}
		}


		if (tab == settings) {

			ImGui::BeginGroup();
			ImGui::SetCursorPos(ImVec2(65, 14));
			if (custom_interface::subtab("Config", 456 == sub_selected)) {
				sub_selected = 456; 
			}
			ImGui::EndGroup();

			//armas
			if (sub_selected == 456) {
				ImGui::SetCursorPos(ImVec2(65, 44));
				ImGui::BeginChild("Binds", ImVec2(219, 342));
				{
					ImGui::ColorEdit4("Particle Colour", &particleColour.x);
					ImGui::Checkbox("Snowflake Background Animation", &Snowflakenable);
					ImGui::Combo("Menu Bind", &bind_menu, menu_bind, IM_ARRAYSIZE(menu_bind));
					ImGui::Combo("Aimbot Bind", &bind_aimbot, aimbot_bind, IM_ARRAYSIZE(aimbot_bind));
					ImGui::Combo("TriggerBot Bind", &bind_trigger, trigger_bind, IM_ARRAYSIZE(trigger_bind));
				}
				ImGui::EndChild();


			}
		}

		ImGui::End();

	}


	auto RGB = ImGui::GetColorU32({ color_red, color_green, color_blue, 255 });

	if (gaybow) {

		Colors::ESPCorner = RGB;

		Colors::ESPLines = RGB;
		Colors::ESPBox = RGB;
		Colors::ESPName = RGB;
		Colors::ESPSkeleton = RGB;

		Colors::ESPDistance = RGB;
		Colors::ESPHpText = RGB;

		Colors::FovCircle = RGB;

		Colors::Crosshair = RGB;




		//Colors::ESPCorner = ImColor(Colors::ESPCorner_float[0], Colors::ESPCorner_float[1], Colors::ESPCorner_float[2], Colors::ESPCorner_float[3]);
		//Colors::ESPLines = ImColor(Colors::ESPLines_float[0], Colors::ESPLines_float[1], Colors::ESPLines_float[2], Colors::ESPLines_float[3]);
		//Colors::ESPBox = ImColor(Colors::ESPBox_float[0], Colors::ESPBox_float[1], Colors::ESPBox_float[2], Colors::ESPBox_float[3]);
		//Colors::ESPName = ImColor(Colors::ESPName_float[0], Colors::ESPName_float[1], Colors::ESPName_float[2], Colors::ESPName_float[3]);
		//Colors::FovCircle = ImColor(Colors::FovCircle_float[0], Colors::FovCircle_float[1], Colors::FovCircle_float[2], Colors::FovCircle_float[3]);
	}
	else {

	}


	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(menu_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(menu_window);
}

void ReallockLocalPlayer() {
	while (true) {

		localplayer = read_mem<uintptr_t>(world_ptr + (0x8));

	}
}

//
//void debuginfo() {
//	std::cout << " [-] ProcessName:                " << procname << "\n";
//
//	std::cout << " [-] pid:                        " << pid << "\n";
//	std::cout << " [-] process_handle:             " << process_handle << "\n";
//	std::cout << " [-] base_address.modBaseAddr:   " << base_address.modBaseAddr << "\n\n";
//
//	ReplayInterface_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_replay));
//	std::cout << " [-] ReplayInterface:            " << ReplayInterface_ptr << "\n";
//
//	world_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_world));
//	std::cout << " [-] world_ptr:                  " << world_ptr << "\n";
//
//	viewport_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_view));
//	std::cout << " [-] viewport:                   " << viewport_ptr << "\n\n";
//
//	localplayer = read_mem<uintptr_t>(world_ptr + (0x8));
//	std::cout << " [-] LocalPlayer:                " << localplayer << "\n";
//}

string procname = "";
int initialize() {
	attach_window = FindWindow("grcWindow", 0);
	DWORD off_world, off_replay, off_view;
	if (isProcRunning("FiveM_GTAProcess.exe")) {
		off_world = offset::b1604::world_ptr;
		off_replay = offset::b1604::ReplayInterface_ptr;
		off_view = offset::b1604::viewport_ptr;
		procname = "FiveM_GTAProcess.exe";
	}
	else if (isProcRunning("FiveM_b2060_GTAProcess.exe")) {
		off_world = offset::b2060::world_ptr;
		off_replay = offset::b2060::ReplayInterface_ptr;
		off_view = offset::b2060::viewport_ptr;
		procname = "FiveM_b2060_GTAProcess.exe";

	}
	else if (isProcRunning("FiveM_b2189_GTAProcess.exe")) {
		off_world = offset::b2189::world_ptr;
		off_replay = offset::b2189::ReplayInterface_ptr;
		off_view = offset::b2189::viewport_ptr;
		procname = "FiveM_b2189_GTAProcess.exe";

	}
	else if (isProcRunning("FiveM_b2372_GTAProcess.exe")) {
		off_world = offset::b2372::world_ptr;
		off_replay = offset::b2372::ReplayInterface_ptr;
		off_view = offset::b2372::viewport_ptr;
		procname = "FiveM_b2372_GTAProcess.exe";

	}
	else if (isProcRunning("FiveM_b2545_GTAProcess.exe")) {
		off_world = offset::b2545::world_ptr;
		off_replay = offset::b2545::ReplayInterface_ptr;
		off_view = offset::b2545::viewport_ptr;
		procname = "FiveM_b2545_GTAProcess.exe";

	}
	else if (isProcRunning("FiveM_b2612_GTAProcess.exe")) {
		off_world = offset::b2612::world_ptr;
		off_replay = offset::b2612::ReplayInterface_ptr;
		off_view = offset::b2612::viewport_ptr;
		procname = "FiveM_b2612_GTAProcess.exe";
	}
	else if (isProcRunning("FiveM_b2699_GTAProcess.exe")) {
		off_world = offset::b2699::world_ptr;
		off_replay = offset::b2699::ReplayInterface_ptr;
		off_view = offset::b2699::viewport_ptr;
		procname = "FiveM_b2699_GTAProcess.exe";
	}
	else if (isProcRunning("FiveM_b2802_GTAProcess.exe")) {
		off_world = offset::b2802::world_ptr;
		off_replay = offset::b2802::ReplayInterface_ptr;
		off_view = offset::b2802::viewport_ptr;
		procname = "FiveM_b2802_GTAProcess.exe";
	}
	if (!attach_window) {
		MessageBox(NULL, "Could not find FiveM process.", "Error", MB_ICONERROR);
		ExitProcess(0);
	}

	//fps();

	DWORD pid;
	GetWindowThreadProcessId(attach_window, &pid);

	process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	base_address = get_module_base64(pid, (procname).c_str());

	ReplayInterface_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_replay));

	world_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_world));

	viewport_ptr = read_mem<uintptr_t>(base_address.modBaseAddr + (off_view));

	localplayer = read_mem<uintptr_t>(world_ptr + (0x8));


	setupWindow();
	if (!menu_window) { return 1; }

	CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)ReallockLocalPlayer, nullptr, NULL, nullptr);
	tema();
	while (!glfwWindowShouldClose(menu_window)) {
		handleKeyPresses();
		Render();
	}

	cleanupWindow();
}


//UNDO TO INTERNAL

#ifdef _WINDLL
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	if (fdwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)initialize, nullptr, NULL, nullptr);
		return TRUE;

	}
	return TRUE;
}

//#ifdef _WINDLL
//BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
//	if (fdwReason == DLL_PROCESS_ATTACH) {
//		DisableThreadLibraryCalls(hinstDLL);
//		CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)initialize, nullptr, NULL, nullptr);
//		return TRUE;
//
//	}
//	return TRUE;
//}

//api KeyAuthApp(name, ownerid, secret, version, url);

int main() {
	namespace con = JadedHoboConsole;
	SetConsoleTitleA(skCrypt("Overlay | FiveM"));

	initialize();
}

std::string tm_to_readable_time(tm ctx) {
	char buffer[80];

	strftime(buffer, sizeof(buffer), "%a %m/%d/%y %H:%M:%S %Z", &ctx);

	return std::string(buffer);
}

static std::time_t string_to_timet(std::string timestamp) {
	auto cv = strtol(timestamp.c_str(), NULL, 10); // long

	return (time_t)cv;
}

static std::tm timet_to_tm(time_t timestamp) {
	std::tm context;

	localtime_s(&context, &timestamp);

	return context;

}
#endif} //UNDO FOR INTERNAL