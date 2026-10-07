#include "journey_allocation_runtime.h"
// Promotion: OtCopyTrailDateNameTriple @ 0x00419430.
//
// The original copies three null-terminated global strings (current day-name,
// month-name, year-name labels) into adjacent fields of the calendar-state
// struct using inline strcpy expansions (repne scas + rep movsd/b).

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This match-candidate file must be compiled with 32-bit MSVC."
#endif

extern "C" char* __cdecl strcpy(char* destination, const char* source);
extern "C" int __cdecl strcmp(const char* left, const char* right);
#pragma intrinsic(strcpy)
#pragma intrinsic(strcmp)

extern "C" char g_currentDayName_00439D30[1] = { 0 };
extern "C" char g_currentMonthName_00439D38[1] = { 0 };
extern "C" char g_currentYearName_00439D28[1] = { 0 };

#pragma pack(push, 1)
struct TrailCalendarNameTriple_00419430 {
    char day_name[5];
    char month_name[0x40];
    char year_name[0x20];

    TrailCalendarNameTriple_00419430* OtCopyTrailDateNameTriple_RealCpp();
    int OtMatchTrailDateNameTriple_RealCpp();
};
#pragma pack(pop)

#pragma optimize("s", off)
#pragma optimize("t", on)

TrailCalendarNameTriple_00419430*
TrailCalendarNameTriple_00419430::OtCopyTrailDateNameTriple_RealCpp()
{
    register TrailCalendarNameTriple_00419430* state = this;
    strcpy(state->day_name, g_currentDayName_00439D30);
    strcpy(state->month_name, g_currentMonthName_00439D38);
    strcpy(state->year_name, g_currentYearName_00439D28);
    return state;
}

int TrailCalendarNameTriple_00419430::OtMatchTrailDateNameTriple_RealCpp()
{
    register TrailCalendarNameTriple_00419430* state = this;
    register int day_compare =
        strcmp(state->day_name, g_currentDayName_00439D30);
    register int month_compare =
        strcmp(state->month_name, g_currentMonthName_00439D38);
    register int year_compare =
        strcmp(state->year_name, g_currentYearName_00439D28);
    register int year_after = year_compare > 0;

    return day_compare == 0 && month_compare == 0 && year_after == 0;
}

// Native constructor used by new expressions so VC4 emits the original EH flow.
JourneyRuntime_00419430::JourneyRuntime_00419430()
{
    strcpy(day_name, g_currentDayName_00439D30);
    strcpy(month_name, g_currentMonthName_00439D38);
    strcpy(year_name, g_currentYearName_00439D28);
}
