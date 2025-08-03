#include "BigInt.hpp"

// TODO : implement divide and conquer after div and mod
constexpr uint64_t magic = 0xCCCCCCCCCCCCCCCD;

constexpr inline void fast_to_char(uint64_t &n, char *buf)
{
   uint64_t tmp = (static_cast<__uint128_t>(n) * magic) >> 67;
   *buf = static_cast<char>('0' + (n - tmp * 10));
   n = tmp;
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

   __uint64_t rem = 0;

   while (!temp.empty())
   {
      rem = 0;
      for (long i = tmp_len - 1; i >= 0; --i)
      {
         asm("mov $10000000000000000000, %%rcx\n\t"
             "divq %%rcx"
             : "+a"(*(tmp_data + i)), "+d"(rem)
             :
             : "rcx", "cc");
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

   char TEN19CHUNKS[19];

   for (long i = tmp_len - 2; i >= 0; --i)
   {
      uint64_t n = tmp_data[i];

      for (int j = 18; j >= 0; j--)
      {
         fast_to_char(n, TEN19CHUNKS + j);
      }
      result.append(TEN19CHUNKS, 19);
   }

   return result;
}
