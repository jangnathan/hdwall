#include "wallet.h"
#include "helper/hex.h"
#include "logging.h"
#include "argon2.h"

#include <openssl/sha.h>
#include <iostream>

const char *chainType512Name(ChainType512 type) {
	switch (type) {
		case ChainType512_Arbitary: return "Arbitary";
		case ChainType512_Bitcoin: return "Bitcoin";
		case ChainType512_Ethereum: return "Ethereum";
		case ChainType512_Solana: return "Solana";
		case ChainType512_Litecoin: return "Litecoin";
		default: return "None";
	}
}

// some parameters defined here
void my_argon2id_hash(uint8_t *out, size_t outSize, uint8_t *data, size_t dataLen, uint8_t *salt, size_t saltLen) {
	int t_cost = 2;
	int m_cost = 1024 * 19; // OWASP recommended
	int parallelism = 1;

	argon2i_hash_raw(t_cost, m_cost, parallelism, data, dataLen, salt, saltLen, out, outSize);
}

void Wallet512::resetToRoot() {
	currentBranch = "";
	SHA512(masterKey.data(), masterKey.size(), hash512);
}

#define WALLET_MAX_BRANCHBUF_SIZE 64
bool derive512HashFromBuf(uint8_t *hash, uint8_t *inbuf, size_t inbufSize, bool strengthened) {
	if (inbufSize > WALLET_MAX_BRANCHBUF_SIZE) {
		return false;
	}

	uint8_t hashReadCpy[64];
	memcpy(hashReadCpy, hash, 64);

	uint8_t *chaincode = hashReadCpy + 32;

	if (strengthened == 1) {
		my_argon2id_hash(hash, 64, inbuf, inbufSize, chaincode, 32);
	} else {
		uint8_t combined[32 + WALLET_MAX_BRANCHBUF_SIZE];
		memcpy(combined, chaincode, 32);

		memcpy(combined + 32, inbuf, inbufSize);
		SHA512(combined, 32 + inbufSize, hash);
	}

	return true;
}

// buf must be able to contain 256 bits, 256 / 8 = 32 length
// protocol
bool Wallet512::derive512BranchFromStr(uint8_t *out, std::string input, char seperater) {
	size_t offset = 0;
	size_t offsetSize = 0;

	size_t readLen = input.size();
	if (input[readLen - 1] == seperater) {
		readLen--;
	}

	uint8_t hash[64];
	memcpy(hash, hash512, 64);

	size_t hashCount = 0;
	while (offset + offsetSize < readLen) {
		offsetSize++;

		// reached seperator or end
		if (input[offset + offsetSize] == seperater || offset + offsetSize == readLen) {
			uint8_t strengthened = 0;
			if (input[offset] == '\'') { // means use a strengthened hash function
				strengthened = 1;
				offset++;
				offsetSize--;
			}

			uint8_t hexBuf[WALLET_MAX_BRANCHBUF_SIZE]; // number of hex limit per branch

			size_t numHexDigits;
			char *branchStrStart = input.data() + offset;
			if (!decodeStrToHex(hexBuf, 64, &numHexDigits, branchStrStart, offsetSize)) return false;

			bool res = derive512HashFromBuf(hash, hexBuf, numHexDigits / 2 + 1, strengthened);
			if (!res) return false;

			hashCount++;

			// update offsets
			offset += offsetSize + 1; // skip seperator
			offsetSize = 0;
		}
	}

	memcpy(out, hash, 64);

	LOG_DEBUG("hashed " << hashCount << " times");

	return true;
}
void Wallet512::recordStrToCurrentBranch(std::string& str) {
	for (char &c : str) {
		c = std::toupper(static_cast<unsigned char>(c));
	}
	if (str[str.size()] == '/') {
		currentBranch.append(str, 0, str.size() - 1);
	} else {
		currentBranch.append(str);
		currentBranch.append("/");
	}
}

void Wallet512::importAccountFs(std::ifstream& file) {
}
void Wallet512::exportAccountFs(std::ofstream& file) {
}
