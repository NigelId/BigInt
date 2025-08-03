#include "core_utils.hpp"
#include <cstring>
#include <utility>

// Assume A > B
void add_n(uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr, const size_t B_size)
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

void add_n(uint64_t *dest, const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
           const size_t B_size)
{
   const u_int64_t *A_Ptr = A_ptr;
   const u_int64_t *B_Ptr = B_ptr;

   size_t A_s = A_size;
   size_t B_s = B_size;

   if (A_size < B_size)
   {
      std::swap(A_Ptr, B_Ptr);
      std::swap(A_s, B_s);
   }

   u_int8_t carry{};

   unsigned long long *dest_ull = reinterpret_cast<unsigned long long *>(dest);

   for (u_int64_t i = 0; i < B_s; i++)
   {
      carry = _addcarry_u64(carry, A_Ptr[i], B_Ptr[i], (dest_ull + i));
   }

   for (u_int64_t i = B_s; i < A_s; i++)
   {
      carry = _addcarry_u64(carry, A_Ptr[i], 0, (dest_ull + i));
   }

   dest_ull[A_s] = carry;
}
