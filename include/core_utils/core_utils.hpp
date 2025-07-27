#pragma once

#include <sys/types.h>

void add_n(u_int64_t *A_ptr, u_int64_t A_size, u_int64_t *B_ptr, u_int64_t B_size);

void sub_n(u_int64_t *A_ptr, u_int64_t A_size, u_int64_t *B_ptr, u_int64_t B_size);

void mul_n(u_int64_t *Res, u_int64_t *A_ptr, u_int64_t A_size, u_int64_t *B_ptr,
           u_int64_t b_size);

void shl_n(u_int64_t *Res, u_int64_t *A_ptr, u_int64_t A_size, u_int64_t *B_ptr,
           u_int64_t B_size);
