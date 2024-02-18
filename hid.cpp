#include <Windows.h>
#include <pshpack4.h>
#include <iostream>
#include <fstream>
#include <cstdint>

#define HIDP_STATUS_SUCCESS (0x11 << 16)
struct HIDP_PREPARSED_DATA;

struct HIDD_ATTRIBUTES {
  ULONG Size; // = sizeof (struct _HIDD_ATTRIBUTES)
  USHORT VendorID;
  USHORT ProductID;
  USHORT VersionNumber;
};

typedef struct _HIDD_CONFIGURATION {
  PVOID  cookie;
  ULONG  size;
  ULONG  RingBufferSize;
} HIDD_CONFIGURATION, *PHIDD_CONFIGURATION;

struct HIDP_CAPS {
  USHORT Usage;
  USHORT UsagePage;
  USHORT InputReportByteLength;
  USHORT OutputReportByteLength;
  USHORT FeatureReportByteLength;
  USHORT Reserved[17];

  USHORT NumberLinkCollectionNodes;
  USHORT NumberInputButtonCaps;
  USHORT NumberInputValueCaps;
  USHORT NumberInputDataIndices;
  USHORT NumberOutputButtonCaps;
  USHORT NumberOutputValueCaps;
  USHORT NumberOutputDataIndices;
  USHORT NumberFeatureButtonCaps;
  USHORT NumberFeatureValueCaps;
  USHORT NumberFeatureDataIndices;
};
typedef enum _HIDP_REPORT_TYPE {
  HidP_Input, HidP_Output, HidP_Feature
} HIDP_REPORT_TYPE;

typedef uint16_t USAGE;

typedef struct _HIDP_BUTTON_CAPS {
  USAGE UsagePage;
  UCHAR ReportID;
  BOOLEAN IsAlias;
  USHORT BitField;
  USHORT LinkCollection;
  USAGE LinkUsage;
  USAGE LinkUsagePage;
  BOOLEAN IsRange;
  BOOLEAN IsStringRange;
  BOOLEAN IsDesignatorRange;
  BOOLEAN IsAbsolute;
  ULONG Reserved[10];
  union {
    struct {
      USAGE UsageMin;
      USAGE UsageMax;
      USHORT StringMin;
      USHORT StringMax;
      USHORT DesignatorMin;
      USHORT DesignatorMax;
      USHORT DataIndexMin;
      USHORT DataIndexMax;
    } Range;
    struct {
      USAGE Usage;
      USAGE Reserved1;
      USHORT StringIndex;
      USHORT Reserved2;
      USHORT DesignatorIndex;
      USHORT Reserved3;
      USHORT DataIndex;
      USHORT Reserved4;
    } NotRange;
  };
} HIDP_BUTTON_CAPS, *PHIDP_BUTTON_CAPS;

typedef void * PHIDP_PREPARSED_DATA;
typedef void * PHIDP_LINK_COLLECTION_NODE;
typedef void * PHIDP_DATA;
typedef void * PHIDP_EXTENDED_ATTRIBUTES;
typedef void * PHIDP_VALUE_CAPS;
typedef void * PHIDP_KEYBOARD_MODIFIER_STATE;
typedef void * PHIDP_INSERT_SCANCODES;
typedef uint32_t USAGE_AND_PAGE;
typedef USAGE * PUSAGE;
typedef USAGE_AND_PAGE * PUSAGE_AND_PAGE;
typedef enum _HIDP_KEYBOARD_DIRECTION {
  HidP_Keyboard_Break, HidP_Keyboard_Make
} HIDP_KEYBOARD_DIRECTION;
typedef void * PHID_MINIDRIVER_REGISTRATION;
// Macros to declare and resolve needed functions from library.
#define OVR_DECLARE_HIDFUNC(func, rettype, args)   \
typedef rettype (__stdcall *PFn_##func) args;  \
PFn_##func      Real_##func;
#define OVR_RESOLVE_HIDFUNC(func) \
Real_##func = (PFn_##func)::GetProcAddress(hHidLib, #func)

OVR_DECLARE_HIDFUNC(HidD_FlushQueue, BOOLEAN, (HANDLE hidDev));
OVR_DECLARE_HIDFUNC(HidD_FreePreparsedData, BOOLEAN, (HIDP_PREPARSED_DATA *preparsedData));
OVR_DECLARE_HIDFUNC(HidD_GetHidGuid, void, (GUID *hidGuid));
OVR_DECLARE_HIDFUNC(HidD_GetIndexedString, BOOLEAN, (HANDLE hidDev, ULONG strIndex, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetInputReport, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetFeature, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetAttributes, BOOLEAN, (HANDLE hidDev, HIDD_ATTRIBUTES *attributes));
OVR_DECLARE_HIDFUNC(HidD_GetConfiguration, BOOLEAN, (HANDLE hidDev, PHIDD_CONFIGURATION config, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetManufacturerString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetNumInputBuffers, BOOLEAN, (HANDLE hidDev, PULONG numberBuffers));
OVR_DECLARE_HIDFUNC(HidD_GetPhysicalDescriptor, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetPreparsedData, BOOLEAN, (HANDLE hidDev, HIDP_PREPARSED_DATA **preparsedData));
OVR_DECLARE_HIDFUNC(HidD_GetProductString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_GetSerialNumberString, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_Hello, ULONG, (PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_SetConfiguration, BOOLEAN, (HANDLE hidDev, PHIDD_CONFIGURATION config, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_SetFeature, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));
OVR_DECLARE_HIDFUNC(HidD_SetNumInputBuffers, BOOLEAN, (HANDLE hidDev, ULONG numberBuffers));
OVR_DECLARE_HIDFUNC(HidD_SetOutputReport, BOOLEAN, (HANDLE hidDev, PVOID buffer, ULONG bufferLength));

OVR_DECLARE_HIDFUNC(HidP_GetCaps, NTSTATUS, (HIDP_PREPARSED_DATA *preparsedData, HIDP_CAPS* caps));
OVR_DECLARE_HIDFUNC(HidP_GetData, NTSTATUS, (HIDP_REPORT_TYPE ReportType, PHIDP_DATA DataList, PULONG DataLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_GetExtendedAttributes, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USHORT DataIndex, PHIDP_PREPARSED_DATA PreparsedData, PHIDP_EXTENDED_ATTRIBUTES Attributes, PULONG LengthAttributes));
OVR_DECLARE_HIDFUNC(HidP_GetLinkCollectionNodes, NTSTATUS, (PHIDP_LINK_COLLECTION_NODE LinkCollectionNodes, PULONG LinkCollectionNodesLength, PHIDP_PREPARSED_DATA PreparsedData));
OVR_DECLARE_HIDFUNC(HidP_GetScaledUsageValue, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PLONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_GetSpecificButtonCaps, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PHIDP_BUTTON_CAPS ButtonCaps, PUSHORT ButtonCapsLength, PHIDP_PREPARSED_DATA PreparsedData));
OVR_DECLARE_HIDFUNC(HidP_GetSpecificValueCaps, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PHIDP_VALUE_CAPS ValueCaps, PUSHORT ValueCapsLength, PHIDP_PREPARSED_DATA PreparsedData));
OVR_DECLARE_HIDFUNC(HidP_GetUsages, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_GetUsagesEx, NTSTATUS, (HIDP_REPORT_TYPE ReportType ,USHORT LinkCollection, PUSAGE_AND_PAGE ButtonList, ULONG * UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_GetUsageValue, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PULONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_GetUsageValueArray, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PCHAR UsageValue, USHORT UsageValueByteLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_InitializeReportForID, NTSTATUS, (HIDP_REPORT_TYPE ReportType, UCHAR ReportID, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_MaxDataListLength, NTSTATUS, (HIDP_REPORT_TYPE ReportType, PHIDP_PREPARSED_DATA PreparsedData));
OVR_DECLARE_HIDFUNC(HidP_MaxUsageListLength, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, PHIDP_PREPARSED_DATA PreparsedData));
OVR_DECLARE_HIDFUNC(HidP_SetData, NTSTATUS, (HIDP_REPORT_TYPE ReportType, PHIDP_DATA DataList, PULONG DataLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_SetScaledUsageValue, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, LONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_SetUsages, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_SetUsageValue, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, ULONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_SetUsageValueArray, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PCHAR UsageValue, USHORT UsageValueByteLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_TranslateUsagesToI8042ScanCodes, NTSTATUS, (PUSAGE ChangedUsageList, ULONG UsageListLength, HIDP_KEYBOARD_DIRECTION KeyAction, PHIDP_KEYBOARD_MODIFIER_STATE ModifierState, PHIDP_INSERT_SCANCODES InsertCodesProcedure, PVOID InsertCodesContext));
OVR_DECLARE_HIDFUNC(HidP_UnsetUsages, NTSTATUS, (HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength));
OVR_DECLARE_HIDFUNC(HidP_UsageListDifference, NTSTATUS, (PUSAGE PreviousUsageList, PUSAGE CurrentUsageList, PUSAGE BreakUsageList, PUSAGE MakeUsageList, ULONG UsageListLength));

using namespace std;


void log(const string & s) {
  ofstream of("f:\\hid.txt", ios::app);
  of << GetTickCount() << " " << s.c_str() << endl;
  of.close();
}

void log(const string & s, HANDLE handle, PVOID data, ULONG length) {
  ofstream of("f:\\hid.txt", ios::app);
  of << GetTickCount() << " " << s.c_str() << " " << handle << " \n";
  of << "Buffer length: " << length << "\n";
  of << "{\n";
  uint8_t * b = (uint8_t *)data;
  static char buffer[64];
  memset(buffer, 0, 64);
  while (length) {
    for (int i = 0; i < 16 && length; ++i) {
      sprintf(buffer + (3 * i), "%02X ", *b++);
      --length;
    }
    of << buffer << "\n";
  }
  of << "}" << endl;
  of.close();
}

extern "C" {

__declspec(dllexport) void __stdcall HidD_GetHidGuid(GUID *hidGuid) {
  log("HidD_GetHidGuid");
  Real_HidD_GetHidGuid(hidGuid);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_SetNumInputBuffers(HANDLE hidDev, ULONG numberBuffers) {
  log("HidD_SetNumInputBuffers");
  return Real_HidD_SetNumInputBuffers(hidDev, numberBuffers);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_GetFeature(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  BOOLEAN result = Real_HidD_GetFeature(hidDev, buffer, bufferLength);
  log("HidD_GetFeature", hidDev, buffer, bufferLength);
  return result;
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_SetFeature(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  log("HidD_SetFeature", hidDev, buffer, bufferLength);
  return Real_HidD_SetFeature(hidDev, buffer, bufferLength);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_GetAttributes(HANDLE hidDev, HIDD_ATTRIBUTES *attributes) {
  log("HidD_GetAttributes");
  return Real_HidD_GetAttributes(hidDev, attributes);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_GetManufacturerString(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  log("HidD_GetManufacturerString");
  return Real_HidD_GetManufacturerString(hidDev, buffer, bufferLength);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_GetProductString(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  log("HidD_GetProductString");
  return Real_HidD_GetProductString(hidDev, buffer, bufferLength);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_GetSerialNumberString(HANDLE hidDev, PVOID buffer, ULONG bufferLength) {
  log("HidD_GetSerialNumberString");
  return Real_HidD_GetSerialNumberString(hidDev, buffer, bufferLength);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_GetPreparsedData(HANDLE hidDev, HIDP_PREPARSED_DATA **preparsedData) {
  log("HidD_GetPreparsedData");
  return Real_HidD_GetPreparsedData(hidDev, preparsedData);
}

__declspec(dllexport)  BOOLEAN __stdcall HidD_FreePreparsedData(HIDP_PREPARSED_DATA *preparsedData) {
  log("HidD_FreePreparsedData");
  return Real_HidD_FreePreparsedData(preparsedData);
}


__declspec(dllexport)  NTSTATUS __stdcall HidP_GetCaps(HIDP_PREPARSED_DATA *preparsedData, HIDP_CAPS* caps) {
  log(__FUNCTION__);
  return Real_HidP_GetCaps(preparsedData, caps);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetData(HIDP_REPORT_TYPE ReportType, PHIDP_DATA DataList, PULONG DataLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_GetData(ReportType, DataList, DataLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetExtendedAttributes(HIDP_REPORT_TYPE ReportType, USHORT DataIndex, PHIDP_PREPARSED_DATA PreparsedData, PHIDP_EXTENDED_ATTRIBUTES Attributes, PULONG LengthAttributes) {
  log(__FUNCTION__);
  return Real_HidP_GetExtendedAttributes(ReportType, DataIndex, PreparsedData, Attributes, LengthAttributes);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetLinkCollectionNodes(PHIDP_LINK_COLLECTION_NODE LinkCollectionNodes, PULONG LinkCollectionNodesLength, PHIDP_PREPARSED_DATA PreparsedData) {
  log(__FUNCTION__);
  return Real_HidP_GetLinkCollectionNodes(LinkCollectionNodes, LinkCollectionNodesLength, PreparsedData);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetScaledUsageValue(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PLONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_GetScaledUsageValue(ReportType, UsagePage, LinkCollection, Usage, UsageValue, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetSpecificButtonCaps(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PHIDP_BUTTON_CAPS ButtonCaps, PUSHORT ButtonCapsLength, PHIDP_PREPARSED_DATA PreparsedData) {
  log(__FUNCTION__);
  return Real_HidP_GetSpecificButtonCaps(ReportType, UsagePage, LinkCollection, Usage, ButtonCaps, ButtonCapsLength, PreparsedData);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetSpecificValueCaps(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PHIDP_VALUE_CAPS ValueCaps, PUSHORT ValueCapsLength, PHIDP_PREPARSED_DATA PreparsedData) {
  log(__FUNCTION__);
  return Real_HidP_GetSpecificValueCaps(ReportType, UsagePage, LinkCollection, Usage, ValueCaps, ValueCapsLength, PreparsedData);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetUsages(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_GetUsages(ReportType, UsagePage, LinkCollection, UsageList, UsageLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetUsagesEx(HIDP_REPORT_TYPE ReportType ,USHORT LinkCollection, PUSAGE_AND_PAGE ButtonList, ULONG * UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_GetUsagesEx(ReportType, LinkCollection, ButtonList, UsageLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetUsageValue(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PULONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_GetUsageValue(ReportType, UsagePage, LinkCollection, Usage, UsageValue, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_GetUsageValueArray(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PCHAR UsageValue, USHORT UsageValueByteLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_GetUsageValueArray(ReportType, UsagePage, LinkCollection, Usage, UsageValue, UsageValueByteLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_InitializeReportForID(HIDP_REPORT_TYPE ReportType, UCHAR ReportID, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_InitializeReportForID(ReportType, ReportID, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_MaxDataListLength(HIDP_REPORT_TYPE ReportType, PHIDP_PREPARSED_DATA PreparsedData) {
  log(__FUNCTION__);
  return Real_HidP_MaxDataListLength(ReportType, PreparsedData);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_MaxUsageListLength(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, PHIDP_PREPARSED_DATA PreparsedData) {
  log(__FUNCTION__);
  return Real_HidP_MaxUsageListLength(ReportType, UsagePage, PreparsedData);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_SetData(HIDP_REPORT_TYPE ReportType, PHIDP_DATA DataList, PULONG DataLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_SetData(ReportType, DataList, DataLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_SetScaledUsageValue(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, LONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_SetScaledUsageValue(ReportType, UsagePage, LinkCollection, Usage, UsageValue, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_SetUsages(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_SetUsages(ReportType, UsagePage, LinkCollection, UsageList, UsageLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_SetUsageValue(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, ULONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_SetUsageValue(ReportType, UsagePage, LinkCollection, Usage, UsageValue, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_SetUsageValueArray(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PCHAR UsageValue, USHORT UsageValueByteLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_SetUsageValueArray(ReportType, UsagePage, LinkCollection, Usage, UsageValue, UsageValueByteLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_TranslateUsagesToI8042ScanCodes(PUSAGE ChangedUsageList, ULONG UsageListLength, HIDP_KEYBOARD_DIRECTION KeyAction, PHIDP_KEYBOARD_MODIFIER_STATE ModifierState, PHIDP_INSERT_SCANCODES InsertCodesProcedure, PVOID InsertCodesContext) {
  log(__FUNCTION__);
  return Real_HidP_TranslateUsagesToI8042ScanCodes(ChangedUsageList, UsageListLength, KeyAction, ModifierState, InsertCodesProcedure, InsertCodesContext);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_UnsetUsages(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength) {
  log(__FUNCTION__);
  return Real_HidP_UnsetUsages(ReportType, UsagePage, LinkCollection, UsageList, UsageLength, PreparsedData, Report, ReportLength);
}

__declspec(dllexport)  NTSTATUS __stdcall HidP_UsageListDifference(PUSAGE PreviousUsageList, PUSAGE CurrentUsageList, PUSAGE BreakUsageList, PUSAGE MakeUsageList, ULONG UsageListLength) {
  log(__FUNCTION__);
  return Real_HidP_UsageListDifference(PreviousUsageList, CurrentUsageList, BreakUsageList, MakeUsageList, UsageListLength);
}

}

HMODULE hHidLib = NULL;

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
  if (NULL != hHidLib) {
    return TRUE;
  }
  hHidLib = ::LoadLibraryA("C:\\Windows\\System32\\hid.dll");
  OVR_RESOLVE_HIDFUNC(HidD_FlushQueue);
  OVR_RESOLVE_HIDFUNC(HidD_FreePreparsedData);
  OVR_RESOLVE_HIDFUNC(HidD_GetAttributes);
  OVR_RESOLVE_HIDFUNC(HidD_GetConfiguration);
  OVR_RESOLVE_HIDFUNC(HidD_GetFeature);
  OVR_RESOLVE_HIDFUNC(HidD_GetHidGuid);
  OVR_RESOLVE_HIDFUNC(HidD_GetIndexedString);
  OVR_RESOLVE_HIDFUNC(HidD_GetInputReport);
  OVR_RESOLVE_HIDFUNC(HidD_GetManufacturerString);
  OVR_RESOLVE_HIDFUNC(HidD_GetNumInputBuffers);
  OVR_RESOLVE_HIDFUNC(HidD_GetPhysicalDescriptor);
  OVR_RESOLVE_HIDFUNC(HidD_GetPreparsedData);
  OVR_RESOLVE_HIDFUNC(HidD_GetProductString);
  OVR_RESOLVE_HIDFUNC(HidD_GetSerialNumberString);
  OVR_RESOLVE_HIDFUNC(HidD_Hello);
  OVR_RESOLVE_HIDFUNC(HidD_SetConfiguration);
  OVR_RESOLVE_HIDFUNC(HidD_SetFeature);
  OVR_RESOLVE_HIDFUNC(HidD_SetNumInputBuffers);
  OVR_RESOLVE_HIDFUNC(HidD_SetOutputReport);

  OVR_RESOLVE_HIDFUNC(HidP_GetCaps);
  OVR_RESOLVE_HIDFUNC(HidP_GetData);
  OVR_RESOLVE_HIDFUNC(HidP_GetExtendedAttributes);
  OVR_RESOLVE_HIDFUNC(HidP_GetLinkCollectionNodes);
  OVR_RESOLVE_HIDFUNC(HidP_GetScaledUsageValue);
  OVR_RESOLVE_HIDFUNC(HidP_GetSpecificButtonCaps);
  OVR_RESOLVE_HIDFUNC(HidP_GetSpecificValueCaps);
  OVR_RESOLVE_HIDFUNC(HidP_GetUsages);
  OVR_RESOLVE_HIDFUNC(HidP_GetUsagesEx);
  OVR_RESOLVE_HIDFUNC(HidP_GetUsageValue);
  OVR_RESOLVE_HIDFUNC(HidP_GetUsageValueArray);
  OVR_RESOLVE_HIDFUNC(HidP_InitializeReportForID);
  OVR_RESOLVE_HIDFUNC(HidP_MaxDataListLength);
  OVR_RESOLVE_HIDFUNC(HidP_MaxUsageListLength);
  OVR_RESOLVE_HIDFUNC(HidP_SetData);
  OVR_RESOLVE_HIDFUNC(HidP_SetScaledUsageValue);
  OVR_RESOLVE_HIDFUNC(HidP_SetUsages);
  OVR_RESOLVE_HIDFUNC(HidP_SetUsageValue);
  OVR_RESOLVE_HIDFUNC(HidP_SetUsageValueArray);
  OVR_RESOLVE_HIDFUNC(HidP_TranslateUsagesToI8042ScanCodes);
  OVR_RESOLVE_HIDFUNC(HidP_UnsetUsages);
  OVR_RESOLVE_HIDFUNC(HidP_UsageListDifference);
  log("Loaded");
  return TRUE;
}
