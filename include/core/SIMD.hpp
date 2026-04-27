
#pragma once

#if defined(__ARM_NEON) || defined(__ARM_NEON__)
#include <arm_neon.h>
#define HAS_SIMD 1
#define SIMD_NEON 1
#elif defined(__AVX2__)
#include <immintrin.h>
#define HAS_SIMD 1
#define SIMD_AVX2 1
#endif

namespace Math {
    // Helper to calculate dot product of 3D vectors using SIMD
    inline float dotSIMD(float x1, float y1, float z1, float x2, float y2, float z2) {
#ifdef SIMD_NEON
        float32x4_t v1 = {x1, y1, z1, 0.0f};
        float32x4_t v2 = {x2, y2, z2, 0.0f};
        return vaddvq_f32(vmulq_f32(v1, v2));
#elif defined(SIMD_AVX2)
        __m128 v1 = _mm_set_ps(0.0f, z1, y1, x1);
        __m128 v2 = _mm_set_ps(0.0f, z2, y2, x2);
        __m128 res = _mm_dp_ps(v1, v2, 0x71);
        return _mm_cvtss_f32(res);
#else
        return x1 * x2 + y1 * y2 + z1 * z2;
#endif
    }
}
