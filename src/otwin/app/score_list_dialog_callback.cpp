// List of Legends command handling and profile ownership @ 0x00430350.
#include <windows.h>
#include "../trail/trail_score_list.h"
struct TrailLeaderboardProfileList_0042ff00 { void OtSaveLeaderboardProfile_0042ff00_RealCpp(); };
struct TrailOverlayCaptionState_0042fe90 { int OtFormatTrailOverlayCaption_RealCpp(); };
struct RiverRecordTable_0042fd20 { void OtRemoveRiverRecordAt_0042fd20_RealCpp(int); };
extern "C" void OtDrawScoreListItem_00430000(HWND,DRAWITEMSTRUCT*);
extern "C" void OtInitializeScoreListDialog_00430180(HWND);
#pragma optimize("s",off)
#pragma optimize("t",on)
extern "C" long __stdcall OtTrailGameShutdownDialogProc_00430350_Product(
    HWND dialog,
    unsigned int message,
    unsigned int wparam,
    long lparam)
{
    TrailGameScoreList_0042fc30* scores;
    unsigned int selected_items[10];
    int index;
    int selected_count;
    HWND listbox;

    switch (message) {
    case 0x002b:
        OtDrawScoreListItem_00430000(dialog, (DRAWITEMSTRUCT*)lparam);
        return 1;
    case 0x0110:
        OtInitializeScoreListDialog_00430180(dialog);
        return 1;
    case 0x0111:
        scores = (TrailGameScoreList_0042fc30*)GetWindowLongA(dialog, 8);
        switch (wparam & 0xffff) {
        case 300:
            reinterpret_cast<TrailLeaderboardProfileList_0042ff00*>(scores)->
                OtSaveLeaderboardProfile_0042ff00_RealCpp();
            delete scores;
            SendMessageA(GetParent(dialog), 0x047f, 0, 0);
            EndDialog(dialog, 1);
            return 1;

        case 0x12d:
            delete scores;
            EndDialog(dialog, 1);
            return 1;

        case 0x12f:
            reinterpret_cast<TrailOverlayCaptionState_0042fe90*>(scores)->
                OtFormatTrailOverlayCaption_RealCpp();
            listbox = GetDlgItem(dialog, 500);
            SendMessageA(listbox, 0x0184, 0, 0);
            index = 0;
            if (scores->count > 0) {
                do {
                    SendMessageA(listbox, 0x0180, 0, 0);
                    ++index;
                } while (index < scores->count);
            }
            return 1;

        case 0x130:
            listbox = GetDlgItem(dialog, 500);
            selected_count = (int)SendMessageA(
                listbox,
                0x0191,
                10,
                (long)selected_items);
            index = 0;
            while (index < selected_count) {
                SendMessageA(listbox, 0x0182, selected_items[index], 0);
                reinterpret_cast<RiverRecordTable_0042fd20*>(scores)->
                    OtRemoveRiverRecordAt_0042fd20_RealCpp(
                        selected_items[index]);
                ++index;
                for (int tail = index; tail < selected_count; ++tail) {
                    --selected_items[tail];
                }
            }
            return 1;
        }

        return 1;
    case 0x0136:
        return (long)GetStockObject(0);
    default:
        return 0;
    }
}

#pragma optimize("", on)
