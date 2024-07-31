//#pragma once
//#include "main.hpp"
//#include "include.h"
//#include "esp.hpp"
//#include "aimbot.hpp"
//#include "memory.h"
//#include "offsets.h"
//#include "exploit.h"
//#include "xor.hpp"
//#include <Windows.h>
//#include "auth.hpp"
//#include <string>
//#include "skStr.h"
//#include <urlmon.h>
//#include "color.hpp"
//#include "user_interface.h"
//#include "imgui/imgui_impl_win32.h"
//#include "trigger.hpp"
//#include "nav_elements.h"
//#include "Console.h"
//#include "fa_solid_900.h"
//#include "Fonts.hpp"
//#include "main.hpp"
//#include "include.h"
//static float noclipspeed = 1.00001f;
//static bool speed = false;
//
//class hk_Ped
//{
//public:
//};
//
//class hk_World
//{
//public:
//	hk_Ped* LocalPlayer()
//	{
//		if (!this) return 0;
//		return (hk_Ped*)(*(uint64_t*)(this + 0x8));
//	}
//};
//
//class hk_ObjectNavigationPed
//{
//public:
//	Vector3 GetCoordinate()
//	{
//		if (!this) return Vector3{ 0,0,0 };
//		return *(Vector3*)(this + 0x50);
//	}
//	Vector3 SetCoordinate(Vector3 Cords)
//	{
//		if (!this) return Vector3{ 0,0,0 };
//		return *(Vector3*)(this + 0x50) = Cords;
//	}
//
//	Vector4 SetRotation(Vector4 Coords)
//	{
//		if (!this) return Vector4{ 0,0,0,0 };
//		return *(Vector4*)(this + 0x30) = Coords;
//	}
//
//	hk_ObjectNavigationPed* ObjectNavigation()
//	{
//		if (!this) return 0;
//		return (hk_ObjectNavigationPed*)(*(uint64_t*)(this + 0x30));
//	}
//	Vector3 GetCoordinate()
//	{
//		if (localplayer) return Vector3{ 0,0,0 };
//		return *(Vector3*)(localplayer + 0x50);
//	}
//	Vector3 SetCoordinate(Vector3 Cords)
//	{
//		if (!localplayer) return Vector3{ 0,0,0 };
//		return *(Vector3*)(localplayer + 0x50) = Cords;
//	}
//
//	Vector4 SetRotation(Vector4 Coords)
//	{
//		if (!localplayer) return Vector4{ 0,0,0,0 };
//		return *(Vector4*)(localplayer + 0x30) = Coords;
//	}
//
//	hk_ObjectNavigationPed* ObjectNavigation()
//	{
//		if (!localplayer) return 0;
//		return (hk_ObjectNavigationPed*)(*(uint64_t*)(localplayer + 0x30));
//	}
//};
//
//Vector3 GetCoordinate()
//{
//	if (localplayer) return Vector3{ 0,0,0 };
//	return *(Vector3*)(localplayer + 0x50);
//}
//Vector3 SetCoordinate(Vector3 Cords)
//{
//	if (!localplayer) return Vector3{ 0,0,0 };
//	return *(Vector3*)(localplayer + 0x50) = Cords;
//}
//
//Vector4 SetRotation(Vector4 Coords)
//{
//	if (!localplayer) return Vector4{ 0,0,0,0 };
//	return *(Vector4*)(localplayer + 0x30) = Coords;
//}
//
//hk_ObjectNavigationPed* ObjectNavigation()
//{
//	if (!localplayer) return 0;
//	return (hk_ObjectNavigationPed*)(*(uint64_t*)(localplayer + 0x30));
//}
//Vector3 SetVelocity()
//{
//	if (!localplayer) return Vector3{ 0,0,0 };
//	return *(Vector3*)(localplayer + 0x320) = Vector3(0, 0, 0);
//}
//bool IsInAVehicule()
//{
//	if (!localplayer) return false;
//	if (*(BYTE*)(localplayer + 0x40))
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//namespace NoClip
//{
//	void Hook(void)
//	{
//		if (esp_shield)
//		{
//			hk_World* World = (hk_World*)*(uint64_t*)(world_ptr);
//			if (!World)
//				return;
//
//			hk_Ped* LocalPlayer = World->LocalPlayer();
//			if (!LocalPlayer)
//				return;
//
//			hk_ObjectNavigationPed* Nav = ObjectNavigation();
//			if (!Nav)
//				return;
//
//			Vector3 ActualPos = GetCoordinate();
//
//			if (IsInAVehicule() == true)
//			{
//				return;
//			}
//			if (Player::GetHealth() < 100)return;
//			/// Monter
//
//			if ((GetAsyncKeyState)(VK_LSHIFT))
//				speed = true;
//			else
//				speed = false;
//			inline int noclipspeed = false;
//			if (NoClipSpeed_bool)
//			{
//				if (speed)
//				{
//					noclipspeed = speed;
//				}
//				else
//				{
//					noclipspeed = speed;
//
//				}
//			}
//			else {
//
//				if (speed)
//				{
//					noclipspeed = 1.0f;
//				}
//				else
//				{
//					noclipspeed = 0.1f;
//
//				}
//
//
//			}
//			inline int isNoclipWorking = true;
//			inline int NoclipKey = 0;
//			//VEHICLE::GET_CLOSEST_VEHICLE(ActualPos.x, ActualPos.y, ActualPos.z, 200.0f, 0, 70);
//
//
//			if ((GetAsyncKeyState)(NoclipKey))
//			{
//				isNoclipWorking = !isNoclipWorking;
//
//			}
//			else {
//
//				isNoclipWorking;
//
//			}
//
//
//			if (isNoclipWorking)
//			{
//				inline DWORD64 GetCamera();
//				{
//					if (offset::b2699::camera_ptr)
//						(DWORD64*)(offset::b2699::camera_ptr + 0x0);
//				}
//
//				class Vector4
//				{
//				public:
//					float x, y, z, w;
//				};
//
//				inline int ForwardHotkey = 90;
//
//				inline int BackwardHotkey = 0x53;
//
//				Nav->SetRotation(Vector4(0, 0, 0, 0));
//
//
//				if ((GetAsyncKeyState)(ForwardHotkey) & 0x8000)
//				{
//					SetVelocity();
//					//	LocalPlayer->SetFreeze(true);
//
//					DWORD64 addr = GetCamera();
//					Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
//					if (TPSangles == Vector3(0, 0, 0))
//					{
//						TPSangles = *(Vector3*)(addr + 0x40);
//					}
//					Vector3 newpos = ActualPos;
//					newpos.x += (TPSangles.x * noclipspeed);
//					newpos.y += (TPSangles.y * noclipspeed);
//					newpos.z += (TPSangles.z * noclipspeed);
//					SetCoordinate(newpos);
//					Nav->SetCoordinate(newpos);
//					//	LocalPlayer->SetFreeze(false);
//				}
//
//				if ((GetAsyncKeyState)(BackwardHotkey) & 0x8000)
//				{
//					SetVelocity();
//					//	LocalPlayer->SetFreeze(true);
//					DWORD64 addr = GetCamera();
//					Vector3 TPSangles = *(Vector3*)(addr + 0x03D0);
//					if (TPSangles == Vector3(0, 0, 0))
//					{
//						TPSangles = *(Vector3*)(addr + 0x40);
//					}
//					Vector3 newpos = ActualPos;
//					newpos.x -= (TPSangles.x * noclipspeed);
//					newpos.y -= (TPSangles.y * noclipspeed);
//					newpos.z -= (TPSangles.z * noclipspeed);
//					SetCoordinate(newpos);
//					Nav->SetCoordinate(newpos);
//					//	LocalPlayer->SetFreeze(false);
//				}
//
//			}
//		}
//	}
//}
//
//
//
