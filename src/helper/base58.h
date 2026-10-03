#pragma once
#include <cstdint>
#include <string>

class Base58Encoder {
};

class Base58Decoder {
private:
	uint8_t lookupTable[256];

public:
	Base58Decoder();

	bool decode(std::vector<uint8_t>& vec, const std::string& str);
};
