#include "net/WebSvcMgr.h"
#include "net/WebSvcReq.h"
#include "obj/Dir.h"
#include "os/Debug.h"
#include "os/NetworkSocket.h"

const char *kHMXDomain = "harmonixmusic.com";

WebSvcMgr::WebSvcMgr() {}

WebSvcMgr::~WebSvcMgr() { DeleteAll(unk2c); }

BEGIN_HANDLERS(WebSvcMgr)
END_HANDLERS

void WebSvcMgr::Init() { SetName("web_svc_mgr", ObjectDir::Main()); }

void WebSvcMgr::OnReqFinished(WebSvcRequest *req) {
    MILO_ASSERT(req, 0x181);
    MILO_ASSERT(req->IsDeleteReady(), 0x182);
    delete req;
}

int WebSvcMgr::NumRequestsStarted() {
    int listSize = unk2c.size();
    int num = 0;
    FOREACH (it, unk2c) {
        WebSvcRequest *cur = *it;
        if (cur->StateZero()) {
            num++;
        }
    }
    return listSize - num;
}

int WebSvcMgr::NumRequests() { return unk2c.size(); }

void WebSvcMgr::Start(WebSvcRequest *req) { req->Start(); }

void WebSvcMgr::CancelOutstandingCalls() {
    FOREACH (it, unk2c) {
        WebSvcRequest *cur = *it;
        if (!cur->IsWebSvcRequest() && (cur->StateZero() || cur->StateOne())) {
            cur->Cancel(true);
        }
    }
}

bool WebSvcMgr::AddRequest(WebSvcRequest *req, unsigned int ui, bool b3, bool b4) {
    MILO_ASSERT(req, 0xD7);
    if (b4 && !ResolveHostname(req)) {
        req->Cancel(true);
        return false;
    }
    req->SetTimeout(ui);
    if (b3) {
        unk2c.push_front(req);
    } else {
        unk2c.push_back(req);
    }
    return true;
}

bool WebSvcMgr::ResolveHostname(WebSvcRequest *req) {
    unsigned int ip = req->GetIPAddr();
    if (ip == 0) {
        NetAddress addr = ResolveHostname(req->GetHostName(), kHMXDomain, 0x50);
        if (addr.mIP == 0) {
            addr = ResolveHostname(req->GetHostName(), nullptr, 0x50);
            if (addr.mIP == 0) {
                return false;
            }
        }
        req->UpdateIP(addr.mIP);
    }
    return true;
}

NetAddress WebSvcMgr::ResolveHostname(const char *c1, const char *c2, unsigned short us) {
    NetAddress ret;
    String str(c1);
    if (c2) {
        str += ".";
        str += c2;
    }
    auto it = unk34.find(str.c_str());
    if (it != unk34.end()) {
        ret = it->second;
    } else {
        ret = NetworkSocket::SetIPPortFromHostPort(c1, c2, us);
    }
    if (ret.mIP != 0 && it == unk34.end()) {
        unk34.insert(std::make_pair(str, ret));
    }
    return ret;
}
