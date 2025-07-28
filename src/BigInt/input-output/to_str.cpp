#include "BigInt.hpp"
constexpr u_int64_t magic = 0xCCCCCCCCCCCCCCCD;
constexpr u_int64_t TEN18 = 1e18;

constexpr inline void fast_to_char(u_int64_t &n, char *buf)
{
   u_int64_t tmp = (static_cast<__uint128_t>(n) * magic) >> 67;
   *buf = static_cast<char>('0' + (n - tmp * 10));
   n = tmp;
}

std::string BigInt::to_str() const
{
   if (digits.empty() || (digits.size() == 1 && digits[0] == 0))
   {
      return "0";
   }

   std::vector<u_int64_t> temp(digits);
   std::vector<u_int64_t> chunks;

   u_int64_t *tmp_data = temp.data();

   size_t tmp_len = temp.size();

   chunks.reserve(tmp_len);

   while (!temp.empty())
   {
      __uint64_t rem = 0;
      for (long i = tmp_len - 1; i >= 0; --i)
      {
         __uint128_t cur = (__uint128_t(rem) << 64 | tmp_data[i]);
         tmp_data[i] = static_cast<u_int64_t>(cur / TEN18);
         rem = static_cast<u_int64_t>(cur - tmp_data[i] * TEN18);
      }

      chunks.push_back(rem);

      while (!temp.empty() && temp.back() == 0)
      {
         temp.pop_back();
         tmp_len--;
      }
      tmp_data = temp.data();
   }

   tmp_data = chunks.data();
   tmp_len = chunks.size();

   std::string result =
       static_cast<char>(45 & -this->is_negative) + std::to_string(tmp_data[tmp_len - 1]);

   result.reserve(tmp_len * 18 - 1);

   char TEN18CHUNKS[18];

   for (long i = tmp_len - 2; i >= 0; --i)
   {
      u_int64_t n = tmp_data[i];

      for (int j = 17; j >= 0; j--)
      {
         fast_to_char(n, TEN18CHUNKS + j);
      }
      result.append(TEN18CHUNKS, 18);
   }

   return result;
}
