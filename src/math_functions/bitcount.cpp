#include "math_functions.hpp"

uint64_t bit_length(const uint64_t *digits, size_t n)
{

   while (n > 0 && digits[n - 1] == 0)
   {
      --n;
   }

   if (n == 0)
   {
      return 0;
   }

   return (n << 6) - __builtin_clzll(digits[n - 1]);
}
