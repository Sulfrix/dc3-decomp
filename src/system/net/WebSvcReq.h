#pragma once
#include "HttpReq.h"
#include "obj/Dir.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "os/NetworkSocket.h"
#include "utl/Symbol.h"

class WebSvcRequest : public Hmx::Object {
public:
    WebSvcRequest(const char *, const char *, Hmx::Object *);
    virtual ~WebSvcRequest();
    virtual void Start();
    virtual char *GetResponseData() { return mResponseData; }
    virtual unsigned int GetResponseDataLength() { return mResponseDataLength; }
    virtual unsigned int GetResponseStatusCode() { return mResponseStatusCode; }
    virtual bool IsWebSvcRequest() const { return true; }

    void Cancel(bool);
    void Do();
    bool HasFailed();
    bool HasSucceeded();
    bool IsRunning();
    void SetTimeout(unsigned int);
    void OnReqFailed();
    void OnReqSucceeded();
    void *GetRequest();
    void SetHttpReq(HttpReq *);
    void SetUserAgent(char const *);
    void SetStatusCode(unsigned int);
    char const *GetHostName();
    unsigned int GetIPAddr();
    char const *GetURL();
    void Poll();
    void SetCookies(std::map<String, String> const &);
    const std::map<String, String> &GetCookies() const;
    bool IsDeleteReady() const { return unk54 == 4; }
    bool StateZero() const { return unk54 == 0; } // rename once context known
    bool StateOne() const { return unk54 == 1; }
    void UpdateIP(unsigned int ip) { SetIPAddr(ip); }

protected:
    virtual void CleanUp(bool);
    virtual void SendCallback(bool, bool);
    virtual bool CheckReqResult() { return true; }
    virtual void Reset();
    virtual bool MustFinishBeforeNext() { return false; }

    void SetIPAddr(unsigned int);
    void SetURL(char const *);
    void MarkSuccess();
    void MarkFailure();

    char *mResponseData; // 0x2c
    unsigned int mResponseDataLength; // 0x30
    ObjPtr<Hmx::Object> unk34; // 0x34
    String mBaseUrl; // 0x48
    HttpReq *mHttpReq; // 0x50
    int unk54; // 0x54
    String unk58; // 0x58
    unsigned int mResponseStatusCode; // 0x60
    std::map<String, String> mCookies; // 0x64
};

DECLARE_MESSAGE(WebReqCompleteMsg, "web_req_complete")
WebReqCompleteMsg(WebSvcRequest *r, bool b) : Message(Type(), r, b) {}
END_MESSAGE
