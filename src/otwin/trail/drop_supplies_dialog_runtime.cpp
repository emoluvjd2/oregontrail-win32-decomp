#include "drop_supplies_owned_state.h"
extern "C" void OtInitializeDropSuppliesDialog_0041efb0(void* dialog, void* result);
// Product semantic WIP for the drop-supplies dialog callback @ 0x0041ead0.
//
// Ghidra originally treated this callback as a raw label.  The recovered
// function is a four-argument Win32 dialog procedure.  Its two large helpers
// populate the inventory controls and validate/mutate the selected supply.

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This product source must be compiled with 32-bit MSVC."
#endif

#include <stdlib.h>
#include <string.h>

#pragma intrinsic(strlen, strcat)

extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_gamePalette;
extern "C" void* g_journeyState;
extern "C" void* g_sharedDialogBackgroundBrush_004390c0;
extern "C" void* g_dialogFont_004390d8_00405320;
extern "C" int g_appBusyCursorActive_Product_004034d0;

extern "C" __declspec(dllimport) void* __stdcall BeginPaint(
    void* window,
    void* paint);
extern "C" __declspec(dllimport) int __stdcall EndPaint(
    void* window,
    const void* paint);
extern "C" __declspec(dllimport) void* __stdcall SelectPalette(
    void* dc,
    void* palette,
    int force_background);
extern "C" __declspec(dllimport) int __stdcall UnrealizeObject(void* object);
extern "C" __declspec(dllimport) unsigned int __stdcall RealizePalette(
    void* dc);
extern "C" __declspec(dllimport) void* __stdcall LoadCursorA(
    void* instance,
    const void* cursor_name);
extern "C" __declspec(dllimport) void* __stdcall SetCursor(void* cursor);
extern "C" __declspec(dllimport) int __stdcall GetUpdateRect(
    void* window,
    void* rect,
    int erase);
extern "C" __declspec(dllimport) int __stdcall FillRect(
    void* dc,
    const void* rect,
    void* brush);
extern "C" __declspec(dllimport) int __stdcall GetClientRect(
    void* window,
    void* rect);
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(
    void* window,
    void* rect);
extern "C" __declspec(dllimport) void* __stdcall GetParent(void* window);
extern "C" __declspec(dllimport) int __stdcall ClientToScreen(
    void* window,
    void* point);
extern "C" __declspec(dllimport) int __stdcall SetWindowPos(
    void* window,
    void* insert_after,
    int x,
    int y,
    int width,
    int height,
    unsigned int flags);
extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(
    void* window,
    int index);
extern "C" __declspec(dllimport) long __stdcall SetWindowLongA(
    void* window,
    int index,
    long value);
extern "C" __declspec(dllimport) void* __stdcall GetDlgItem(
    void* dialog,
    int control_id);
extern "C" __declspec(dllimport) int __stdcall GetWindowTextA(
    void* window,
    char* text,
    int text_count);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(
    void* window,
    const char* text);
extern "C" __declspec(dllimport) int __stdcall LoadStringA(
    void* instance,
    unsigned int resource_id,
    char* text,
    int text_count);
extern "C" __declspec(dllimport) long __stdcall SendMessageA(
    void* window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) int __stdcall PostMessageA(
    void* window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) void* __stdcall SetFocus(void* window);
extern "C" __declspec(dllimport) int __stdcall EndDialog(
    void* dialog,
    int result);
extern "C" __declspec(dllimport) int __stdcall MessageBeep(
    unsigned int type);
extern "C" __declspec(dllimport) void* __stdcall SelectObject(
    void* dc,
    void* object);
extern "C" __declspec(dllimport) int __stdcall SetBkMode(
    void* dc,
    int mode);
extern "C" __declspec(dllimport) unsigned long __stdcall SetTextColor(
    void* dc,
    unsigned long color);
extern "C" __declspec(dllimport) int __stdcall DrawTextA(
    void* dc,
    const char* text,
    int text_length,
    void* rect,
    unsigned int format);

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

extern "C" int __cdecl OtTalkDialogResponsePaint_0041f8f0_RealCpp(
    int response_id,
    void* parent_window);

#pragma pack(push, 1)
struct DropSuppliesRect_0041ead0 {
    int left;
    int top;
    int right;
    int bottom;
};

struct DropSuppliesPoint_0041ead0 {
    int x;
    int y;
};

struct DropSuppliesPaint_0041ead0 {
    char data[0x40];
};

struct DropSuppliesDrawItem_0041ead0 {
    unsigned int control_type;
    unsigned int control_id;
    unsigned int item_id;
    unsigned int item_action;
    unsigned int item_state;
    void* item_window;
    void* dc;
    DropSuppliesRect_0041ead0 item_rect;
    unsigned long item_data;
};

struct DropSuppliesDialogResult_0041ead0 {
    short selected_item;
    short drop_amount;
};

struct DropSuppliesJourneyState_0041ead0 {
    char reserved_000[0x5a];
    unsigned short broken_supply_flags;
    char reserved_05c[0x3e];
    short clothing;
    short ammunition;
    short wagon_wheels;
    short wagon_axles;
    short wagon_tongues;
    short food_pounds;
    short pending_food_pounds;
};
#pragma pack(pop)

static const char kDropSupplyWeightPrefix_0041ead0[] = " ";
static const char kDropSupplyWeightSuffix_0041ead0[] = " lbs. each.";

#pragma code_seg(".otsem")
#pragma optimize("s", off)
#pragma optimize("t", on)

static void OtSetDropSuppliesBusyCursor_0041ead0(int busy)
{
    g_appBusyCursorActive_Product_004034d0 = busy;
    SetCursor(LoadCursorA(
        0,
        (const void*)(busy != 0 ? 0x7f02 : 0x7f00)));
}

static void OtCenterDropSuppliesDialog_0041ead0(void* dialog)
{
    DropSuppliesRect_0041ead0 dialog_rect;
    DropSuppliesRect_0041ead0 parent_rect;
    DropSuppliesPoint_0041ead0 center;
    void* parent = GetParent(dialog);

    GetWindowRect(dialog, &dialog_rect);
    GetClientRect(parent, &parent_rect);
    center.x = parent_rect.left +
        (parent_rect.right - parent_rect.left) / 2;
    center.y = parent_rect.top +
        (parent_rect.bottom - parent_rect.top) / 2;
    ClientToScreen(parent, &center);

    SetWindowPos(
        dialog,
        0,
        center.x + (dialog_rect.left - dialog_rect.right) / 2,
        center.y + (dialog_rect.top - dialog_rect.bottom) / 2,
        dialog_rect.right - dialog_rect.left,
        dialog_rect.bottom - dialog_rect.top,
        4);
}

static void OtPopulateDropSupplyRow_0041ead0(
    void* dialog,
    int row,
    unsigned int label_resource,
    int pounds_each,
    int available)
{
    char text[100];
    char number[16];

    text[0] = '\0';
    LoadStringA(g_applicationModule_00405a40_20260603, label_resource, text, sizeof(text));
    if (pounds_each > 0) {
        strcat(text, kDropSupplyWeightPrefix_0041ead0);
        _itoa(pounds_each, number, 10);
        strcat(text, number);
        strcat(text, kDropSupplyWeightSuffix_0041ead0);
    }
    SetWindowTextA(GetDlgItem(dialog, 0x11fd + row), text);

    _itoa(available, number, 10);
    SetWindowTextA(GetDlgItem(dialog, 0x1204 + row), number);
}

static int OtFindSelectedDropSupply_0041ead0(void* dialog)
{
    int selected_item = 0;

    while (selected_item < 6) {
        if (SendMessageA(
                GetDlgItem(dialog, selected_item + 0x11fd),
                0x00f0,
                0,
                0) != 0) {
            return selected_item;
        }
        ++selected_item;
    }
    return -1;
}

static int OtRemoveDropSupplyPart_0041ead0(
    void* dialog,
    short* count,
    int quantity,
    unsigned short broken_flag,
    int response_id)
{
    short remaining;

    if (*count < quantity) {
        OtTalkDialogResponsePaint_0041f8f0_RealCpp(response_id, dialog);
        return 0;
    }

    remaining = (short)(*count - (short)quantity);
    if ((g_journeyState != 0) &&
        ((((DropSuppliesJourneyState_0041ead0*)g_journeyState)->
              broken_supply_flags & broken_flag) != 0) &&
        remaining > 0) {
        ((DropSuppliesJourneyState_0041ead0*)g_journeyState)->
            broken_supply_flags ^= broken_flag;
        --remaining;
    }
    *count = remaining;
    return 1;
}

static int OtCommitDropSuppliesSelection_0041f9c0_ProductWip(
    void* dialog,
    DropSuppliesDialogResult_0041ead0* result)
{
    DropSuppliesJourneyState_0041ead0* journey =
        (DropSuppliesJourneyState_0041ead0*)g_journeyState;
    char quantity_text[8];
    int selected_item;
    int quantity;
    int available;
    short pending;

    if (result == 0 || journey == 0) {
        return 0;
    }

    quantity_text[0] = '\0';
    GetWindowTextA(
        GetDlgItem(dialog, 0x11f9),
        quantity_text,
        5);
    quantity = atoi(quantity_text);
    selected_item = OtFindSelectedDropSupply_0041ead0(dialog);

    if (quantity <= 0 || selected_item < 0) {
        result->selected_item = -1;
        result->drop_amount = 0;
        MessageBeep(0);
        SetFocus(GetDlgItem(dialog, 0x11f9));
        return 0;
    }

    switch (selected_item) {
    case 0:
        if (journey->clothing < quantity) {
            OtTalkDialogResponsePaint_0041f8f0_RealCpp(1, dialog);
            return 0;
        }
        journey->clothing = (short)(journey->clothing - (short)quantity);
        break;

    case 1:
        available = (journey->ammunition + 19) / 20;
        if (available < quantity) {
            OtTalkDialogResponsePaint_0041f8f0_RealCpp(2, dialog);
            return 0;
        }
        if (available == quantity) {
            journey->ammunition = 0;
        } else {
            journey->ammunition =
                (short)(journey->ammunition - (short)(quantity * 20));
        }
        break;

    case 2:
        if (!OtRemoveDropSupplyPart_0041ead0(
                dialog,
                &journey->wagon_wheels,
                quantity,
                2,
                3)) {
            return 0;
        }
        break;

    case 3:
        if (!OtRemoveDropSupplyPart_0041ead0(
                dialog,
                &journey->wagon_axles,
                quantity,
                4,
                4)) {
            return 0;
        }
        break;

    case 4:
        if (!OtRemoveDropSupplyPart_0041ead0(
                dialog,
                &journey->wagon_tongues,
                quantity,
                8,
                5)) {
            return 0;
        }
        break;

    case 5:
        if ((short)(journey->food_pounds + journey->pending_food_pounds) <
            quantity) {
            OtTalkDialogResponsePaint_0041f8f0_RealCpp(6, dialog);
            return 0;
        }

        pending = journey->pending_food_pounds;
        if (pending > 0) {
            if (quantity < pending) {
                pending = (short)(pending - (short)quantity);
                if ((int)journey->food_pounds + pending > 2000) {
                    journey->pending_food_pounds =
                        (short)(2000 - journey->food_pounds);
                } else {
                    journey->pending_food_pounds = pending;
                }
            } else {
                quantity -= pending;
                if (journey->food_pounds > 2000) {
                    journey->pending_food_pounds =
                        (short)(2000 - journey->food_pounds);
                } else {
                    journey->pending_food_pounds = 0;
                }
                journey->food_pounds =
                    (short)(journey->food_pounds - (short)quantity);
            }
        } else {
            journey->food_pounds =
                (short)(journey->food_pounds - (short)quantity);
        }
        break;
    }

    result->selected_item = (short)(selected_item + 1);
    result->drop_amount = (short)quantity;
    return 1;
}

struct PositionedBitmap_0040b7b0_Semantic {
    int OtBlitWrappedPositionedBitmap_0040b7b0_Semantic(void* dc, int x, int y);
};

static long OtDrawDropSuppliesControl_0041ead0(
    void* dialog,
    DropSuppliesDrawItem_0041ead0* draw_item)
{
    char text[100];
    if (draw_item == 0) return 1;
    SelectPalette(draw_item->dc, g_gamePalette, 0);
    RealizePalette(draw_item->dc);
    if (draw_item->control_id == 0x12c || draw_item->control_id == 0x12d) {
        DropOwnedState* state = reinterpret_cast<DropOwnedState*>(GetWindowLongA(dialog, 8));
        if (state == 0) return 1;
        PositionedBitmapDescriptorState_0040ba40* bitmap;
        if (draw_item->control_id == 0x12c)
            bitmap = (draw_item->item_state & 1) ? &state->okay_down : &state->okay_up;
        else
            bitmap = (draw_item->item_state & 1) ? &state->cancel_down : &state->cancel_up;
        reinterpret_cast<PositionedBitmap_0040b7b0_Semantic*>(bitmap)->
            OtBlitWrappedPositionedBitmap_0040b7b0_Semantic(draw_item->dc, 0, 0);
        return 1;
    }
    FillRect(
        draw_item->dc,
        &draw_item->item_rect,
        g_sharedDialogBackgroundBrush_004390c0);
    SelectObject(draw_item->dc, g_dialogFont_004390d8_00405320);
    SetBkMode(draw_item->dc, 1);
    SetTextColor(draw_item->dc, 0);
    text[0] = '\0';
    GetWindowTextA(draw_item->item_window, text, sizeof(text));
    DrawTextA(
        draw_item->dc,
        text,
        -1,
        &draw_item->item_rect,
        0x25);
    return 1;
}

extern "C" long __stdcall OtDropSuppliesDialogProc_0041ead0_ProductWip(
    void* dialog,
    unsigned int message,
    unsigned int wparam,
    long lparam)
{
    switch (message) {
    case 0x0002:
        delete reinterpret_cast<DropOwnedState*>(GetWindowLongA(dialog, 8));
        SetWindowLongA(dialog, 8, 0);
        OtSetDropSuppliesBusyCursor_0041ead0(0);
        return 1;

    case 0x000f: {
        DropSuppliesPaint_0041ead0 paint;
        void* dc;

        OtSetDropSuppliesBusyCursor_0041ead0(1);
        dc = BeginPaint(dialog, &paint);
        SelectPalette(dc, g_gamePalette, 0);
        UnrealizeObject(g_gamePalette);
        RealizePalette(dc);
        EndPaint(dialog, &paint);
        OtSetDropSuppliesBusyCursor_0041ead0(0);
        return 1;
    }

    case 0x0014: {
        DropSuppliesRect_0041ead0 rect;
        void* dc = (void*)wparam;

        SelectPalette(dc, g_gamePalette, 0);
        RealizePalette(dc);
        if (GetUpdateRect(dialog, &rect, 0) != 0) {
            FillRect(dc, &rect, g_sharedDialogBackgroundBrush_004390c0);
        }
        return 1;
    }

    case 0x0020:
        SetCursor(LoadCursorA(
            0,
            (const void*)(
                g_appBusyCursorActive_Product_004034d0 != 0
                    ? 0x7f02
                    : 0x7f00)));
        return 1;

    case 0x002b:
        return OtDrawDropSuppliesControl_0041ead0(
            dialog,
            (DropSuppliesDrawItem_0041ead0*)lparam);

    case 0x0110:
        OtSetDropSuppliesBusyCursor_0041ead0(1);
        OtInitializeDropSuppliesDialog_0041efb0(
            dialog,
            (DropSuppliesDialogResult_0041ead0*)lparam);
        OtSetDropSuppliesBusyCursor_0041ead0(0);
        return 0;

    case 0x0111: {
        unsigned int control_id = wparam & 0xffff;
        DropOwnedState* owner = reinterpret_cast<DropOwnedState*>(GetWindowLongA(dialog, 8));
        DropSuppliesDialogResult_0041ead0* result = owner != 0
            ? static_cast<DropSuppliesDialogResult_0041ead0*>(owner->result) : 0;

        if (control_id == 300) {
            if (OtCommitDropSuppliesSelection_0041f9c0_ProductWip(
                    dialog,
                    result) != 0) {
                EndDialog(dialog, 1);
            }
            return 1;
        }
        if (control_id == 0x12d) {
            if (result != 0) {
                result->selected_item = -1;
                result->drop_amount = 0;
            }
            EndDialog(dialog, 1);
            return 1;
        }
        if (control_id >= 0x11fd && control_id <= 0x1203) {
            SetFocus(GetDlgItem(dialog, 0x11f9));
            return 1;
        }
        return 0;
    }

    case 0x0133:
    case 0x0135:
    case 0x0136:
    case 0x0138: {
        void* dc = (void*)wparam;
        SelectPalette(dc, g_gamePalette, 0);
        RealizePalette(dc);
        SetBkMode(dc, 1);
        SetTextColor(dc, 0);
        SelectObject(dc, g_dialogFont_004390d8_00405320);
        return (long)g_sharedDialogBackgroundBrush_004390c0;
    }
    }

    return 0;
}

#pragma optimize("", on)
#pragma code_seg()
