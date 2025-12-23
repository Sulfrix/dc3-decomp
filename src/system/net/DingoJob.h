#pragma once
#include "net/HttpReq.h"
#include "net/JsonUtils.h"
#include "net/WebSvcReq.h"
#include "obj/Msg.h"
#include "obj/Object.h"
#include "utl/DataPointMgr.h"

class DingoJob : public WebSvcRequest {
public:
    DingoJob(const char *, Hmx::Object *);
    virtual ~DingoJob();
    virtual void Start();
    virtual unsigned int GetResponseDataLength() { return mResponseDataLength; }
    virtual unsigned int GetResponseStatusCode() { return mResponseStatusCode; }
    virtual bool IsWebSvcRequest() const { return false; }
    virtual void SendCallback(bool, bool);

    const char *GetResponseString();

    int mResult; // 0x7c
    DataPoint *mDataPoint; // 0x80
    void *unk84;
    String mResponseStr; // 0x88
    JsonConverter mJsonConverter; // 0x90
    JsonObject *mJsonResponse; // 0xa4
    int unka8; // 0xa8
    int unkac; // 0xac

protected:
    virtual void CleanUp(bool);
    virtual bool CheckReqResult();
    virtual void Reset();
    virtual void StartImpl();
    virtual bool DidCallSucceed() { return true; }
    virtual bool CheckReturned() { return true; }
    virtual void AddContent(HttpReq *);

    void ParseResponse();
    void SetDataPoint(DataPoint const &);

private:
    void ParseResponse(JsonConverter *, JsonObject **, int *);
};

DECLARE_MESSAGE(DingoJobCompleteMsg, "dingo_job_complete")
DingoJobCompleteMsg(DingoJob *dj, bool b) : Message(Type(), dj, b) {}
END_MESSAGE
