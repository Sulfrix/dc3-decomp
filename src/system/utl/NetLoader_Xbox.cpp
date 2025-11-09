#include "utl/NetLoader_Xbox.h"

NetLoaderXbox::NetLoaderXbox(const String &str) : NetLoader(str), unk24(0) {
    // clang-format off
//   lVar1 = __RTDynamicCast(TheNetCacheMgr,0,0xffffffff82f18eec,0xffffffff82f19014,0);
//   if (lVar1 == 0) {
//     local_60[0] = 0x17;
//     pcVar2 = MakeString<>(kAssertStr,"NetLoader_Xbox.cpp",local_60,"pNetCacheMgrXbox");
//     Debug::Fail(&TheDebug,pcVar2,0x0);
//   }
//   uVar3 = NetCacheMgrXbox::GetIP(lVar1);
//   pcVar2 = NetCacheMgr::GetServerRoot(TheNetCacheMgr);
//   String::String(aSStack_58,pcVar2);
//   pFVar6 = &param_1->super_FixedString;
//   if (param_1 == 0x0) {
//     pFVar6 = 0x0;
//   }
//   String::operator+=(aSStack_58,pFVar6);
//   this_00 = MemAlloc(0x88,"e:\\lazer_build_gmc1\\system\\src\\net/HttpGet.h",0x1c,"HttpGet",0);
//   local_60[0] = this_00;
//   if (this_00 == 0x0) {
//     iVar4 = 0;
//   }
//   else {
//     uVar5 = NetCacheMgr::GetPort(TheNetCacheMgr);
//     iVar4 = HttpGet::HttpGet(this_00,uVar3,uVar5,aSStack_58[0].super_FixedString.mStr,0x0);
//   }
//   *(this + 0x20) = iVar4;
//   if (iVar4 == 0) {
//     local_60[0] = 0x20;
//     pcVar2 = MakeString<>(kAssertStr,"NetLoader_Xbox.cpp",local_60,"mHttpGet");
//     Debug::Fail(&TheDebug,pcVar2,0x0);
//   }
//   String::~String(aSStack_58);
//   return this;
    // clang-format on
}
