#ifndef OTWIN_DROP_SUPPLIES_OWNED_STATE_H
#define OTWIN_DROP_SUPPLIES_OWNED_STATE_H
#include "../graphics/positioned_bitmap_descriptor_state.h"
#include <stddef.h>
struct DropOwnedState {
    PositionedBitmapDescriptorState_0040ba40 okay_up, okay_down, cancel_up, cancel_down;
    int selection;
    void* result;
};
typedef char DropOwnerSizeCheck[sizeof(DropOwnedState) == 0xa8 ? 1 : -1];
typedef char DropResultOffsetCheck[offsetof(DropOwnedState, result) == 0xa4 ? 1 : -1];
#endif
