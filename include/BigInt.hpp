#pragma once
#include <string>
#include <sys/types.h>
#include <vector>

class BigInt
{
 private:
   std::vector<u_int64_t> digits;
   bool is_negative{};

 public:
   BigInt(const int64_t s);
   BigInt(const std::string &);
   BigInt(const BigInt &) noexcept = default;

 public:
   std::string to_str() const;
   std::string to_vec() const;

 public:
   BigInt &operator=(const BigInt &) noexcept = default;

   friend BigInt &operator+=(BigInt &, const BigInt &);
   friend BigInt operator+(const BigInt &, const BigInt &);

   friend BigInt &operator-=(BigInt &, const BigInt &);
   friend BigInt operator-(const BigInt &, const BigInt &);

   friend BigInt &operator*=(BigInt &, const BigInt &);
   friend BigInt operator*(const BigInt &, const BigInt &);

   friend BigInt &operator<<=(BigInt &, const u_int64_t &);
   friend BigInt operator<<(const BigInt &, const u_int64_t &);

   friend std::ostream &operator<<(std::ostream &os, const BigInt &);
};
