#pragma once
#include <iostream>

using namespace std;

bool testBuf(unsigned char *bufA, size_t sizeA, unsigned char *bufB, size_t sizeB) {
	if (sizeA != sizeB) {
		cout << "mismatching sizes\n";
		return false;
	}

	bool same = true;
	for (size_t i = 0; i < sizeA; i++) {
		if (bufA[i] != bufB[i]) {
			same = false;
		}
	}


	for (size_t i = 0; i < sizeA; i++) {
		cout << static_cast<int>(bufA[i]) << " ";
	}
	if (same) {
		cout << " == ";
	} else {
		cout << " != ";
	}
	for (size_t i = 0; i < sizeA; i++) {
		cout << static_cast<int>(bufB[i]) << " ";
	}
	cout << "\n";

	return same;
}
