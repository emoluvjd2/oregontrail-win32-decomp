// Status dialog placement, scaling and owned close-button initialization @ 0x0041d400.

#include "../app/dialog_callback_runtime.h"

extern "C" __declspec(dllimport) long __stdcall GetWindowLongA(
    OtDialogHandle_Product window,
    int index);
extern "C" __declspec(dllimport) long __stdcall SetWindowLongA(
    OtDialogHandle_Product window,
    int index,
    long value);
extern "C" __declspec(dllimport) OtDialogHandle_Product __stdcall GetParent(
    OtDialogHandle_Product window);
extern "C" __declspec(dllimport) unsigned int __stdcall GetDialogBaseUnits();
extern "C" __declspec(dllimport) int __stdcall SetWindowPos(
    OtDialogHandle_Product window,
    OtDialogHandle_Product insert_after,
    int x,
    int y,
    int width,
    int height,
    unsigned int flags);
extern "C" __declspec(dllimport) long __stdcall SendMessageA(
    OtDialogHandle_Product window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) int __stdcall MessageBoxA(
    OtDialogHandle_Product window,
    const char* text,
    const char* caption,
    unsigned int type);
extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int exit_code);
extern "C" __declspec(dllimport) int __stdcall HideCaret(
    OtDialogHandle_Product window);
extern "C" __declspec(dllimport) int __stdcall PostMessageA(
    OtDialogHandle_Product window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) int __stdcall DestroyWindow(
    OtDialogHandle_Product window);

extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_resourceModule;
extern "C" int g_cdMediaMode_00439108;
extern "C" int DAT_004390e8;
extern "C" void* g_journeyState;

extern "C" void __cdecl
OtScaleDialogChildFromDialogUnits_00401290_DirectImport(
    OtDialogHandle_Product dialog,
    int control_id,
    int dialog_unit_width,
    int dialog_unit_height);
extern "C" void __cdecl OtResizeControl_RealCpp(
    OtDialogHandle_Product dialog,
    int control_id,
    int width,
    int height);
extern "C" int __cdecl OtSelectDialogCursor_0040d530_RealCpp(
    int busy,
    OtDialogHandle_Product window);
extern "C" void __cdecl OtOpenWaveAudioFile_0000d110_RealCpp(
    OtDialogHandle_Product owner,
    const char* path);
extern "C" void __cdecl OtPlayWaveAudioDirectImport_0040d3e0_RealCpp();
extern "C" void __cdecl OtCloseWaveAudioDevice_0040d0a0_RealCpp();
extern "C" void __cdecl OtStopWaveAudioDirectImport_0040d480_RealCpp();

extern "C" __declspec(dllimport) void* __stdcall GetDlgItem(void*,int);
extern "C" __declspec(dllimport) void* __stdcall SetFocus(void*);
#include <string.h>
#include <stdlib.h>
#pragma intrinsic(strcpy,strcat,strlen,memset)
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(void*,OtDialogRect_Product*);
struct DialogPoint { int x,y; };
extern "C" __declspec(dllimport) int __stdcall ClientToScreen(void*,DialogPoint*);
extern "C" __declspec(dllimport) int __stdcall LoadStringA(void*,unsigned int,char*,int);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(void*,const char*);
extern "C" void OtScaleWindowToDialogCoords_00401370_Product(void*,void*,int,int);
extern "C" int OtLoadSavedDialogPlacement_00401110_RealCpp(const char*,OtDialogRect_Product*);
#include "status_owned_state.h"
extern "C" const char status_setup_placement_section[]="Status Dialog";
extern "C" const char status_setup_allocation_text[]="Unable to allocate dialog information structure";
extern "C" const char status_setup_allocation_caption[]="WhoAmIDlgProc";
#pragma optimize("s",off)
#pragma optimize("t",on)
extern "C" void OtInitializeStatusDialog_0041d400(void* dialog) {
 OtDialogRect_Product placement,parent_rect;
 OtDialogRect_Product window_rect;
 DialogPoint center;
 int unit_width,unit_height;
 StatusOwnedState* state;
 unit_width=static_cast<unsigned short>(GetDialogBaseUnits());
 unit_height=static_cast<unsigned short>(GetDialogBaseUnits()>>16);
 OtScaleWindowToDialogCoords_00401370_Product(GetParent(dialog),dialog,unit_width,unit_height);
 GetWindowRect(dialog,&window_rect);
 if(OtLoadSavedDialogPlacement_00401110_RealCpp(status_setup_placement_section,&placement)==0) {
  GetClientRect(GetParent(dialog),&parent_rect);
  center.x=parent_rect.left+(parent_rect.right-parent_rect.left)/2;
  center.y=parent_rect.top+(parent_rect.bottom-parent_rect.top)/2;
  ClientToScreen(GetParent(dialog),&center);
  SetWindowPos(dialog,0,center.x+(window_rect.left-window_rect.right)/2,
   center.y+(window_rect.top-window_rect.bottom)/2,
   window_rect.right-window_rect.left,window_rect.bottom-window_rect.top,4);
 } else {
  SetWindowPos(dialog,0,placement.left,placement.top,
   window_rect.right-window_rect.left,window_rect.bottom-window_rect.top,4);
 }
 for(int control=0x10cc;control<=0x10ef;++control) OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,control,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,300,unit_width,unit_height);
 state=new StatusOwnedState;
 if(state==0) { MessageBoxA(GetParent(dialog),status_setup_allocation_text,status_setup_allocation_caption,0); PostQuitMessage(0); }
 else {
  state->close_normal.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,0x2826);
  state->close_pressed.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,0x2827);
  SetWindowLongA(dialog,8,reinterpret_cast<long>(state));
  OtResizeControl_RealCpp(dialog,300,state->close_normal.width,state->close_normal.height);
  SetFocus(GetDlgItem(dialog,300)); SendMessageA(dialog,0x401,300,0);
 }
}
