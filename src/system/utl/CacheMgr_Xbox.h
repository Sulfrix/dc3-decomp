#pragma once
#include "utl/CacheMgr.h"
#include "xdk/win_types.h"

// size 0x18c
class CacheMgrXbox : public CacheMgr {
public:
    CacheMgrXbox();
    virtual ~CacheMgrXbox();
    virtual void Poll();
    virtual bool SearchAsync(char const *, CacheID **);
    virtual bool
    ShowUserSelectUIAsync(LocalUser *, u64, char const *, char const *, CacheID **);
    virtual bool
    CreateCacheIDFromDeviceID(unsigned int, const char *, const char *, CacheID **);
    virtual bool MountAsync(CacheID *, Cache **, Hmx::Object *);
    virtual bool UnmountAsync(Cache **, Hmx::Object *);
    virtual bool DeleteAsync(CacheID *);

private:
    HANDLE unk18; // 0x18
};
