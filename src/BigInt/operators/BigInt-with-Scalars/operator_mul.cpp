#include "BigInt.hpp"
#include "core_utils.hpp"

BigInt &operator*=(BigInt &A, const uint64_t &s)
{
   A.digits.push_back(0);

   mul_scalar_n(A.digits.data(), A.digits.size(), s);

   if (A.digits.back() == 0)
   {
      A.digits.pop_back();
   }
   return A;
}

BigInt operator*(const BigInt &A, const uint64_t &s)
{
   BigInt tmp = A;
   tmp *= s;
   return tmp;
}
