#include "net/XLSPConnection.h"
#include "utl/MemMgr.h"
#include "xdk/XAPILIB.h"
#include "xdk/XNET.h"
#include "xdk/XONLINE.h"
#include <utility>

const int XLSPConnection::kTitleServerEnumMaxCount = 8;
std::map<unsigned long, int> XLSPConnection::mXLSPRefCountMap;

XLSPConnection::XLSPConnection()
    : unk4((State)-1), unk8(0), unk14(0), unk18(INVALID_HANDLE_VALUE), unk1c(0),
      unk20(0) {
    memset(&mXOverlapped, 0, sizeof(XOVERLAPPED));
    unk44 = 0;
    unk48.Reset();
    SetState((State)0);
}

XLSPConnection::~XLSPConnection() { SetState((State)-1); }

int XLSPConnection::ThreadStart() {
    if (unk4 != 5) {
        MILO_FAIL("Unhandled state %d in ThreadStart", unk4);
    } else {
        XCancelOverlapped(&mXOverlapped);
    }
    return 0;
}

void XLSPConnection::ThreadDone(int i1) {
    if (unk4 != 5) {
        MILO_FAIL("Unhandled state %d in ThreadStart", unk4);
    } else {
        memset(&mXOverlapped, 0, sizeof(XOVERLAPPED));
        CloseHandle(unk18);
        unk20 = 0;
        unk18 = INVALID_HANDLE_VALUE;
        if (unk1c) {
            MemFree(unk1c, __FILE__, 299);
            unk1c = nullptr;
        }
        SetState((State)0);
    }
}

void XLSPConnection::Connect(const char *cc, unsigned int ui) {
    unkc = cc;
    unk14 = ui;
    if (unk8 != 3) {
        unk8 = 3;
    }
    if (unk4 == 0) {
        SetState((State)1);
    }
}

void XLSPConnection::Disconnect() {
    if (unk8 != 0) {
        unk8 = 0;
    }
    if (unk4 > 0 && unk4 <= 4) {
        SetState((State)5);
    }
}

void XLSPConnection::StartEnumeration() {
    DWORD res = XTitleServerCreateEnumerator(unkc.c_str(), 8, &unk20, &unk18);
    if (res != ERROR_SUCCESS) {
        MILO_NOTIFY("XTitleServerCreateEnumerator failed with error %d", res);
        SetState((State)4);
    } else {
        unk1c = _MemAllocTemp(unk20, __FILE__, 0x1CB, "XLSPConnection", 0);
        res = XEnumerate(unk18, unk1c, unk20, nullptr, &mXOverlapped);
        if (res != ERROR_IO_PENDING) {
            MILO_NOTIFY("XEnumerate failed with error %d", res);
            SetState((State)4);
        }
    }
}

bool XLSPConnection::SecureDisconnect(in_addr a) {
    bool ret = true;
    auto it = mXLSPRefCountMap.find(a.s_un.s_addr);
    if (it != mXLSPRefCountMap.end()) {
        it->second--;
        if (it->second == 0) {
            mXLSPRefCountMap.erase(it);
            if (XNetGetConnectStatus(a) != 3) {
                XNetUnregisterInAddr(a);
            }
        }
    } else {
        ret = false;
        MILO_NOTIFY("XLSPConnection::SecureDisconnect() - connection not found!");
    }
    return ret;
}

int XLSPConnection::StartGatewayConnection(in_addr a) {
    int ret;
    auto it = mXLSPRefCountMap.find(a.s_un.s_addr);
    if (it != mXLSPRefCountMap.end()) {
        ret = 0;
        it->second++;
    } else {
        ret = XNetConnect(a);
        if (ret == 0) {
            mXLSPRefCountMap.insert(std::make_pair(a.s_un.s_addr, 1));
        } else {
            MILO_NOTIFY(
                "XNetConnect(%d.%d.%d.%d) failed with %d",
                a.s_un.s_un_b.s_b1,
                a.s_un.s_un_b.s_b2,
                a.s_un.s_un_b.s_b3,
                a.s_un.s_un_b.s_b4,
                ret
            );
        }
    }
    return ret;
}
