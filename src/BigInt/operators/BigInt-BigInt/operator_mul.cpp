#include "BigInt.hpp"
#include "core_utils.hpp"
#include "internal/config.hpp"
#include "math_functions.hpp"

BigInt &operator*=(BigInt &A, const BigInt &B)
{
   uint64_t A_size = A.digits.size(), B_size = B.digits.size();

   if (A_size > KARATSUBA_THRESHOLD || B_size > KARATSUBA_THRESHOLD)
   {
      karatsuba_n(A.digits, A.digits.data(), A_size, B.digits.data(), B_size);

      if (A.digits.back() == 0)
      {
         A.digits.pop_back();
      }

      A.is_negative = A.is_negative ^ B.is_negative;

      return A;
   }
   std::vector<uint64_t> Res(A_size + B_size, 0);

   mul_n(Res.data(), A.digits.data(), A_size, B.digits.data(), B_size);

   A.digits = std::move(Res);

   if (A.digits.back() == 0)
   {
      A.digits.pop_back();
   }

   A.is_negative = A.is_negative ^ B.is_negative;

   return A;
}
BigInt operator*(const BigInt &A, const BigInt &B)
{
   BigInt tmp = A;
   tmp *= B;
   return tmp;
}
