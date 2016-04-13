#pragma once

#include <iostream>
#include <boost/multiprecision/miller_rabin.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/random.hpp>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

using namespace boost::random;
using namespace boost::multiprecision;
namespace mp = boost::multiprecision;
typedef mp::cpp_int Int;		// boost::multiprecision cpp_int

static boost::random::mt19937 gen(clock());

class Algorithms
{

public:
	Algorithms();
	~Algorithms();

	template <unsigned int B>
	static inline Int randomPrime(unsigned int it){
		mt11213b base_gen(clock());
		independent_bits_engine<mt11213b, B, Int> gen(base_gen);
		//
		// We must use a different generator for the tests and number generation, otherwise
		// we get false positives.
		//
		mt19937 gen2(clock());
		for (;;){
			Int n = gen();
			if (miller_rabin_test(n, it, gen2))
				return n;
		}					
	}

	static inline void seedRNG(){
		gen.seed(static_cast<unsigned int>(std::time(0)));
	}

	static inline Int getRandomNumber(Int lb, Int ub){
		boost::random::uniform_int_distribution<Int> dist( lb, ub );
		return dist(gen);
	}


	static inline std::pair<Int, std::pair<Int, Int> > extendedEuclid(Int a, Int b) {
		Int x = 1, y = 0;
		Int xLast = 0, yLast = 1;
		Int q, r, m, n;
		while (a != 0) {
			q = b / a;
			r = b % a;
			m = xLast - q * x;
			n = yLast - q * y;
			xLast = x, yLast = y;
			x = m, y = n;
			b = a, a = r;
		}
		return std::make_pair(b, std::make_pair(xLast, yLast));
	}

	static inline Int modInverse(Int a, Int m) {
		return (extendedEuclid(a, m).second.first + m) % m;
	}
	
};