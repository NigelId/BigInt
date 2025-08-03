#include "BigInt.hpp"
constexpr uint64_t magic = 0xCCCCCCCCCCCCCCCD;

constexpr uint64_t BASE = 10000000000000000000ULL; // 1e19
constexpr inline void fast_to_char(uint64_t &n, char *buf)
{
   uint64_t tmp = (static_cast<__uint128_t>(n) * magic) >> 67;
   *buf = static_cast<char>('0' + (n - tmp * 10));
   n = tmp;
}

uint64_t Divide128Div64To64(uint64_t high, uint64_t low, uint64_t divisor, uint64_t *remainder)
{
   uint64_t result;
   __asm__("divq %[v]"
           : "=a"(result), "=d"(*remainder)
           : [v] "r"(divisor), "a"(low), "d"(high));
   return result;
}

std::string BigInt::to_str() const
{
   if (digits.empty() || (digits.size() == 1 && digits[0] == 0))
   {
      return "0";
   }

   std::vector<uint64_t> temp(digits);
   std::vector<uint64_t> chunks;

   uint64_t *tmp_data = temp.data();

   size_t tmp_len = temp.size();

   chunks.reserve(tmp_len);

   uint64_t rem = 0;

   while (!temp.empty())
   {
      rem = 0;
      for (long i = tmp_len - 1; i >= 0; --i)
      {
         tmp_data[i] = Divide128Div64To64(rem, tmp_data[i], BASE, &rem);
      }

      chunks.push_back(rem);

      while (tmp_len > 0 && tmp_data[tmp_len - 1] == 0)
      {
         temp.pop_back();
         tmp_len--;
         tmp_data = temp.data();
      }
   }

   tmp_data = chunks.data();
   tmp_len = chunks.size();

   std::string result =
       static_cast<char>(45 & -this->is_negative) + std::to_string(tmp_data[tmp_len - 1]);

   result.reserve(tmp_len * 18 - 1);

   char TEN18CHUNKS[18];

   for (long i = tmp_len - 2; i >= 0; --i)
   {
      uint64_t n = tmp_data[i];

      for (int j = 17; j >= 0; j--)
      {
         fast_to_char(n, TEN18CHUNKS + j);
      }
      result.append(TEN18CHUNKS, 18);
   }

   return result;
}
