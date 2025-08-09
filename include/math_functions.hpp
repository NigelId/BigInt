#pragma once
#include "Arena.hpp"
#include "core_utils.hpp"
#include "internal/config.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <vector>

void mul_karatsuba_n(std::vector<uint64_t> &Res, const uint64_t *A_ptr, const size_t A_size,
                     const uint64_t *B_ptr, const size_t B_size);

void mul_karatsuba_n(uint64_t *Res, const uint64_t *A_ptr, const size_t A_size,
                     const uint64_t *B_ptr, const size_t B_size);
