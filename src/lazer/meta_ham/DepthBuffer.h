#pragma once
#include "obj/Data.h"
#include "obj/Object.h"
#include "ui/UIPanel.h"

class DepthBuffer : public Hmx::Object {
public:
    enum State {
        kDepthBuffer_Normal = 0
    };
    DepthBuffer();
    virtual ~DepthBuffer() {}
    virtual DataNode Handle(DataArray *, bool);

    void Init(UIPanel *);
    void Poll();

    void SetState(int state) {
        if (state != mState) {
            mState = (State)state;
        }
    }

private:
    UIPanel *unk2c; // 0x2c
    State mState; // 0x30
    bool unk34;
};
