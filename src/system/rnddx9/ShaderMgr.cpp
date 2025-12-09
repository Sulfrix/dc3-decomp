
#include "os/Debug.h"
#include "rnddx9/Rnd.h"
#include "rnddx9/Shader.h"
#include "rnddx9/ShaderInclude.h"
#include "rndobj/ShaderOptions.h"
#include "rndobj/ShaderProgram.h"
#include "xdk/d3d9i/d3d9.h"
#include "xdk/xgraphics/xgraphics.h"

DxShader::~DxShader() {
    if (mPreCreated) {
        MILO_ASSERT(mVShader != NULL, 0x60);
        MILO_ASSERT(mPShader != NULL, 0x61);
        mVShader = nullptr;
        mPShader = nullptr;
    } else {
        DX_RELEASE(mVShader);
        DX_RELEASE(mPShader);
    }
}

void DxShader::Copy(const RndShaderProgram &src) {
    MILO_ASSERT(mPreCreated == false, 0xA5);
    MILO_ASSERT(src.Cached(), 0xA6);
    DX_RELEASE(mVShader);
    DX_RELEASE(mPShader);
    const DxShader &dxSrc = static_cast<const DxShader &>(src);
    mVShader = dxSrc.mVShader;
    D3DResource_AddRef(mVShader);
    mPShader = dxSrc.mPShader;
    D3DResource_AddRef(mPShader);
    mMinOverall = dxSrc.mMinOverall;
    mMaxOverall = dxSrc.mMaxOverall;
}

void DxShader::EstimatedCost(float &min, float &max) {
    if (mMinOverall < 0 || mMaxOverall < 0) {
        mMinOverall = 0;
        mMaxOverall = 0;
        if (mPShader) {
            UINT sizeOfData;
            D3DPixelShader_GetFunction(mPShader, nullptr, &sizeOfData);
            if (sizeOfData != 0) {
                std::vector<char> chars(sizeOfData);
                auto it = chars.begin();
                D3DPixelShader_GetFunction(mPShader, it, &sizeOfData);
                XGIDEALSHADERCOST shaderCost;
                if (XGEstimateIdealShaderCost(it, 0, &shaderCost) == 0) {
                    mMinOverall = shaderCost.MinOverall;
                    mMaxOverall = shaderCost.MaxOverall;
                }
            }
        }
    }
    min = mMinOverall;
    max = mMaxOverall;
}

RndShaderBuffer *DxShader::NewBuffer(unsigned int ui) { return new DxShaderBuffer(ui); }

bool DxShader::
    Compile(ShaderType s, const ShaderOptions &opts, RndShaderBuffer *&, RndShaderBuffer *&) {
    std::vector<ShaderMacro> defines;
    opts.GenerateMacros(s, defines);
    const char *shaderName = ShaderTypeName(s);
    MILO_ASSERT(streq("PIXEL_SHADER", defines[0].Name), 0xBB);
    MILO_ASSERT(!mVShader, 0xBD);
    MILO_ASSERT(!mPShader, 0xBE);
    // the rest requires D3DX9

    return 0;
}

void DxShader::CreateVertexShader(RndShaderBuffer &buffer) {
    MILO_ASSERT(mVShader == NULL, 0x80);
    mVShader = D3DDevice_CreateVertexShader((const DWORD *)buffer.Storage());
    DX_ASSERT(mVShader, 0x82);
}

void DxShader::CreatePixelShader(RndShaderBuffer &buffer, ShaderType) {
    MILO_ASSERT(mPShader == NULL, 0x86);
    mPShader = D3DDevice_CreatePixelShader((const DWORD *)buffer.Storage());
    DX_ASSERT(mPShader, 0x88);
}

void DxShader::SetShaders(D3DVertexShader *v, D3DPixelShader *p) {
    if (mCached) {
        MILO_ASSERT(mPreCreated, 0x92);
        MILO_ASSERT(mVShader, 0x93);
        MILO_ASSERT(mPShader, 0x94);
    } else {
        MILO_ASSERT(mVShader == NULL, 0x99);
        MILO_ASSERT(mPShader == NULL, 0x9A);
        MILO_ASSERT(mPreCreated == false, 0x9B);
        mVShader = v;
        mPShader = p;
        mCached = true;
        mPreCreated = true;
    }
}
