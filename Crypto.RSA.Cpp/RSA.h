#pragma once

#include "Algorithms.h"

#define _CRT_SECURE_NO_WARNINGS

class RSA{
public:
	static std::pair<std::pair<Int, Int>, std::pair<Int, Int>> keyGen();

	static Int encrypt(std::pair<Int, Int> pk, Int message);
	static Int decrypt(std::pair<Int, Int> sk, Int ciphertext);

};