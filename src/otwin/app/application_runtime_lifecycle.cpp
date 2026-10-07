// Product-tree semantic recovery of the main application runtime lifecycle:
// Oregon32.exe RVAs 0x000044f0, 0x00004730, and the associated message
// dispatcher at 0x000039d0. The lifecycle is intentionally kept as ordinary
// C++ so VC4 emits the original nested-constructor/destructor and EH shape.

#include "application_runtime_lifecycle.h"

#include <string.h>

#pragma intrinsic(strcmp, memset)

extern "C" __declspec(dllimport) void* __stdcall SetCursor(void* cursor);
extern "C" __declspec(dllimport) void* __stdcall LoadCursorA(
    void* instance,
    const void* cursor_name);
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(
    const char* file_name);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(void* module);
extern "C" __declspec(dllimport) void* __stdcall FindResourceA(
    void* module,
    const void* name,
    const void* type);
extern "C" __declspec(dllimport) void* __stdcall LoadResource(
    void* module,
    void* resource_info);
extern "C" __declspec(dllimport) void* __stdcall LockResource(
    void* resource_handle);
extern "C" __declspec(dllimport) int __stdcall FreeResource(
    void* resource_handle);
extern "C" __declspec(dllimport) void __stdcall FatalAppExitA(
    unsigned int action,
    const char* message);
extern "C" __declspec(dllimport) void* __stdcall CreateWindowExA(
    unsigned long ex_style,
    const char* class_name,
    const char* window_name,
    unsigned long style,
    int x,
    int y,
    int width,
    int height,
    void* parent,
    void* menu,
    void* instance,
    void* parameter);
extern "C" __declspec(dllimport) int __stdcall ShowWindow(
    void* window,
    int command_show);
extern "C" __declspec(dllimport) int __stdcall DrawMenuBar(void* window);
extern "C" __declspec(dllimport) void* __stdcall LoadAcceleratorsA(
    void* instance,
    const char* table_name);
extern "C" __declspec(dllimport) int __stdcall DeleteObject(void* object);
extern "C" __declspec(dllimport) void __stdcall PostQuitMessage(int exit_code);
extern "C" __declspec(dllimport) int __stdcall PostMessageA(
    void* window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) long __stdcall SendMessageA(
    void* window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) int __stdcall IsWindow(void* window);
extern "C" __declspec(dllimport) int __stdcall IsIconic(void* window);
extern "C" __declspec(dllimport) int __stdcall GetWindowRect(
    void* window,
    void* rect);
extern "C" __declspec(dllimport) int __stdcall KillTimer(
    void* window,
    unsigned int timer_id);
extern "C" __declspec(dllimport) int __stdcall DestroyWindow(void* window);
extern "C" __declspec(dllimport) int __stdcall InvalidateRect(
    void* window,
    const void* rect,
    int erase);
extern "C" __declspec(dllimport) int __stdcall WinHelpA(
    void* window,
    const char* help_file,
    unsigned int command,
    unsigned long data);
extern "C" __declspec(dllimport) void* __stdcall CreateDialogParamA(
    void* instance,
    const void* template_name,
    void* parent_window,
    ApplicationDialogProc_00405a40 dialog_proc,
    long init_param);
extern "C" __declspec(dllimport) int __stdcall DialogBoxParamA(
    void* instance,
    const void* template_name,
    void* parent_window,
    ApplicationDialogProc_00405a40 dialog_proc,
    long init_param);
extern "C" __declspec(dllimport) long __stdcall DefWindowProcA(
    void* window,
    unsigned int message,
    unsigned int wparam,
    long lparam);
extern "C" __declspec(dllimport) void* __stdcall GetDC(void* window);
extern "C" __declspec(dllimport) int __stdcall ReleaseDC(
    void* window,
    void* dc);
extern "C" __declspec(dllimport) void* __stdcall SelectPalette(
    void* dc,
    void* palette,
    int force_background);
extern "C" __declspec(dllimport) int __stdcall UnrealizeObject(void* object);
extern "C" __declspec(dllimport) unsigned int __stdcall RealizePalette(
    void* dc);
extern "C" __declspec(dllimport) unsigned long __stdcall GetNearestColor(
    void* dc,
    unsigned long color);
extern "C" __declspec(dllimport) void* __stdcall CreateSolidBrush(
    unsigned long color);
extern "C" __declspec(dllimport) unsigned int __stdcall GetPrivateProfileIntA(
    const char* section,
    const char* key,
    int default_value,
    const char* file_name);
extern "C" __declspec(dllimport) unsigned long __stdcall GetPrivateProfileStringA(
    const char* section,
    const char* key,
    const char* default_value,
    char* returned_string,
    unsigned long size,
    const char* file_name);
extern "C" __declspec(dllimport) int __stdcall WritePrivateProfileStringA(
    const char* section,
    const char* key,
    const char* value,
    const char* file_name);
extern "C" __declspec(dllimport) void* __stdcall GetMenu(void* window);
extern "C" __declspec(dllimport) void* __stdcall GetSubMenu(
    void* menu,
    int position);
extern "C" __declspec(dllimport) unsigned int __stdcall CheckMenuItem(
    void* menu,
    unsigned int item,
    unsigned int flags);
extern "C" __declspec(dllimport) int __stdcall DeleteMenu(
    void* menu,
    unsigned int position,
    unsigned int flags);
extern "C" __declspec(dllimport) int __stdcall GetSystemMetrics(int index);
extern "C" __declspec(dllimport) int __stdcall GetVersionExA(
    void* version_information);

#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

struct SavedMainWindowRect_004035b0 {
    int x;
    int y;
    int width;
    int height;
};

struct OSVersionInfoA_004035b0 {
    unsigned long size;
    unsigned long major_version;
    unsigned long minor_version;
    unsigned long build_number;
    unsigned long platform_id;
    char service_pack[128];
};

typedef char OSVersionInfoSizeCheck_004035b0[
    sizeof(OSVersionInfoA_004035b0) == 0x94 ? 1 : -1];

struct DisplayCapabilityPureProbe_00403480 {
    char reserved_00[4];
    void* window;
    void OtProbeIndexedDisplayCapabilityDirectThis_00403480_RealCpp();
};

struct PaletteOwner_004036b0 {
    char reserved_00[4];
    void* owner_window;
    int OtLoadGlobalPalette_004036b0_Semantic();
};

struct FourStringResourceOwner_00403830 {
    void OtLoadFourStringIntoSubResources_00403830_RealCpp();
};

struct StringResourceGroupOwner_004038d0 {
    void OtStringResourceGroupLoad_004038d0_RealCpp();
};

struct ApplicationOptionMenuStateSync_00405320 {
    char reserved_00[4];
    void* main_window;
    void OtOptionMenuStateSync_00405320_RealCpp();
};

struct ApplicationRect_004039d0 {
    long left;
    long top;
    long right;
    long bottom;
};

struct StateTransitionConfirmation_00003390 {
    int OtConfirmStateTransitionMsgBox_00003390_RealCpp();
};

struct CloseConfirmationState_00403410 {
    int OtConfirmCloseTransition_Product_00403410();
};

struct MainWindowCloseState_00403470 {
    int OtIsCloseConfirmationState_RealCpp() const;
};

struct ActiveScreenDialogState_004034d0 {
    void OtDestroyActiveScreenDialog_Product_004034d0();
};

struct MainWindowPaintState_00404880 {
    void OtPaintMainWindow_00404880_RealCpp();
};

struct ControlNotificationDispatcher_00404a70 {
    int OtDispatchControlNotification_6e_72_00404a70_RealCpp(
        unsigned int notification_id,
        unsigned int notify_code);
};

struct MenuCommandRangeDispatch_00404b30_20260605 {
    int OtMenuCommandRangeDispatch_00004b30_20260605_Wip(
        unsigned int command_id,
        long notify_code);
};

struct ApplicationMenuCommandState_00404dd0 {
    int OtHandleApplicationMenuCommandAlt1_00404dd0(
        unsigned int command_id,
        long notify_code);
};

struct MenuCommandDispatcher_00404ed0 {
    int OtDispatchMenuCommand_82_85_00404ed0_RealCpp(
        unsigned int command_id,
        long notify_code);
};

struct MainWindowMessageRouter_00405000 {
    void OtMainWindowMessageRouter_00005000_ProductWip(void* menu);
};

struct ApplicationOptionDialogFlow_00005410 {
    void OtApplicationOptionDialogFlow_00005410_ProductWip();
};

struct PartyStatsDialogList_00419830 {
    void OtPopulatePartyStatsDialogList_00419830_RealCpp();
};

struct JourneyStateDefaults_0041a000_20260525 {
    void OtJourneyInitStateDefaultsMaskClosedFELTDR_0041a000();
};

#pragma pack(push, 1)
struct HandleAppJourneyState_004039d0 {
    char reserved_000[0x5c];
    short hunt_region;
    char reserved_05e[0x2e];
    short current_hunt_region;
    char reserved_08e[0x0e];
    short ammunition;
    char reserved_09e[6];
    short food_from_plants;
    short food_from_hunting;
};

struct HuntOutcomeState_004039d0 {
    int ammunition_used;
    int pounds_obtained;
    int pounds_allowed;
    int pounds_kept;
};
#pragma pack(pop)

typedef char HandleAppJourneyHuntRegionOffsetCheck_004039d0[
    offsetof(HandleAppJourneyState_004039d0, hunt_region) == 0x5c ? 1 : -1];
typedef char HandleAppJourneyCurrentRegionOffsetCheck_004039d0[
    offsetof(HandleAppJourneyState_004039d0, current_hunt_region) == 0x8c ? 1 : -1];
typedef char HandleAppJourneyAmmunitionOffsetCheck_004039d0[
    offsetof(HandleAppJourneyState_004039d0, ammunition) == 0x9c ? 1 : -1];
typedef char HandleAppJourneyFoodOffsetCheck_004039d0[
    offsetof(HandleAppJourneyState_004039d0, food_from_plants) == 0xa4 ? 1 : -1];

extern "C" ApplicationPositionedBitmap_004044f0* __fastcall
    OtInitPositionedBitmap_RealCpp(
        ApplicationPositionedBitmap_004044f0* bitmap);
extern "C" void __fastcall OtFreePositionedBitmapDependencyCall_00406240(
    ApplicationPositionedBitmap_004044f0* bitmap);
extern "C" void __cdecl OtOpenMidiAudioFileMaskClosed_0000cd60_RealCpp(
    void* owner_window,
    const char* filename);
extern "C" void __cdecl OtPlayMidiAudio_0000ced0_RealCpp(int restart);
extern "C" void __cdecl OtOpenWaveAudioFile_0000d110_RealCpp(
    void* owner_window,
    const char* filename);
extern "C" void __cdecl OtPlayWaveAudioDirectImport_0040d3e0_RealCpp();
extern "C" void __cdecl OtInitializeJourneyRuntime_0001a120_ProductWip();
extern "C" void __cdecl OtShutdownJourneyRuntime_RealCpp();
extern "C" void __cdecl OtReleaseCachedGlobalHandle_Product_0040f840();
extern "C" void __cdecl OtPersistDialogPlacement_00401430_RealCpp(
    const char* profile_section,
    const ApplicationRect_004039d0* rect);
extern "C" int __cdecl OtRiverEnsureScratchBuffer_RealCpp();
extern "C" short __fastcall OtCountLivingPartyMembers_RealCpp(
    const void* party);
extern "C" void __stdcall OtLoadRouteDescriptor_RealCpp(short route_id);
extern "C" void __stdcall OtRecordHuntOutcomeMessage_00002fc0_Product(
    HuntOutcomeState_004039d0* outcome);
extern "C" int __cdecl OtSelectDialogCursor_0040d530_RealCpp(
    int force_busy_cursor,
    void* window);
extern "C" void __cdecl OtCloseMidiAudioDeviceNoAsm_0040ccf0_RealCpp();
extern "C" void __cdecl OtCloseWaveAudioDevice_0040d0a0_RealCpp();
extern "C" void __cdecl OtRegisterMainWindowClass_00404f60_RealCpp();
extern "C" int __cdecl OtLoadSavedDialogPlacement_00401110_RealCpp(
    const char* section,
    SavedMainWindowRect_004035b0* rect);
extern "C" char* __cdecl _strlwr(char* text);

extern "C" int __stdcall OtHuntResultsDialogProc_000023b0_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtWillametteValleyArrivalDialogProc_0000fee0_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtDeathDialogProc_00010da0_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtInitHuntDialogProc_00014d00_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtWelcomeDialogProc_000156c0_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtTitleDialogProc_0001baf0_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtStartDateDialogProc_00023da0_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtRaftingDialogProc_00027340_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtWhoAmIDialogProc_00028f00_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtTrailGameDialogProc_0002dff0_Wip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall OtGeneralStoreDialogProc_00407340_ProductWip(
    void*, unsigned int, unsigned int, long);
extern "C" int __stdcall
OtWillametteValleySummaryDialogProc_00424f50_ProductWip(
    void*, unsigned int, unsigned int, long);

extern "C" void* g_applicationModule_00405a40_20260603;
extern "C" void* g_previousInstance_00405a40_20260603;
extern "C" int g_initialShowCommand_00405a40_20260603;
extern "C" void* g_mainAccelerator_00402ed0;
extern "C" void* g_resourceModule;
extern "C" void* g_gamePalette;
extern "C" int g_usesIndexedColorDisplay;
extern "C" int g_cdMediaMode_00439108;
extern "C" int g_titleThemeEnabled_004390ec;
extern "C" int DAT_004390e8;
extern "C" int DAT_004390e0;
extern "C" int DAT_004390e4;
extern "C" int g_trailLeaderboardEnabled_004390f0;
extern "C" void* g_activeScreenDialogWindow_00404dd0;
extern "C" int g_generalStorePurchaseCommitted_004390f8;
extern "C" HandleAppJourneyState_004039d0* g_journeyState;
extern "C" const char* PTR_s_oregon_ini_004390dc;
extern "C" const char s_simulation_speed_00439138[];
extern "C" const char s_hunt_time_0043914c[];
extern "C" void* g_optionMenuFont_004390d4_00405320;
extern "C" void* g_dialogFont_004390d8_00405320;

#pragma data_seg(".otdat")
// These are the canonical DAT_00439100 and DAT_004390c0 slots consumed by
// the dialog callbacks as well as initialized here.  Keeping one Product
// definition prevents the runtime lifecycle and callbacks from observing
// different copies of the original globals.
extern "C" int g_appBusyCursorActive_Product_004034d0;
extern "C" int g_mainWindowClassRegistered_00439120 = 0;
extern "C" int g_titleTransitionFlag_004390fc = 0;
extern "C" void* g_sharedDialogBackgroundBrush_004390c0;
extern "C" void* g_paletteWhiteBrush_004044f0 = 0;
extern "C" int g_graveSitesEnabled_004390f4;
extern "C" int g_newJourneyStoreFlowFlag_0043b594 = 0;
#pragma data_seg()

#pragma code_seg(".otsem")
extern "C" __declspec(allocate(".otsem"))
const char g_resourceLibraryName_004044f0[] = "oregon32.dll";
extern "C" __declspec(allocate(".otsem"))
const char g_resourceLoadFailure_004044f0[] =
    "Can't load resource library. Exiting.";
extern "C" __declspec(allocate(".otsem"))
const char g_resourceAccessFailure_004044f0[] =
    "Trouble accessing resources.";
extern "C" __declspec(allocate(".otsem"))
const char g_mainWindowTitle_004044f0[] = "The Oregon Trail";
extern "C" __declspec(allocate(".otsem"))
const char g_mainWindowCreateFailure_004044f0[] =
    "Couldn't create the main window!";
extern "C" __declspec(allocate(".otsem"))
const char g_logoMidiName_004044f0[] = "logo.mid";
extern "C" __declspec(allocate(".otsem"))
const char g_logoWaveName_004044f0[] = "logo.wav";
extern "C" __declspec(allocate(".otsem"))
const char g_acceleratorTableName_004044f0[] = "OTHOTKEYS";
extern "C" __declspec(allocate(".otsem"))
const char g_mainWindowPlacementSection_004039d0[] = "Oregon Trail Window";
extern "C" __declspec(allocate(".otsem"))
const char g_optionSoundKey_00405410[] = "Sound";
extern "C" __declspec(allocate(".otsem"))
const char g_optionMusicKey_00405410[] = "Music";
extern "C" __declspec(allocate(".otsem"))
const char g_optionLeaderboardKey_00405410[] = "List of Legends";
extern "C" __declspec(allocate(".otsem"))
const char g_optionGraveSitesKey_00405410[] = "GraveSites";
extern "C" __declspec(allocate(".otsem"))
const char g_optionEnabledValue_00405410[] = "on";

#define OT_CLEAR_OPTION_VALUE_00405410(buffer) \
    do {                                        \
        *(int*)&(buffer)[0] = 0;                \
        *(int*)&(buffer)[4] = 0;                \
        *(short*)&(buffer)[8] = 0;              \
    } while (0)

void ApplicationOptionDialogFlow_00005410::
    OtApplicationOptionDialogFlow_00005410_ProductWip()
{
    char option_value[10];
    char configuration[] = "Game Configuration";
    char menu_text[25];
    void* options_menu;

    DAT_004390e0 = GetPrivateProfileIntA(
        configuration,
        s_simulation_speed_00439138,
        4,
        PTR_s_oregon_ini_004390dc);
    DAT_004390e4 = GetPrivateProfileIntA(
        configuration,
        s_hunt_time_0043914c,
        60,
        PTR_s_oregon_ini_004390dc);

    OT_CLEAR_OPTION_VALUE_00405410(option_value);
    GetPrivateProfileStringA(
        configuration,
        g_optionSoundKey_00405410,
        g_optionEnabledValue_00405410,
        option_value,
        9,
        PTR_s_oregon_ini_004390dc);
    _strlwr(option_value);
    DAT_004390e8 = strcmp(option_value, g_optionEnabledValue_00405410) == 0;

    OT_CLEAR_OPTION_VALUE_00405410(option_value);
    GetPrivateProfileStringA(
        configuration,
        g_optionMusicKey_00405410,
        g_optionEnabledValue_00405410,
        option_value,
        9,
        PTR_s_oregon_ini_004390dc);
    _strlwr(option_value);
    g_titleThemeEnabled_004390ec =
        strcmp(option_value, g_optionEnabledValue_00405410) == 0;

    OT_CLEAR_OPTION_VALUE_00405410(option_value);
    GetPrivateProfileStringA(
        configuration,
        g_optionLeaderboardKey_00405410,
        g_optionEnabledValue_00405410,
        option_value,
        9,
        PTR_s_oregon_ini_004390dc);
    if (strcmp(option_value, g_optionEnabledValue_00405410) == 0) {
        g_trailLeaderboardEnabled_004390f0 = 1;
        WritePrivateProfileStringA(
            configuration,
            g_optionLeaderboardKey_00405410,
            option_value,
            PTR_s_oregon_ini_004390dc);
    } else {
        g_trailLeaderboardEnabled_004390f0 = 0;
    }

    OT_CLEAR_OPTION_VALUE_00405410(option_value);
    GetPrivateProfileStringA(
        configuration,
        g_optionGraveSitesKey_00405410,
        g_optionEnabledValue_00405410,
        option_value,
        9,
        PTR_s_oregon_ini_004390dc);
    if (strcmp(option_value, g_optionEnabledValue_00405410) == 0) {
        g_graveSitesEnabled_004390f4 = 1;
        WritePrivateProfileStringA(
            configuration,
            g_optionGraveSitesKey_00405410,
            option_value,
            PTR_s_oregon_ini_004390dc);
    } else {
        g_graveSitesEnabled_004390f4 = 0;
    }

    options_menu = GetSubMenu(
        GetMenu(reinterpret_cast<MainWindowRuntimeObject_00405a40*>(this)->
            main_window),
        2);
    memset(menu_text, 0, sizeof(menu_text));

    CheckMenuItem(options_menu, 0x7a, DAT_004390e8 == 0 ? 0 : 8);
    CheckMenuItem(
        options_menu,
        0x79,
        g_titleThemeEnabled_004390ec == 0 ? 0 : 8);
    if (g_trailLeaderboardEnabled_004390f0 == 0) {
        DeleteMenu(options_menu, 0x7b, 0);
    }
}

#undef OT_CLEAR_OPTION_VALUE_00405410

ApplicationPositionedBitmap_004044f0::
    ApplicationPositionedBitmap_004044f0()
{
    OtInitPositionedBitmap_RealCpp(this);
}

ApplicationPositionedBitmap_004044f0::
    ~ApplicationPositionedBitmap_004044f0()
{
    OtFreePositionedBitmapDependencyCall_00406240(this);
}

extern "C" const char g_mainWindowClassName_00404f60[];


#pragma optimize("s", off)
#pragma optimize("t", on)

void MainWindowRuntimeObject_00405a40::
    OtInitPaletteBrushes_Product_00403530()
{
    MainWindowRuntimeObject_00405a40* runtime = this;
    void* dc = GetDC(runtime->main_window);
    SelectPalette(dc, g_gamePalette, 0);
    UnrealizeObject(g_gamePalette);
    RealizePalette(dc);

    if (g_usesIndexedColorDisplay != 0) {
        g_sharedDialogBackgroundBrush_004390c0 =
            CreateSolidBrush(0x0288f4fcul);
    } else {
        g_sharedDialogBackgroundBrush_004390c0 =
            CreateSolidBrush(GetNearestColor(dc, 0x0088f4fcul));
    }
    g_paletteWhiteBrush_004044f0 = CreateSolidBrush(0x00fffffful);
    ReleaseDC(runtime->main_window, dc);
}

#pragma optimize("", on)

#pragma optimize("s", off)
#pragma optimize("t", on)

MainWindowRuntimeObject_00405a40::MainWindowRuntimeObject_00405a40()
{
    g_appBusyCursorActive_Product_004034d0 = 1;
    SetCursor(LoadCursorA(0, reinterpret_cast<const void*>(0x7f02)));

    flow_state = 0;
    g_activeScreenDialogWindow_00404dd0 = 0;
    captured_interaction_window = 0;

    g_resourceModule = LoadLibraryA(g_resourceLibraryName_004044f0);
    if (reinterpret_cast<unsigned long>(g_resourceModule) < 0x20) {
        FatalAppExitA(0, g_resourceLoadFailure_004044f0);
    }

    void* resource_info = FindResourceA(
        g_resourceModule,
        reinterpret_cast<const void*>(0xc8),
        reinterpret_cast<const void*>(0x0a));
    if (resource_info == 0) {
        FatalAppExitA(0, g_resourceAccessFailure_004044f0);
    }
    void* resource_handle = LoadResource(g_resourceModule, resource_info);
    if (resource_handle == 0) {
        FatalAppExitA(0, g_resourceAccessFailure_004044f0);
    }
    int* sound_mode = static_cast<int*>(LockResource(resource_handle));
    if (sound_mode == 0) {
        FatalAppExitA(0, g_resourceAccessFailure_004044f0);
    }
    g_cdMediaMode_00439108 = *sound_mode;
    FreeResource(resource_handle);

    OtCreateMainWindow_004035b0(this);
    reinterpret_cast<DisplayCapabilityPureProbe_00403480*>(this)->
        OtProbeIndexedDisplayCapabilityDirectThis_00403480_RealCpp();
    reinterpret_cast<PaletteOwner_004036b0*>(this)->
        OtLoadGlobalPalette_004036b0_Semantic();
    reinterpret_cast<StringResourceGroupOwner_004038d0*>(this)->
        OtStringResourceGroupLoad_004038d0_RealCpp();
    reinterpret_cast<FourStringResourceOwner_00403830*>(this)->
        OtLoadFourStringIntoSubResources_00403830_RealCpp();
    OtInitPaletteBrushes_Product_00403530();

    should_start_overlay_timer = 1;
    ShowWindow(main_window, g_initialShowCommand_00405a40_20260603);
    DrawMenuBar(main_window);
    flow_state = 1;
    reinterpret_cast<ApplicationOptionMenuStateSync_00405320*>(this)->
        OtOptionMenuStateSync_00405320_RealCpp();
    reinterpret_cast<ApplicationOptionDialogFlow_00005410*>(this)->
        OtApplicationOptionDialogFlow_00005410_ProductWip();

    if (g_titleThemeEnabled_004390ec != 0) {
        if (g_cdMediaMode_00439108 == 0) {
            OtOpenMidiAudioFileMaskClosed_0000cd60_RealCpp(
                main_window,
                g_logoMidiName_004044f0);
            OtPlayMidiAudio_0000ced0_RealCpp(0);
        } else {
            OtOpenWaveAudioFile_0000d110_RealCpp(
                main_window,
                g_logoWaveName_004044f0);
            OtPlayWaveAudioDirectImport_0040d3e0_RealCpp();
        }
    }

    g_mainAccelerator_00402ed0 = LoadAcceleratorsA(
        g_applicationModule_00405a40_20260603,
        g_acceleratorTableName_004044f0);
    OtInitializeJourneyRuntime_0001a120_ProductWip();
}

MainWindowRuntimeObject_00405a40::~MainWindowRuntimeObject_00405a40()
{
    g_appBusyCursorActive_Product_004034d0 = 1;
    SetCursor(LoadCursorA(0, reinterpret_cast<const void*>(0x7f02)));

    FreeLibrary(g_resourceModule);
    DeleteObject(g_optionMenuFont_004390d4_00405320);
    DeleteObject(g_dialogFont_004390d8_00405320);
    if (g_sharedDialogBackgroundBrush_004390c0 != 0) {
        DeleteObject(g_sharedDialogBackgroundBrush_004390c0);
    }
    if (g_paletteWhiteBrush_004044f0 != 0) {
        DeleteObject(g_paletteWhiteBrush_004044f0);
    }
    if (g_gamePalette != 0) {
        DeleteObject(g_gamePalette);
    }

    if (active_overlay != 0) {
        delete active_overlay;
    }

    OtShutdownJourneyRuntime_RealCpp();
    SetCursor(LoadCursorA(0, reinterpret_cast<const void*>(0x7f00)));
}

long MainWindowRuntimeObject_00405a40::
    OtDispatchWindowMessage_004039d0_ProductWip(
        unsigned int message,
        unsigned int wparam,
        long lparam)
{
    ApplicationRect_004039d0 window_rect;

    if (message < 0x10) {
        if (message == 0x0f) {
            reinterpret_cast<MainWindowPaintState_00404880*>(this)->
                OtPaintMainWindow_00404880_RealCpp();
            return 0;
        }

        if (message == 0x01) {
            return 0;
        }

        if (message == 0x02) {
            reinterpret_cast<StateTransitionConfirmation_00003390*>(this)->
                OtConfirmStateTransitionMsgBox_00003390_RealCpp();
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            if (flow_state == 0x0b) {
                reinterpret_cast<CloseConfirmationState_00403410*>(this)->
                    OtConfirmCloseTransition_Product_00403410();
            }
            OtReleaseCachedGlobalHandle_Product_0040f840();
            GetWindowRect(main_window, &window_rect);
            if (IsIconic(main_window) == 0) {
                OtPersistDialogPlacement_00401430_RealCpp(
                    g_mainWindowPlacementSection_004039d0,
                    &window_rect);
            }
            WinHelpA(main_window, 0, 2, 0);
            PostQuitMessage(0);
            return 0;
        }

        if (message == 0x05) {
            if (wparam == 1 && flow_state == 1) {
                KillTimer(main_window, 700);
                if (g_cdMediaMode_00439108 != 0) {
                    OtCloseWaveAudioDevice_0040d0a0_RealCpp();
                } else {
                    OtCloseMidiAudioDeviceNoAsm_0040ccf0_RealCpp();
                }
                return 0;
            }

            if (wparam == 0) {
                if (flow_state == 1) {
                    PostMessageA(main_window, 0x046d, 0, 0);
                    if (g_cdMediaMode_00439108 != 0) {
                        OtCloseWaveAudioDevice_0040d0a0_RealCpp();
                    } else {
                        OtCloseMidiAudioDeviceNoAsm_0040ccf0_RealCpp();
                    }
                    return 0;
                }

                if (IsWindow(g_activeScreenDialogWindow_00404dd0) != 0 &&
                    IsIconic(main_window) == 0) {
                    PostMessageA(
                        g_activeScreenDialogWindow_00404dd0,
                        0x0467,
                        0,
                        0);
                }
            }
            return 0;
        }
    } else if (message < 0x15) {
        if (message == 0x14) {
            return 1;
        }

        if (message == 0x11) {
            return reinterpret_cast<StateTransitionConfirmation_00003390*>(
                this)->OtConfirmStateTransitionMsgBox_00003390_RealCpp() != 0;
        }
    } else if (message < 0x21) {
        if (message == 0x20) {
            return OtSelectDialogCursor_0040d530_RealCpp(
                g_appBusyCursorActive_Product_004034d0,
                reinterpret_cast<void*>(wparam));
        }

        if (message == 0x1c) {
            if (IsWindow(g_activeScreenDialogWindow_00404dd0) != 0) {
                if (wparam == 0) {
                    PostMessageA(
                        g_activeScreenDialogWindow_00404dd0,
                        0x0465,
                        0,
                        0);
                    return 0;
                }

                if (IsIconic(main_window) == 0) {
                    UnrealizeObject(g_gamePalette);
                    InvalidateRect(
                        g_activeScreenDialogWindow_00404dd0,
                        0,
                        1);
                    PostMessageA(
                        g_activeScreenDialogWindow_00404dd0,
                        0x0467,
                        0,
                        0);
                }
            }
            return 0;
        }
    } else if (message < 0x120) {
        if (message == 0x11f) {
            if (lparam == 0 && (wparam >> 16) == 0xffff) {
                if (IsWindow(g_activeScreenDialogWindow_00404dd0) != 0 &&
                    IsIconic(g_activeScreenDialogWindow_00404dd0) == 0) {
                    PostMessageA(
                        g_activeScreenDialogWindow_00404dd0,
                        0x0466,
                        0,
                        0);
                }
                return 1;
            }

            if (g_activeScreenDialogWindow_00404dd0 != 0) {
                PostMessageA(
                    g_activeScreenDialogWindow_00404dd0,
                    0x0464,
                    0,
                    0);
            }
            reinterpret_cast<MainWindowMessageRouter_00405000*>(this)->
                OtMainWindowMessageRouter_00005000_ProductWip(
                    reinterpret_cast<void*>(lparam));
            return 0;
        }

        if (message == 0x112) {
            if (wparam != 0xf060) {
                return DefWindowProcA(main_window, message, wparam, lparam);
            }

            if (reinterpret_cast<MainWindowCloseState_00403470*>(this)->
                    OtIsCloseConfirmationState_RealCpp() == 0) {
                if (reinterpret_cast<StateTransitionConfirmation_00003390*>(
                        this)->
                        OtConfirmStateTransitionMsgBox_00003390_RealCpp() != 0) {
                    DestroyWindow(main_window);
                }
            } else {
                PostMessageA(main_window, 0x047c, 0, 0);
            }
        }

        if (message == 0x111 || message == 0x112) {
            unsigned int command = wparam & 0xffff;
            if (command >= 0x64 && command <= 0x69) {
                reinterpret_cast<MenuCommandRangeDispatch_00404b30_20260605*>(
                    this)->OtMenuCommandRangeDispatch_00004b30_20260605_Wip(
                        wparam,
                        lparam);
            } else if (command >= 0x6e && command <= 0x72) {
                reinterpret_cast<ControlNotificationDispatcher_00404a70*>(
                    this)->OtDispatchControlNotification_6e_72_00404a70_RealCpp(
                        wparam,
                        static_cast<unsigned int>(lparam));
            } else if (command >= 0x78 && command <= 0x7d) {
                reinterpret_cast<ApplicationMenuCommandState_00404dd0*>(this)->
                    OtHandleApplicationMenuCommandAlt1_00404dd0(
                        wparam,
                        lparam);
            } else if (command >= 0x82 && command <= 0x85) {
                reinterpret_cast<MenuCommandDispatcher_00404ed0*>(this)->
                    OtDispatchMenuCommand_82_85_00404ed0_RealCpp(
                        wparam,
                        lparam);
            }
            return 0;
        }

        if (message == 0x113) {
            if (wparam != 0x02bc) {
                return 1;
            }

            KillTimer(main_window, 700);
            should_start_overlay_timer = 0;
            g_appBusyCursorActive_Product_004034d0 = 0;
            SetCursor(LoadCursorA(0, reinterpret_cast<const void*>(0x7f00)));
            PostMessageA(main_window, 0x046d, 0, 0);
            if (active_overlay != 0) {
                delete active_overlay;
            }
            active_overlay = 0;

            if (g_cdMediaMode_00439108 != 0) {
                OtCloseWaveAudioDevice_0040d0a0_RealCpp();
            } else {
                OtCloseMidiAudioDeviceNoAsm_0040ccf0_RealCpp();
            }
            return 0;
        }
    }

    if (message < 0x46e) {
        if (message == 0x46d) {
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            OtReleaseCachedGlobalHandle_Product_0040f840();
            should_start_overlay_timer = 0;
            g_generalStorePurchaseCommitted_004390f8 = 0;
            g_titleTransitionFlag_004390fc = 0;
            active_dialog_proc = OtTitleDialogProc_0001baf0_Wip;
            CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00d3),
                main_window,
                OtTitleDialogProc_0001baf0_Wip,
                flow_state);
            flow_state = 2;
            return 0;
        }

        if (message == 0x30f || message == 0x311) {
            if (message == 0x311 &&
                (main_window == reinterpret_cast<void*>(wparam) ||
                 g_activeScreenDialogWindow_00404dd0 ==
                    reinterpret_cast<void*>(wparam))) {
                return 0;
            }

            void* dc = GetDC(main_window);
            SelectPalette(dc, g_gamePalette, 0);
            unsigned int changed = RealizePalette(dc);
            ReleaseDC(main_window, dc);
            if (changed != 0) {
                InvalidateRect(main_window, 0, 1);
            }
            return changed;
        }
    } else {
        switch (message) {
        case 0x46e:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            reinterpret_cast<JourneyStateDefaults_0041a000_20260525*>(
                g_journeyState)->
                OtJourneyInitStateDefaultsMaskClosedFELTDR_0041a000();
            g_newJourneyStoreFlowFlag_0043b594 = 1;
            if (OtRiverEnsureScratchBuffer_RealCpp() == 0) {
                return 0;
            }
            OtLoadRouteDescriptor_RealCpp(0);
            flow_state = 3;
            active_dialog_proc = OtWelcomeDialogProc_000156c0_Wip;
            CreateDialogParamA(
                g_resourceModule,
                reinterpret_cast<const void*>(0x00d4),
                main_window,
                OtWelcomeDialogProc_000156c0_Wip,
                reinterpret_cast<long>(g_journeyState));
            return 0;

        case 0x46f:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            flow_state = 4;
            reinterpret_cast<PartyStatsDialogList_00419830*>(g_journeyState)->
                OtPopulatePartyStatsDialogList_00419830_RealCpp();
            active_dialog_proc = OtWhoAmIDialogProc_00028f00_Wip;
            CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00d5),
                main_window,
                OtWhoAmIDialogProc_00028f00_Wip,
                0);
            return 0;

        case 0x470:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            flow_state = 5;
            active_dialog_proc = OtStartDateDialogProc_00023da0_Wip;
            CreateDialogParamA(
                g_resourceModule,
                reinterpret_cast<const void*>(0x00d6),
                main_window,
                OtStartDateDialogProc_00023da0_Wip,
                0);
            return 0;

        case 0x471:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            flow_state = 6;
            active_dialog_proc = OtGeneralStoreDialogProc_00407340_ProductWip;
            CreateDialogParamA(
                g_resourceModule,
                reinterpret_cast<const void*>(0x00d7),
                main_window,
                OtGeneralStoreDialogProc_00407340_ProductWip,
                g_newJourneyStoreFlowFlag_0043b594);
            return 0;

        case 0x472:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            flow_state = 7;
            g_newJourneyStoreFlowFlag_0043b594 = 0;
            active_dialog_proc = OtTrailGameDialogProc_0002dff0_Wip;
            CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00d8),
                main_window,
                OtTrailGameDialogProc_0002dff0_Wip,
                0);
            return 0;

        case 0x473: {
            flow_state = 8;
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            active_dialog_proc = OtInitHuntDialogProc_00014d00_Wip;
            void* hunt_dialog = CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00d9),
                main_window,
                OtInitHuntDialogProc_00014d00_Wip,
                flow_state != 7);
            if (hunt_dialog != 0) {
                PostMessageA(hunt_dialog, 0x0473, 0, 0);
            }
            return 0;
        }

        case 0x474: {
            HuntOutcomeState_004039d0* outcome =
                reinterpret_cast<HuntOutcomeState_004039d0*>(lparam);
            outcome->pounds_allowed = outcome->pounds_obtained;

            if (OtCountLivingPartyMembers_RealCpp(g_journeyState) >= 2 &&
                static_cast<unsigned int>(outcome->pounds_allowed) >= 201) {
                outcome->pounds_allowed = 200;
            } else if (OtCountLivingPartyMembers_RealCpp(g_journeyState) == 1 &&
                       static_cast<unsigned int>(outcome->pounds_allowed) > 100) {
                outcome->pounds_allowed = 100;
            }

            int stored_food = static_cast<short>(
                g_journeyState->food_from_plants +
                g_journeyState->food_from_hunting);
            if (static_cast<unsigned int>(
                    outcome->pounds_allowed + stored_food) < 2001) {
                outcome->pounds_kept = outcome->pounds_allowed;
            } else {
                outcome->pounds_kept = 2000 - stored_food;
            }

            DialogBoxParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00e6),
                main_window,
                OtHuntResultsDialogProc_000023b0_Wip,
                lparam);

            g_journeyState->ammunition = static_cast<short>(
                g_journeyState->ammunition -
                static_cast<short>(outcome->ammunition_used));
            short new_hunted_food = static_cast<short>(
                g_journeyState->food_from_hunting +
                static_cast<short>(outcome->pounds_kept));
            if (static_cast<int>(g_journeyState->food_from_plants) +
                    static_cast<int>(new_hunted_food) < 2001) {
                g_journeyState->food_from_hunting = new_hunted_food;
            } else {
                g_journeyState->food_from_hunting = static_cast<short>(
                    2000 - g_journeyState->food_from_plants);
            }

            if (outcome->pounds_obtained != 0) {
                g_journeyState->current_hunt_region =
                    g_journeyState->hunt_region;
            }
            OtRecordHuntOutcomeMessage_00002fc0_Product(outcome);
            flow_state = 7;
            return 0;
        }

        case 0x475: {
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            flow_state = 9;
            active_dialog_proc = OtRaftingDialogProc_00027340_Wip;
            void* rafting_dialog = CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00da),
                main_window,
                OtRaftingDialogProc_00027340_Wip,
                0);
            if (rafting_dialog != 0) {
                PostMessageA(rafting_dialog, 0x0475, 0, 0);
            }
            return 0;
        }

        case 0x476:
            if (OtCountLivingPartyMembers_RealCpp(g_journeyState) > 0) {
                PostMessageA(main_window, 0x047b, 0, 0);
            } else {
                PostMessageA(main_window, 0x047d, 0, 0);
            }
            return 0;

        case 0x478:
            captured_interaction_window = reinterpret_cast<void*>(wparam);
            flow_state = 10;
            return 0;

        case 0x479:
            flow_state = 7;
            captured_interaction_window = 0;
            return 0;

        case 0x47b:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            flow_state = 0x0b;
            active_dialog_proc =
                OtWillametteValleyArrivalDialogProc_0000fee0_Wip;
            CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00db),
                main_window,
                OtWillametteValleyArrivalDialogProc_0000fee0_Wip,
                0);
            return 0;

        case 0x47c:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            flow_state = 0x0c;
            active_dialog_proc =
                OtWillametteValleySummaryDialogProc_00424f50_ProductWip;
            CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00dc),
                main_window,
                OtWillametteValleySummaryDialogProc_00424f50_ProductWip,
                0);
            return 0;

        case 0x47d:
            reinterpret_cast<ActiveScreenDialogState_004034d0*>(this)->
                OtDestroyActiveScreenDialog_Product_004034d0();
            active_dialog_proc = OtDeathDialogProc_00010da0_Wip;
            CreateDialogParamA(
                g_applicationModule_00405a40_20260603,
                reinterpret_cast<const void*>(0x00dd),
                main_window,
                OtDeathDialogProc_00010da0_Wip,
                flow_state);
            flow_state = 0x0d;
            return 0;

        case 0x47f:
            if (flow_state == 2 || flow_state == 0x0c) {
                SendMessageA(
                    g_activeScreenDialogWindow_00404dd0,
                    0x047f,
                    0,
                    0);
            }
            return 0;
        }
    }

    return DefWindowProcA(main_window, message, wparam, lparam);
}

#pragma code_seg()
#pragma optimize("", on)
