#pragma once
#include "rndobj/ShaderProgram.h"
#include "xdk/D3D9.h"

class DxShader : public RndShaderProgram {
public:
    DxShader();
    virtual ~DxShader();
    virtual void Select(bool);
    virtual void Copy(const RndShaderProgram &);
    virtual void EstimatedCost(float &, float &);
    virtual void SetShaders(D3DVertexShader *, D3DPixelShader *);

protected:
    virtual RndShaderBuffer *NewBuffer(unsigned int);
    virtual bool
    Compile(ShaderType, const ShaderOptions &, RndShaderBuffer *&, RndShaderBuffer *&);
    virtual void CreateVertexShader(RndShaderBuffer &);
    virtual void CreatePixelShader(RndShaderBuffer &, ShaderType);

    D3DVertexShader *mVShader; // 0x20
    D3DPixelShader *mPShader; // 0x24
    float mMinOverall; // 0x28
    float mMaxOverall; // 0x2c
    bool mPreCreated; // unk30
};
