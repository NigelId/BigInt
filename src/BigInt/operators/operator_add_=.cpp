#include "BigInt.hpp"
#include "core_utils.hpp"

BigInt &operator+=(BigInt &A, const BigInt &B)
{
   const u_int64_t B_size = B.digits.size();

   A.digits.resize(std::max(A.digits.size(), B_size) + 1);

   const u_int64_t A_size = A.digits.size();

   add_n(A.digits.data(), A_size, B.digits.data(), B_size);

   if (A.digits.back() == 0)
   {
      A.digits.pop_back();
   }
   return A;
}
