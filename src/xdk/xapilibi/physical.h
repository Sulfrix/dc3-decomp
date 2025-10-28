#pragma once
#include "../win_types.h"

#ifdef __cplusplus
extern "C" {
#endif

void *XPhysicalAlloc(DWORD, DWORD, DWORD, DWORD);
void XPhysicalFree(void *);

#ifdef __cplusplus
}
#endif
