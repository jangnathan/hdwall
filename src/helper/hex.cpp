#include "hex.h"

#include <cctype>

const char hexAlphabet[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static uint8_t hexMap[256];
static uint8_t hexMapInitialized = 0;

void initHexMap() {
	for (int i = 0; i < 256; i++) {
		hexMap[i] = 16; // 16 means NULL
	}

	for (uint8_t i = 0; i < 16; i++) {
		hexMap[hexAlphabet[i]] = i;
	}
}

bool decodeStrToHex(uint8_t *outbuf, size_t buflen, size_t *outLenGet, char *inStr, size_t inStrLen) {
	if (!hexMapInitialized) {
		initHexMap();
		hexMapInitialized = 1;
	}

	int digitIdx = 0;
	int bufIdx = -1;
	// EE = 15 * 16 + 15

	for (size_t i = 0; i < inStrLen; i++) {
		// ignore whitespace
		if (inStr[i] == ' ' || inStr[i] == '\t') {
			continue;
		}

		char ch = std::toupper(inStr[i]);
		if (hexMap[ch] == 16) { // not a valid hex digit
			return false;
		}

		if (digitIdx % 2 == 0) {
			bufIdx++;
			outbuf[bufIdx] = hexMap[ch];
		} else {
			outbuf[bufIdx] = outbuf[bufIdx] * 16 + hexMap[ch];
		}
		digitIdx++;
		
		if (digitIdx > buflen * 2) {
			return false;
		}
	}

	if (outLenGet != NULL) {
		*outLenGet = bufIdx + 1;
	}

	return true;
}
