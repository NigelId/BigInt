#include "BigInt.hpp"

std::string BigInt::to_vec() const
{
   std::string tmp = "[";

   for (auto &d : digits)
   {
      tmp += (std::to_string(d) + ',' + ' ');
   }

   tmp.pop_back();
   tmp.pop_back();
   tmp += ']';
   return tmp;
}
