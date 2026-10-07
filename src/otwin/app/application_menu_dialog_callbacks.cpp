// Product-semantic dialog callbacks reached by the application menu routers.
// These replace the former empty recovery drains with the original dialog,
// resource, owner-draw, animation, and teardown behavior.

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This product source must be compiled with 32-bit MSVC."
#endif

#include "../graphics/positioned_bitmap_descriptor_state.h"
#include "../graphics/raw_indexed_bitmap_runtime.h"
#include "../graphics/sprite_blitter_runtime.h"
#include <string.h>

#pragma intrinsic(memset)
#pragma intrinsic(strlen)

typedef void* OtDialogHandle;
typedef void* OtDeviceContext;
typedef void* OtGdiHandle;
typedef void* OtResourceHandle;

#pragma pack(push, 1)
struct OtMenuRect {
    long left;
    long top;
    long right;
    long bottom;
};

struct OtMenuPoint {
    long x;
    long y;
};

struct OtMenuPaintStruct {
    char bytes[0x40];
};

struct OtMenuTextMetricA {
    long height;
    long ascent;
    long descent;
    long internal_leading;
    long external_leading;
    long average_char_width;
    long maximum_char_width;
    long weight;
    unsigned char italic;
    unsigned char underlined;
    unsigned char struck_out;
    unsigned char first_char;
    unsigned char last_char;
    unsigned char default_char;
    unsigned char break_char;
    unsigned char pitch_and_family;
    unsigned char character_set;
    long overhang;
    long digitized_aspect_x;
    long digitized_aspect_y;
};

struct OtMenuDrawItem {
    unsigned int control_type;
    unsigned int control_id;
    unsigned int item_id;
    unsigned int item_action;
    unsigned int item_state;
    OtDialogHandle item_window;
    OtDeviceContext dc;
    OtMenuRect item_rect;
    unsigned long item_data;
};

struct PositionedBitmap_0040b7b0_Semantic {
    void* bitmap_info_handle;
    void* indexed_pixels_handle;
    BitmapInfoHeader_0040b870_ProductWip* bitmap_info;
    unsigned char* indexed_pixels;
    short left;
    short top;
    short width;
    short height;
    int left_int;
    int top_int;
    int right;
    int bottom;

    int OtBlitWrappedPositionedBitmap_0040b7b0_Semantic(
        OtDeviceContext dc,
        int source_x,
        int source_y);
};

struct IntroDialogState_0040bb30_Product {
    PositionedBitmapDescriptorState_0040ba40 previous_up;
    PositionedBitmapDescriptorState_0040ba40 previous_down;
    PositionedBitmapDescriptorState_0040ba40 next_up;
    PositionedBitmapDescriptorState_0040ba40 next_down;
    PositionedBitmapDescriptorState_0040ba40 close_up;
    PositionedBitmapDescriptorState_0040ba40 close_down;

    IntroDialogState_0040bb30_Product();
};

struct AboutDialogState_0041afa0_Product {
    PositionedBitmapDescriptorState_0040ba40 close_up;
    PositionedBitmapDescriptorState_0040ba40 close_down;

    AboutDialogState_0041afa0_Product();
};

#include "../trail/trail_score_list.h"

struct TrailOverlayCaptionState_0042fe90 {
    int line_count;
    char resource_text[310];

    int OtFormatTrailOverlayCaption_RealCpp();
};

struct TrailLeaderboardProfileList_0042ff00 {
    int count;
    TrailLeaderboardEntry_0042fc30 entries[10];

    void OtSaveLeaderboardProfile_0042ff00_RealCpp();
};

struct RiverRecordTable_0042fd20 {
    int count;
    TrailLeaderboardEntry_0042fc30 entries[10];

    void OtRemoveRiverRecordAt_0042fd20_RealCpp(int index);
};
#pragma pack(pop)

typedef char OtIntroMenuDialogStateSizeMustBeF0[
    sizeof(IntroDialogState_0040bb30_Product) == 0xf0 ? 1 : -1];
typedef char OtAboutMenuDialogStateSizeMustBe50[
    sizeof(AboutDialogState_0041afa0_Product) == 0x50 ? 1 : -1];
typedef char OtTrailGameScoreListSizeMustBe13A[
    sizeof(TrailGameScoreList_0042fc30) == 0x13a ? 1 : -1];
typedef char OtMenuDrawItemDcOffsetMustBe18[
    (unsigned int)&(((OtMenuDrawItem*)0)->dc) == 0x18 ? 1 : -1];

extern "C" __declspec(dllimport) OtDeviceContext __stdcall BeginPaint(
    OtDialogHandle window,
    OtMenuPaintStruct* paint);
extern "C" __declspec(dllimport) int __stdcall EndPaint(
    OtDialogHandle window,
    const OtMenuPaintStruct* paint);
extern "C" __declspec(dllimport) OtGdiHandle __stdcall SelectPalette(
    OtDeviceContext dc,
    OtGdiHandle palette,
    int force_background);
extern "C" __declspec(dllimport) int __stdcall UnrealizeObject(
    OtGdiHandle object);
extern "C" __declspec(dllimport) unsigned int __stdcall RealizePalette(
    OtDeviceContext dc);
extern "C" __declspec(dllimport) OtGdiHandle __stdcall LoadCursorA(
    void* instance,
    const void* cursor_name);
extern "C" __declspec(dllimport) OtGdiHandle __stdcall SetCursor(
    OtGdiHandle cursor);
extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(
    OtDialogHandle window,
    int index);
extern "C" __declspec(dllimport) long __stdcall SetWindowLongA(
    OtDialogHandle window,
    int index,
    long value);
extern "C" __declspec(dllimport) int __stdcall GetUpdateRect(
    OtDialogHandle window,
    OtMenuRect* rect,
    int erase);
extern "C" __declspec(dllimport) int __stdcall FillRect(
    OtDeviceContext dc,
    const OtMenuRect* rect,
    OtGdiHandle brush);
extern "C" __declspec(dllimport) unsigned int __stdcall GetDialogBaseUnits();
extern "C" __declspec(dllimport) OtDialogHandle __stdcall GetParent(
    OtDialogHandle window);
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(
    OtDialogHandle window,
    OtMenuRect* rect);
extern "C" __declspec(dllimport) int __stdcall GetClientRect(
    OtDialogHandle window,
    OtMenuRect* rect);
extern "C" __declspec(dllimport) int __stdcall ClientToScreen(
    OtDialogHandle window,
    OtMenuPoint* point);
extern "C" __declspec(dllimport) int __stdcall SetWindowPos(
    OtDialogHandle window,
    OtDialogHandle insert_after,
    int x,
    int y,
    int width,
    int height,
    unsigned int flags);
extern "C" __declspec(dllimport) OtDialogHandle __stdcall GetDlgItem(
    OtDialogHandle dialog,
    int control_id);
extern "C" __declspec(dllimport) int __stdcall ShowWindow(
    OtDialogHandle window,
    int show_command);
extern "C" __declspec(dllimport) OtResourceHandle __stdcall FindResourceA(
    void* instance,
    const void* resource_name,
    const void* resource_type);
extern "C" __declspec(dllimport) OtResourceHandle __stdcall LoadResource(
    void* instance,
    OtResourceHandle resource_info);
extern "C" __declspec(dllimport) void* __stdcall LockResource(
    OtResourceHandle resource);
extern "C" __declspec(dllimport) int __stdcall FreeResource(
    OtResourceHandle resource);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(
    OtDialogHandle window,
    const char* text);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    OtDialogHandle owner,
    const char* text,
    const char* caption,
    unsigned int type);
extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int code);
extern "C" __declspec(dllimport) OtDialogHandle __stdcall SetFocus(
    OtDialogHandle window);
extern "C" __declspec(dllimport) long __stdcall SendMessageA(
    OtDialogHandle window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) int __stdcall EndDialog(
    OtDialogHandle dialog,
    int result);
extern "C" __declspec(dllimport) int __stdcall SetBkMode(
    OtDeviceContext dc,
    int mode);
extern "C" __declspec(dllimport) unsigned long __stdcall SetTextColor(
    OtDeviceContext dc,
    unsigned long color);
extern "C" __declspec(dllimport) OtGdiHandle __stdcall SelectObject(
    OtDeviceContext dc,
    OtGdiHandle object);
extern "C" __declspec(dllimport) unsigned long __stdcall GetTextColor(
    OtDeviceContext dc);
extern "C" __declspec(dllimport) unsigned long __stdcall GetBkColor(
    OtDeviceContext dc);
extern "C" __declspec(dllimport) unsigned long __stdcall GetSysColor(
    int index);
extern "C" __declspec(dllimport) unsigned long __stdcall SetBkColor(
    OtDeviceContext dc,
    unsigned long color);
extern "C" __declspec(dllimport) OtGdiHandle __stdcall CreateSolidBrush(
    unsigned long color);
extern "C" __declspec(dllimport) int __stdcall DeleteObject(
    OtGdiHandle object);
extern "C" __declspec(dllimport) int __stdcall DrawTextA(
    OtDeviceContext dc,
    const char* text,
    int count,
    OtMenuRect* rect,
    unsigned int format);
extern "C" __declspec(dllimport) int __stdcall EnableWindow(
    OtDialogHandle window,
    int enabled);
extern "C" __declspec(dllimport) OtGdiHandle __stdcall GetStockObject(
    int object_id);
extern "C" __declspec(dllimport) OtDeviceContext __stdcall GetDC(
    OtDialogHandle window);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(
    OtDialogHandle window,
    OtDeviceContext dc);
extern "C" __declspec(dllimport) int __stdcall GetTextMetricsA(
    OtDeviceContext dc,
    OtMenuTextMetricA* metrics);
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int index);
extern "C" __declspec(dllimport) OtDialogHandle __stdcall CreateWindowExA(
    unsigned long extended_style,
    const char* class_name,
    const char* window_name,
    unsigned long style,
    int x,
    int y,
    int width,
    int height,
    OtDialogHandle parent,
    void* menu,
    void* instance,
    void* param);
extern "C" __declspec(dllimport) OtResourceHandle __stdcall GlobalAlloc(
    unsigned int flags,
    unsigned long bytes);
extern "C" __declspec(dllimport) void* __stdcall GlobalLock(
    OtResourceHandle handle);
extern "C" __declspec(dllimport) int __stdcall GlobalUnlock(
    OtResourceHandle handle);
extern "C" __declspec(dllimport) OtResourceHandle __stdcall GlobalFree(
    OtResourceHandle handle);
extern "C" __declspec(dllimport) unsigned int __stdcall SetTimer(
    OtDialogHandle window,
    unsigned int timer_id,
    unsigned int interval,
    void* timer_proc);
extern "C" __declspec(dllimport) int __stdcall KillTimer(
    OtDialogHandle window,
    unsigned int timer_id);

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "kernel32.lib")

extern "C" void __cdecl OtScaleWindowToDialogCoords_00401370_Product(
    OtDialogHandle parent,
    OtDialogHandle child,
    int dialog_unit_width,
    int dialog_unit_height);
extern "C" void __cdecl OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
    OtDialogHandle dialog,
    int control_id,
    int dialog_unit_width,
    int dialog_unit_height);
extern "C" void __cdecl OtResizeControl_RealCpp(
    OtDialogHandle dialog,
    int control_id,
    int width,
    int height);
extern "C" void __fastcall OtFreeRawIndexedBitmap_RealCpp(void* bitmap);
extern "C" void __fastcall OtFreeSpriteBlitter_RealCpp(void* sprite);
extern "C" int __cdecl OtRandomBelow_RealCpp(int upper_bound);
extern "C" void __cdecl OtCloseWaveAudioDevice_0040d0a0_RealCpp();
extern "C" void __cdecl OtOpenWaveAudioFile_0000d110_RealCpp(
    OtDialogHandle owner_window,
    char* logical_name);
extern "C" void __cdecl OtPlayWaveAudioDirectImport_0040d3e0_RealCpp();

void __cdecl operator delete(void* block);

extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_resourceModule;
extern "C" void* g_gamePalette;
extern "C" void* g_optionMenuFont_004390d4_00405320;
extern "C" void* g_dialogFont_004390d8_00405320;
extern "C" void* g_sharedDialogBackgroundBrush_004390c0;
extern "C" int g_appBusyCursorActive_Product_004034d0;
extern "C" int g_cdMediaMode_00439108;
extern "C" int g_titleThemeEnabled_004390ec;
extern "C" int DAT_004390e8;
extern "C" const char g_titleWavePath_0041c410[];

extern "C" int g_introPageIndex_0040bb30_Product = 0;
extern "C" SpriteBlitter_00410660_Product*
    g_aboutSprite_0041afa0_Product = 0;
extern "C" RawIndexedBitmap_00410490_Product*
    g_aboutBitmap_0041afa0_Product = 0;
extern "C" OtResourceHandle g_aboutScratchHandle_0041afa0_Product = 0;
extern "C" unsigned char* g_aboutScratchBytes_0041afa0_Product = 0;
extern "C" OtResourceHandle g_aboutSpriteResource_0041afa0_Product = 0;
extern "C" int g_aboutAudioPhase_0041afa0_Product = 0;
extern "C" int g_aboutTextIndex_0041afa0_Product = 0;

extern "C" const char g_menuDialogAllocationMessage_0040bb30[] =
    "Can't allocate local memory";
extern "C" const char g_introDialogAllocationCaption_0040bb30[] =
    "IntroDlgProc";
extern "C" const char g_aboutDialogAllocationCaption_0041afa0[] =
    "AboutDlgProc";
extern "C" const char g_aboutBlupWavePath_0041afa0[] = "blup.wav";
extern "C" const char g_trailGameListBoxClass_00430350_Product[] = "LISTBOX";
extern "C" const char g_trailGameAllocationMessage_00430180[] =
    "Can't allocate memory for the list of legends.";
extern "C" const char g_emptyDialogText_00430180[] = "";

#pragma optimize("s", off)
#pragma optimize("t", on)

static void OtCenterMenuDialogInParent(
    OtDialogHandle dialog,
    OtMenuRect* measured_dialog_rect)
{
    OtMenuRect dialog_rect;
    OtMenuRect parent_rect;
    OtMenuPoint center;
    OtDialogHandle parent;

    GetWindowRect(dialog, &dialog_rect);
    if (measured_dialog_rect != 0) {
        *measured_dialog_rect = dialog_rect;
    }
    parent = GetParent(dialog);
    GetClientRect(parent, &parent_rect);
    center.x = parent_rect.left +
        (parent_rect.right - parent_rect.left) / 2;
    center.y = parent_rect.top +
        (parent_rect.bottom - parent_rect.top) / 2;
    ClientToScreen(GetParent(dialog), &center);
    SetWindowPos(
        dialog,
        0,
        center.x + (dialog_rect.left - dialog_rect.right) / 2,
        center.y + (dialog_rect.top - dialog_rect.bottom) / 2,
        dialog_rect.right - dialog_rect.left,
        dialog_rect.bottom - dialog_rect.top,
        4);
}

static void OtSetMenuDialogResourceText(
    OtDialogHandle dialog,
    int control_id,
    void* module,
    int resource_id)
{
    OtResourceHandle resource_info;
    OtResourceHandle resource;
    const char* text;

    resource_info = FindResourceA(
        module,
        (const void*)resource_id,
        (const void*)0x000a);
    resource = LoadResource(module, resource_info);
    text = (const char*)LockResource(resource);
    SetWindowTextA(GetDlgItem(dialog, control_id), text);
    FreeResource(resource);
}

static void OtBlitMenuPositionedBitmap(
    PositionedBitmapDescriptorState_0040ba40* bitmap,
    OtDeviceContext dc)
{
    reinterpret_cast<PositionedBitmap_0040b7b0_Semantic*>(bitmap)->
        OtBlitWrappedPositionedBitmap_0040b7b0_Semantic(dc, 0, 0);
}

static PositionedBitmapDescriptorState_0040ba40*
OtSelectIntroButtonBitmap(
    IntroDialogState_0040bb30_Product* state,
    unsigned int control_id,
    int pressed)
{
    if (control_id == 0x012c) {
        return pressed ? &state->close_down : &state->close_up;
    }
    if (control_id == 0x0137) {
        return pressed ? &state->previous_down : &state->previous_up;
    }
    if (control_id == 0x0138) {
        return pressed ? &state->next_down : &state->next_up;
    }
    return 0;
}

static long OtDrawIntroButton(
    OtDialogHandle dialog,
    unsigned int control_id,
    OtMenuDrawItem* item)
{
    IntroDialogState_0040bb30_Product* state;
    PositionedBitmapDescriptorState_0040ba40* bitmap;
    int pressed;

    state = (IntroDialogState_0040bb30_Product*)GetWindowLongA(dialog, 8);
    SelectPalette(item->dc, g_gamePalette, 0);
    RealizePalette(item->dc);

    if (item->item_action != 1 && item->item_action != 2) {
        return 0;
    }

    pressed = item->item_action == 2 && (item->item_state & 1) != 0;
    bitmap = OtSelectIntroButtonBitmap(state, control_id, pressed);
    if (bitmap != 0) {
        OtBlitMenuPositionedBitmap(bitmap, item->dc);
    }
    return 1;
}

static long OtInitializeIntroDialog(OtDialogHandle dialog)
{
    unsigned int dialog_units;
    int unit_width;
    int unit_height;
    IntroDialogState_0040bb30_Product* state;

    g_appBusyCursorActive_Product_004034d0 = 1;
    SetCursor(LoadCursorA(0, (const void*)0x7f02));

    dialog_units = GetDialogBaseUnits();
    unit_width = dialog_units & 0xffff;
    unit_height = dialog_units >> 16;
    OtScaleWindowToDialogCoords_00401370_Product(
        GetParent(dialog), dialog, unit_width, unit_height);
    OtCenterMenuDialogInParent(dialog, 0);

    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 32000, unit_width, unit_height);
    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 300, unit_width, unit_height);
    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 0x137, unit_width, unit_height);
    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 0x138, unit_width, unit_height);

    g_introPageIndex_0040bb30_Product = 0;
    ShowWindow(GetDlgItem(dialog, 0x137), 0);
    OtSetMenuDialogResourceText(
        dialog,
        32000,
        g_applicationModule_00405a40_20260603,
        0x7d01);

    state = new IntroDialogState_0040bb30_Product;
    if (state == 0) {
        MessageBoxA(
            GetParent(dialog),
            g_menuDialogAllocationMessage_0040bb30,
            g_introDialogAllocationCaption_0040bb30,
            0);
        PostQuitMessage(0);
        return 0;
    }

    state->previous_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2830);
    state->previous_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2831);
    state->next_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2832);
    state->next_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2833);
    state->close_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2826);
    state->close_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2827);

    OtResizeControl_RealCpp(
        dialog, 300, state->close_up.width, state->close_up.height);
    OtResizeControl_RealCpp(
        dialog, 0x137, state->previous_up.width, state->previous_up.height);
    OtResizeControl_RealCpp(
        dialog, 0x138, state->next_up.width, state->next_up.height);

    SetWindowLongA(dialog, 8, (long)state);
    SetFocus(GetDlgItem(dialog, 300));
    SendMessageA(dialog, 0x0401, 300, 0);
    return 0;
}

extern "C" long __stdcall OtIntroDialogProc_0040bb30_Product(
    OtDialogHandle dialog,
    unsigned int message,
    unsigned int wparam,
    long lparam)
{
    switch (message) {
    case 0x0002: {
        IntroDialogState_0040bb30_Product* state =
            (IntroDialogState_0040bb30_Product*)GetWindowLongA(dialog, 8);
        if (state != 0) {
            delete state;
        }
        return 1;
    }

    case 0x000f: {
        OtMenuPaintStruct paint;
        OtDeviceContext dc = BeginPaint(dialog, &paint);
        SelectPalette(dc, g_gamePalette, 0);
        UnrealizeObject(g_gamePalette);
        RealizePalette(dc);
        EndPaint(dialog, &paint);
        g_appBusyCursorActive_Product_004034d0 = 0;
        SetCursor(LoadCursorA(0, (const void*)0x7f00));
        return 1;
    }

    case 0x0014: {
        OtMenuRect update_rect;
        SelectPalette((OtDeviceContext)wparam, g_gamePalette, 0);
        RealizePalette((OtDeviceContext)wparam);
        if (GetUpdateRect(dialog, &update_rect, 0) != 0) {
            FillRect(
                (OtDeviceContext)wparam,
                &update_rect,
                g_sharedDialogBackgroundBrush_004390c0);
        }
        return 1;
    }

    case 0x002b:
        return OtDrawIntroButton(
            dialog,
            wparam,
            (OtMenuDrawItem*)lparam);

    case 0x0110:
        return OtInitializeIntroDialog(dialog);

    case 0x0111:
        switch (wparam & 0xffff) {
        case 300:
            EndDialog(dialog, 1);
            return 1;

        case 0x137:
            g_appBusyCursorActive_Product_004034d0 = 1;
            SetCursor(LoadCursorA(0, (const void*)0x7f02));
            if (g_introPageIndex_0040bb30_Product > 0) {
                --g_introPageIndex_0040bb30_Product;
            }
            ShowWindow(
                GetDlgItem(dialog, 0x137),
                g_introPageIndex_0040bb30_Product < 1 ? 0 : 5);
            ShowWindow(GetDlgItem(dialog, 0x138), 5);
            OtSetMenuDialogResourceText(
                dialog,
                32000,
                g_applicationModule_00405a40_20260603,
                0x7d01 + g_introPageIndex_0040bb30_Product);
            g_appBusyCursorActive_Product_004034d0 = 0;
            SetCursor(LoadCursorA(0, (const void*)0x7f00));
            return 1;

        case 0x138:
            g_appBusyCursorActive_Product_004034d0 = 1;
            SetCursor(LoadCursorA(0, (const void*)0x7f02));
            if (g_introPageIndex_0040bb30_Product < 2) {
                ++g_introPageIndex_0040bb30_Product;
            }
            ShowWindow(
                GetDlgItem(dialog, 0x138),
                g_introPageIndex_0040bb30_Product > 1 ? 0 : 5);
            ShowWindow(GetDlgItem(dialog, 0x137), 5);
            OtSetMenuDialogResourceText(
                dialog,
                32000,
                g_applicationModule_00405a40_20260603,
                0x7d01 + g_introPageIndex_0040bb30_Product);
            g_appBusyCursorActive_Product_004034d0 = 0;
            SetCursor(LoadCursorA(0, (const void*)0x7f00));
            return 1;
        }
        return 0;

    case 0x0136:
        SelectPalette((OtDeviceContext)wparam, g_gamePalette, 0);
        RealizePalette((OtDeviceContext)wparam);
        SetBkMode((OtDeviceContext)wparam, 1);
        SetTextColor((OtDeviceContext)wparam, 0);
        SelectObject(
            (OtDeviceContext)wparam,
            g_optionMenuFont_004390d4_00405320);
        return (long)g_sharedDialogBackgroundBrush_004390c0;

    case 0x0138:
        SelectPalette((OtDeviceContext)wparam, g_gamePalette, 0);
        RealizePalette((OtDeviceContext)wparam);
        SetBkMode((OtDeviceContext)wparam, 1);
        SetTextColor((OtDeviceContext)wparam, 0);
        SelectObject(
            (OtDeviceContext)wparam,
            g_dialogFont_004390d8_00405320);
        return (long)g_sharedDialogBackgroundBrush_004390c0;
    }

    return 0;
}

TrailGameScoreList_0042fc30::TrailGameScoreList_0042fc30()
{
    memset(entries, 0, sizeof(entries));
}

static long OtDrawAboutCloseButton(
    OtDialogHandle dialog,
    unsigned int control_id,
    OtMenuDrawItem* item)
{
    AboutDialogState_0041afa0_Product* state;
    PositionedBitmapDescriptorState_0040ba40* bitmap;

    state = (AboutDialogState_0041afa0_Product*)GetWindowLongA(dialog, 8);
    SelectPalette(item->dc, g_gamePalette, 0);
    RealizePalette(item->dc);
    if (control_id != 300 ||
        (item->item_action != 1 && item->item_action != 2)) {
        return 0;
    }

    bitmap = item->item_action == 2 && (item->item_state & 1) != 0
        ? &state->close_down
        : &state->close_up;
    OtBlitMenuPositionedBitmap(bitmap, item->dc);
    return 1;
}

static void OtPlayAboutWave(
    OtDialogHandle dialog,
    const char* logical_name)
{
    OtOpenWaveAudioFile_0000d110_RealCpp(dialog, (char*)logical_name);
    OtPlayWaveAudioDirectImport_0040d3e0_RealCpp();
}

static void OtInitializeAboutDialog(OtDialogHandle dialog)
{
    unsigned int dialog_units;
    int unit_width;
    int unit_height;
    OtResourceHandle resource_info;
    AboutDialogState_0041afa0_Product* state;

    g_appBusyCursorActive_Product_004034d0 = 1;
    g_aboutSprite_0041afa0_Product = new SpriteBlitter_00410660_Product;
    g_aboutBitmap_0041afa0_Product =
        new RawIndexedBitmap_00410490_Product(
            g_resourceModule, 0x00fa, 0x003c, 0);
    g_aboutScratchHandle_0041afa0_Product = GlobalAlloc(0, 5000);
    g_aboutScratchBytes_0041afa0_Product =
        (unsigned char*)GlobalLock(g_aboutScratchHandle_0041afa0_Product);
    resource_info = FindResourceA(
        g_resourceModule, (const void*)0x07d3, (const void*)0x000a);
    g_aboutSpriteResource_0041afa0_Product =
        LoadResource(g_resourceModule, resource_info);

    g_aboutBitmap_0041afa0_Product->last_x = 0;
    g_aboutBitmap_0041afa0_Product->last_y = 0x00be;
    g_aboutSprite_0041afa0_Product->source_frame = 0;
    g_aboutSprite_0041afa0_Product->source_pixels =
        (unsigned char*)LockResource(g_aboutSpriteResource_0041afa0_Product);
    g_aboutSprite_0041afa0_Product->horizontal_flip = 0;
    g_aboutSprite_0041afa0_Product->transparent_index = 0xe1;
    g_aboutSprite_0041afa0_Product->reserved_11 = 0;
    g_aboutSprite_0041afa0_Product->source_columns_per_row = 9;
    g_aboutSprite_0041afa0_Product->source_width = 0x003a;
    g_aboutSprite_0041afa0_Product->source_height = 0x0026;
    g_aboutSprite_0041afa0_Product->requested_x = -70;
    g_aboutSprite_0041afa0_Product->requested_y = 0;
    g_aboutSprite_0041afa0_Product->
        OtResetSpriteBlitterBitmapInfo_Product_004107b0();
    g_aboutAudioPhase_0041afa0_Product = 0;

    dialog_units = GetDialogBaseUnits();
    unit_height = dialog_units >> 16;
    unit_width = dialog_units & 0xffff;
    OtScaleWindowToDialogCoords_00401370_Product(
        GetParent(dialog), dialog, unit_width, unit_height);
    OtCenterMenuDialogInParent(dialog, 0);
    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 30000, unit_width, unit_height);
    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 0x7532, unit_width, unit_height);
    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 300, unit_width, unit_height);
    OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
        dialog, 0x7536, unit_width, unit_height);

    g_aboutTextIndex_0041afa0_Product = 0;
    OtSetMenuDialogResourceText(
        dialog, 0x7532, g_resourceModule, 0x7533);
    OtSetMenuDialogResourceText(
        dialog, 30000, g_resourceModule, 0x5dc0);
    if (g_cdMediaMode_00439108 != 0 &&
        g_titleThemeEnabled_004390ec != 0) {
        OtPlayAboutWave(dialog, g_titleWavePath_0041c410);
    }
    SetTimer(dialog, 0x7531, 7000, 0);
    SetTimer(dialog, 0x7535, 200, 0);

    state = new AboutDialogState_0041afa0_Product;
    if (state == 0) {
        MessageBoxA(
            GetParent(dialog),
            g_menuDialogAllocationMessage_0040bb30,
            g_aboutDialogAllocationCaption_0041afa0,
            0);
        PostQuitMessage(0);
        return;
    }

    state->close_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2826);
    state->close_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_applicationModule_00405a40_20260603, 0x2827);
    OtResizeControl_RealCpp(
        dialog, 300, state->close_up.width, state->close_up.height);
    SetWindowLongA(dialog, 8, (long)state);
    SetFocus(GetDlgItem(dialog, 300));
    SendMessageA(dialog, 0x0401, 300, 0);
}

static void OtDestroyAboutAnimation(OtDialogHandle dialog)
{
    GlobalUnlock(g_aboutScratchHandle_0041afa0_Product);
    GlobalFree(g_aboutScratchHandle_0041afa0_Product);
    FreeResource(g_aboutSpriteResource_0041afa0_Product);
    if (g_aboutBitmap_0041afa0_Product != 0) {
        OtFreeRawIndexedBitmap_RealCpp(g_aboutBitmap_0041afa0_Product);
        operator delete(g_aboutBitmap_0041afa0_Product);
        g_aboutBitmap_0041afa0_Product = 0;
    }
    if (g_aboutSprite_0041afa0_Product != 0) {
        OtFreeSpriteBlitter_RealCpp(g_aboutSprite_0041afa0_Product);
        operator delete(g_aboutSprite_0041afa0_Product);
        g_aboutSprite_0041afa0_Product = 0;
    }
    KillTimer(dialog, 0x7531);
    KillTimer(dialog, 0x7535);
    if (g_cdMediaMode_00439108 != 0) {
        OtCloseWaveAudioDevice_0040d0a0_RealCpp();
    }
}

static void OtPaintAboutDialog(OtDialogHandle dialog)
{
    OtMenuPaintStruct paint;
    OtDeviceContext dc;
    PositionedBitmapDescriptorState_0040ba40 background;
    PositionedBitmapDescriptorState_0040ba40 foreground;

    g_appBusyCursorActive_Product_004034d0 = 1;
    dc = BeginPaint(dialog, &paint);
    SelectPalette(dc, g_gamePalette, 0);
    RealizePalette(dc);
    background.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_resourceModule, 30000);
    OtBlitMenuPositionedBitmap(&background, dc);
    foreground.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(
        g_resourceModule, 0x7531);
    OtBlitMenuPositionedBitmap(&foreground, dc);
    EndPaint(dialog, &paint);
    g_appBusyCursorActive_Product_004034d0 = 0;
}

static void OtAdvanceAboutAnimation(OtDialogHandle dialog)
{
    OtDeviceContext dc;
    unsigned int* fill;
    int fill_count;
    unsigned int next_frame;

    g_aboutSprite_0041afa0_Product->
        OtExtractSpriteRegionToBuffer_Product_00410840(
            g_aboutBitmap_0041afa0_Product,
            g_aboutScratchBytes_0041afa0_Product);
    fill = (unsigned int*)g_aboutScratchBytes_0041afa0_Product;
    fill_count = 1250;
    while (fill_count > 0) {
        *fill = 0x57575757ul;
        ++fill;
        --fill_count;
    }
    g_aboutSprite_0041afa0_Product->
        OtCompositeSpriteIntoBuffer_Product_00410a30(
            g_aboutSprite_0041afa0_Product,
            g_aboutScratchBytes_0041afa0_Product,
            g_aboutBitmap_0041afa0_Product);
    dc = GetDC(dialog);
    SelectPalette(dc, g_gamePalette, 0);
    RealizePalette(dc);
    g_aboutSprite_0041afa0_Product->
        OtBlitSpriteBuffer_Product_004106e0(
            dc,
            g_aboutBitmap_0041afa0_Product,
            g_aboutScratchBytes_0041afa0_Product);
    ReleaseDC(dialog, dc);

    g_aboutSprite_0041afa0_Product->requested_x += 10;
    if (g_aboutSprite_0041afa0_Product->source_frame < 4) {
        next_frame = g_aboutSprite_0041afa0_Product->source_frame + 1;
        if (next_frame > 3) {
            next_frame = 0;
        }
        g_aboutSprite_0041afa0_Product->source_frame =
            (unsigned short)next_frame;
    }
    if (g_aboutSprite_0041afa0_Product->requested_x > 0x00b4) {
        g_aboutSprite_0041afa0_Product->requested_x = 0x00b4;
        if (OtRandomBelow_RealCpp(10) == 0) {
            g_aboutSprite_0041afa0_Product->source_frame =
                (unsigned short)(8 - OtRandomBelow_RealCpp(3));
        }
    }
}

extern "C" long __stdcall OtAboutDialogProc_0041afa0_Product(
    OtDialogHandle dialog,
    unsigned int message,
    unsigned int wparam,
    long lparam)
{
    switch (message) {
    case 0x0002: {
        AboutDialogState_0041afa0_Product* state =
            (AboutDialogState_0041afa0_Product*)GetWindowLongA(dialog, 8);
        if (state != 0) {
            delete state;
        }
        return 1;
    }

    case 0x000f:
        OtPaintAboutDialog(dialog);
        return 1;

    case 0x0014: {
        OtMenuRect update_rect;
        SelectPalette((OtDeviceContext)wparam, g_gamePalette, 0);
        RealizePalette((OtDeviceContext)wparam);
        if (GetUpdateRect(dialog, &update_rect, 0) != 0) {
            FillRect(
                (OtDeviceContext)wparam,
                &update_rect,
                g_sharedDialogBackgroundBrush_004390c0);
        }
        return 1;
    }

    case 0x002b:
        return OtDrawAboutCloseButton(
            dialog,
            wparam,
            (OtMenuDrawItem*)lparam);

    case 0x0110:
        OtInitializeAboutDialog(dialog);
        return 0;

    case 0x0111:
        if ((wparam & 0xffff) == 300) {
            OtDestroyAboutAnimation(dialog);
            EndDialog(dialog, 1);
        }
        return 1;

    case 0x0113:
        if (wparam == 0x7535) {
            OtAdvanceAboutAnimation(dialog);
        } else {
            ++g_aboutTextIndex_0041afa0_Product;
            if (g_aboutTextIndex_0041afa0_Product > 13) {
                g_aboutTextIndex_0041afa0_Product = 0;
            }
            OtSetMenuDialogResourceText(
                dialog,
                30000,
                g_resourceModule,
                0x5dc0 + g_aboutTextIndex_0041afa0_Product);
        }
        return 1;

    case 0x0136:
        SelectPalette((OtDeviceContext)wparam, g_gamePalette, 0);
        RealizePalette((OtDeviceContext)wparam);
        SetBkMode((OtDeviceContext)wparam, 1);
        SetTextColor((OtDeviceContext)wparam, 0);
        SelectObject(
            (OtDeviceContext)wparam,
            g_optionMenuFont_004390d4_00405320);
        return (long)g_sharedDialogBackgroundBrush_004390c0;

    case 0x0138:
        SelectPalette((OtDeviceContext)wparam, g_gamePalette, 0);
        RealizePalette((OtDeviceContext)wparam);
        SetBkMode((OtDeviceContext)wparam, 1);
        SetTextColor((OtDeviceContext)wparam, 0);
        SelectObject(
            (OtDeviceContext)wparam,
            g_dialogFont_004390d8_00405320);
        return (long)g_sharedDialogBackgroundBrush_004390c0;

    case 0x03b9:
        if (g_cdMediaMode_00439108 == 1) {
            if (wparam == 1) {
                if (g_aboutAudioPhase_0041afa0_Product == 0) {
                    OtCloseWaveAudioDevice_0040d0a0_RealCpp();
                    if (DAT_004390e8 != 0) {
                        OtPlayAboutWave(dialog, g_aboutBlupWavePath_0041afa0);
                    }
                    g_aboutAudioPhase_0041afa0_Product = 1;
                } else {
                    OtCloseWaveAudioDevice_0040d0a0_RealCpp();
                    if (g_titleThemeEnabled_004390ec != 0) {
                        OtPlayAboutWave(dialog, g_titleWavePath_0041c410);
                    }
                }
            } else {
                OtCloseWaveAudioDevice_0040d0a0_RealCpp();
            }
        }
        return 1;

    case 0x0464:
        if (g_cdMediaMode_00439108 != 0) {
            OtCloseWaveAudioDevice_0040d0a0_RealCpp();
        }
        KillTimer(dialog, 0x7531);
        KillTimer(dialog, 0x7535);
        return 1;

    case 0x0466:
        if (g_cdMediaMode_00439108 != 0 &&
            g_titleThemeEnabled_004390ec != 0) {
            OtPlayAboutWave(dialog, g_titleWavePath_0041c410);
        }
        SetTimer(dialog, 0x7531, 7000, 0);
        SetTimer(dialog, 0x7535, 200, 0);
        return 1;
    }

    return 0;
}

#pragma optimize("", on)
