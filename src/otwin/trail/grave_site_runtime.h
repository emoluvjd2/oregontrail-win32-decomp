#ifndef OTWIN_TRAIL_GRAVE_SITE_RUNTIME_H
#define OTWIN_TRAIL_GRAVE_SITE_RUNTIME_H

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This recovered Product state requires 32-bit Microsoft C++."
#endif

#pragma pack(push, 1)
struct GraveSiteRuntime_00411ee0 {
    short cached_zone;
    short last_landmark;
    short next_landmark;
    short miles_to_next;
    char grave_name[15];
    char epitaph[45];
    int grave_event_reported;

    GraveSiteRuntime_00411ee0();
    GraveSiteRuntime_00411ee0* OtInitGraveSiteRuntime_RealCpp();
    void OtWriteGraveRecordToIni_000120b0_Product(
        const char* epitaph_text);
};
#pragma pack(pop)

typedef char OtGraveSiteRuntimeSizeMustBe48[
    sizeof(GraveSiteRuntime_00411ee0) == 0x48 ? 1 : -1];
typedef char OtGraveNameOffsetMustBe08[
    (unsigned int)&(((GraveSiteRuntime_00411ee0*)0)->grave_name) == 0x08
        ? 1
        : -1];
typedef char OtGraveEpitaphOffsetMustBe17[
    (unsigned int)&(((GraveSiteRuntime_00411ee0*)0)->epitaph) == 0x17
        ? 1
        : -1];
typedef char OtGraveEventReportedOffsetMustBe44[
    (unsigned int)&(
        ((GraveSiteRuntime_00411ee0*)0)->grave_event_reported) == 0x44
        ? 1
        : -1];

extern "C" GraveSiteRuntime_00411ee0* g_graveSiteRuntime;

#endif
