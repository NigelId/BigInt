#include "core_utils.hpp"
#include "internal/config.hpp"
#include "math_functions.hpp"
/* The idea is for karatsuba_n to create 2 arena, then pass it to karatsuba_arena then copy into
Res, the second arena is only for tmp value, that doesnt need copying , we cache z0, z1 and z2.
It should be noted that both arena are basically tmp chunks of memory. The sratch one are ment for
value that does not need to live beyond the function  */

/* If you're confused go to line 45 to 64, look at how i swap out and sratch arena the recursion
 * call*/

/* And like always, we assume Res has the correct size */

/* Memory is almost O(n) */

inline uint64_t *karatsuba_arena(const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
                                 const size_t B_size, Arena &out_arena, Arena &sratch_arena)
{
   if (B_size > A_size)
   {
      return karatsuba_arena(B_ptr, B_size, A_ptr, A_size, out_arena, sratch_arena);
   }

   if (A_size <= KARATSUBA_CUTOFF || B_size <= KARATSUBA_CUTOFF)
   {
      uint64_t *Res = out_arena.alloc(A_size + B_size);
      memset(Res, 0, (A_size) * sizeof(uint64_t));
      mul_n(Res, A_ptr, A_size, B_ptr, B_size);
      return Res;
   }

   const size_t a_high_len = A_size >> 1;
   const size_t a_low_len = A_size - a_high_len;

   const uint64_t *a_low = A_ptr;
   const uint64_t *a_high = A_ptr + a_low_len;

   const size_t b_low_len = std::min(B_size, a_low_len);
   const size_t b_high_len = B_size - b_low_len;

   const uint64_t *b_low = B_ptr;
   const uint64_t *b_high = B_ptr + b_low_len;

   const size_t mark = sratch_arena.mark(); // mark to reuse memory

   uint64_t *z0 = karatsuba_arena(a_low, a_low_len, b_low, b_low_len, sratch_arena, out_arena);
   uint64_t *z2 = karatsuba_arena(a_high, a_high_len, b_high, b_high_len, sratch_arena, out_arena);

   const size_t a_tmp_len = std::max(a_low_len, a_high_len) + 1;

   uint64_t *a_tmp = sratch_arena.alloc(a_tmp_len);

   add_n(a_tmp, a_low, a_low_len, a_high, a_high_len);

   const size_t b_tmp_len = std::max(b_low_len, b_high_len) + 1;

   uint64_t *b_tmp = sratch_arena.alloc(b_tmp_len);

   add_n(b_tmp, b_low, b_low_len, b_high, b_high_len);

   uint64_t *z1 = karatsuba_arena(a_tmp, a_tmp_len, b_tmp, b_tmp_len, sratch_arena, out_arena);

   sratch_arena.rewind(mark); // rewind ptr back

   const size_t &z1_len = a_tmp_len + b_tmp_len;
   const size_t &z0_len = a_low_len + b_low_len;
   const size_t &z2_len = a_high_len + b_high_len;

   sub_n(z1, z1_len, z0, z0_len);

   sub_n(z1, z1_len, z2, z2_len);

   const size_t result_len = A_size + B_size;

   uint64_t *result = out_arena.alloc(result_len);

   memset(result + z0_len, 0, (result_len - z0_len) * sizeof(uint64_t));
   memcpy(result, z0, z0_len * sizeof(uint64_t));

   add_n(result + a_low_len, result_len - a_low_len, z1, z1_len);

   add_n(result + 2 * a_low_len, result_len - 2 * a_low_len, z2, z2_len);

   return result;
}

void mul_karatsuba_n(std::vector<uint64_t> &Res, const uint64_t *A_ptr, const size_t A_size,
                     const uint64_t *B_ptr, const size_t B_size)
{
   const size_t n = std::max(A_size, B_size);
   Arena out_arena(KARATSUBA_OUT_ARENA_FACTOR * n);
   Arena sratch_arena(KARATSUBA_SRATCH_ARENA_FACTOR * n);

   uint64_t *intermidiate = karatsuba_arena(A_ptr, A_size, B_ptr, B_size, out_arena, sratch_arena);
   Res.assign(intermidiate, intermidiate + A_size + B_size);
}

void mul_karatsuba_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size,
                     const uint64_t *B_ptr, const size_t B_size)
{
   const size_t n = std::max(A_size, B_size);
   Arena out_arena(KARATSUBA_OUT_ARENA_FACTOR * n);
   Arena sratch_arena(KARATSUBA_SRATCH_ARENA_FACTOR * n);

   uint64_t *intermidiate = karatsuba_arena(A_ptr, A_size, B_ptr, B_size, out_arena, sratch_arena);
   memcpy(Res, intermidiate, (A_size + B_size) * sizeof(uint64_t));
}
