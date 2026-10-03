#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <variant>

enum ChainType512 {
	ChainType512_Arbitary,
	ChainType512_Bitcoin,
	ChainType512_Ethereum,
	ChainType512_Solana,
	ChainType512_Litecoin,
	ChainType512End
};

const char *chainType512Name(ChainType512 type); 

struct Account512 {
	std::string branchSegment;
	ChainType512 chainType;

	uint8_t hash512[64];
};

class Wallet512 {
public:
	std::vector<uint8_t> masterKey;

	std::string currentBranch;
	Account512 account;

	bool derive512BranchFromStr(uint8_t *out, std::string input, char seperater);
	void recordStrToCurrentBranch(std::string& str);
	void resetToRoot();

	void importAccountFs(std::ifstream& file);
	void exportAccountFs(std::ofstream& file);

	uint8_t hash512[64];
};
