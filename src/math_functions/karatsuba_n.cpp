#include "core_utils.hpp"
#include "internal/config.hpp"
#include "math_functions.hpp"

/* the idea is for karatsuba_n to create an arena pass it to karatsuba_arena then copy into Res,
you can use karatsuba_arena without karatsuba_n by creating your own arena but be warned, it
will spit out a pointer that will die with the arena when the arena gets out of scope.
*/

/* And like always, we assume Res has the correct size */

void karatsuba_n(std::vector<uint64_t> &Res, const uint64_t *A_ptr, const size_t A_size,
                 const uint64_t *B_ptr, const size_t B_size)
{
   Arena arena(static_cast<size_t>(std::pow(A_size + B_size, 1.5201)));  // ~(Log2(3) - 0.6)
   uint64_t *intermidiate = karatsuba_arena(A_ptr, A_size, B_ptr, B_size, arena);
   Res.assign(intermidiate, intermidiate + A_size + B_size);
}

uint64_t *karatsuba_arena(const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
                          const size_t B_size, Arena &arena)
{
   if (B_size > A_size)
   {
      return karatsuba_arena(B_ptr, B_size, A_ptr, A_size, arena);
   }

   if (A_size < KARATSUBA_THRESHOLD || B_size < KARATSUBA_THRESHOLD)
   {
      uint64_t *Res = arena.alloc(A_size + B_size);
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

   uint64_t *z0 = karatsuba_arena(a_low, a_low_len, b_low, b_low_len, arena);

   uint64_t *z2 = karatsuba_arena(a_high, a_high_len, b_high, b_high_len, arena);
   const size_t a_tmp_len = std::max(a_low_len, a_high_len) + 1;
   uint64_t *a_tmp = arena.alloc(a_tmp_len);

   add_n(a_tmp, a_low, a_low_len, a_high, a_high_len);

   const size_t b_tmp_len = std::max(b_low_len, b_high_len) + 1;

   uint64_t *b_tmp = arena.alloc(b_tmp_len);

   add_n(b_tmp, b_low, b_low_len, b_high, b_high_len);

   uint64_t *z1 = karatsuba_arena(a_tmp, a_tmp_len, b_tmp, b_tmp_len, arena);

   const size_t &z1_len = a_tmp_len + b_tmp_len;
   const size_t &z0_len = a_low_len + b_low_len;
   const size_t &z2_len = a_high_len + b_high_len;

   sub_n(z1, z1_len, z0, z0_len);

   sub_n(z1, z1_len, z2, z2_len);

   const size_t result_len = A_size + B_size;

   uint64_t *result = arena.alloc(result_len);

   memset(result + z0_len, 0, (result_len - z0_len) * sizeof(uint64_t));
   memcpy(result, z0, z0_len * sizeof(uint64_t));

   add_n(result + a_low_len, result_len - a_low_len, z1, z1_len);

   add_n(result + 2 * a_low_len, result_len - 2 * a_low_len, z2, z2_len);
   return result;
}
