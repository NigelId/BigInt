#include "core_utils.hpp"

// expected Res to be at least A_size + 1
void mul_scalar_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t s)
{
   uint64_t carry = 0;
   for (size_t i = 0; i < A_size; i++)
   {
      __uint128_t prod = static_cast<__uint128_t>(A_ptr[i]) * s + carry;
      Res[i] = static_cast<uint64_t>(prod);
      carry = prod >> 64;
   }
   Res[A_size] = carry;
}
// this version expect A to be padded properly, that is A_size = Prev A_size + 1
void mul_scalar_n(uint64_t *A_ptr, const size_t A_size, const uint64_t s)
{
   uint64_t carry = 0;
   for (size_t i = 0; i < A_size; i++)
   {
      __uint128_t prod = static_cast<__uint128_t>(A_ptr[i]) * s + carry;
      A_ptr[i] = static_cast<uint64_t>(prod);
      carry = prod >> 64;
   }
}
