// Crypto.RSA.Cpp.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "stdafx.h"
#include <iostream>
#include "RSA.h"

int _tmain(int argc, _TCHAR* argv[])
{
	
	auto keys = RSA::keyGen();
	auto pk = keys.first;
	auto sk = keys.second;

	Int msg = 2;

	Int c = RSA::encrypt(pk, msg);
	Int m = RSA::decrypt(sk, c);

	std::cout << "Message: " << msg << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "m: " << m << std::endl;
	int i;
	std::cin >> i;
	return 0;
}

