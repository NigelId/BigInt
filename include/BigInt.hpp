#pragma once
#include <string>
#include <sys/types.h>
#include <vector>

class BigInt
{
 private:
   bool is_negative{};

 public:
   std::vector<u_int64_t> digits;
   BigInt(const int64_t s);
   BigInt(const std::string &);

   BigInt(const BigInt &) noexcept = default;

 public:
   std::string to_str() const;
   std::string to_vec() const;

   friend BigInt &operator+=(BigInt &, const BigInt &);
   friend BigInt operator+(const BigInt &, const BigInt &);

   friend BigInt &operator-=(BigInt &, const BigInt &);
   friend BigInt operator-(const BigInt &, const BigInt &);

   BigInt &operator=(const BigInt &) noexcept = default;
};
