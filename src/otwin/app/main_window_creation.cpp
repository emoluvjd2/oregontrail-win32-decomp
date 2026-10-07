// Recovered main-window creation at Oregon32.exe VA 0x004035b0.
// The original receives the runtime object in ECX and has no stack arguments.
// This fastcall facade preserves that ABI for the application constructor.

#include "application_runtime_lifecycle.h"
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int);
extern "C" __declspec(dllimport) int __stdcall GetVersionExA(void*);
extern "C" __declspec(dllimport) void __stdcall FatalAppExitA(unsigned int,const char*);
extern "C" __declspec(dllimport) void* __stdcall CreateWindowExA(unsigned long,const char*,const char*,unsigned long,int,int,int,int,void*,void*,void*,void*);
extern "C" int g_mainWindowClassRegistered_00439120;
extern "C" void* g_previousInstance_00405a40_20260603;
extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" const char g_mainWindowClassName_00404f60[];
extern "C" const char g_mainWindowPlacementSection_004039d0[];
extern "C" const char g_mainWindowTitle_004044f0[];
extern "C" const char g_mainWindowCreateFailure_004044f0[];
extern "C" void __cdecl OtRegisterMainWindowClass_00404f60_RealCpp();
struct SavedMainWindowRect_004035b0 { int x,y,width,height; };
struct OSVersionInfoA_004035b0 { unsigned long size,major_version,minor_version,build_number,platform_id; char service_pack[128]; };
extern "C" int __cdecl OtLoadSavedDialogPlacement_00401110_RealCpp(const char*,SavedMainWindowRect_004035b0*);
#pragma optimize("s", off)
#pragma optimize("t", on)
extern "C" void __fastcall OtCreateMainWindow_004035b0(
    MainWindowRuntimeObject_00405a40* runtime)
{
    SavedMainWindowRect_004035b0 placement;
    OSVersionInfoA_004035b0 version;
    int frame_width;
    int frame_height;
    int window_width;
    int window_height;

    if (g_mainWindowClassRegistered_00439120 == 0 &&
        g_previousInstance_00405a40_20260603 == 0) {
        OtRegisterMainWindowClass_00404f60_RealCpp();
        g_mainWindowClassRegistered_00439120 = 1;
    }

    frame_width = GetSystemMetrics(5);
    frame_height = GetSystemMetrics(6);
    version.size = sizeof(version);
    GetVersionExA(&version);
    if (version.major_version > 3) {
        frame_width += GetSystemMetrics(45);
        frame_height += GetSystemMetrics(46);
    }

    window_width = frame_width * 2 + 0x280;
    window_height = GetSystemMetrics(4) + GetSystemMetrics(15) +
        frame_height * 2 + 0x1b8;
    placement.x = 0;
    placement.y = 0;
    placement.width = window_width;
    placement.height = window_height;
    OtLoadSavedDialogPlacement_00401110_RealCpp(
        g_mainWindowPlacementSection_004039d0,
        &placement);

    runtime->main_window = CreateWindowExA(
        0,
        g_mainWindowClassName_00404f60,
        g_mainWindowTitle_004044f0,
        0x00ca0000ul,
        placement.x,
        placement.y,
        window_width,
        window_height,
        0,
        0,
        g_applicationModule_00405a40_20260603,
        runtime);
    if (runtime->main_window == 0) {
        FatalAppExitA(0, g_mainWindowCreateFailure_004044f0);
    }
}

#pragma optimize("", on)
