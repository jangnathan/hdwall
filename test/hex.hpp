#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include "../src/helper/hex.h"
#include "test.hpp"

void testHex() {
	std::string test = "e5";

	unsigned char buf[64];
	size_t bufLen = 0;
	decodeStrToHex(buf, 64, &bufLen, test.data(), test.size());
	unsigned char expected[] = {16 * 14 + 5};
	testBuf(buf, bufLen, expected, 1 /* Length of expected[] */);
	// ---
	std::string test2 = "00";
	unsigned char buf2[64];
	size_t bufLen2 = 0;
	decodeStrToHex(buf2, 64, &bufLen2, test2.data(), test2.size());
	unsigned char expected2[] = {0};
	testBuf(buf2, bufLen2, expected2, 1);

	std::string test3 = "ff";
	unsigned char buf3[64];
	size_t bufLen3 = 0;
	decodeStrToHex(buf3, 64, &bufLen3, test3.data(), test3.size());
	unsigned char expected3[] = {16 * 15 + 15};
	testBuf(buf3, bufLen3, expected3, 1);

	std::string test4 = "1a";
	unsigned char buf4[64];
	size_t bufLen4 = 0;
	decodeStrToHex(buf4, 64, &bufLen4, test4.data(), test4.size());
	unsigned char expected4[] = {16 * 1 + 10};
	testBuf(buf4, bufLen4, expected4, 1);

	std::string test5 = "E5";
	unsigned char buf5[64];
	size_t bufLen5 = 0;
	decodeStrToHex(buf5, 64, &bufLen5, test5.data(), test5.size());
	unsigned char expected5[] = {16 * 14 + 5};
	testBuf(buf5, bufLen5, expected5, 1);

	std::string test6 = "deadbeef";
	unsigned char buf6[64];
	size_t bufLen6 = 0;
	decodeStrToHex(buf6, 64, &bufLen6, test6.data(), test6.size());
	unsigned char expected6[] = {16 * 13 + 14, 16 * 10 + 13, 16 * 11 + 14, 16 * 14 + 15};
	testBuf(buf6, bufLen6, expected6, 4);

	std::string test7 = "DEADBEEF";
	unsigned char buf7[64];
	size_t bufLen7 = 0;
	decodeStrToHex(buf7, 64, &bufLen7, test7.data(), test7.size());
	unsigned char expected7[] = {16 * 13 + 14, 16 * 10 + 13, 16 * 11 + 14, 16 * 14 + 15};
	testBuf(buf7, bufLen7, expected7, 4);

	std::string test8 = "0102030405";
	unsigned char buf8[64];
	size_t bufLen8 = 0;
	decodeStrToHex(buf8, 64, &bufLen8, test8.data(), test8.size());
	unsigned char expected8[] = {16 * 0 + 1, 16 * 0 + 2, 16 * 0 + 3, 16 * 0 + 4, 16 * 0 + 5};
	testBuf(buf8, bufLen8, expected8, 5);

	std::string test9 = "abcdef";
	unsigned char buf9[64];
	size_t bufLen9 = 0;
	decodeStrToHex(buf9, 64, &bufLen9, test9.data(), test9.size());
	unsigned char expected9[] = {16 * 10 + 11, 16 * 12 + 13, 16 * 14 + 15};
	testBuf(buf9, bufLen9, expected9, 3);

	std::string test10 = "A1B2C3";
	unsigned char buf10[64];
	size_t bufLen10 = 0;
	decodeStrToHex(buf10, 64, &bufLen10, test10.data(), test10.size());
	unsigned char expected10[] = {16 * 10 + 1, 16 * 11 + 2, 16 * 12 + 3};
	testBuf(buf10, bufLen10, expected10, 3);

	std::string test11 = "7f80";
	unsigned char buf11[64];
	size_t bufLen11 = 0;
	decodeStrToHex(buf11, 64, &bufLen11, test11.data(), test11.size());
	unsigned char expected11[] = {16 * 7 + 15, 16 * 8 + 0};
	testBuf(buf11, bufLen11, expected11, 2);

	std::string test12 = "1234567890";
	unsigned char buf12[64];
	size_t bufLen12 = 0;
	decodeStrToHex(buf12, 64, &bufLen12, test12.data(), test12.size());
	unsigned char expected12[] = {16 * 1 + 2, 16 * 3 + 4, 16 * 5 + 6, 16 * 7 + 8, 16 * 9 + 0};
	testBuf(buf12, bufLen12, expected12, 5);

	std::string test13 = "cafebabe";
	unsigned char buf13[64];
	size_t bufLen13 = 0;
	decodeStrToHex(buf13, 64, &bufLen13, test13.data(), test13.size());
	unsigned char expected13[] = {16 * 12 + 10, 16 * 15 + 14, 16 * 11 + 10, 16 * 11 + 14};
	testBuf(buf13, bufLen13, expected13, 4);

	std::string test14 = "0f1e2d3c";
	unsigned char buf14[64];
	size_t bufLen14 = 0;
	decodeStrToHex(buf14, 64, &bufLen14, test14.data(), test14.size());
	unsigned char expected14[] = {16 * 0 + 15, 16 * 1 + 14, 16 * 2 + 13, 16 * 3 + 12};
	testBuf(buf14, bufLen14, expected14, 4);

	std::string test15 = "99";
	unsigned char buf15[64];
	size_t bufLen15 = 0;
	decodeStrToHex(buf15, 64, &bufLen15, test15.data(), test15.size());
	unsigned char expected15[] = {16 * 9 + 9};
	testBuf(buf15, bufLen15, expected15, 1);

	std::string test16 = "a0b1c2d3";
	unsigned char buf16[64];
	size_t bufLen16 = 0;
	decodeStrToHex(buf16, 64, &bufLen16, test16.data(), test16.size());
	unsigned char expected16[] = {16 * 10 + 0, 16 * 11 + 1, 16 * 12 + 2, 16 * 13 + 3};
	testBuf(buf16, bufLen16, expected16, 4);

	std::string test17 = "FF00FF00";
	unsigned char buf17[64];
	size_t bufLen17 = 0;
	decodeStrToHex(buf17, 64, &bufLen17, test17.data(), test17.size());
	unsigned char expected17[] = {16 * 15 + 15, 16 * 0 + 0, 16 * 15 + 15, 16 * 0 + 0};
	testBuf(buf17, bufLen17, expected17, 4);

	std::string test18 = "5a5a5a5a";
	unsigned char buf18[64];
	size_t bufLen18 = 0;
	decodeStrToHex(buf18, 64, &bufLen18, test18.data(), test18.size());
	unsigned char expected18[] = {16 * 5 + 10, 16 * 5 + 10, 16 * 5 + 10, 16 * 5 + 10};
	testBuf(buf18, bufLen18, expected18, 4);

	std::string test19 = "0123456789abcdef";
	unsigned char buf19[64];
	size_t bufLen19 = 0;
	decodeStrToHex(buf19, 64, &bufLen19, test19.data(), test19.size());
	unsigned char expected19[] = {16 * 0 + 1, 16 * 2 + 3, 16 * 4 + 5, 16 * 6 + 7, 16 * 8 + 9, 16 * 10 + 11, 16 * 12 + 13, 16 * 14 + 15};
	testBuf(buf19, bufLen19, expected19, 8);

	std::string test20 = "89abcdef";
	unsigned char buf20[64];
	size_t bufLen20 = 0;
	decodeStrToHex(buf20, 64, &bufLen20, test20.data(), test20.size());
	unsigned char expected20[] = {16 * 8 + 9, 16 * 10 + 11, 16 * 12 + 13, 16 * 14 + 15};
	testBuf(buf20, bufLen20, expected20, 4);

	std::string test21 = "00112233";
	unsigned char buf21[64];
	size_t bufLen21 = 0;
	decodeStrToHex(buf21, 64, &bufLen21, test21.data(), test21.size());
	unsigned char expected21[] = {16 * 0 + 0, 16 * 1 + 1, 16 * 2 + 2, 16 * 3 + 3};
	testBuf(buf21, bufLen21, expected21, 4);

	std::string test22 = "4567";
	unsigned char buf22[64];
	size_t bufLen22 = 0;
	decodeStrToHex(buf22, 64, &bufLen22, test22.data(), test22.size());
	unsigned char expected22[] = {16 * 4 + 5, 16 * 6 + 7};
	testBuf(buf22, bufLen22, expected22, 2);

	std::string test23 = "fedcba98";
	unsigned char buf23[64];
	size_t bufLen23 = 0;
	decodeStrToHex(buf23, 64, &bufLen23, test23.data(), test23.size());
	unsigned char expected23[] = {16 * 15 + 14, 16 * 13 + 12, 16 * 11 + 10, 16 * 9 + 8};
	testBuf(buf23, bufLen23, expected23, 4);

	std::string test24 = "10";
	unsigned char buf24[64];
	size_t bufLen24 = 0;
	decodeStrToHex(buf24, 64, &bufLen24, test24.data(), test24.size());
	unsigned char expected24[] = {16 * 1 + 0};
	testBuf(buf24, bufLen24, expected24, 1);

	std::string test25 = "abcdef0123456789";
	unsigned char buf25[64];
	size_t bufLen25 = 0;
	decodeStrToHex(buf25, 64, &bufLen25, test25.data(), test25.size());
	unsigned char expected25[] = {16 * 10 + 11, 16 * 12 + 13, 16 * 14 + 15, 16 * 0 + 1, 16 * 2 + 3, 16 * 4 + 5, 16 * 6 + 7, 16 * 8 + 9};
	testBuf(buf25, bufLen25, expected25, 8);

	std::string test26 = "beef";
	unsigned char buf26[64];
	size_t bufLen26 = 0;
	decodeStrToHex(buf26, 64, &bufLen26, test26.data(), test26.size());
	unsigned char expected26[] = {16 * 11 + 14, 16 * 14 + 15};
	testBuf(buf26, bufLen26, expected26, 2);

	std::string test27 = "BEEF";
	unsigned char buf27[64];
	size_t bufLen27 = 0;
	decodeStrToHex(buf27, 64, &bufLen27, test27.data(), test27.size());
	unsigned char expected27[] = {16 * 11 + 14, 16 * 14 + 15};
	testBuf(buf27, bufLen27, expected27, 2);

	std::string test28 = "0a0b0c0d";
	unsigned char buf28[64];
	size_t bufLen28 = 0;
	decodeStrToHex(buf28, 64, &bufLen28, test28.data(), test28.size());
	unsigned char expected28[] = {16 * 0 + 10, 16 * 0 + 11, 16 * 0 + 12, 16 * 0 + 13};
	testBuf(buf28, bufLen28, expected28, 4);

	std::string test29 = "aabbccdd";
	unsigned char buf29[64];
	size_t bufLen29 = 0;
	decodeStrToHex(buf29, 64, &bufLen29, test29.data(), test29.size());
	unsigned char expected29[] = {16 * 10 + 10, 16 * 11 + 11, 16 * 12 + 12, 16 * 13 + 13};
	testBuf(buf29, bufLen29, expected29, 4);

	std::string test30 = "13579bdf";
	unsigned char buf30[64];
	size_t bufLen30 = 0;
	decodeStrToHex(buf30, 64, &bufLen30, test30.data(), test30.size());
	unsigned char expected30[] = {16 * 1 + 3, 16 * 5 + 7, 16 * 9 + 11, 16 * 13 + 15};
	testBuf(buf30, bufLen30, expected30, 4);
}
