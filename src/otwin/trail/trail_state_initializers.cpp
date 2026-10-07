#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This match-candidate file must be compiled with 32-bit MSVC."
#endif

#include "grave_site_runtime.h"

#pragma pack(push, 1)
struct GameDateTextState_00419300 {
    char formatted_date[0x14];
    short year;
    short month_string_id;
    short day;

    void OtRefreshGameDateText_00419300_RealCpp();
};

struct GameDateState_00419410 {
    char formatted_date[0x14];
    short year;
    short month_string_id;
    short day;

    void OtInitializeGameDate_RealCpp(short month_string_id_value);
};

struct PendingMileageState_0041a100 {
    char reserved_00[0x5c];
    short applied_miles;
    char reserved_5e[0x2c];
    short pending_miles;
};
#pragma pack(pop)

#pragma optimize("s", off)
#pragma optimize("t", on)

void GameDateState_00419410::OtInitializeGameDate_RealCpp(
    short month_string_id_value)
{
    year = 0x0738;
    day = 1;
    month_string_id = month_string_id_value;
    reinterpret_cast<GameDateTextState_00419300*>(this)->
        OtRefreshGameDateText_00419300_RealCpp();
}

extern "C" void __fastcall OtFlushPendingMileageAdjustment_RealCpp(
    PendingMileageState_0041a100* state)
{
    short pending_miles = state->pending_miles;
    state->pending_miles = 0;
    state->applied_miles =
        static_cast<short>(state->applied_miles + pending_miles);
}

GraveSiteRuntime_00411ee0*
GraveSiteRuntime_00411ee0::OtInitGraveSiteRuntime_RealCpp()
{
    cached_zone = -1;
    return this;
}

GraveSiteRuntime_00411ee0::GraveSiteRuntime_00411ee0()
{
    cached_zone = -1;
}

#pragma optimize("", on)
