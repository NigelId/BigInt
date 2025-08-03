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
   Arena arena(static_cast<size_t>(std::pow(A_size + B_size, 1.5401)));
   uint64_t *intermidiate = karatsuba_arena(A_ptr, A_size, B_ptr, B_size, arena);
   Res.assign(intermidiate, intermidiate + A_size + B_size);
}

uint64_t *karatsuba_arena(const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
                          const size_t B_size, Arena &arena)
{
   if (B_size > A_size)
   {
      karatsuba_arena(B_ptr, B_size, A_ptr, A_size, arena);
   }

   if (A_size < KARATSUBA_THRESHOLD || B_size < KARATSUBA_THRESHOLD)
   {
      uint64_t *Res = arena.alloc(A_size + B_size);
      memset(Res, 0, (A_size) * sizeof(uint64_t));
      mul_n(Res, A_ptr, A_size, B_ptr, B_size);
      return Res;
   }

   const size_t A_HIGH_LEN = A_size >> 1;
   const size_t A_LOW_LEN = A_size - A_HIGH_LEN;

   const uint64_t *A_LOW = A_ptr;
   const uint64_t *A_HIGH = A_ptr + A_LOW_LEN;

   const size_t B_LOW_LEN = std::min(B_size, A_LOW_LEN);
   const size_t B_HIGH_LEN = B_size - B_LOW_LEN;

   const uint64_t *B_LOW = B_ptr;
   const uint64_t *B_HIGH = B_ptr + B_LOW_LEN;

   uint64_t *z0 = karatsuba_arena(A_LOW, A_LOW_LEN, B_LOW, B_LOW_LEN, arena);

   uint64_t *z2 = karatsuba_arena(A_HIGH, A_HIGH_LEN, B_HIGH, B_HIGH_LEN, arena);
   const size_t A_TEMP_LEN = std::max(A_LOW_LEN, A_HIGH_LEN) + 1;
   uint64_t *A_TEMP = arena.alloc(A_TEMP_LEN);

   // memset(A_TEMP + A_LOW_LEN, 0, (A_TEMP_LEN - A_LOW_LEN) * sizeof(uint64_t));
   // memcpy(A_TEMP, A_LOW, A_LOW_LEN * sizeof(uint64_t));

   add_n(A_TEMP, A_LOW, A_LOW_LEN, A_HIGH, A_HIGH_LEN);

   const size_t B_TEMP_LEN = std::max(B_LOW_LEN, B_HIGH_LEN) + 1;
   uint64_t *B_TEMP = arena.alloc(B_TEMP_LEN);

   // memset(B_TEMP, 0, B_TEMP_LEN * sizeof(uint64_t));
   // memcpy(B_TEMP, B_LOW, B_LOW_LEN * sizeof(uint64_t));

   add_n(B_TEMP, B_LOW, B_LOW_LEN, B_HIGH, B_HIGH_LEN);

   uint64_t *z1 = karatsuba_arena(A_TEMP, A_TEMP_LEN, B_TEMP, B_TEMP_LEN, arena);

   const size_t &z1_len = A_TEMP_LEN + B_TEMP_LEN;
   const size_t &z0_len = A_LOW_LEN + B_LOW_LEN;
   const size_t &z2_len = A_HIGH_LEN + B_HIGH_LEN;

   sub_n(z1, z1_len, z0, z0_len);

   sub_n(z1, z1_len, z2, z2_len);

   const size_t result_len = A_size + B_size;

   uint64_t *result = arena.alloc(result_len);

   memset(result + z0_len, 0, (result_len - z0_len) * sizeof(uint64_t));
   memcpy(result, z0, z0_len * sizeof(uint64_t));

   add_n(result + A_LOW_LEN, result_len - A_LOW_LEN, z1, z1_len);

   add_n(result + 2 * A_LOW_LEN, result_len - 2 * A_LOW_LEN, z2, z2_len);
   return result;
}
