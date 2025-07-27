#include "core_utils.hpp"
#include "immintrin.h"

// Assume A > B
void add_n(u_int64_t *A_ptr, u_int64_t A_size, u_int64_t *B_ptr, u_int64_t B_size)
{
   u_int8_t carry{};

   unsigned long long *A_ptr_ull = reinterpret_cast<unsigned long long *>(A_ptr);

   for (u_int64_t i = 0; i < B_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr_ull[i], B_ptr[i], &A_ptr_ull[i]);
   }

   for (u_int64_t i = B_size; i < A_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr_ull[i], 0, &A_ptr_ull[i]);
   }
}
