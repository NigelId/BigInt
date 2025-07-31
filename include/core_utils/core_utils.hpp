#pragma once

#include <cstdint>
#include <cstring>

void add_n(uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr, const size_t &B_size);

void add_n(uint64_t *dest, const uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr,
           const size_t &B_size);

void sub_n(uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr, const size_t &B_size);

void sub_n(uint64_t *dest, const uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr,
           const size_t &B_size);

void mul_n(uint64_t *Res, const uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr,
           const size_t &B_size);
// Assume putting old size in and already padded before
void shl_n(uint64_t *A_ptr, const size_t &Ao_size, const uint64_t &shift);

void shl_n(uint64_t *Res, const uint64_t *A_ptr, const size_t &A_size, const uint64_t &shift);

int cmp_abs_n(const uint64_t *A_ptr, const size_t &A_size, const uint64_t *B_ptr,
              const size_t &B_size);
