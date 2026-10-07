#ifndef OTWIN_TRAIL_STATUS_OWNED_STATE_H
#define OTWIN_TRAIL_STATUS_OWNED_STATE_H

#include "../graphics/positioned_bitmap_descriptor_state.h"

// Stored in the status dialog's extra window bytes. Native member destruction
// releases both close-button bitmaps, including exceptional cleanup paths.
struct StatusOwnedState {
    PositionedBitmapDescriptorState_0040ba40 close_normal, close_pressed;

    StatusOwnedState() : close_normal(), close_pressed() {}
    ~StatusOwnedState() {}
};

typedef char StatusOwnedStateSize[(sizeof(StatusOwnedState) == 0x50) ? 1 : -1];

#endif
