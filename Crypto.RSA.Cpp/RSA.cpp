#include "RSA.h"
#include <boost/math/common_factor_rt.hpp>

std::pair<std::pair<Int, Int>, std::pair<Int, Int>> RSA::keyGen(){
	Algorithms::seedRNG();

	// generate 2 large random prime numbers
	Int p = Algorithms::randomPrime<512>(10);
	Int q = Algorithms::randomPrime<512>(10);

	// build the modulus
	Int N = p*q;


	Int phi = (p - 1)*(q - 1);		// eulers totient function of N	

	Int e = 0;		// get a random relatively prime number e where gcd(e and N ) = 0
	for (;;){
		e = Algorithms::getRandomNumber(2, phi-1);
		Int gcd = boost::math::gcd(e, phi);
		if (gcd == 1)
			break;
	}

	// calculate d such that d*e \equiv 1 mod phi(N)
	Int d = Algorithms::modInverse(e, phi);
	

	std::pair<Int, Int> pk = std::make_pair(N, e);
	std::pair<Int, Int> sk = std::make_pair(N, d);

#ifdef _DEBUG
	std::cout << "p = " << p << std::endl;
	std::cout << "q = " << q << std::endl;
	std::cout << "N = " << N << std::endl;
	std::cout << "phi(N) = " << phi << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "d = " << d << std::endl;
#endif

	return std::make_pair(pk, sk);
}

Int RSA::encrypt(std::pair<Int, Int> pk, Int message){
	//modexp(m, pk)
	return powm(message, pk.second, pk.first);
}

Int RSA::decrypt(std::pair<Int, Int> sk, Int ciphertext){
	return powm(ciphertext, sk.second, sk.first);
}