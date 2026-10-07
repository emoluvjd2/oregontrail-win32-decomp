#ifndef OTWIN_RESOURCE_POSITIONED_BITMAP_H
#define OTWIN_RESOURCE_POSITIONED_BITMAP_H
#include "positioned_bitmap_descriptor_state.h"
// Layout view for the resource-taking constructor at 0x0040b730.
// Kept separate from the default-constructed dialog bitmap view.
#pragma pack(push, 1)
struct PositionedBitmap_0040b720 {
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

    PositionedBitmap_0040b720(void* module, void* descriptor_id);
    int OtLoadPositionedBitmapDescriptorDependency_RealCpp(void* module, void* descriptor_id);
};
#pragma pack(pop)
typedef char ResourcePositionedBitmap_size_check[
 sizeof(PositionedBitmap_0040b720)==sizeof(PositionedBitmapDescriptorState_0040ba40)?1:-1];
#endif
