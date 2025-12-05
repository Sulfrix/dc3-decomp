#pragma once
#include "obj/Object.h"
#include "os/File.h"
#include "rndobj/Movie.h"
#include "rndobj/SIVideo.h"

class DxMovie : public RndMovie {
public:
    DxMovie();
    virtual ~DxMovie();
    OBJ_CLASSNAME(Movie);
    OBJ_SET_TYPE(Movie);
    virtual void SetFrame(float frame, float blend);
    virtual float EndFrame() { return mVideo.NumFrames(); }
    virtual void SetFile(const FilePath &, bool);
    virtual void SetTex(RndTex *tex);

    NEW_OBJ(DxMovie)

private:
    void StreamReadFinish();
    void Update();
    int StreamChunkSize();
    void StreamNextBuffer();
    void StreamRestart(int);

    SIVideo mVideo; // 0x30
    void *unk44;
    int unk48;
    File *unk4c; // 0x4c
    int unk50;
    int unk54;
    void *unk58;
};
