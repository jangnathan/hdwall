#include "cli.h"
#include "logging.h"
#include "helper/parsing.h"
#include "helper/hex.h"
#include "wallet/wallet.h"
#include "cli_state.h"

#include <cstdint>
#include <iostream>
#include <fstream>

CliState cliState;

using namespace std;

void bigText() {
	cout <<
		"__          __     _      _      ______ _______ \n"
		"\\        / /\\   | |    | |    |  ____|__   __|\n"
		"\\ \\  /\\  / /  \\  | |    | |    | |__     | |\n"
		"\\ \\/  \\/ / /\\ \\ | |    | |    |  __|    | |\n"
		"\\  /\\  / ____ \\| |____| |____| |____   | |\n"
		"\\/  \\/_/    \\_\\______|______|______|  |_|\n"
		"___________________________________________________\n";

}

void appendBranch512TUI() {
	Wallet512 *wallet = &cliState.wallet;

	// branch inputting
	// recursive input in HEX, or type like this / / / 
	// you must write your scheme down so you dont forget (this is safe to do), as long as master key is safe
	string input;
	// set current key
	bool worked = false;
	uint8_t buf[64];

	bool leftBlank = false;

	cout << "Leave '.' if blank\nenter your branch: ";
	while (!worked && !leftBlank) {
		cin >> input;
		if (input == " " || input == ".") {
			leftBlank = true;
			break;
		}

		worked = wallet->derive512BranchFromStr(buf, input, '/');
		if (!worked) {
			LOG_ERROR("error parsing string, try again");
		}
	}

	if (!leftBlank) {
		cliState.wallet.recordStrToCurrentBranch(input);

		memcpy(wallet->hash512, buf, 64);
	}

	cout << "BRANCH (HEX): ";
	for (int i = 0; i < 64; i++) {
		cout << hex << std::setfill('0') << std::setw(2) << static_cast<int>(buf[i]);
	}
	cout << "\n";
}

void rootOptionHandler(string op) {
	Wallet512 *wallet = &cliState.wallet;

	// q is reserved
	if (op == "r") {
		wallet->resetToRoot();
	} else if (op == "ar2") {
		appendBranch512TUI();
	} else if (op == "h") {
		// print hex priv key 32 bytes
		cout << "\n";
		for (int i = 0; i < 32; i++) {
			cout << hex << static_cast<int>(wallet->hash512[i]);
		}
		cout << "\ny?";

		string n;
		cin >> n; // wait
	} else if (op == "b58") {
			LOG_DEBUG("WARN: Not found a use case for this");
	} else {
		cout << "Not an option\n";
	}
}

bool cliEnterMasterKey() {
	cout << "Enter master key (hex): ";
	string masterKeyStr;

	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, masterKeyStr);

	removeWhitespace(masterKeyStr);

	Wallet512 *wallet = &cliState.wallet;
	wallet->masterKey.resize(masterKeyStr.size() / 2 + 1);

	size_t outLen = 0;
	bool result = decodeStrToHex(wallet->masterKey.data(), wallet->masterKey.size(), &outLen, 
								masterKeyStr.data(), masterKeyStr.size());

	wallet->masterKey.resize(outLen);
	if (!result) {
		return false;
	}

	cout << wallet->masterKey.size() << "MASTER KEY (HEX): ";
	for (int i = 0; i < wallet->masterKey.size(); i++) {
		cout << hex << static_cast<int>(wallet->masterKey[i]);
	}

	wallet->resetToRoot();
	return true;
}

void cliStarting() {
	bigText();
	cout <<
		"\n"
		"OPTIONS: \n\n"
		"ENTER MASTER KEY (hex): (e)\n"
		"LOAD KEY + PIN: (l)\n"
		"Quit (q)\n";

	string input = "";
	bool valid = false;
	while (!valid && input != "q") {
		cin >> input;
		if (input == "e") {
			if (!cliEnterMasterKey()) {
				LOG_ERROR("INVALID, needs to be hex");
				return; // if unsuccessful, return back to loop
			}
			valid = true;
		} else if (input == "l") {
			valid = true;
		}
	}

	cliState.screen = CLI_MENU;
}

void cliMenu() {
	cout <<
		"OPTIONS: \n"
		"reset branch root (r)\n"
		"append branch 512 bit (ar2)\n"

		"\nprivate key hex (h)\n"
		"private key base 58 (b58)\n"

		"\n"
		"quit (q)\n"
		"\n";
	cout << "\n=== MAIN MENU ===\n";
	cout << "currentBranch: " << cliState.wallet.currentBranch << "\n\n";
	cout << "OPTION: ";

	string optionStr;
	cin >> optionStr;

	rootOptionHandler(optionStr);
}

void cli() {
	Wallet512 *wallet = &cliState.wallet;

	// hash the masterKey into currentHash
	string optionStr = "";
	while (optionStr != "q") {
		cout << "\n\nNEW SCREEN\n"
			"=============================================\n\n";
		switch (cliState.screen) {
			case CLI_STARTING:
				cliStarting();
				break;
			case CLI_MENU:
				cliMenu();
				break;
			default:
				break;
		}
	}
}
