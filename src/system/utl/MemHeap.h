#pragma once

class FreeBlock {
public:
    unsigned int mSizeWords;
    unsigned int mTimeStamp;
    FreeBlock *mNextBlock;
};

class MemHeap {
public:
    enum Strategy {
        kFirstFit = 0,
        kBestFit = 1,
        kLRUFit = 2,
        kLastFit = 3,
    };
    struct FreeBlockInfo {
        FreeBlock *mBlock;
        FreeBlock *mPrevBlock;
        int mSizeWords;
        int mPadWords;
    };

    int Free(int *);
    int *Truncate(int *, int, int &);
    void Print(class TextStream &, bool);
    void Init(const char *, int, int *, int, bool, Strategy, int, bool);
    int AllocSize(int *);

    const char *Name() const { return mName; }
    int SizeWords() const { return mSizeWords; }
    int *Start() const { return mStart; }
    int *End() const { return mStart + mSizeWords; }

private:
    FreeBlock *mFreeBlockChain; // 0x0
    int *mStart; // 0x4
    const char *mName; // 0x8
    int mSizeWords; // 0xc
    int mNum; // 0x10
    bool mIsHandleHeap; // 0x14
    int mDebugLevel; // 0x18
    Strategy mStrategy; // 0x1c
    bool mAllowTemp; // 0x20
    int unk24; // 0x24
};

class MemHeapStack {
public:
    int mStack[16]; // 0x0
    int mSize; // 0x40
    int mTempRefs; // 0x44
};
