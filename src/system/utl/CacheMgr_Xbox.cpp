#include "utl/CacheMgr_Xbox.h"
#include "CacheMgr.h"
#include "xdk/XAPILIB.h"

bool IsDeviceConnected(DWORD deviceID) {
    return XContentGetDeviceState(deviceID, nullptr) == 0;
}
