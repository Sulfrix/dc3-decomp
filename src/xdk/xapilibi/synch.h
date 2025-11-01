#pragma once
#include "../win_types.h"

#ifdef __cplusplus
extern "C" {
#endif

HANDLE CreateSemaphoreA(
    void *lpSemaphoreAttributes, LONG lInitialCount, LONG lMaximumCount, LPCSTR lpName
);
BOOL ReleaseSemaphore(HANDLE hSemaphore, LONG lReleaseCount, LONG *lpPreviousCount);

#ifdef __cplusplus
}
#endif
