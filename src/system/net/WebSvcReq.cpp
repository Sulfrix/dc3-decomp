#include "net/WebSvcReq.h"
#include "HttpReq.h"
#include "macros.h"
#include "obj/Dir.h"
#include "obj/Object.h"
#include "os/Debug.h"
#include "utl/MemMgr.h"
#include "utl/Symbol.h"

WebSvcRequest::WebSvcRequest(const char *c1, const char *c2, Hmx::Object *o)
    : mResponseData(0), mResponseDataLength(0), unk34(this, o), mBaseUrl(c1), mHttpReq(0),
      unk54(0), unk58(c2), mResponseStatusCode(0) {}

WebSvcRequest::~WebSvcRequest() {
    Reset();
    RELEASE(mHttpReq);
}

void WebSvcRequest::Start() {
    MILO_ASSERT(!mResponseData, 0x40);
    MILO_ASSERT(mHttpReq, 0x41);
    mHttpReq->Start();
    unk54 = 1;
}

void WebSvcRequest::CleanUp(bool b) {
    MILO_ASSERT(mHttpReq, 0x16e);
    MILO_ASSERT(!mResponseData, 0x16f);
    if (b) {
        mResponseData = mHttpReq->DetachBuffer();
        mResponseDataLength = mHttpReq->GetBufferSize();
    }
    mResponseStatusCode = mHttpReq->GetStatusCode();
}

void WebSvcRequest::SendCallback(bool b1, bool b2) {
    if (unk34) {
        static WebReqCompleteMsg msg(this, false);
        msg[0] = this;
        msg[1] = b1;
        unk34->Handle(msg, true);
    }
}

void WebSvcRequest::Reset() {
    if (mResponseData) {
        MemFree(mResponseData, __FILE__, 0x32);
        mResponseData = nullptr;
    }
    mResponseDataLength = 0;
    mResponseStatusCode = 0;
    unk54 = 0;
    if (mHttpReq) {
        SetURL(mBaseUrl.c_str());
        mHttpReq->Reset();
    }
}

void WebSvcRequest::Cancel(bool b) {
    unk54 = 2;
    if (b) {
        SendCallback(false, true);
    }
}

void WebSvcRequest::Do() {
    MILO_ASSERT(IsRunning(), 0x77);
    MILO_ASSERT(mHttpReq, 0x78);
    mHttpReq->Do();
}

bool WebSvcRequest::HasFailed() {
    MILO_ASSERT(mHttpReq, 0x81);
    return mHttpReq->HasFailed();
}

bool WebSvcRequest::HasSucceeded() {
    MILO_ASSERT(mHttpReq, 0x88);
    return mHttpReq->HasSucceeded();
}

bool WebSvcRequest::IsRunning() { return unk54 != 1; }

void WebSvcRequest::SetTimeout(unsigned int ui) {
    MILO_ASSERT(mHttpReq, 0x8f);
    mHttpReq->SetTimeout(ui);
}

void WebSvcRequest::OnReqFailed() {
    MILO_ASSERT(HasFailed(), 0x96);
    CleanUp(false);
    if (unk54 != 2) {
        unk54 = 2;
        SendCallback(false, false);
    }
}

void WebSvcRequest::OnReqSucceeded() {
    MILO_ASSERT(HasSucceeded(), 0xa3);
    CleanUp(true);
    if (CheckReqResult()) {
        unk54 = 2;
        SendCallback(true, false);
    } else {
        unk54 = 3;
    }
}

void *WebSvcRequest::GetRequest() {
    MILO_ASSERT(mHttpReq, 0xc4);
    return mHttpReq->GetRequest();
}

void WebSvcRequest::SetHttpReq(HttpReq *req) {
    MILO_ASSERT(!mHttpReq, 0xcb);
    MILO_ASSERT(req, 0xcc);
    mHttpReq = req;
}

void WebSvcRequest::SetUserAgent(const char *c) {
    MILO_ASSERT(mHttpReq, 0x103);
    mHttpReq->SetUserAgent(c);
}

void WebSvcRequest::SetStatusCode(unsigned int ui) {
    MILO_ASSERT(mHttpReq, 300);
    mHttpReq->SetStatusCode(ui);
}

const char *WebSvcRequest::GetHostName() {
    MILO_ASSERT(mHttpReq, 0x134);
    return mHttpReq->GetHostName();
}

unsigned int WebSvcRequest::GetIPAddr() {
    MILO_ASSERT(mHttpReq, 0x13b);
    return mHttpReq->GetIPAddr();
}

const char *WebSvcRequest::GetURL() {
    MILO_ASSERT(mHttpReq, 0x149);
    return mHttpReq->GetURL();
}

void WebSvcRequest::Poll() {
    switch (unk54) {
    case 1: {
        MILO_ASSERT(mHttpReq, 0x53);
        mHttpReq->Poll();
        if (HasFailed()) {
            OnReqFailed();
        } else if (HasSucceeded()) {
            OnReqSucceeded();
        }
        break;
    }
    case 2: {
        if (mHttpReq->IsSafeToDelete()) {
            unk54 = 4;
        }
        break;
    }
    case 0:
    case 3:
    case 4:
        break;
    default:
        int state = unk54;
        MILO_NOTIFY("WebSvcRequest: Unknown state %d", state);
        break;
    }
}

const std::map<String, String> &WebSvcRequest::GetCookies() const { return mCookies; }
void WebSvcRequest::SetCookies(std::map<String, String> const &map) { mCookies = map; }

void WebSvcRequest::SetIPAddr(unsigned int ui) {
    MILO_ASSERT(mHttpReq, 0xe7);
    mHttpReq->SetIPAddr(ui);
}

void WebSvcRequest::SetURL(char const *c) {
    MILO_ASSERT(mHttpReq, 0xfc);
    mHttpReq->SetURL(c);
}

void WebSvcRequest::MarkSuccess() {
    MILO_ASSERT(mHttpReq, 0x15d);
    mHttpReq->MarkSuccess();
}

void WebSvcRequest::MarkFailure() {
    MILO_ASSERT(mHttpReq, 0x15d);
    mHttpReq->MarkFailure();
}
