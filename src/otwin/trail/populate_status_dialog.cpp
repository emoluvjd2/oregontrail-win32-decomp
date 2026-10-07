// Recovered status labels, supplies, wagon weight, and party condition display.
// Oregon32.exe VA 0x0041d650;
// Every formatting block is present in the original.
#include "accepted_semantic_dependencies.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#pragma intrinsic(strcpy, strcat, strlen, memset)
extern "C" __declspec(dllimport) int __stdcall LoadStringA(void*,unsigned int,char*,int);
extern "C" __declspec(dllimport) void* __stdcall GetDlgItem(void*,int);
extern "C" __declspec(dllimport) int __stdcall SetWindowTextA(void*,const char*);
extern "C" __declspec(dllimport) int __stdcall wvsprintfA(char*,const char*,char*);
extern "C" void* g_applicationModule_00405a40_20260603;
#pragma pack(push,1)
struct StatusJourney {
 char reserved_000[0x90];
    short pace;
    short ration;
    short delay;
 short oxen;
    short sick_oxen;
    short clothing;
    short bullets;
 short wheels;
    short axles;
    short tongues;
    short food;
    short meat;
 int money;
    short occupation;
    char reserved_0ae[0x10];
    short health;
 char names[5][15];
    char reserved_10b[11];
    short conditions[5];
};
#pragma pack(pop)
typedef char StatusNamesOffsetCheck[offsetof(StatusJourney, names) == 0xc0 ? 1 : -1];
typedef char StatusConditionsOffsetCheck[offsetof(StatusJourney, conditions) == 0x116 ? 1 : -1];
extern "C" StatusJourney* g_journeyState;
extern "C" const char status_occupation[] = "Occupation: ";
extern "C" const char status_colon[] = ":";
extern "C" const char status_open_weight[] = " (";
extern "C" const char status_close_weight[] = ")";
extern "C" const char status_bullets[] = "Bullets:";
extern "C" const char status_food[] = "Non-perishable food:";
extern "C" const char status_meat[] = "Perishable food:";
extern "C" const char status_money[] = "Money:";
extern "C" const char status_dollar[] = "$";
extern "C" const char status_total_weight[] = "Total wagon weight: ";
extern "C" const char status_name_separator[] = ": ";
extern "C" const char status_money_format[] = "%4d.%02d";
extern "C" const char status_empty[] = "";
#define SET_TEXT(id) SetWindowTextA(GetDlgItem(dialog,id),text)
#define LOAD_TEXT(id) LoadStringA(g_applicationModule_00405a40_20260603,id,text,sizeof(text))
#define APPEND_UNITS() LoadStringA(g_applicationModule_00405a40_20260603,0x3bb,text+strlen(text),sizeof(text)-strlen(text))
#pragma optimize("s",off)
#pragma optimize("t",on)
extern "C" void OtPopulateStatusDialog_0041d650(void* dialog) {
 char text[100];
    int money_parts[2];
 strcpy(text,status_occupation);
 LoadStringA(g_applicationModule_00405a40_20260603,g_journeyState->occupation+0xa0,text+strlen(text),sizeof(text)-strlen(text));
 SET_TEXT(0x10cc);
 memset(text,0,sizeof(text));
    LOAD_TEXT(500);
    strcat(text,status_colon);
    SET_TEXT(0x10cf);
 memset(text,0,sizeof(text));
    _itoa(g_journeyState->oxen,text,10);
    SET_TEXT(0x10d8);
memset(text,0,sizeof(text));
    LOAD_TEXT(501);
    strcat(text,status_colon);
    SET_TEXT(4304);
memset(text,0,sizeof(text));
    _itoa(g_journeyState->clothing,text,10);
 strcat(text,status_open_weight);
    _itoa(g_journeyState->clothing*3,text+strlen(text),10);
    APPEND_UNITS();
    strcat(text,status_close_weight);
    SET_TEXT(4313);
SetWindowTextA(GetDlgItem(dialog,4305),status_bullets);
memset(text,0,sizeof(text));
    _itoa(g_journeyState->bullets,text,10);
 strcat(text,status_open_weight);
    _itoa(((g_journeyState->bullets+19)/20)*2,text+strlen(text),10);
    APPEND_UNITS();
    strcat(text,status_close_weight);
    SET_TEXT(4314);
memset(text,0,sizeof(text));
    LOAD_TEXT(503);
    strcat(text,status_colon);
    SET_TEXT(4306);
memset(text,0,sizeof(text));
    _itoa(g_journeyState->wheels,text,10);
 strcat(text,status_open_weight);
    _itoa(g_journeyState->wheels*40,text+strlen(text),10);
    APPEND_UNITS();
    strcat(text,status_close_weight);
    SET_TEXT(4315);
memset(text,0,sizeof(text));
    LOAD_TEXT(504);
    strcat(text,status_colon);
    SET_TEXT(4307);
memset(text,0,sizeof(text));
    _itoa(g_journeyState->axles,text,10);
 strcat(text,status_open_weight);
    _itoa(g_journeyState->axles*70,text+strlen(text),10);
    APPEND_UNITS();
    strcat(text,status_close_weight);
    SET_TEXT(4316);
memset(text,0,sizeof(text));
    LOAD_TEXT(505);
    strcat(text,status_colon);
    SET_TEXT(4308);
memset(text,0,sizeof(text));
    _itoa(g_journeyState->tongues,text,10);
 strcat(text,status_open_weight);
    _itoa(g_journeyState->tongues*50,text+strlen(text),10);
    APPEND_UNITS();
    strcat(text,status_close_weight);
    SET_TEXT(4317);
SetWindowTextA(GetDlgItem(dialog,4309),status_food);
 memset(text,0,sizeof(text));
    _itoa(g_journeyState->food,text,10);
    APPEND_UNITS();
    SET_TEXT(4318);
SetWindowTextA(GetDlgItem(dialog,4310),status_meat);
 memset(text,0,sizeof(text));
    _itoa(g_journeyState->meat,text,10);
    APPEND_UNITS();
    SET_TEXT(4319);
SetWindowTextA(GetDlgItem(dialog,0x10d7),status_money);
 memset(text,0,sizeof(text));
    strcpy(text,status_dollar);
 money_parts[0]=g_journeyState->money/100;
    money_parts[1]=g_journeyState->money%100;
 wvsprintfA(text+1,status_money_format,reinterpret_cast<char*>(money_parts));
    SET_TEXT(0x10e0);
 memset(text,0,sizeof(text));
    strcpy(text,status_total_weight);
 _itoa(reinterpret_cast<PartyHealthScoreState_00419560_80pct*>(g_journeyState)->OtComputePartyHealthScore_RealCpp(),text+strlen(text),10);
 APPEND_UNITS();
    SET_TEXT(0x10ef);
 for (int index=0;index<5;++index) {
  int member_index = (short)index;
  if (strlen(g_journeyState->names[member_index])!=0) {
   memset(text,0,sizeof(text));
    strcpy(text,g_journeyState->names[member_index]);
    strcat(text,status_name_separator);
    SET_TEXT(index+0x10e1);
   memset(text,0,sizeof(text));
   unsigned int id;
   if (g_journeyState->conditions[member_index]!=0) id=g_journeyState->conditions[member_index]+0xc0;
   else id=g_journeyState->health/35+0xb0;
   LOAD_TEXT(id);
    SET_TEXT(index+0x10e6);
  } else {
   SetWindowTextA(GetDlgItem(dialog,index+0x10e1),status_empty);
   SetWindowTextA(GetDlgItem(dialog,index+0x10e6),status_empty);
  }
 }
 memset(text,0,sizeof(text));
    LOAD_TEXT(g_journeyState->pace+0x50);
    SET_TEXT(0x10ec);
 memset(text,0,sizeof(text));
    LOAD_TEXT(g_journeyState->ration+0x60);
    SET_TEXT(0x10ee);
}

#pragma optimize("", on)
