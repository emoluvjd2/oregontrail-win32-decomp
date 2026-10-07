// Owner-drawn List of Legends names and scores @ 0x00430000.
#include <windows.h>
#include <string.h>
#include "../trail/trail_score_list.h"
#pragma intrinsic(strlen)
#pragma optimize("s",off)
#pragma optimize("t",on)
extern "C" void OtDrawScoreListItem_00430000(
    HWND dialog,
    DRAWITEMSTRUCT* item)
{
    TrailGameScoreList_0042fc30* scores;
    unsigned long old_background;
    unsigned long old_text;
    unsigned long fill_color;
    HBRUSH brush;
    RECT* item_rect;

    scores = (TrailGameScoreList_0042fc30*)GetWindowLongA(dialog, 8);
    if (scores == 0) {
        return;
    }

    old_text = GetTextColor(item->hDC);
    fill_color = GetBkColor(item->hDC);
    old_background = fill_color;
    if ((item->itemState & 1) != 0) {
        SetTextColor(item->hDC, GetSysColor(14));
        fill_color = GetSysColor(13);
        SetBkColor(item->hDC, fill_color);
    }

    brush = CreateSolidBrush(fill_color);
    item_rect = &item->rcItem;
    FillRect(item->hDC, item_rect, brush);
    DeleteObject(brush);

    if (strlen(scores->entries[item->itemID].name) < 20) {
        DrawTextA(item->hDC, scores->entries[item->itemID].name, -1, item_rect, 0);
    } else {
        DrawTextA(item->hDC, scores->entries[item->itemID].name, 20, item_rect, 0);
    }
    if (strlen(scores->entries[item->itemID].score) < 10) {
        DrawTextA(item->hDC, scores->entries[item->itemID].score, -1, item_rect, 2);
    } else {
        DrawTextA(item->hDC, scores->entries[item->itemID].score, 10, item_rect, 2);
    }

    SetTextColor(item->hDC, old_text);
    SetBkColor(item->hDC, old_background);
    EnableWindow(
        GetDlgItem(dialog, 0x130),
        SendMessageA(item->hwndItem, 0x0190, 0, 0) > 0);
}


#pragma optimize("", on)
