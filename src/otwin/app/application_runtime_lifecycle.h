#ifndef OTWIN_APPLICATION_RUNTIME_LIFECYCLE_H
#define OTWIN_APPLICATION_RUNTIME_LIFECYCLE_H

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This product header requires the 32-bit Microsoft compiler."
#endif

#include <stddef.h>

#pragma pack(push, 1)

struct ApplicationPositionedBitmap_004044f0 {
    unsigned long bitmap_info_handle;
    unsigned long indexed_pixels_handle;
    unsigned long bitmap_info;
    unsigned long indexed_pixels;
    short left;
    short top;
    short width;
    short height;
    int left_int;
    int top_int;
    int right;
    int bottom;

    ApplicationPositionedBitmap_004044f0();
    ~ApplicationPositionedBitmap_004044f0();
};

typedef int (__stdcall *ApplicationDialogProc_00405a40)(
    void* dialog,
    unsigned int message,
    unsigned int wparam,
    long lparam);

class MainWindowRuntimeObject_00405a40 {
public:
    virtual long OtDispatchWindowMessage_004039d0_ProductWip(
        unsigned int message,
        unsigned int wparam,
        long lparam);

    void* main_window;
    int flow_state;
    ApplicationDialogProc_00405a40 active_dialog_proc;
    void* captured_interaction_window;
    ApplicationPositionedBitmap_004044f0 backdrop;
    ApplicationPositionedBitmap_004044f0 title;
    ApplicationPositionedBitmap_004044f0 guide;
    ApplicationPositionedBitmap_004044f0 wagon;
    ApplicationPositionedBitmap_004044f0* active_overlay;
    unsigned int overlay_timer;
    int should_start_overlay_timer;

    void OtInitPaletteBrushes_Product_00403530();
    MainWindowRuntimeObject_00405a40();
    ~MainWindowRuntimeObject_00405a40();
};

typedef char ApplicationPositionedBitmapSizeCheck_004044f0[
    sizeof(ApplicationPositionedBitmap_004044f0) == 0x28 ? 1 : -1];
typedef char MainWindowRuntimeObjectSizeCheck_00405a40[
    sizeof(MainWindowRuntimeObject_00405a40) == 0xc0 ? 1 : -1];
typedef char MainWindowRuntimeMainWindowOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, main_window) == 0x04 ? 1 : -1];
typedef char MainWindowRuntimeFlowStateOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, flow_state) == 0x08 ? 1 : -1];
typedef char MainWindowRuntimeDialogProcOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, active_dialog_proc) == 0x0c ? 1 : -1];
typedef char MainWindowRuntimeInteractionOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, captured_interaction_window) == 0x10 ? 1 : -1];
typedef char MainWindowRuntimeBackdropOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, backdrop) == 0x14 ? 1 : -1];
typedef char MainWindowRuntimeTitleOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, title) == 0x3c ? 1 : -1];
typedef char MainWindowRuntimeGuideOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, guide) == 0x64 ? 1 : -1];
typedef char MainWindowRuntimeWagonOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, wagon) == 0x8c ? 1 : -1];
typedef char MainWindowRuntimeOverlayOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, active_overlay) == 0xb4 ? 1 : -1];
typedef char MainWindowRuntimeTimerOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, overlay_timer) == 0xb8 ? 1 : -1];
typedef char MainWindowRuntimeTimerFlagOffsetCheck_00405a40[
    offsetof(MainWindowRuntimeObject_00405a40, should_start_overlay_timer) == 0xbc ? 1 : -1];

#pragma pack(pop)

extern "C" void __fastcall OtCreateMainWindow_004035b0(
    MainWindowRuntimeObject_00405a40* runtime);

#endif
