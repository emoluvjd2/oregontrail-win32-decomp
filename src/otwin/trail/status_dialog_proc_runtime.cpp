#include <windows.h>
// Recovered status dialog callback @ 0x0041d040.
//
// The original is a four-argument Win32 dialog procedure.  This recovery
// preserves its palette-aware paint path, owner-drawn close button, owned
// bitmap lifetime, modeless-window registration, and custom status refresh.

#if !defined(_MSC_VER) || !defined(_M_IX86)
#error "This product source must be compiled with 32-bit MSVC."
#endif

extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_gamePalette;
extern "C" void* g_journeyState;
extern "C" void* g_sharedDialogBackgroundBrush_004390c0;
extern "C" void* g_optionMenuFont_004390d4_00405320;
extern "C" void* g_dialogFont_004390d8_00405320;
extern "C" void* g_trailStatusNotifyWindow_004390d0;
extern "C" int g_appBusyCursorActive_Product_004034d0;

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

extern void* __cdecl operator new(unsigned int bytes);
extern void __cdecl operator delete(void* block);

extern "C" void* __fastcall OtInitPositionedBitmap_RealCpp(void* bitmap);
extern "C" void __cdecl OtResizeControl_RealCpp(
    void* dialog,
    int control_id,
    int width,
    int height);
extern "C" int __cdecl OtSelectDialogCursor_0040d530_RealCpp(
    int force_busy_cursor,
    void* window);

#include "status_owned_state.h"
typedef RECT StatusRect;
typedef PAINTSTRUCT StatusPaint;
typedef DRAWITEMSTRUCT StatusDraw;
struct PositionedBitmap_0040b7b0_Semantic { int OtBlitWrappedPositionedBitmap_0040b7b0_Semantic(void*,int,int); };

extern "C" void OtPersistDialogPlacement_00401430_RealCpp(const char*,StatusRect*);
extern "C" void OtInitializeStatusDialog_0041d400(void*);
extern "C" void OtPopulateStatusDialog_0041d650(void*);
extern "C" const char status_callback_placement_section[]="Status Dialog";
#define BLIT(member) reinterpret_cast<PositionedBitmap_0040b7b0_Semantic*>(&owner->member)->OtBlitWrappedPositionedBitmap_0040b7b0_Semantic(draw->hDC,0,0)
#pragma optimize("s",off)
#pragma optimize("t",on)
extern "C" long __stdcall OtStatusDialogProc_0041d040_ProductWip(void* dialog,unsigned int message,unsigned int wparam,long lparam) {
 StatusPaint paint;
 StatusRect window_rect;
 StatusOwnedState* owner;
 StatusDraw* draw;
 void* dc;
 switch(message) {
 case 2: {
  owner=reinterpret_cast<StatusOwnedState*>(GetWindowLongA(dialog,8));
  delete owner;
  GetWindowRect(dialog,&window_rect);
  OtPersistDialogPlacement_00401430_RealCpp(status_callback_placement_section,&window_rect);
  g_trailStatusNotifyWindow_004390d0=0;
  g_appBusyCursorActive_Product_004034d0=0;
  SetCursor(LoadCursorA(0,reinterpret_cast<const char*>(0x7f00)));
  break;
 }
 case 0xf:
  g_appBusyCursorActive_Product_004034d0=1;
  SetCursor(LoadCursorA(0,reinterpret_cast<const char*>(0x7f02)));
  dc=BeginPaint(dialog,&paint);
  SelectPalette(dc,g_gamePalette,0); UnrealizeObject(g_gamePalette); RealizePalette(dc);
  EndPaint(dialog,&paint);
  g_appBusyCursorActive_Product_004034d0=0;
  SetCursor(LoadCursorA(0,reinterpret_cast<const char*>(0x7f00)));
  break;
 case 0x14: {
  StatusRect update_rect;
  dc=reinterpret_cast<void*>(wparam); SelectPalette(dc,g_gamePalette,0); RealizePalette(dc);
  if(GetUpdateRect(dialog,&update_rect,0)!=0) FillRect(dc,&update_rect,g_sharedDialogBackgroundBrush_004390c0);
  break;
 }
 case 0x20:
  return OtSelectDialogCursor_0040d530_RealCpp(g_appBusyCursorActive_Product_004034d0,reinterpret_cast<void*>(wparam));
 case 0x2b: {
  draw=reinterpret_cast<StatusDraw*>(lparam);
  owner=reinterpret_cast<StatusOwnedState*>(GetWindowLongA(dialog,8));
  SelectPalette(draw->hDC,g_gamePalette,0);RealizePalette(draw->hDC);
  switch(draw->itemAction) {
   case 1: if(wparam==300) { BLIT(close_normal); } break;
   case 2:
    if((draw->itemState&1)!=0) { if(wparam==300) { BLIT(close_pressed); } }
    else { if(wparam==300) { BLIT(close_normal); } }
    break;
  }
  break;
 }
 case 0x110:
  g_appBusyCursorActive_Product_004034d0=1;
  SetCursor(LoadCursorA(0,reinterpret_cast<const char*>(0x7f02)));
  g_trailStatusNotifyWindow_004390d0=dialog;
  OtInitializeStatusDialog_0041d400(dialog);OtPopulateStatusDialog_0041d650(dialog);
  return 0;
 case 0x111:
  switch(static_cast<unsigned short>(wparam)) { case 300: DestroyWindow(dialog); break; }
  break;
 case 0x138:
  dc=reinterpret_cast<void*>(wparam);SelectPalette(dc,g_gamePalette,0);RealizePalette(dc);
  SetBkMode(dc,1);SetTextColor(dc,0);SelectObject(dc,g_optionMenuFont_004390d4_00405320);
  {
   int control_id=GetWindowLongA(reinterpret_cast<void*>(lparam),-12);
   if(control_id==0x10cc || control_id==0x10cd || control_id==0x10ce || control_id==0x10ef)
    SelectObject(dc,g_optionMenuFont_004390d4_00405320);
   else SelectObject(dc,g_dialogFont_004390d8_00405320);
  }
  return reinterpret_cast<long>(g_sharedDialogBackgroundBrush_004390c0);
 case 0x47e:OtPopulateStatusDialog_0041d650(dialog);break;
 default:return 0;
 }
 return 1;
}
