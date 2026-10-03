#pragma once
#include "wallet/wallet.h"

enum CliScreen {
	CLI_STARTING,
	CLI_MENU,
	CLI_SETTING,
	CLI_END
};

struct CliState {
	Wallet512 wallet;

	CliScreen screen;
};

extern CliState cliState;
