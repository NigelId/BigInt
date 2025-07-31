#include "core_utils.hpp"

void mul_n(uint64_t *Res, const uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr,
           const size_t &B_size)
{
   uint64_t carry{};
   __uint128_t scratch{};

   for (size_t i = 0; i < A_size; i++)
   {
      carry = 0;
      uint64_t Ai = A_ptr[i];

      for (size_t j = 0; j < B_size; j++)
      {
         scratch = static_cast<__uint128_t>(Ai) * (B_ptr[j]) + Res[i + j] + carry;
         Res[i + j] = static_cast<uint64_t>(scratch);
         carry = scratch >> 64;
      }
      Res[i + B_size] = static_cast<uint64_t>(carry);
   }
}
