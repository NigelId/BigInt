#include "BigInt.hpp"

const uint64_t TEN18 = 1000000000000000000ULL;

constexpr inline uint64_t parse_18(const char *slice, size_t len)
{
   uint64_t res{};
   for (size_t i{}; i < len; i++)
   {
      res = res * 10ULL + (slice[i] - '0');
   }
   return res;
}

BigInt::BigInt(const std::string &str)
{
   this->is_negative = (str[0] == '-');

   const char *data = str.data() + this->is_negative;

   size_t len = str.length() - this->is_negative;

   size_t rem = (len - 1) % 18 + 1;

   uint64_t carry = parse_18(data, rem);

   this->digits.reserve(len / 18 + 2);

   this->digits.push_back(carry);

   for (size_t i = rem; i < len; i += 18)
   {
      carry = parse_18(data + i, 18);

      for (uint64_t &d : this->digits)
      {
         __uint128_t tmp = static_cast<__uint128_t>(d) * TEN18 + carry;
         carry = tmp >> 64;
         d = static_cast<uint64_t>(tmp);
      }
      if (carry)
      {
         this->digits.push_back(carry);
      }
   }
}
