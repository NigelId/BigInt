#include "BigInt.hpp"
#include "core_utils.hpp"

BigInt &operator*=(BigInt &A, const BigInt &B)
{
   u_int64_t A_size = A.digits.size(), B_size = B.digits.size();

   std::vector<u_int64_t> Res(A_size + B_size, 0);

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
