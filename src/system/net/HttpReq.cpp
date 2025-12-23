#include "net/HttpReq.h"
#include "macros.h"

HttpReq::HttpReq(ReqType r, unsigned int ui, unsigned short us, char const *c)
    : mHostName(), mIPAddr(ui), mPort(us), mURL(c), mType(r), mContent(0),
      mContentLength(0), mStatusCode(0), unk4c(-1) {}

HttpReq::HttpReq(ReqType r, char const *c1, unsigned short us, char const *c2)
    : mHostName(c1), mIPAddr(0), mPort(us), mURL(c2), mType(r), mContent(0),
      mContentLength(0), mStatusCode(0), unk4c(-1) {}

HttpReq::~HttpReq() { RELEASE(mContent); }

void HttpReq::Reset() {
    unk4c = -1;
    mStatusCode = 0;
}

bool HttpReq::HasFailed() { return unk4c == 4; }

bool HttpReq::HasSucceeded() { return unk4c == 3; }

unsigned int HttpReq::GetStatusCode() { return mStatusCode; }
