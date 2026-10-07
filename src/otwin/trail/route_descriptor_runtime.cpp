// Canonical product implementation of Oregon32.exe route-resource loading
// (RVA 0x00024dd0).

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This product source must be compiled with 32-bit MSVC."
#endif

#include "journey_allocation_runtime.h"

extern "C" void* g_resourceModule;
extern "C" void* g_activeRouteDescriptor;

extern "C" __declspec(dllimport) void* __stdcall FindResourceA(
    void* instance,
    const void* name,
    const void* type);
extern "C" __declspec(dllimport) void* __stdcall LoadResource(
    void* instance,
    void* resource_info);
extern "C" __declspec(dllimport) void* __stdcall LockResource(
    void* resource_handle);
extern "C" __declspec(dllimport) int __stdcall FreeResource(
    void* resource_handle);

#pragma comment(lib, "kernel32.lib")

#pragma code_seg(".otsem")
#pragma optimize("s", off)
#pragma optimize("t", on)
void RouteDescriptorBlock_00424dd0_Product::Load(short route_id)
{
    unsigned short resource_name = static_cast<unsigned short>(route_id);
    resource_name = static_cast<unsigned short>(resource_name + 0x4b0);

    void* resource_info = FindResourceA(
        g_resourceModule,
        reinterpret_cast<const void*>(
            static_cast<unsigned int>(resource_name)),
        reinterpret_cast<const void*>(0x1f4));
    void* resource_handle = LoadResource(g_resourceModule, resource_info);
    RouteDescriptorBlock_00424dd0_Product* source =
        static_cast<RouteDescriptorBlock_00424dd0_Product*>(
            LockResource(resource_handle));

    *static_cast<RouteDescriptorBlock_00424dd0_Product*>(
        g_activeRouteDescriptor) = *source;

    FreeResource(resource_handle);
}
#pragma optimize("", on)
#pragma code_seg()

// Compatibility entry for existing recovered callers with a stdcall facade.
extern "C" void __stdcall OtLoadRouteDescriptor_RealCpp(short route_id)
{
    static_cast<RouteDescriptorBlock_00424dd0_Product*>(g_activeRouteDescriptor)->Load(route_id);
}
