#include "BigInt.hpp"
#include "core_utils.hpp"

BigInt &operator<<=(BigInt &A, const uint64_t &shift)
{
   uint64_t A_size = A.digits.size();

   A.digits.resize(A_size + (shift >> 6) + 1);

   shl_n(A.digits.data(), (A_size + (shift >> 6) + 1), shift);

   if (A.digits.back() == 0)
   {
      A.digits.pop_back();
   }
   return A;
}

BigInt operator<<(const BigInt &A, const uint64_t &shift)
{
   BigInt tmp = A;
   tmp <<= shift;
   return tmp;
}
