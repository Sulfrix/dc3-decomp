#pragma once
#include "net/WebSvcReq.h"
#include "obj/Data.h"
#include "obj/Object.h"
#include "os/NetworkSocket.h"

class WebSvcMgr : public Hmx::Object {
public:
    WebSvcMgr();
    virtual ~WebSvcMgr();
    virtual DataNode Handle(DataArray *, bool);
    virtual void Init();
    virtual void Poll();
    virtual bool DoRequest(
        ReqType,
        unsigned int,
        unsigned short,
        const char *,
        const char *,
        unsigned int,
        const char *,
        unsigned int
    ) = 0;
    virtual void OnReqFinished(WebSvcRequest *);
    virtual bool InitRequest(
        WebSvcRequest *, ReqType, unsigned int, unsigned short, const char *, unsigned int
    ) = 0;
    virtual bool InitRequest(
        WebSvcRequest *, ReqType, const char *, unsigned short, const char *, unsigned int
    ) = 0;
    virtual int NumRequestsStarted();
    virtual int NumRequests();

    void CancelOutstandingCalls();
    bool AddRequest(WebSvcRequest *, unsigned int, bool, bool);

private:
    bool ResolveHostname(WebSvcRequest *);

protected:
    virtual void Start(WebSvcRequest *);
    NetAddress ResolveHostname(const char *, const char *, unsigned short);

    std::list<WebSvcRequest *> unk2c; // 0x2c
    std::map<String, NetAddress> unk34; // 0x34
};

extern WebSvcMgr &TheWebSvcMgr;
extern const char *kHMXDomain;
