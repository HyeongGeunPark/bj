/*
bj31876 자존심 강한 두 천재의 대결

같은 길이의 U진법과 V진법으로 표기된 수의 대소를 비교하자.

2 <= U, V <= 10이다.
수의 길이는 최대 3'000'000이다.

접근:
unsigned long long으로 입력받을 수 있는 최대 숫자는
18'446'744'073'709'551'615
즉, 10^19-1, 19자리까지는 안전하게 입력이 된다.
 9'999'999'999'999'999'999

그런데 19자리의 가장 작은 10진수는
 1'000'000'000'000'000'000 == 10^18
19자리의 가장 큰 9진수는 9^19 - 1 ==
 1,350,851,717,672,992,088

20자리의 가장 작은 10진수는
10'000'000'000'000'000'000 == 10^19
20자리의 가장 큰 9진수는 9^20 - 1 ==
12,157,665,459,056,928,800

21자리의 가장 작은 10진수는
100'000'000'000'000'000'000 == 10^20
20자리의 가장 큰 9진수는 9^21 - 1 ==
109'418'989'131'512'359'208

22자리의 가장 작은 10진수는
1'000'000'000'000'000'000'000 == 10^21
22자리의 가장 큰 9진수는 9^22 - 1 ==
  984'770'902'183'611'232'880

  -> 22자리부터는 그냥 진법이 큰 쪽이 크다.

어떻게든 10^23 범위가 표현 가능한 정수형이 있으면 쉽게 풀 수 있다.



편법: 사실 임의 크기, 임의 진법 수의 입출력을 지원하는 언어/라이브러리를
사용하면 바로 해결된다.

*/

#include <array>
#include <cmath>
#include <iostream>
#include <string>

struct my_u128;

my_u128 operator+(const my_u128 a, const my_u128 b);
my_u128 operator*(const my_u128 a, const my_u128 b);

struct my_u128 {
  //	little-endian : least significant uint in lower address
  my_u128() : data{{0, 0, 0, 0}} {}
  my_u128(unsigned int a) : data{{a, 0, 0, 0}} {}
  my_u128(unsigned long long a) : data{{a & 0xFFFFFFFF, a >> 32, 0, 0}} {}
  std::array<unsigned int, 4> data;

  my_u128& operator+=(const my_u128& other) {
    *this = *this + other;
    return *this;
  }

  my_u128& operator*=(const my_u128& other) {
    *this = *this * other;
    return *this;
  }

  bool operator==(const my_u128& other) { return this->data == other.data; }

  bool operator<(const my_u128& other) {
    for (int i = 3; i >= 0; --i) {
      if (this->data[i] < other.data[i]) return true;
    }
    return false;
  }
};

my_u128 operator+(const my_u128 a, const my_u128 b) {
  my_u128 result;

  unsigned long long temp = 0;
  for (int i = 0; i < 4; ++i) {
    temp = (unsigned long long)a.data[i] + (unsigned long long)b.data[i] + temp;
    result.data[i] = (unsigned int)(temp & 0xFFFFFFFF);
    temp >>= 32;
  }

  // ignore carry
  // if unlimited bigint is needed, change array<> to vector<> and append new
  // element
  return result;
}

my_u128 operator*(const my_u128 a, const my_u128 b) {
  my_u128 result;

  for (int i = 0; i < 4; ++i) {
    my_u128 temp;
    unsigned long long carry = 0;
    // ignore overflow.
    for (int j = 0; (i + j) < 4; ++j) {
      // there *should* be no overflow. and it can be proved.
      carry += a.data[i] * b.data[j];
      temp.data[i + j] = carry & 0xFFFFFFFF;
      carry >>= 32;
    }
    result += temp;
  }
  return result;
}

int main(void) {
  // c++ fast io
  std::cin.tie(0);
  std::ios_base::sync_with_stdio(false);

  unsigned int u, v;
  std::cin >> u >> v;
  std::string ras;
  std::string auq;

  my_u128 ras_c;
  my_u128 auq_c;

  std::cin >> ras;
  std::cin >> auq;

  if (ras.length() >= 22) {
    if (u > v) {
      goto ras_won;
    } else if (u < v) {
      goto auq_won;
    } else {
      for (int i = 0; i < ras.length(); ++i) {
        if (ras[i] > auq[i]) {
          goto ras_won;
        } else if (ras[i] < auq[i]) {
          goto auq_won;
        }
      }
      goto tied;
    }
  }

  if (u == v) {
    for (int i = 0; i < ras.length(); ++i) {
      if (ras[i] > auq[i]) {
        goto ras_won;
      } else if (ras[i] < auq[i]) {
        goto auq_won;
      }
    }
    goto tied;
  }

  // 진법변환과 비교를 해야 하는 경우: u != v, length < 22
  for (int i = 0; i < ras.length(); ++i) {
    // it is extremely inefficient, but doesn't matter in this bounded condition
    ras_c *= my_u128{u};
    auq_c *= my_u128{v};
    ras_c += my_u128{(unsigned int)(ras[i] - '0')};
    auq_c += my_u128{(unsigned int)(auq[i] - '0')};
  }

  if (ras_c < auq_c) {
    goto auq_won;
  } else if (auq_c < ras_c) {
    goto ras_won;
  } else {
    goto tied;
  }

  std::cout << "something not good happened.";
  return 0;

ras_won:
  std::cout << "ras";
  return 0;

auq_won:
  std::cout << "auq";
  return 0;

tied:
  std::cout << "rasauq";
  return 0;
}