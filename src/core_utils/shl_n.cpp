#include "core_utils.hpp"

void shl_n(uint64_t *A_ptr, const size_t &Ao_size, const uint64_t &shift)
{
   if (shift == 0 || Ao_size == 0)
   {
      return;
   }
   const uint64_t limb_shift = shift >> 6;
   const uint64_t bit_shift = shift & 63;
   const uint64_t bit_shift_cmpl = 64 - bit_shift;

   if (limb_shift)
   {
      memmove(A_ptr + limb_shift, A_ptr, Ao_size * sizeof(uint64_t));
      memset(A_ptr, 0, limb_shift * sizeof(uint64_t));
   }

   if (bit_shift)
   {
      uint64_t carry = 0;
      for (size_t i = limb_shift; i < (Ao_size + limb_shift); i++)
      {
         uint64_t new_car = A_ptr[i] >> bit_shift_cmpl;
         A_ptr[i] = (A_ptr[i] << bit_shift) + carry;
         carry = new_car;
      }
      A_ptr[Ao_size + limb_shift] = carry;
   }
}
