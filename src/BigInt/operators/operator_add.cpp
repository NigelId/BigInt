#include "BigInt.hpp"

BigInt operator+(const BigInt &A, const BigInt &B)
{
   BigInt tmp = A;
   tmp += B;
   return tmp;
}
