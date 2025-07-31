#include "BigInt.hpp"
#include "core_utils.hpp"

BigInt &operator+=(BigInt &A, const BigInt &B)
{
   const size_t &B_size = B.digits.size();
   const uint64_t *B_ptr = B.digits.data();

   size_t A_size = A.digits.size();
   uint64_t *A_ptr = A.digits.data();

   if (A.is_negative == B.is_negative)
   {
      A_size = std::max(A_size, B_size) + 1;

      A.digits.resize(A_size);

      A_ptr = A.digits.data();

      add_n(A_ptr, A_size, B_ptr, B_size);

      if (A.digits.back() == 0)
      {
         A.digits.pop_back();
      }
      return A;
   }

   int cmp = cmp_abs_n(A_ptr, A_size, B_ptr, B_size);

   if (cmp == 0)
   {
      A.digits.clear();
      A.digits.push_back(0);
      A.is_negative = false;
      return A;
   }
   if (cmp > 0)
   {
      sub_n(A_ptr, A_size, B_ptr, B_size);
      while (A_size >= 1 && A.digits.back() == 0)
      {
         A.digits.pop_back();
         A_size--;
      }
      return A;
   }

   A.digits.resize(B_size);

   A_ptr = A.digits.data();

   sub_n(A_ptr, B_ptr, B_size, A_ptr, A_size);

   while (A_size >= 1 && A.digits.back() == 0)
   {
      A.digits.pop_back();
      A_size--;
   }
   A.is_negative = B.is_negative;
   return A;
}
BigInt operator+(const BigInt &A, const BigInt &B)
{
   BigInt tmp = A;
   tmp += B;
   return tmp;
}
