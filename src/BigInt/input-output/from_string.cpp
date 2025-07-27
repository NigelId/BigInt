#include "BigInt.hpp"

inline u_int64_t parse_18(const char *slice, size_t len)
{
   u_int64_t res{};
   for (size_t i{}; i < len; i++)
   {
      res = res * 10ULL + (slice[i] - '0');
   }
   return res;
}

BigInt::BigInt(const std::string &str)
{
   const char *str_data = str.data();

   const size_t strlen = (str.length());

   this->is_negative = (str_data[0] == '-');

   this->digits.reserve(strlen / 18 + 2);

   this->digits.push_back(0);

   constexpr u_int64_t TEN18 = 1e18;

   for (size_t i = this->is_negative; i < strlen; i += 18)
   {
      u_int64_t carry = parse_18(str_data + i, std::min<u_int64_t>(strlen - i, 18));

      for (u_int64_t &limb : this->digits)
      {
         __uint128_t scratch = static_cast<__uint128_t>(limb) * TEN18 + carry;
         limb = static_cast<u_int64_t>(scratch);
         carry = scratch >> 64;
      }

      this->digits.push_back(carry);
   }

   this->digits.pop_back();
}
