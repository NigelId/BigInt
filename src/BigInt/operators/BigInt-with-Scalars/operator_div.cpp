#include "BigInt.hpp"
#include "core_utils.hpp"

BigInt &operator/=(BigInt &A, const uint64_t &divisor)
{
   size_t A_size = A.digits.size();
   div_scalar_n(A.digits.data(), A_size, divisor);
   while (A_size > 1 && A.digits.back() == 0)
   {
      A.digits.pop_back();
      A_size--;
   }
   return A;
}
BigInt operator/(const BigInt &A, const uint64_t &divisor)
{
   BigInt tmp = A;
   tmp /= divisor;
   return tmp;
}
