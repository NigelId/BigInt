#include "BigInt.hpp"

BigInt::BigInt(int64_t s)
{
   this->digits.push_back((s ^ (s >> 63)) - (s >> 63));
   this->is_negative = (s >> 63) & 1;
}

BigInt::BigInt(const uint64_t s) { this->digits.push_back(s); }
