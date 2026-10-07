// Original start-date dialog initialization at 0x00424730.
// Named bitmap members preserve the original construction and unwind order.
// Product-reachable semantic DLGPROC for OtStartDateDialogProc @ 0x00423da0.

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

struct StartDateOwnedState_00424730 {
 PositionedBitmapDescriptorState_0040ba40 play_audio_up;
 PositionedBitmapDescriptorState_0040ba40 play_audio_down;
 PositionedBitmapDescriptorState_0040ba40 stop_audio_up;
 PositionedBitmapDescriptorState_0040ba40 stop_audio_down;
 PositionedBitmapDescriptorState_0040ba40 date_0_up;
 PositionedBitmapDescriptorState_0040ba40 date_0_down;
 PositionedBitmapDescriptorState_0040ba40 date_1_up;
 PositionedBitmapDescriptorState_0040ba40 date_1_down;
 PositionedBitmapDescriptorState_0040ba40 date_2_up;
 PositionedBitmapDescriptorState_0040ba40 date_2_down;
 PositionedBitmapDescriptorState_0040ba40 date_3_up;
 PositionedBitmapDescriptorState_0040ba40 date_3_down;
 PositionedBitmapDescriptorState_0040ba40 date_4_up;
 PositionedBitmapDescriptorState_0040ba40 date_4_down;
 PositionedBitmapDescriptorState_0040ba40 date_5_up;
 PositionedBitmapDescriptorState_0040ba40 date_5_down;
 PositionedBitmapDescriptorState_0040ba40 back_up;
 PositionedBitmapDescriptorState_0040ba40 back_down;
 PositionedBitmapDescriptorState_0040ba40 selected_date_marker;
};
extern "C" const char start_date_allocation_text[]="Unable to allocate dialog information structure";
extern "C" const char start_date_allocation_caption[]="StartDateDlgProc";
#pragma optimize("s",off)
#pragma optimize("t",on)
extern "C" void OtInitStartDateDialog_00424730(void* dialog) {
 OtDialogRect_Product rect;
 int unit_width, unit_height;
 StartDateOwnedState_00424730* state;
 SendMessageA(dialog,0x30,reinterpret_cast<unsigned int>(g_optionMenuFont_004390d4_00405320),1);
 GetClientRect(GetParent(dialog),&rect);
 int window_x=rect.left+10;
 int window_y=rect.top+10;
 SetWindowPos(dialog,0,window_x,window_y,rect.right-rect.left-20,rect.bottom-rect.top-20,4);
 unit_width=static_cast<unsigned short>(GetDialogBaseUnits());
 unit_height=static_cast<unsigned short>(GetDialogBaseUnits()>>16);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1402,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1403,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1404,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1405,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1406,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1410,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1411,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1412,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1413,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1414,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,1415,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,301,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,306,unit_width,unit_height);
 OtScaleDialogChildFromDialogUnits_00401290_DirectImport(dialog,307,unit_width,unit_height);
 state=new StartDateOwnedState_00424730;
 if(state==0) {
  MessageBoxA(GetParent(dialog),start_date_allocation_text,start_date_allocation_caption,0); PostQuitMessage(0);
 } else {
  if(g_cdMediaMode_00439108!=0) {
   state->play_audio_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,10284);
   state->play_audio_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,10285);
   state->stop_audio_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,10286);
   state->stop_audio_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,10287);
   OtResizeControl_RealCpp(dialog,0x132,state->play_audio_up.width,state->play_audio_up.height);
   OtResizeControl_RealCpp(dialog,0x133,state->stop_audio_up.width,state->stop_audio_up.height);
  }
  state->date_0_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10301);
  state->date_0_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10302);
  state->date_1_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10303);
  state->date_1_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10304);
  state->date_2_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10305);
  state->date_2_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10306);
  state->date_3_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10307);
  state->date_3_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10308);
  state->date_4_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10309);
  state->date_4_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10310);
  state->date_5_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10311);
  state->date_5_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,10312);
  state->back_up.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,10280);
  state->back_down.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_applicationModule_00405a40_20260603,10281);
  state->selected_date_marker.OtLoadPositionedBitmapDescriptor_0040ba40_RealCpp(g_resourceModule,1401);
  SetWindowLongA(dialog,8,reinterpret_cast<long>(state));
  OtResizeControl_RealCpp(dialog,1410,state->date_0_up.width,state->date_0_up.height);
  OtResizeControl_RealCpp(dialog,1411,state->date_1_up.width,state->date_1_up.height);
  OtResizeControl_RealCpp(dialog,1412,state->date_2_up.width,state->date_2_up.height);
  OtResizeControl_RealCpp(dialog,1413,state->date_3_up.width,state->date_3_up.height);
  OtResizeControl_RealCpp(dialog,1414,state->date_4_up.width,state->date_4_up.height);
  OtResizeControl_RealCpp(dialog,1415,state->date_5_up.width,state->date_5_up.height);
  OtResizeControl_RealCpp(dialog,0x12d,state->back_up.width,state->back_up.height);
 }
}

#pragma optimize("",on)
