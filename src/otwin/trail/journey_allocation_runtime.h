#ifndef OTWIN_JOURNEY_ALLOCATION_RUNTIME_H
#define OTWIN_JOURNEY_ALLOCATION_RUNTIME_H

// The allocation at 0x0041a120 establishes a 0x158-byte journey object.
// Its constructor at 0x00419430 initializes only the three text fields.
#pragma pack(push, 1)
struct JourneyRuntime_00419430 {
    char day_name[5];
    char month_name[0x40];
    char year_name[0x20];
    char remaining_state[0xf3];
    JourneyRuntime_00419430();
};
struct RouteDescriptorBlock_00424dd0_Product {
    unsigned long words[0x4f];
    void Load(short route_id);
};
#pragma pack(pop)
typedef char JourneyRuntimeSizeMustBe158[sizeof(JourneyRuntime_00419430) == 0x158 ? 1 : -1];
typedef char RouteDescriptorSizeMustBe13c[sizeof(RouteDescriptorBlock_00424dd0_Product) == 0x13c ? 1 : -1];
#endif
