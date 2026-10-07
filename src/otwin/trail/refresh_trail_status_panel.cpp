// Recovered trail status-panel refresh @ 0x0042d5d0.

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This product source must be compiled with 32-bit MSVC."
#endif

#include "accepted_semantic_dependencies.h"

typedef void* WindowHandle_0042d5d0;
typedef void* DeviceContext_0042d5d0;

extern "C" void* g_journeyState;
extern "C" void* g_activeRouteDescriptor;
extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_resourceModule;
extern "C" void* g_gamePalette;

extern "C" __declspec(dllimport) WindowHandle_0042d5d0 __stdcall GetDlgItem(
    WindowHandle_0042d5d0 window,
    int control_id);
extern "C" __declspec(dllimport) int __stdcall GetWindowTextA(
    WindowHandle_0042d5d0 window,
    char* text,
    int max_count);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(
    WindowHandle_0042d5d0 window,
    const char* text);
extern "C" __declspec(dllimport) DeviceContext_0042d5d0 __stdcall GetDC(
    WindowHandle_0042d5d0 window);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(
    WindowHandle_0042d5d0 window,
    DeviceContext_0042d5d0 dc);
extern "C" __declspec(dllimport) void* __stdcall SelectPalette(
    DeviceContext_0042d5d0 dc,
    void* palette,
    int force_background);
extern "C" __declspec(dllimport) unsigned int __stdcall RealizePalette(
    DeviceContext_0042d5d0 dc);
extern "C" __declspec(dllimport) int __stdcall LoadStringA(
    void* instance,
    unsigned int id,
    char* buffer,
    int max_count);
extern "C" __declspec(dllimport) int __stdcall IsWindow(
    WindowHandle_0042d5d0 window);
extern "C" __declspec(dllimport) int __stdcall PostMessageA(
    WindowHandle_0042d5d0 window,
    unsigned int message,
    unsigned int wparam,
    long lparam);

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

extern "C" char* __cdecl strncpy(
    char* destination,
    const char* source,
    unsigned int count);
extern "C" char* __cdecl strcpy(char* destination, const char* source);
extern "C" char* __cdecl strcat(char* destination, const char* source);
extern "C" int __cdecl strcmp(const char* left, const char* right);
extern "C" void* __cdecl memset(
    void* destination,
    int value,
    unsigned int count);
extern "C" char* __cdecl _itoa(int value, char* buffer, int radix);

#pragma pack(push, 1)
struct JourneyStatusState_0042d5d0_ProductWip {
    char reserved_000[0x5a];
    unsigned short route_stop_flags;
    short current_route_mile;
    char reserved_05e[0x2c];
    short miles_to_next_landmark;
    char reserved_08c[4];
    short ration_level;
    short pace;
    char reserved_094[0x10];
    short food_whole;
    short food_fraction;
    char reserved_0a8[0x16];
    short daily_condition_value;
    char reserved_0c0[0x64];
    char date_text[0x28];
};

struct RouteDescriptor_0042d5d0_ProductWip {
    unsigned short route_id;
};

struct TrailConditionGaugeState_0042ad80_ProductWip {
    void OtDrawTrailConditionGauge_0042ad80_ProductWip(
        DeviceContext_0042d5d0 dc);
};

struct TrailSceneCaptionState_0042af80_20260603 {
    void OtDrawTrailSceneCaptionDirect_0042af80_RealCpp(
        DeviceContext_0042d5d0 dc);
};

struct TrailStatusPanelState_0042d5d0_ProductWip {
    char reserved_000[0x0a1c];
    int stopped;
    int river_crossing_mode;
    char reserved_a24[0x24];
    unsigned int travelled_distance;
    unsigned int total_distance;

    void OtRefreshTrailStatusPanel_0042d5d0_ProductWip(
        WindowHandle_0042d5d0 owner);
};

// Most trail runtimes hold this same object under its owning UI-state type.
// Keep the measured status-panel implementation above as the verifier target
// and expose the owner-class ABI as a semantic forwarding entry point.
struct TrailUiState_0042b370 {
    void OtRefreshTrailStatusPanel_0042d5d0_ProductWip(
        WindowHandle_0042d5d0 owner);
};
#pragma pack(pop)

#pragma data_seg(".otdat")
extern "C" __declspec(allocate(".otdat"))
WindowHandle_0042d5d0 g_trailStatusNotifyWindow_004390d0 = 0;
#pragma data_seg()

extern "C" const char g_trailLocationPrefix_0042d5d0[] = "To ";
extern "C" const char g_trailLocationSuffix_0042d5d0[] = ":";
extern "C" const char g_trailMotionStopped_0042d5d0[] = "Stopped";
extern "C" const char g_trailMotionRiverCrossing_0042d5d0[] = "River-crossing";
extern "C" const char g_trailMotionMoving_0042d5d0[] = "Moving";
extern "C" const char g_trailMotionWaiting_0042d5d0[] = "Waiting";
extern "C" const char g_trailMotionCamping_0042d5d0[] = "Camping";
extern "C" const char g_trailMotionDelayed_0042d5d0[] = "Delayed";
extern "C" const char g_trailMotionResting_0042d5d0[] = "Resting";

#pragma code_seg(".otsem")
#pragma optimize("s", off)
#pragma optimize("t", on)
#pragma intrinsic(strcmp)
#pragma intrinsic(strcpy)
#pragma intrinsic(strcat)
#pragma intrinsic(memset)

#define OTWIN_STATUS_JOURNEY_0042d5d0 \
    (static_cast<JourneyStatusState_0042d5d0_ProductWip*>(g_journeyState))

#define OTWIN_CLEAR_STATUS_TEXT_0042d5d0() \
    memset(desired_text, 0, sizeof(desired_text))

#define OTWIN_REFRESH_STATUS_TEXT_0042d5d0(control_id, desired_value) \
    GetWindowTextA( \
        GetDlgItem(owner_window, control_id), \
        current_text, \
        0x27); \
    if (strcmp(current_text, desired_value) != 0) { \
        SetWindowTextA( \
            GetDlgItem(owner_window, control_id), \
            desired_value); \
    }

void TrailStatusPanelState_0042d5d0_ProductWip::
OtRefreshTrailStatusPanel_0042d5d0_ProductWip(
    WindowHandle_0042d5d0 owner)
{
    char desired_text[40];
    char current_text[40];
    WindowHandle_0042d5d0 owner_window = owner;
    int miles;
    DeviceContext_0042d5d0 dc;

    strncpy(
        desired_text,
        OTWIN_STATUS_JOURNEY_0042d5d0->date_text,
        0x27);
    GetWindowTextA(
        GetDlgItem(owner_window, 0x1069),
        current_text,
        0x27);
    if (strcmp(desired_text, current_text) != 0) {
        SetWindowTextA(
            GetDlgItem(owner_window, 0x1069),
            OTWIN_STATUS_JOURNEY_0042d5d0->date_text);
    }

    dc = GetDC(owner_window);
    SelectPalette(dc, g_gamePalette, 0);
    RealizePalette(dc);
    reinterpret_cast<TrailConditionGaugeState_0042ad80_ProductWip*>(this)->
        OtDrawTrailConditionGauge_0042ad80_ProductWip(dc);
    reinterpret_cast<TrailSceneCaptionState_0042af80_20260603*>(this)->
        OtDrawTrailSceneCaptionDirect_0042af80_RealCpp(dc);
    ReleaseDC(owner_window, dc);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    strcpy(desired_text, g_trailLocationPrefix_0042d5d0);
    LoadStringA(
        g_resourceModule,
        static_cast<RouteDescriptor_0042d5d0_ProductWip*>(
            g_activeRouteDescriptor)->route_id * 0x10 + 0xdb,
        desired_text + 3,
        0x23);
    strcat(desired_text, g_trailLocationSuffix_0042d5d0);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x106c, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    miles = OTWIN_STATUS_JOURNEY_0042d5d0->miles_to_next_landmark;
    if (miles < 0) {
        miles = 0;
    }
    _itoa(miles, desired_text, 10);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x106d, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    _itoa(
        OTWIN_STATUS_JOURNEY_0042d5d0->current_route_mile,
        desired_text,
        10);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x106f, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    _itoa(
        OTWIN_STATUS_JOURNEY_0042d5d0->food_whole +
            OTWIN_STATUS_JOURNEY_0042d5d0->food_fraction,
        desired_text,
        10);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x1071, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    LoadStringA(
        g_applicationModule_00405a40_20260603,
        OTWIN_STATUS_JOURNEY_0042d5d0->daily_condition_value / 35 + 0xb0,
        desired_text,
        0x27);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x1073, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    LoadStringA(
        g_applicationModule_00405a40_20260603,
        OTWIN_STATUS_JOURNEY_0042d5d0->ration_level + 0x50,
        desired_text,
        0x27);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x1075, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    LoadStringA(
        g_applicationModule_00405a40_20260603,
        OTWIN_STATUS_JOURNEY_0042d5d0->pace + 0x60,
        desired_text,
        0x27);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x1077, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    LoadStringA(
        g_applicationModule_00405a40_20260603,
        reinterpret_cast<const PartyHealthScoreState_00419560_80pct*>(
            g_journeyState)->OtGetPartyHealthClassStringId_RealCpp(),
        desired_text,
        0x27);
    OTWIN_REFRESH_STATUS_TEXT_0042d5d0(0x1079, desired_text);

    OTWIN_CLEAR_STATUS_TEXT_0042d5d0();
    if (this->stopped == 1) {
        SetWindowTextA(GetDlgItem(owner_window, 0x107b),
            g_trailMotionStopped_0042d5d0);
    } else {
        if ((OTWIN_STATUS_JOURNEY_0042d5d0->route_stop_flags & 0x10) != 0) {
            SetWindowTextA(GetDlgItem(owner_window, 0x107b),
                g_trailMotionResting_0042d5d0);
        } else if ((OTWIN_STATUS_JOURNEY_0042d5d0->route_stop_flags & 0x20) != 0) {
            SetWindowTextA(GetDlgItem(owner_window, 0x107b),
                g_trailMotionDelayed_0042d5d0);
        } else if (this->travelled_distance >= this->total_distance) {
            SetWindowTextA(GetDlgItem(owner_window, 0x107b),
                g_trailMotionCamping_0042d5d0);
        } else if ((OTWIN_STATUS_JOURNEY_0042d5d0->route_stop_flags & 0x40) != 0) {
            SetWindowTextA(GetDlgItem(owner_window, 0x107b),
                g_trailMotionWaiting_0042d5d0);
        } else if (this->river_crossing_mode == 0) {
            SetWindowTextA(GetDlgItem(owner_window, 0x107b),
                g_trailMotionMoving_0042d5d0);
        } else {
            SetWindowTextA(GetDlgItem(owner_window, 0x107b),
                g_trailMotionRiverCrossing_0042d5d0);
        }
    }

    if (IsWindow(g_trailStatusNotifyWindow_004390d0) != 0) {
        PostMessageA(g_trailStatusNotifyWindow_004390d0, 0x47e, 0, 0);
    }
}

#undef OTWIN_REFRESH_STATUS_TEXT_0042d5d0
#undef OTWIN_CLEAR_STATUS_TEXT_0042d5d0
#undef OTWIN_STATUS_JOURNEY_0042d5d0

void TrailUiState_0042b370::
OtRefreshTrailStatusPanel_0042d5d0_ProductWip(
    WindowHandle_0042d5d0 owner)
{
    reinterpret_cast<TrailStatusPanelState_0042d5d0_ProductWip*>(this)
        ->OtRefreshTrailStatusPanel_0042d5d0_ProductWip(owner);
}

#pragma optimize("", on)
#pragma code_seg()
