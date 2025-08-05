#pragma once
#include "Arena.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <vector>

void karatsuba_n(std::vector<uint64_t> &Res, const uint64_t *A_ptr, const size_t A_size,
                 const uint64_t *B_ptr, const size_t B_size);

uint64_t *karatsuba_arena(const uint64_t *A_ptr, const size_t A_size, const uint64_t *B_ptr,
                          const size_t B_size, Arena &out_arena, Arena &sratch_arena);
