#include "journey_allocation_runtime.h"
#include "grave_site_runtime.h"

// Product-tree semantic recovery of OtInitializeJourneyRuntime @ 0x0041a120.

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This product source must be compiled with 32-bit MSVC."
#endif

extern "C" __declspec(dllimport) void* __stdcall FindResourceA(
    void* module,
    const void* resource_name,
    const void* resource_type);
extern "C" __declspec(dllimport) void* __stdcall LoadResource(
    void* module,
    void* resource_info);
extern "C" __declspec(dllimport) void* __stdcall LockResource(
    void* resource_handle);

extern "C" void* __cdecl memset(
    void* destination,
    int value,
    unsigned int count);
extern void* __cdecl operator new(unsigned int bytes);

#pragma intrinsic(memset)
#pragma comment(lib, "kernel32.lib")

struct JourneyStateDefaults_0041a000_20260525 {
    void OtJourneyInitStateDefaultsMaskClosedFELTDR_0041a000();
};

struct GraveEpitaphState_00411fd0_20260603;

extern "C" void* g_journeyState;
extern "C" void* g_activeRouteDescriptor;

extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_cachedTrailResourceHandle;

extern "C" void __cdecl OtInitTrailEventTable_00018230_RealCpp();

extern "C" void __fastcall OtRefreshGraveEpitaphIniCache_00411fd0_RealCpp(
    GraveEpitaphState_00411fd0_20260603* state);

#pragma data_seg(".otdat")
extern "C" void* g_cachedTrailWeatherResourceData_0041a120_ProductWip = 0;
#pragma data_seg()

#pragma code_seg(".otsem")
extern "C" __declspec(allocate(".otsem"))
const char g_weatherResourceName_0041a120_ProductWip[] = "WEATHER_1";

#pragma optimize("s", off)
#pragma optimize("t", on)

extern "C" void __cdecl OtInitializeJourneyRuntime_0001a120_ProductWip()
{
    if (g_journeyState == 0) {
        g_journeyState = new JourneyRuntime_00419430;
    }
    if (g_activeRouteDescriptor == 0) {
        g_activeRouteDescriptor = operator new(0x13c);
    }
    if (g_graveSiteRuntime == 0) {
        g_graveSiteRuntime = new GraveSiteRuntime_00411ee0;
    }

    g_cachedTrailResourceHandle = LoadResource(g_applicationModule_00405a40_20260603, FindResourceA(
        g_applicationModule_00405a40_20260603,
        g_weatherResourceName_0041a120_ProductWip,
        reinterpret_cast<const void*>(0x4b0)));
    g_cachedTrailWeatherResourceData_0041a120_ProductWip =
        LockResource(g_cachedTrailResourceHandle);

    OtInitTrailEventTable_00018230_RealCpp();
    if (g_journeyState != 0) {
        reinterpret_cast<JourneyStateDefaults_0041a000_20260525*>(
            g_journeyState)->
                OtJourneyInitStateDefaultsMaskClosedFELTDR_0041a000();
    }
    if (g_activeRouteDescriptor != 0) {
        reinterpret_cast<RouteDescriptorBlock_00424dd0_Product*>(g_activeRouteDescriptor)->Load(0);
    }
    if (g_graveSiteRuntime != 0) {
        OtRefreshGraveEpitaphIniCache_00411fd0_RealCpp(
            reinterpret_cast<GraveEpitaphState_00411fd0_20260603*>(
                g_graveSiteRuntime));
    }
}

#pragma optimize("", on)
#pragma code_seg()
