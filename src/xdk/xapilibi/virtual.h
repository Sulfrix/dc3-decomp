#pragma once
#include "../win_types.h"

#ifdef __cplusplus
extern "C" {
#endif

struct _MEMORYSTATUS { /* Size=0x20 */
    DWORD dwLength; /* 0x0000 */
    DWORD dwMemoryLoad; /* 0x0004 */
    DWORD dwTotalPhys; /* 0x0008 */
    DWORD dwAvailPhys; /* 0x000c */
    DWORD dwTotalPageFile; /* 0x0010 */
    DWORD dwAvailPageFile; /* 0x0014 */
    DWORD dwTotalVirtual; /* 0x0018 */
    DWORD dwAvailVirtual; /* 0x001c */
};
typedef _MEMORYSTATUS MEMORYSTATUS;

void GlobalMemoryStatus(MEMORYSTATUS *);

#ifdef __cplusplus
}
#endif
