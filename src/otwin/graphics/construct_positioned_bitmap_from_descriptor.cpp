// Native constructor at 0x0040b730, used by composite-map allocation.
#include "resource_positioned_bitmap.h"

#pragma optimize("s", off)
#pragma optimize("t", on)
PositionedBitmap_0040b720::PositionedBitmap_0040b720(
    void* module, void* descriptor_id)
{
    bitmap_info_handle = 0;
    indexed_pixels_handle = 0;
    indexed_pixels = 0;
    bitmap_info = 0;
    OtLoadPositionedBitmapDescriptorDependency_RealCpp(module, descriptor_id);
}
#pragma optimize("", on)
