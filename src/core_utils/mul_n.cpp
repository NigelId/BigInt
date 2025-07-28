#include "core_utils.hpp"

void mul_n(u_int64_t *Res, const u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
           const size_t &B_size)
{
   u_int64_t carry{};
   __uint128_t scratch{};

   for (size_t i = 0; i < A_size; i++)
   {
      carry = 0;
      for (size_t j = 0; j < B_size; j++)
      {
         scratch = static_cast<__uint128_t>(A_ptr[i]) * (B_ptr[j]) + Res[i + j] + carry;
         Res[i + j] = static_cast<u_int64_t>(scratch);
         carry = scratch >> 64;
      }
      Res[i + B_size] = static_cast<u_int64_t>(carry);
   }
}
