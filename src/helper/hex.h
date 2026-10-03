#pragma once
#include <cstddef>
#include <cstdint>

bool decodeStrToHex(uint8_t *outbuf, size_t buflen, size_t *outLenGet, char *inStr, size_t inStrLen);
