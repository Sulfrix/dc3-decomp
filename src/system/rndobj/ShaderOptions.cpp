#include "ShaderOptions.h"
#include "os/Debug.h"
#include "rndobj/ShaderOptions.h"
#include "os/File.h"
#include "os/System.h"
#include "utl/Loader.h"
#include "utl/Symbol.h"

Symbol sShaderTypes[kMaxShaderTypes];

void InitShaderOptions() {
    sShaderTypes[kBloomShader] = "bloom";
    sShaderTypes[kBloomGlareShader] = "bloom_glare";
    sShaderTypes[kBlurShader] = "blur";
    sShaderTypes[kDepthVolumeShader] = "depthvolume";
    sShaderTypes[kDownsampleDepthShader] = "downsample_depth";
    sShaderTypes[kDownsampleShader] = "downsample";
    sShaderTypes[kDownsample4xShader] = "downsample_4x";
    sShaderTypes[kDrawRectShader] = "drawrect";
    sShaderTypes[kErrorShader] = "error";
    sShaderTypes[kFurShader] = "fur";
    sShaderTypes[kLineNozShader] = "line_noz";
    sShaderTypes[kLineShader] = "line";
    sShaderTypes[kMovieShader] = "movie";
    sShaderTypes[kMultimeshBBShader] = "multimesh_bb";
    sShaderTypes[kMultimeshShader] = "multimesh";
    sShaderTypes[kParticlesShader] = "particles";
    sShaderTypes[kPostprocessErrorShader] = "postproc_error";
    sShaderTypes[kPostprocessShader] = "postprocess";
    sShaderTypes[kShadowmapShader] = "shadowmap";
    sShaderTypes[kStandardShader] = "standard";
    sShaderTypes[kSyncTrackShader] = "sync_track";
    sShaderTypes[kUnwrapUVShader] = "unwrapuv";
    sShaderTypes[kVelocityCameraShader] = "velocity_camera";
    sShaderTypes[kVelocityObjectShader] = "velocity_object";
    sShaderTypes[kPlayerDepthVisShader] = "playerdepth_vis";
    sShaderTypes[kPlayerDepthShellShader] = "playerdepth_shell";
    sShaderTypes[kPlayerDepthShell2Shader] = "playerdepth_shell2";
    sShaderTypes[kDepthBuffer3DShader] = "depthbuffer_3d";
    sShaderTypes[kYUVtoRGBShader] = "yuv_to_rgb";
    sShaderTypes[kYUVtoBlackAndWhiteShader] = "yuv_to_black_and_white";
    sShaderTypes[kPlayerGreenScreenShader] = "player_greenscreen";
    sShaderTypes[kPlayerDepthGreenScreenShader] = "player_depthgreenscreen";
    sShaderTypes[kCrewPhotoShader] = "crew_photo";
    sShaderTypes[kTwirlShader] = "twirl";
    sShaderTypes[kKillAlphaShader] = "killalpha";
    sShaderTypes[kAllWhiteShader] = "allwhite";
}

const char *ShaderTypeName(ShaderType shader) {
    MILO_ASSERT(shader >= ShaderType(0) && shader < kMaxShaderTypes, 0x41);
    return sShaderTypes[shader].Str();
}

const char *sShaderErrors[] = { "pulse" };

ShaderType ShaderTypeFromName(const char *name) {
    for (int i = 0; i < kMaxShaderTypes; i++) {
        if (streq(name, sShaderTypes[i].Str())) {
            return (ShaderType)i;
        }
    }
    for (int i = 0; i < DIM(sShaderErrors); i++) {
        if (streq(name, sShaderErrors[i])) {
            return kErrorShader;
        }
    }
    MILO_FAIL("Shader type name %s not found\n", name);
    return (ShaderType)-1;
}

const char *ShaderSourcePath(const char *file) {
    if (file) {
        return FileMakePath(
            FileSystemRoot(), MakeString("shaders/%s.fx", FileGetBase(file))
        );
    } else {
        return FileMakePath(FileSystemRoot(), "shaders");
    }
}

const char *ShaderCachedPath(const char *file, u64 i2, bool b3) {
    Platform plat = TheLoadMgr.GetPlatform();
    return MakeString(
        "%s/gen/%s_%llx_%s.%s_%s",
        FileGetPath(file),
        FileGetBase(file),
        i2,
        b3 ? "ps" : "vs",
        FileGetExt(file),
        PlatformSymbol(plat)
    );
}

bool IsPostProcShaderType(ShaderType s) {
    switch (s) {
    case kBloomShader:
    case kBlurShader:
    case kDepthVolumeShader:
    case kDownsampleShader:
    case kDownsample4xShader:
    case kDownsampleDepthShader:
    case kDrawRectShader:
        return false;
    case kErrorShader:
        return true;
    case kFurShader:
    case kLineNozShader:
    case kLineShader:
    case kMovieShader:
        return false;
    case kMultimeshShader:
    case kMultimeshBBShader:
    case kParticlesShader:
        return true;
    case kPostprocessErrorShader:
    case kPostprocessShader:
    case kShadowmapShader:
        return false;
    case kStandardShader:
    case (ShaderType)19:
    case kSyncTrackShader:
    case (ShaderType)21:
        return true;
    case kUnwrapUVShader:
    case kVelocityCameraShader:
    case kVelocityObjectShader:
    case kPlayerDepthVisShader:
    case kPlayerDepthShellShader:
    case kBloomGlareShader:
    case kPlayerDepthShell2Shader:
    case kDepthBuffer3DShader:
    case kYUVtoRGBShader:
    case kYUVtoBlackAndWhiteShader:
    case kPlayerGreenScreenShader:
    case kPlayerDepthGreenScreenShader:
    case kCrewPhotoShader:
    case kTwirlShader:
    case kKillAlphaShader:
        return false;
    case kAllWhiteShader:
        return true;
    default:
        MILO_FAIL("unknown shader type %s", ShaderTypeName(s));
        return false;
    }
}
