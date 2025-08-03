#include "BigInt.hpp"
#include "internal/config.hpp"

constexpr inline uint64_t parse_19(const char *slice, size_t len)
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

   size_t rem = (len - 1) % 19 + 1;

   uint64_t carry = parse_19(data, rem);

   this->digits.reserve(len / 19 + 2);

   this->digits.push_back(carry);

   for (size_t i = rem; i < len; i += 19)
   {
      carry = parse_19(data + i, 19);

      for (uint64_t &d : this->digits)
      {
         __uint128_t tmp = static_cast<__uint128_t>(d) * RADIX_IO_CONSTANT + carry;
         carry = tmp >> 64;
         d = static_cast<uint64_t>(tmp);
      }
      if (carry)
      {
         this->digits.push_back(carry);
      }
   }
}
