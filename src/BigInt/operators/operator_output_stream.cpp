#include "BigInt.hpp"
#include <iostream>

std::ostream &operator<<(std::ostream &os, const BigInt &X)
{
   os << X.to_str();
   return os;
}
