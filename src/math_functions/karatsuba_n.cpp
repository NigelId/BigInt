#include "math_functions.hpp"
/* The idea is for karatsuba_n to create an arena, so it can handle memory easier all allocations
 * lives in arena, like z0,z1,z2. Do be noted the pointer that karatsuba_arena will get its data
 * deleted when arena gets out of scope*/

/* And like always, we assume Res has the correct size */

/* Memory is O(n) */

inline uint64_t *karatsuba_arena(const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
                                 const size_t B_size, Arena &out_arena)
{
   if (B_size > A_size)
   {
      return karatsuba_arena(B_ptr, B_size, A_ptr, A_size, out_arena);
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

   size_t z0_len = a_low_len + b_low_len;
   size_t z2_len = a_high_len + b_high_len;

   const size_t result_mark = out_arena.mark();

   const size_t result_len = A_size + B_size;

   uint64_t *result = out_arena.alloc(result_len);

   // step 1 : put z0 , z2 into out buffer
   {
      // jump back to force write z0,z2 into result by changing the offset of the arena

      out_arena.jump_to(result_mark);

      karatsuba_arena(a_low, a_low_len, b_low, b_low_len, out_arena);
      z0_len -= !(result[z0_len - 1]);

      karatsuba_arena(a_high, a_high_len, b_high, b_high_len, out_arena);
      z2_len -= !(result[z2_len - 1]);
   }

   {
      // step 2 : recursion again and calculate z1 , reusing z0 and z2 from result

      size_t a_tmp_len = std::max(a_low_len, a_high_len) + 1;
      size_t b_tmp_len = std::max(b_low_len, b_high_len) + 1;

      uint64_t *a_tmp = out_arena.alloc(a_tmp_len);
      add_n(a_tmp, a_low, a_low_len, a_high, a_high_len);

      a_tmp_len -= (!a_tmp[a_tmp_len - 1]);

      uint64_t *b_tmp = out_arena.alloc(b_tmp_len);
      add_n(b_tmp, b_low, b_low_len, b_high, b_high_len);

      b_tmp_len -= (!b_tmp[b_tmp_len - 1]);
      b_tmp_len -= (!b_tmp[b_tmp_len - 1]);

      uint64_t *z1 = karatsuba_arena(a_tmp, a_tmp_len, b_tmp, b_tmp_len, out_arena);

      size_t z1_len = a_tmp_len + b_tmp_len - (!z1[a_tmp_len + b_tmp_len - 1]);

      sub_n(z1, z1_len, result, z0_len);

      sub_n(z1, z1_len, result + 2 * a_low_len, z2_len);

      // step 3 reconstruct
      add_n(result + a_low_len, result_len - a_low_len, z1, z1_len);
   }
   // finally jump to the end of the result buffer so data wont overlap
   out_arena.jump_to(result_mark + result_len);
   return result;
}

void mul_karatsuba_n(std::vector<uint64_t> &Res, const uint64_t *A_ptr, const size_t A_size,
                     const uint64_t *B_ptr, const size_t B_size)
{
   const size_t n = std::max(A_size, B_size);
   Arena out_arena(KARATSUBA_ARENA_FACTOR * n);

   uint64_t *intermidiate = karatsuba_arena(A_ptr, A_size, B_ptr, B_size, out_arena);
   Res.assign(intermidiate, intermidiate + A_size + B_size);
}

void mul_karatsuba_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size,
                     const uint64_t *B_ptr, const size_t B_size)
{
   const size_t n = std::max(A_size, B_size);
   Arena out_arena(KARATSUBA_ARENA_FACTOR * n);

   uint64_t *intermidiate = karatsuba_arena(A_ptr, A_size, B_ptr, B_size, out_arena);
   memcpy(Res, intermidiate, (A_size + B_size) * sizeof(uint64_t));
}
