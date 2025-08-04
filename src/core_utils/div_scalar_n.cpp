#include "core_utils.hpp"

/* Perform short division on an u64 , multiply the remainder with 2^64 then add A_ptr[i], divide
 * that by the divisor and store the remainder. The function will return a u64 since any BigInt
 * % u64 =  u64 */

/* There should be 2 types of the same function, write data over the existing buffer or to a new
 * buffer */
uint64_t div_scalar_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size,
                      const uint64_t divisor)
{
   uint64_t rem = 0;

   for (long i = A_size - 1; i >= 0; --i)
   {
      __uint128_t dividend = (static_cast<__uint128_t>(rem) << 64) | A_ptr[i];
      Res[i] = static_cast<uint64_t>((dividend / divisor));
      rem = static_cast<uint64_t>((dividend - static_cast<__uint128_t>(Res[i]) * divisor));
   }

   return rem;
}

uint64_t div_scalar_n(uint64_t *A_ptr, const size_t &A_size, const uint64_t &divisor)
{
   uint64_t rem = 0;

   for (long i = A_size - 1; i >= 0; --i)
   {
      __uint128_t dividend = (static_cast<__uint128_t>(rem) << 64) | A_ptr[i];
      A_ptr[i] = static_cast<uint64_t>((dividend / divisor));
      rem = static_cast<uint64_t>((dividend - static_cast<__uint128_t>(A_ptr[i]) * divisor));
   }

   return rem;
}
