// I should wrap this in a namespace but im too lazy

#ifndef __BIG_INT_
#define __BIG_INT_

#include <cstdint>
#include <cstring>
#include <immintrin.h>
#include <iostream>
#include <string>
#include <vector>

using u_int64_t = uint64_t;
using u_int8_t = uint8_t;
int inline cmp_abs_n(const u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
                     const size_t &B_size)
{
   if (A_size > B_size)
   {
      return 1;
   }

   if (A_size < B_size)
   {
      return -1;
   }

   for (size_t i = A_size; i-- > 0;)
   {
      if (A_ptr[i] > B_ptr[i])
      {
         return 1;
      }
      if (A_ptr[i] < B_ptr[i])
      {
         return -1;
      }
   }
   return 0;
}

void inline add_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
                  const size_t &B_size)
{
   u_int8_t carry{};

   unsigned long long *A_ptr_ull = reinterpret_cast<unsigned long long *>(A_ptr);

   for (u_int64_t i = 0; i < B_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr_ull[i], B_ptr[i], &A_ptr_ull[i]);
   }

   for (u_int64_t i = B_size; i < A_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr_ull[i], 0, &A_ptr_ull[i]);
   }
}

void inline add_n(u_int64_t *dest, const u_int64_t *A_ptr, const size_t &A_size,
                  const u_int64_t *B_ptr, const size_t &B_size)
{
   u_int8_t carry{};

   unsigned long long *dest_ull = reinterpret_cast<unsigned long long *>(dest);

   for (u_int64_t i = 0; i < B_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr[i], B_ptr[i], (dest_ull + i));
   }

   for (u_int64_t i = B_size; i < A_size; i++)
   {
      carry = _addcarry_u64(carry, A_ptr[i], 0, (dest_ull + i));
   }
}

void inline sub_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
                  const size_t &B_size)
{
   u_int8_t borrow{};

   unsigned long long *A_ptr_ull = reinterpret_cast<unsigned long long *>(A_ptr);

   for (size_t i = 0; i < B_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr_ull[i], B_ptr[i], &A_ptr_ull[i]);
   }

   for (size_t i = B_size; i < A_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr_ull[i], 0, &A_ptr_ull[i]);
   }
}

void inline sub_n(u_int64_t *dest, const u_int64_t *A_ptr, const size_t &A_size,
                  const u_int64_t *B_ptr, const size_t &B_size)
{
   u_int8_t borrow{};

   unsigned long long *dest_ull = reinterpret_cast<unsigned long long *>(dest);

   for (size_t i = 0; i < B_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr[i], B_ptr[i], dest_ull + i);
   }

   for (size_t i = B_size; i < A_size; i++)
   {
      borrow = _subborrow_u64(borrow, A_ptr[i], 0, dest_ull + i);
   }
}

void inline mul_n(u_int64_t *Res, const u_int64_t *A_ptr, const size_t &A_size,
                  const u_int64_t *B_ptr, const size_t &B_size)
{
   u_int64_t carry{};
   __uint128_t scratch{};

   for (size_t i = 0; i < A_size; i++)
   {
      carry = 0;
      for (size_t j = 0; j < B_size; j++)
      {
         scratch = static_cast<__uint128_t>(A_ptr[i]) * (B_ptr[j]) + Res[i + j] + carry;
         Res[i + j] = static_cast<u_int64_t>(scratch);
         carry = scratch >> 64;
      }
      Res[i + B_size] = static_cast<u_int64_t>(carry);
   }
}

inline void shl_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t &shift)
{
   if (shift == 0 || A_size == 0)
   {
      return;
   }
   const u_int64_t limb_shift = shift >> 6;
   const u_int64_t bit_shift = shift & 63;
   const u_int64_t bit_shift_cmpl = 64 - bit_shift;

   if (limb_shift)
   {
      memmove(A_ptr + limb_shift, A_ptr, A_size * sizeof(u_int64_t));

      for (size_t i = 0; i < limb_shift; i++)
      {
         A_ptr[i] = 0;
      }
   }

   if (bit_shift)
   {
      u_int64_t carry = 0;
      for (size_t i = 0; i < (A_size + limb_shift); i++)
      {
         A_ptr[i] = (A_ptr[i] << bit_shift) + carry;
         carry = A_ptr[i] >> bit_shift_cmpl;
      }
   }
}
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
   friend BigInt operator-(BigInt &, const BigInt &);

   friend BigInt &operator*=(BigInt &, const BigInt &);
   friend BigInt operator*(const BigInt &, const BigInt &);

   friend BigInt &operator<<=(BigInt &, const u_int64_t &);
   friend BigInt operator<<(const BigInt &, const u_int64_t &);

   friend std::ostream &operator<<(std::ostream &os, const BigInt &);
};

inline BigInt &operator+=(BigInt &A, const BigInt &B)
{
   const size_t &B_size = B.digits.size();
   const u_int64_t *B_ptr = B.digits.data();

   size_t A_size = A.digits.size();
   u_int64_t *A_ptr = A.digits.data();

   if (A.is_negative == B.is_negative)
   {
      A_size = std::max(A_size, B_size) + 1;

      A.digits.resize(A_size);

      A_ptr = A.digits.data();

      add_n(A_ptr, A_size, B_ptr, B_size);

      if (A.digits.back() == 0)
      {
         A.digits.pop_back();
      }
      return A;
   }

   int cmp = cmp_abs_n(A_ptr, A_size, B_ptr, B_size);

   if (cmp == 0)
   {
      A.digits.clear();
      A.digits.push_back(0);
      A.is_negative = false;
      return A;
   }

   if (cmp > 0)
   {
      sub_n(A_ptr, A_size, B_ptr, B_size);
      while (A_size >= 1 && A.digits.back() == 0)
      {
         A.digits.pop_back();
         A_size--;
      }
      return A;
   }

   A.digits.resize(B_size);

   A_ptr = A.digits.data();

   sub_n(A_ptr, B_ptr, B_size, A_ptr, A_size);

   while (A_size >= 1 && A.digits.back() == 0)
   {
      A.digits.pop_back();
      A_size--;
   }
   A.is_negative = B.is_negative;
   return A;
}

inline BigInt operator+(const BigInt &A, const BigInt &B)
{
   BigInt tmp = A;
   tmp += B;
   return tmp;
}

inline BigInt &operator-=(BigInt &A, const BigInt &B)
{
   const size_t B_size = B.digits.size();
   const u_int64_t *B_ptr = B.digits.data();

   size_t A_size = A.digits.size();
   u_int64_t *A_ptr = A.digits.data();

   if (A.is_negative != B.is_negative)
   {
      A_size = std::max(A_size, B_size) + 1;
      A.digits.resize(A_size);
      A_ptr = A.digits.data();

      add_n(A_ptr, A_size, B_ptr, B_size);

      if (A.digits.back() == 0)
      {
         A.digits.pop_back();
      }
      return A;
   }

   int cmp = cmp_abs_n(A_ptr, A_size, B_ptr, B_size);

   if (cmp == 0)
   {
      A.digits.clear();
      A.digits.push_back(0);
      A.is_negative = false;
      return A;
   }

   if (cmp > 0)
   {
      sub_n(A_ptr, A_size, B_ptr, B_size);

      while (A_size > 1 && A.digits.back() == 0)
      {
         A.digits.pop_back();
         A_size--;
      }
      return A;
   }

   A.digits.resize(B_size);

   A_ptr = A.digits.data();

   sub_n(A_ptr, B_ptr, B_size, A_ptr, A_size);

   while (!A.digits.empty() && A.digits.back() == 0)
   {
      A.digits.pop_back();
   }

   A.is_negative = !A.is_negative;

   return A;
}

inline BigInt operator-(const BigInt &A, const BigInt &B)
{
   BigInt tmp = A;
   tmp -= B;
   return tmp;
}

inline BigInt &operator*=(BigInt &A, const BigInt &B)
{
   u_int64_t A_size = A.digits.size(), B_size = B.digits.size();

   std::vector<u_int64_t> Res(A_size + B_size, 0);

   mul_n(Res.data(), A.digits.data(), A_size, B.digits.data(), B_size);

   A.digits = std::move(Res);

   if (A.digits.back() == 0)
   {
      A.digits.pop_back();
   }

   A.is_negative = A.is_negative ^ B.is_negative;

   return A;
}

inline BigInt operator*(const BigInt &A, const BigInt &B)
{
   BigInt tmp = A;
   tmp *= B;
   return tmp;
}

inline BigInt &operator<<=(BigInt &A, const u_int64_t &shift)
{

   u_int64_t A_size = A.digits.size();

   A.digits.resize(A_size + shift / 64 + 1);

   shl_n(A.digits.data(), A_size, shift);

   if (A.digits.back() == 0)
   {
      A.digits.pop_back();
   }
   return A;
}

inline BigInt operator<<(const BigInt &A, const u_int64_t &shift)
{
   BigInt tmp = A;
   tmp <<= shift;
   return A;
}
inline BigInt::BigInt(int64_t s)
{
   this->digits.push_back((s ^ (s >> 63)) - (s >> 63));
   this->is_negative = (s >> 63) & 1;
}

constexpr u_int64_t TEN18 = 1e18;

constexpr inline u_int64_t parse_18(const char *slice, size_t len)
{
   u_int64_t res{};
   for (size_t i{}; i < len; i++)
   {
      res = res * 10ULL + (slice[i] - '0');
   }
   return res;
}

inline BigInt::BigInt(const std::string &str)
{
   this->is_negative = (str[0] == '-');

   const char *data = str.data() + this->is_negative;

   size_t len = str.length() - this->is_negative;

   size_t rem = (len - 1) % 18 + 1;

   u_int64_t carry = parse_18(data, rem);

   this->digits.reserve(len / 18 + 2);

   this->digits.push_back(carry);

   for (size_t i = rem; i < len; i += 18)
   {
      carry = parse_18(data + i, 18);

      for (u_int64_t &d : this->digits)
      {
         __uint128_t tmp = static_cast<__uint128_t>(d) * TEN18 + carry;
         carry = tmp >> 64;
         d = static_cast<u_int64_t>(tmp);
      }
      if (carry)
      {
         this->digits.push_back(carry);
      }
   }
}

constexpr u_int64_t magic = 0xCCCCCCCCCCCCCCCD;

constexpr inline void fast_to_char(u_int64_t &n, char *buf)
{
   u_int64_t tmp = (static_cast<__uint128_t>(n) * magic) >> 67;
   *buf = static_cast<char>('0' + (n - tmp * 10));
   n = tmp;
}

inline std::string BigInt::to_str() const
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
      u_int64_t rem = 0;
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

inline std::ostream &operator<<(std::ostream &os, const BigInt &X)
{
   os << X.to_str();
   return os;
}
#endif
