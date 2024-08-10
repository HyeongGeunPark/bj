#ifndef _MATH_HPP
#define _MATH_HPP

#include<tuple>
#include<vector>

using ll = long long;

// modular computations

/* safe_mod
* safe modular computation, which always returns non-negative value
* argument: a, m
* return value: (a mod m) in non-negative value 
*/
inline ll safe_mod(ll a, ll m) {
	ll result = a % m;
	if (result < 0) result += m;
	return result;
}

/* gcd
* computes greatest common divisor
* arguments: two integers
* return value: greatest common divisor of two arguments
*/
template<typename T>
inline T gcd(T a, T b) {
	T r = safe_mod(a, b);
	while (r) {
		a = b;
		b = r;
		r = safe_mod(a, b);
	}
	return b;
}

/* xgcd
* computes extended euclidean method
*/

/* lcm
* computes least commmon multiplier
* arguments: two integers
* return value: least commont multiplier of two arguments
*/
template<typename T>
inline T lcm(T a, T b) {
	return (a / gcd(a, b)) * b;
}

/* pow_mod 
* computes modular power
* arguments: a=base e=exponent m=modulus
* return value: (a^e mod m) in non-negative value 
*/
inline ll pow_mod(ll a, ll e, ll m) {
//TODO
}

/* inv_mod
* computes modular inverse
* arguments: a, m
* return value: non-negative integer x which satisfies a*x == 1 (mod m) 
*/
inline ll inv_mod(ll a, ll m) {
//TODO
}



#endif