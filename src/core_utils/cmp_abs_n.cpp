#include "core_utils.hpp"

int cmp_abs_n(const uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr,
              const size_t &B_size)
{
   if (A_size > B_size)
   {
      return 1;
   }

   if (A_size < B_size)
   {
      return -1;
   }

   for (size_t i = A_size; i-- > 0;)
   {
      if (A_ptr[i] > B_ptr[i])
      {
         return 1;
      }
      if (A_ptr[i] < B_ptr[i])
      {
         return -1;
      }
   }
   return 0;
}
