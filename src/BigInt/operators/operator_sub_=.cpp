#include "BigInt.hpp"
#include "core_utils.hpp"

BigInt &operator-=(BigInt &A, const BigInt &B)
{
   const u_int64_t A_size = A.digits.size();
   const u_int64_t B_size = B.digits.size();

   sub_n(A.digits.data(), A_size, B.digits.data(), B_size);

   if (A.digits.back() == 0)
   {
      A.digits.pop_back();
   }

   return A;
}
