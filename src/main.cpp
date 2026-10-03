#include "cli/cli.h"

#include <iostream>

// wallet

int main(int argc, char **argv) {
	#ifdef CLI_APP
	cli();
	#endif

	return 0;
}
