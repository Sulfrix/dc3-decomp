#pragma once
#include "../win_types.h"
#include "xcontent.h"
#include "xuser.h"

#ifdef __cplusplus
extern "C" {
#endif

DWORD XCancelOverlapped(XOVERLAPPED *);
DWORD XGetOverlappedExtendedError(XOVERLAPPED *pOverlapped);
DWORD XShowKeyboardUI(
    DWORD dwUserIndex,
    DWORD dwFlags,
    LPCWSTR wseDefaultText,
    LPCWSTR wszTitleText,
    LPCWSTR wszDescriptionText,
    LPWSTR wszResultText,
    DWORD cchResultText,
    XOVERLAPPED *pOverlapped
);

#ifdef __cplusplus
}
#endif
