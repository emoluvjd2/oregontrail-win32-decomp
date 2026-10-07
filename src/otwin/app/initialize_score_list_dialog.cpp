// List of Legends dialog initialization @ 0x00430180.
#include <windows.h>
#include "../trail/trail_score_list.h"

extern "C" HINSTANCE g_applicationModule_00405a40_20260603;
extern "C" const char g_trailGameAllocationMessage_00430180[];
extern "C" const char g_emptyDialogText_00430180[];
extern "C" const char g_trailGameListBoxClass_00430350_Product[];

#pragma optimize("s", off)
#pragma optimize("t", on)

extern "C" void OtInitializeScoreListDialog_00430180(HWND dialog)
{
    RECT dialog_rect;
    TEXTMETRICA metrics;
    TrailGameScoreList_0042fc30* scores;
    HDC dc;
    int index;
    HWND listbox;
    RECT parent_rect;
    POINT center;

    GetWindowRect(dialog, &dialog_rect);
    GetClientRect(GetParent(dialog), &parent_rect);
    center.x = parent_rect.left + (parent_rect.right - parent_rect.left) / 2;
    center.y = parent_rect.top + (parent_rect.bottom - parent_rect.top) / 2;
    ClientToScreen(GetParent(dialog), &center);
    SetWindowPos(dialog, 0,
        center.x + (dialog_rect.left - dialog_rect.right) / 2,
        center.y + (dialog_rect.top - dialog_rect.bottom) / 2,
        dialog_rect.right - dialog_rect.left,
        dialog_rect.bottom - dialog_rect.top, 4);

    scores = new TrailGameScoreList_0042fc30;
    if (scores != 0) {
        scores->OtLoadScoreList_0042fda0_RealCpp();
    } else {
        MessageBoxA(GetParent(dialog), g_trailGameAllocationMessage_00430180,
            g_emptyDialogText_00430180, 0);
    }
    SetWindowLongA(dialog, 8, reinterpret_cast<long>(scores));

    dc = GetDC(dialog);
    GetTextMetricsA(dc, &metrics);
    ReleaseDC(dialog, dc);
    int list_width = ((-10 - GetSystemMetrics(7)) * 2 - dialog_rect.left)
        + dialog_rect.right;
    int list_height = metrics.tmHeight * 10;
    listbox = CreateWindowExA(0, g_trailGameListBoxClass_00430350_Product,
        g_emptyDialogText_00430180, 0x50a00018ul, 10, 10,
        list_width, list_height, dialog, reinterpret_cast<HMENU>(0x01f4),
        g_applicationModule_00405a40_20260603, 0);

    index = 0;
    if (scores->count > 0) {
        do {
            SendMessageA(listbox, 0x0180, 0, 0);
            ++index;
        } while (index < scores->count);
    }
}

#pragma optimize("", on)
