#include "core_utils.hpp"
#include "immintrin.h"

// Assume A > B
void add_n(uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr, const size_t &B_size)
{
   u_int8_t carry{};

   unsigned long long *A_ptr_ull = reinterpret_cast<unsigned long long *>(A_ptr);

   for (uint64_t i = 0; i < B_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr_ull[i], B_ptr[i], &A_ptr_ull[i]);
   }

   for (uint64_t i = B_size; i < A_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr_ull[i], 0, &A_ptr_ull[i]);
   }
}

void add_n(uint64_t *dest, const uint64_t *A_ptr, const size_t &A_size,
           const uint64_t *B_ptr, const size_t &B_size)
{
   u_int8_t carry{};

   unsigned long long *dest_ull = reinterpret_cast<unsigned long long *>(dest);

   for (uint64_t i = 0; i < B_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr[i], B_ptr[i], (dest_ull + i));
   }

   for (uint64_t i = B_size; i < A_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr[i], 0, (dest_ull + i));
   }
}
