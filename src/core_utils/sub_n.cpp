#include "core_utils.hpp"
#include "immintrin.h"
#include <cassert>
#include <utility>

// Both functions assume non leading 0

// this version force A_size >= B_size
bool sub_n(uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr, const size_t B_size)
{
   assert(A_size >= B_size);
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

   return borrow;
}
// this version wont, but assume Res >= A_size
bool sub_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
           const size_t B_size)
{
   uint8_t borrow{};

   unsigned long long *dest_ull = reinterpret_cast<unsigned long long *>(Res);

   const uint64_t *A_PTR = A_ptr;
   const uint64_t *B_PTR = B_ptr;

   size_t A_SIZE = A_size;
   size_t B_SIZE = B_size;

   if (B_SIZE > A_SIZE)
   {
      std::swap(A_PTR, B_PTR);
      std::swap(A_SIZE, B_SIZE);
   }

   for (size_t i = 0; i < B_SIZE; i++)
   {
      borrow = _subborrow_u64(borrow, A_PTR[i], B_PTR[i], dest_ull + i);
   }

   for (size_t i = B_SIZE; i < A_SIZE; i++)
   {
      borrow = _subborrow_u64(borrow, A_PTR[i], 0, dest_ull + i);
   }

   borrow = B_size > A_size;

   return borrow;
}
