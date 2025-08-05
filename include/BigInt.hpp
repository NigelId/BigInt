#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class BigInt
{
 private:
   std::vector<uint64_t> digits;
   bool is_negative{};

 public:
   BigInt() = default;

   BigInt(const int64_t s);
   BigInt(const uint64_t s);

   BigInt(const std::string &);
   BigInt(const BigInt &) noexcept = default;
   BigInt(std::initializer_list<uint64_t> init) : digits(init) {}

 public:
   template <typename T, typename = typename std::enable_if<
                             std::is_integral<T>::value && !std::is_same<T, uint64_t>::value>::type>
   BigInt(T val)
       : BigInt(static_cast<
                typename std::conditional<std::is_signed<T>::value, int64_t, uint64_t>::type>(val))
   {
   }

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

   friend BigInt &operator/=(BigInt &, const BigInt &);
   friend BigInt operator/(const BigInt &, const BigInt &);

   friend BigInt &operator%=(BigInt &, const BigInt &);
   friend BigInt operator%(const BigInt &, const BigInt &);

 public:
   BigInt &operator++();
   BigInt &operator--();

 public:
   friend BigInt &operator+=(BigInt &, const uint64_t &);
   friend BigInt operator+(const BigInt &, const uint64_t &);

   friend BigInt &operator-=(BigInt &, const uint64_t &);
   friend BigInt operator-(const BigInt &, const uint64_t &);

   friend BigInt &operator*=(BigInt &, const uint64_t &);
   friend BigInt operator*(const BigInt &, const uint64_t &);

   friend BigInt &operator/=(BigInt &, const uint64_t &);
   friend BigInt operator/(const BigInt &, const uint64_t &);

   friend BigInt &operator%=(BigInt &, const uint64_t &);
   friend BigInt operator%(const BigInt &, const uint64_t &);

   friend BigInt &operator<<=(BigInt &, const uint64_t &);
   friend BigInt operator<<(const BigInt &, const uint64_t &);

 public:
   friend std::ostream &operator<<(std::ostream &os, const BigInt &);

 public:
   template <typename T>
   using IfNotU64_Return_BigInt_Ref =
       typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, uint64_t>::value,
                               BigInt &>::type;

   template <typename T>
   using IfNotU64_Return_BigInt =
       typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, uint64_t>::value,
                               BigInt>::type;

 public:
   /* BigInt x (sign int) can change sign of BigInt, using template to group all sign/unsign
    * type smaller than u64 */

   template <typename T> IfNotU64_Return_BigInt_Ref<T> friend operator*=(BigInt &A, const T &val);

   template <typename T> IfNotU64_Return_BigInt<T> friend operator*(const BigInt &A, const T &val);

   template <typename T> IfNotU64_Return_BigInt_Ref<T> friend operator/=(BigInt &A, const T &val);

   template <typename T> IfNotU64_Return_BigInt<T> friend operator/(const BigInt &A, const T &val);
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
using IfNotU64_Return_BigInt_Ref =
    typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, uint64_t>::value,
                            BigInt &>::type;

template <typename T>
using IfNotU64_Return_BigInt =
    typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, uint64_t>::value,
                            BigInt>::type;

template <typename T> IfNotU64_Return_BigInt_Ref<T> operator*=(BigInt &A, const T &val)
{
   int64_t tmp = val;
   A *= static_cast<uint64_t>(((tmp ^ (tmp >> 63)) - (tmp >> 63)));
   A.is_negative ^= (val < 0);
   return A;
}

template <typename T> IfNotU64_Return_BigInt<T> operator*(const BigInt &A, const T &val)
{
   BigInt a = A;
   a *= (val);
   return a;
}

template <typename T> IfNotU64_Return_BigInt_Ref<T> operator/=(BigInt &A, const T &val)
{
   int64_t tmp = val;
   A /= static_cast<uint64_t>(((tmp ^ (tmp >> 63)) - (tmp >> 63)));
   A.is_negative ^= (val < 0);
   return A;
}

template <typename T> IfNotU64_Return_BigInt<T> operator/(const BigInt &A, const T &val)
{
   BigInt a = A;
   a /= (val);
   return a;
}
