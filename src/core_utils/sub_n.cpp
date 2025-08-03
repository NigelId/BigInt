#include "core_utils.hpp"
#include "immintrin.h"

void sub_n(uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr, const size_t B_size)
{
   uint8_t borrow{};

   unsigned long long *A_ptr_ull = reinterpret_cast<unsigned long long *>(A_ptr);

   for (size_t i = 0; i < B_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr_ull[i], B_ptr[i], &A_ptr_ull[i]);
   }

   for (size_t i = B_size; i < A_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr_ull[i], 0, &A_ptr_ull[i]);
   }
}

void sub_n(uint64_t *dest, const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
           const size_t B_size)
{
   uint8_t borrow{};

   unsigned long long *dest_ull = reinterpret_cast<unsigned long long *>(dest);

   for (size_t i = 0; i < B_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr[i], B_ptr[i], dest_ull + i);
   }

   for (size_t i = B_size; i < A_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr[i], 0, dest_ull + i);
   }
}
