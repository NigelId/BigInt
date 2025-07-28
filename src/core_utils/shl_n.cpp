#include "core_utils.hpp"

// Assume that A is allocated enough and have already been shifted to the right if need any
void shl_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t &shift)
{
   if (shift == 0 || A_size == 0)
   {
      return;
   }
}
