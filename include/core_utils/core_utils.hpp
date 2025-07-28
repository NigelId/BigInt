#pragma once

#include <sys/types.h>

void add_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
           const size_t &B_size);

void add_n(u_int64_t *dest, const u_int64_t *A_ptr, const size_t &A_size,
           const u_int64_t *B_ptr, const size_t &B_size);

void sub_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
           const size_t &B_size);

void sub_n(u_int64_t *dest, const u_int64_t *A_ptr, const size_t &A_size,
           const u_int64_t *B_ptr, const size_t &B_size);

void mul_n(u_int64_t *Res, const u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
           const size_t &B_size);

void shl_n(u_int64_t *A_ptr, const size_t &A_size, const u_int64_t &shift);

void shl_n(u_int64_t *Res, const u_int64_t *A_ptr, const size_t &A_size,
           const u_int64_t &shift);

int cmp_abs_n(const u_int64_t *A_ptr, const size_t &A_size, const u_int64_t *B_ptr,
              const size_t &B_size);
