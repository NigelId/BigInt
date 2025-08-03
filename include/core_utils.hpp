#pragma once

#include <cstdint>
#include <cstring>
#include <immintrin.h>

// function that act on limbs
void add_n(uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr, const size_t B_size);

void add_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
           const size_t B_size);

void sub_n(uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr, const size_t B_size);

void sub_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
           const size_t B_size);

void mul_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
           const size_t B_size);

void mul_scalar_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t s);
void mul_scalar_n(uint64_t *A_ptr, const size_t &A_size, const uint64_t &s);

void shl_n(uint64_t *A_ptr, const size_t Ao_size, const uint64_t shift);
void shl_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size, const uint64_t shift);

int cmp_abs_n(const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
              const size_t B_size);
