#pragma once
#include <string>

bool isWhitespaceChar(char ch) {
	if (ch == ' ') return true;
	return false;
}

void removeWhitespace(std::string &str) {
	int sLen = 0;
	for (int i = 0; i < str.size(); i++) {
		if (isWhitespaceChar(str[i])) {
		} else {
			str[sLen] = str[i]; 
			sLen++;
		}
	}
	str.resize(sLen);
}
