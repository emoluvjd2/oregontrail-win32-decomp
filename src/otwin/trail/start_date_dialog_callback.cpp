// Product-reachable semantic DLGPROC for OtStartDateDialogProc @ 0x00423da0.

#include "../app/dialog_callback_runtime.h"

extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(
    OtDialogHandle_Product window,
    int index);
extern "C" __declspec(dllimport) long __stdcall SetWindowLongA(
    OtDialogHandle_Product window,
    int index,
    long value);
extern "C" __declspec(dllimport) OtDialogHandle_Product __stdcall GetParent(
    OtDialogHandle_Product window);
extern "C" __declspec(dllimport) unsigned int __stdcall GetDialogBaseUnits();
extern "C" __declspec(dllimport) int __stdcall SetWindowPos(
    OtDialogHandle_Product window,
    OtDialogHandle_Product insert_after,
    int x,
    int y,
    int width,
    int height,
    unsigned int flags);
extern "C" __declspec(dllimport) long __stdcall SendMessageA(
    OtDialogHandle_Product window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    OtDialogHandle_Product window,
    const char* text,
    const char* caption,
    unsigned int type);
extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int exit_code);
extern "C" __declspec(dllimport) int __stdcall HideCaret(
    OtDialogHandle_Product window);
extern "C" __declspec(dllimport) int __stdcall PostMessageA(
    OtDialogHandle_Product window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) int __stdcall DestroyWindow(
    OtDialogHandle_Product window);

extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_resourceModule;
extern "C" int g_cdMediaMode_00439108;
extern "C" int DAT_004390e8;
extern "C" void* g_journeyState;

extern "C" void __cdecl
OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
    OtDialogHandle_Product dialog,
    int control_id,
    int dialog_unit_width,
    int dialog_unit_height);
extern "C" void __cdecl OtResizeControl_RealCpp(
    OtDialogHandle_Product dialog,
    int control_id,
    int width,
    int height);
extern "C" int __cdecl OtSelectDialogCursor_0040d530_RealCpp(
    int busy,
    OtDialogHandle_Product window);
extern "C" void __cdecl OtOpenWaveAudioFile_0000d110_RealCpp(
    OtDialogHandle_Product owner,
    const char* path);
extern "C" void __cdecl OtPlayWaveAudioDirectImport_0040d3e0_RealCpp();
extern "C" void __cdecl OtCloseWaveAudioDevice_0040d0a0_RealCpp();
extern "C" void __cdecl OtStopWaveAudioDirectImport_0040d480_RealCpp();

#pragma pack(push, 1)
struct StartDateDialogState_00423da0_Product {
    PositionedBitmapDescriptorState_0040ba40 play_audio_up;
    PositionedBitmapDescriptorState_0040ba40 play_audio_down;
    PositionedBitmapDescriptorState_0040ba40 stop_audio_up;
    PositionedBitmapDescriptorState_0040ba40 stop_audio_down;
    struct DateChoicePair {
        PositionedBitmapDescriptorState_0040ba40 up;
        PositionedBitmapDescriptorState_0040ba40 down;
    } date_choice[6];
    PositionedBitmapDescriptorState_0040ba40 back_up;
    PositionedBitmapDescriptorState_0040ba40 back_down;
    PositionedBitmapDescriptorState_0040ba40 selected_date_marker;

    StartDateDialogState_00423da0_Product();
};

struct TrailDailyStatusState_00419660_Product {
    void OtPrepareDailyStatus_00419660_Product(short month);
};
#pragma pack(pop)

typedef char OtStartDateStateSizeMustBe2f8[
    sizeof(StartDateDialogState_00423da0_Product) == 0x2f8 ? 1 : -1];

static const char g_startDateAllocationText_00423da0[] =
    "Unable to allocate dialog information.";
static const char g_startDateAllocationCaption_00423da0[] =
    "StartDateDlgProc";
static const char g_startDateLeavingWave_00423da0[] = "leaving.wav";

extern "C" void OtInitStartDateDialog_00424730(void* dialog);

static void OtLeaveStartDateDialog_00423da0(
    OtDialogHandle_Product dialog,
    unsigned int next_message)
{
    PostMessageA(GetParent(dialog), next_message, 0, 0);
    DestroyWindow(dialog);
    g_activeScreenDialogWindow_00404dd0 = 0;
}

#pragma optimize("s", off)
#pragma optimize("t", on)

extern "C" int __stdcall OtStartDateDialogProc_00023da0_Wip(
    OtDialogHandle_Product dialog,
    unsigned int message,
    unsigned int wparam,
    long lparam)
{
    StartDateDialogState_00423da0_Product* state =
        reinterpret_cast<StartDateDialogState_00423da0_Product*>(
            GetWindowLongA(dialog, 8));

    switch (message) {
    case 0x0002:
        if (state != 0) {
            delete state;
            SetWindowLongA(dialog, 8, 0);
        }
        if (g_cdMediaMode_00439108 != 0) {
            OtCloseWaveAudioDevice_0040d0a0_RealCpp();
        }
        return 0;

    case 0x000f:
        OtSetDialogBusyCursor_Product();
        OtPaintDialogBackground_Product(
            dialog,
            state != 0 ? &state->selected_date_marker : 0,
            g_sharedDialogBackgroundBrush_004390c0);
        OtRestoreDialogArrowCursor_Product();
        return 1;

    case 0x0014:
        return 1;

    case 0x0020:
        return OtSelectDialogCursor_0040d530_RealCpp(
            g_appBusyCursorActive_Product_004034d0,
            reinterpret_cast<OtDialogHandle_Product>(wparam));

    case 0x002b:
        if (state == 0) {
            return 0;
        }
        if ((wparam & 0xffff) >= 0x0582 &&
            (wparam & 0xffff) <= 0x0587) {
            int index = static_cast<int>((wparam & 0xffff) - 0x0582);
            return OtDrawOwnedBitmapButton_Product(
                reinterpret_cast<OtDialogDrawItem_Product*>(lparam),
                &state->date_choice[index].up,
                &state->date_choice[index].down);
        }
        switch (wparam & 0xffff) {
        case 0x012d:
            return OtDrawOwnedBitmapButton_Product(
                reinterpret_cast<OtDialogDrawItem_Product*>(lparam),
                &state->back_up,
                &state->back_down);
        case 0x0132:
            return OtDrawOwnedBitmapButton_Product(
                reinterpret_cast<OtDialogDrawItem_Product*>(lparam),
                &state->play_audio_up,
                &state->play_audio_down);
        case 0x0133:
            return OtDrawOwnedBitmapButton_Product(
                reinterpret_cast<OtDialogDrawItem_Product*>(lparam),
                &state->stop_audio_up,
                &state->stop_audio_down);
        }
        return 1;

    case 0x0110:
        OtSetDialogBusyCursor_Product();
        g_activeScreenDialogWindow_00404dd0 = dialog;
        OtInitStartDateDialog_00424730(dialog);
        HideCaret(0);
        return 1;

    case 0x0111:
        if ((wparam & 0xffff) == 0x012d) {
            OtLeaveStartDateDialog_00423da0(dialog, 0x046d);
            return 1;
        }
        if ((wparam & 0xffff) == 0x0132) {
            if (DAT_004390e8 != 0) {
                OtOpenWaveAudioFile_0000d110_RealCpp(
                    dialog,
                    g_startDateLeavingWave_00423da0);
                OtPlayWaveAudioDirectImport_0040d3e0_RealCpp();
            }
            return 1;
        }
        if ((wparam & 0xffff) == 0x0133) {
            if (DAT_004390e8 != 0) {
                OtCloseWaveAudioDevice_0040d0a0_RealCpp();
            }
            return 1;
        }
        if ((wparam & 0xffff) >= 0x0582 &&
            (wparam & 0xffff) <= 0x0587) {
            reinterpret_cast<TrailDailyStatusState_00419660_Product*>(
                g_journeyState)->OtPrepareDailyStatus_00419660_Product(
                    static_cast<short>((wparam & 0xffff) - 0x0580));
            OtLeaveStartDateDialog_00423da0(dialog, 0x0471);
            return 1;
        }
        return 1;

    case 0x0138:
        return OtPrepareDialogControlColor_Product(
            reinterpret_cast<OtDialogDeviceContext_Product>(wparam),
            g_optionMenuFont_004390d4_00405320,
            0);

    case 0x0465:
        if (g_cdMediaMode_00439108 != 0 && DAT_004390e8 != 0) {
            OtStopWaveAudioDirectImport_0040d480_RealCpp();
        }
        return 1;

    case 0x0469:
        if (g_cdMediaMode_00439108 != 0) {
            OtCloseWaveAudioDevice_0040d0a0_RealCpp();
        }
        return 1;
    }

    return 0;
}

#pragma optimize("", on)
