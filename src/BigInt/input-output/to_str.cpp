#include "BigInt.hpp"

std::string BigInt::to_str() const
{
   if (digits.empty() || (digits.size() == 1 && digits[0] == 0))
   {
      return "0";
   }

   std::vector<u_int64_t> temp(digits);
   std::vector<u_int64_t> chunks;

   while (!temp.empty())
   {
      __uint128_t rem = 0;
      for (int i = static_cast<int>(temp.size()) - 1; i >= 0; --i)
      {
         __uint128_t cur = (__uint128_t(temp[i]) + (rem << 64));
         temp[i] = static_cast<u_int64_t>(cur >> 64);
         rem = static_cast<u_int64_t>(cur);
      }

      chunks.push_back(static_cast<u_int64_t>(rem));
      while (!temp.empty() && temp.back() == 0)
         temp.pop_back();
   }

   std::string result = (is_negative ? "-" : "");
   auto it = chunks.rbegin();
   result += std::to_string(*it++);

   for (; it != chunks.rend(); ++it)
   {
      std::string part = std::to_string(*it);
      result += std::string(18 - part.size(), '0') + part;
   }

   return result;
}
