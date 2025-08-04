#include "core_utils.hpp"
#include <cstring>

/* Assume that you have padded A to the new size which is [Prev A_size +  shift / 64 + 1]
 we extract carry first then shift each limbs then add the previous carry*/

void shl_n(uint64_t *A_ptr, const size_t A_size, const uint64_t shift)
{
   if (shift == 0 || A_size == 0)
   {
      return;
   }
   const uint64_t limb_shift = shift >> 6;
   const uint64_t bit_shift = shift & 63;
   const uint64_t bit_shift_cmpl = 64 - bit_shift;

   // calculate the previous unpadded size
   size_t original_size = A_size - limb_shift - 1;

   if (limb_shift)
   {
      memmove(A_ptr + limb_shift, A_ptr, original_size * sizeof(uint64_t));
      memset(A_ptr, 0, limb_shift * sizeof(uint64_t));
   }

   if (bit_shift)
   {
      uint64_t carry = 0;
      for (size_t i = limb_shift; i < (A_size); i++)
      {
         uint64_t new_car = A_ptr[i] >> bit_shift_cmpl;
         A_ptr[i] = (A_ptr[i] << bit_shift) + carry;
         carry = new_car;
      }
   }
}

// same logic here, assume Res is big enough, at least A_size + limb_shift + 1.

void shl_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t shift)
{
   if (A_size == 0)
   {
      return;
   }

   const uint64_t limb_shift = shift >> 6;
   const uint64_t bit_shift = shift & 63;
   const uint64_t bit_shift_cmpl = 64 - bit_shift;

   if (limb_shift)
   {
      memset(Res, 0, limb_shift * sizeof(uint64_t));
   }
   memcpy(Res + limb_shift, A_ptr, A_size * sizeof(uint64_t));

   if (bit_shift)
   {
      uint64_t carry = 0;
      for (size_t i = limb_shift; i < (A_size + limb_shift); i++)
      {
         uint64_t new_car = Res[i] >> bit_shift_cmpl;
         Res[i] = (Res[i] << bit_shift) + carry;
         carry = new_car;
      }
      Res[A_size + limb_shift] = carry;
   }
}
