#pragma once
#include "rndobj/ShaderProgram.h"

class DxShaderBuffer : public RndShaderBuffer {
public:
    DxShaderBuffer(unsigned int);
    virtual ~DxShaderBuffer() {}
    virtual void *Storage();
    virtual unsigned int Size() const;

private:
    int unk4;
};

// : public ID3DXInclude
// class DxShaderInclude {
// public:
// };
