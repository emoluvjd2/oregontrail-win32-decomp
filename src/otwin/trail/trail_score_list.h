#ifndef OTWIN_TRAIL_SCORE_LIST_H
#define OTWIN_TRAIL_SCORE_LIST_H

// The profile stores ten fixed-width name/score pairs following its count.
#pragma pack(push, 1)
struct TrailLeaderboardEntry_0042fc30 {
    char name[20];
    char score[11];
};

struct TrailGameScoreList_0042fc30 {
    int count;
    TrailLeaderboardEntry_0042fc30 entries[10];

    TrailGameScoreList_0042fc30();
    int OtLoadScoreList_0042fda0_RealCpp();
};
#pragma pack(pop)

typedef char TrailScoreListSizeCheck[
    sizeof(TrailGameScoreList_0042fc30) == 0x13a ? 1 : -1];

#endif
