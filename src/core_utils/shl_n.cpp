#include "core_utils.hpp"

void shl_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t &shift)
{
   if (shift == 0 || A_size == 0)
   {
      return;
   }
   const u_int64_t limb_shift = shift >> 6;
   const u_int64_t bit_shift = shift & 63;
   const u_int64_t bit_shift_cmpl = 64 - bit_shift;

   if (limb_shift)
   {
      for (size_t i = 0; i < A_size; i++)
      {
         A_ptr[i + limb_shift] = A_ptr[i];
      }

      for (size_t i = 0; i < limb_shift; i++)
      {
         A_ptr[i] = 0;
      }
   }

   if (bit_shift)
   {
      u_int64_t carry = 0;
      for (size_t i = 0; i < (A_size + limb_shift); i++)
      {
         A_ptr[i] = (A_ptr[i] << bit_shift) + carry;
         carry = A_ptr[i] >> bit_shift_cmpl;
      }
   }
}
