// Copyright 2023 ShenMian
// License(Apache-2.0)

#pragma once

#include "check.hpp"

#if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
#define USE_SSE
#elif defined(__clang__) && (defined(__i386__) || defined(__x86_64__))
#define USE_SSE
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
#define USE_SSE
#else
#error "Do not support SSE"
#endif

#ifdef USE_SSE
#include <xmmintrin.h>
#endif

namespace simd
{

#ifdef USE_SSE

/**
 * @brief SSE 矩阵相加.
 *
 * @param a 矩阵 A.
 * @param b 矩阵 B.
 * @param c 结果矩阵 C.
 */
inline void matrix_addu(const float a[16], const float b[16], float c[16])
{
	for(size_t i = 0; i < 4; i++)
	{
		const __m128 a_row = _mm_loadu_ps(a + i * 4);
		const __m128 b_row = _mm_loadu_ps(b + i * 4);
		const __m128 c_row = _mm_add_ps(a_row, b_row);
		_mm_storeu_ps(c + i * 4, c_row);
	}
}

/**
 * @brief SSE 矩阵相减.
 *
 * @param a 矩阵 A.
 * @param b 矩阵 B.
 * @param c 结果矩阵 C.
 */
inline void matrix_subu(const float a[16], const float b[16], float c[16])
{
	for(size_t i = 0; i < 4; i++)
	{
		const __m128 a_row = _mm_loadu_ps(a + i * 4);
		const __m128 b_row = _mm_loadu_ps(b + i * 4);
		const __m128 c_row = _mm_sub_ps(a_row, b_row);
		_mm_storeu_ps(c + i * 4, c_row);
	}
}

/**
 * @brief SSE 矩阵相乘.
 *
 * @param a 矩阵 A.
 * @param b 矩阵 B.
 * @param c 结果矩阵 C.
 */
inline void matrix_mulu(const float a[16], const float b[16], float c[16])
{
	const __m128 row1 = _mm_loadu_ps(&a[0]);
	const __m128 row2 = _mm_loadu_ps(&a[4]);
	const __m128 row3 = _mm_loadu_ps(&a[8]);
	const __m128 row4 = _mm_loadu_ps(&a[12]);

	for(int i = 0; i < 4; i++)
	{
		const __m128 col1 = _mm_set1_ps(b[i * 4 + 0]);
		const __m128 col2 = _mm_set1_ps(b[i * 4 + 1]);
		const __m128 col3 = _mm_set1_ps(b[i * 4 + 2]);
		const __m128 col4 = _mm_set1_ps(b[i * 4 + 3]);

		const __m128 row = _mm_add_ps(_mm_add_ps(_mm_mul_ps(col1, row1), _mm_mul_ps(col2, row2)),
		                        _mm_add_ps(_mm_mul_ps(col3, row3), _mm_mul_ps(col4, row4)));

		_mm_store_ps(&c[i * 4], row);
	}
}


/**
 * @brief 将数据从内存加载到 SSE 寄存器.
 *
 * @param mat 矩阵数据.
 */
inline void loadu(__m128 m[4], const std::span<float, 16> mat) noexcept
{
	m[0] = _mm_loadu_ps(&mat[0 * 4]);
	m[1] = _mm_loadu_ps(&mat[1 * 4]);
	m[2] = _mm_loadu_ps(&mat[2 * 4]);
	m[3] = _mm_loadu_ps(&mat[3 * 4]);
}

/**
 * @brief 将数据从内存加载到 SSE 寄存器.
 *
 * @param mat 矩阵数据. 内存地址必须是 16 字节对齐.
 */
inline void load(__m128 m[4], const float mat[16]) noexcept
{
	m[0] = _mm_load_ps(&mat[0 * 4]);
	m[1] = _mm_load_ps(&mat[1 * 4]);
	m[2] = _mm_load_ps(&mat[2 * 4]);
	m[3] = _mm_load_ps(&mat[3 * 4]);
}

inline void storeu(float* mat, const __m128 m[4]) noexcept
{
	_mm_storeu_ps(&mat[0 * 4], m[0]);
	_mm_storeu_ps(&mat[1 * 4], m[1]);
	_mm_storeu_ps(&mat[2 * 4], m[2]);
	_mm_storeu_ps(&mat[3 * 4], m[3]);
}

inline void store(float* mat, const __m128 m[4]) noexcept
{
	_mm_store_ps(&mat[0 * 4], m[0]);
	_mm_store_ps(&mat[1 * 4], m[1]);
	_mm_store_ps(&mat[2 * 4], m[2]);
	_mm_store_ps(&mat[3 * 4], m[3]);
}

inline void loadu(__m128& v, const float* vec) noexcept
{
	v = _mm_loadu_ps(vec);
}

inline void load(__m128& v, const float* vec) noexcept
{
	v = _mm_load_ps(vec);
}

inline void storeu(float* vec, const __m128& v) noexcept
{
	_mm_storeu_ps(vec, v);
}

inline void store(float* vec, const __m128& v) noexcept
{
	_mm_store_ps(vec, v);
}

inline void add(const __m128 m1[4], const __m128 m2[4], __m128 dst[4]) noexcept
{
	dst[0] = _mm_add_ps(m1[0], m2[0]);
	dst[1] = _mm_add_ps(m1[1], m2[1]);
	dst[2] = _mm_add_ps(m1[2], m2[2]);
	dst[3] = _mm_add_ps(m1[3], m2[3]);
}

inline void sub(const __m128 m1[4], const __m128 m2[4], __m128 dst[4]) noexcept
{
	dst[0] = _mm_sub_ps(m1[0], m2[0]);
	dst[1] = _mm_sub_ps(m1[1], m2[1]);
	dst[2] = _mm_sub_ps(m1[2], m2[2]);
	dst[3] = _mm_sub_ps(m1[3], m2[3]);
}

inline void mul(const __m128 m1[4], const __m128 m2[4], __m128 dst[4]) noexcept
{
	__m128 tmp[4];
	{
		__m128 e0 = _mm_shuffle_ps(m2[0], m2[0], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(m2[0], m2[0], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(m2[0], m2[0], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(m2[0], m2[0], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 v0 = _mm_mul_ps(m1[0], e0);
		__m128 v1 = _mm_mul_ps(m1[1], e1);
		__m128 v2 = _mm_mul_ps(m1[2], e2);
		__m128 v3 = _mm_mul_ps(m1[3], e3);

		__m128 a0 = _mm_add_ps(v0, v1);
		__m128 a1 = _mm_add_ps(v2, v3);
		__m128 a2 = _mm_add_ps(a0, a1);

		tmp[0] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(m2[1], m2[1], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(m2[1], m2[1], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(m2[1], m2[1], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(m2[1], m2[1], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 v0 = _mm_mul_ps(m1[0], e0);
		__m128 v1 = _mm_mul_ps(m1[1], e1);
		__m128 v2 = _mm_mul_ps(m1[2], e2);
		__m128 v3 = _mm_mul_ps(m1[3], e3);

		__m128 a0 = _mm_add_ps(v0, v1);
		__m128 a1 = _mm_add_ps(v2, v3);
		__m128 a2 = _mm_add_ps(a0, a1);

		tmp[1] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(m2[2], m2[2], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(m2[2], m2[2], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(m2[2], m2[2], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(m2[2], m2[2], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 v0 = _mm_mul_ps(m1[0], e0);
		__m128 v1 = _mm_mul_ps(m1[1], e1);
		__m128 v2 = _mm_mul_ps(m1[2], e2);
		__m128 v3 = _mm_mul_ps(m1[3], e3);

		__m128 a0 = _mm_add_ps(v0, v1);
		__m128 a1 = _mm_add_ps(v2, v3);
		__m128 a2 = _mm_add_ps(a0, a1);

		tmp[2] = a2;
	}

	{
		__m128 e0 = _mm_shuffle_ps(m2[3], m2[3], _MM_SHUFFLE(0, 0, 0, 0));
		__m128 e1 = _mm_shuffle_ps(m2[3], m2[3], _MM_SHUFFLE(1, 1, 1, 1));
		__m128 e2 = _mm_shuffle_ps(m2[3], m2[3], _MM_SHUFFLE(2, 2, 2, 2));
		__m128 e3 = _mm_shuffle_ps(m2[3], m2[3], _MM_SHUFFLE(3, 3, 3, 3));

		__m128 v0 = _mm_mul_ps(m1[0], e0);
		__m128 v1 = _mm_mul_ps(m1[1], e1);
		__m128 v2 = _mm_mul_ps(m1[2], e2);
		__m128 v3 = _mm_mul_ps(m1[3], e3);

		__m128 a0 = _mm_add_ps(v0, v1);
		__m128 a1 = _mm_add_ps(v2, v3);
		__m128 a2 = _mm_add_ps(a0, a1);

		tmp[3] = a2;
	}

	dst[0] = tmp[0];
	dst[1] = tmp[1];
	dst[2] = tmp[2];
	dst[3] = tmp[3];
}

inline void negate(const __m128 m[4], __m128 dst[4]) noexcept
{
	__m128 z = _mm_setzero_ps();
	dst[0]   = _mm_sub_ps(z, m[0]);
	dst[1]   = _mm_sub_ps(z, m[1]);
	dst[2]   = _mm_sub_ps(z, m[2]);
	dst[3]   = _mm_sub_ps(z, m[3]);
}

inline void transpose(const __m128 m[4], __m128 dst[4]) noexcept
{
	__m128 tmp0 = _mm_shuffle_ps(m[0], m[1], 0x44);
	__m128 tmp2 = _mm_shuffle_ps(m[0], m[1], 0xEE);
	__m128 tmp1 = _mm_shuffle_ps(m[2], m[3], 0x44);
	__m128 tmp3 = _mm_shuffle_ps(m[2], m[3], 0xEE);

	dst[0] = _mm_shuffle_ps(tmp0, tmp1, 0x88);
	dst[1] = _mm_shuffle_ps(tmp0, tmp1, 0xDD);
	dst[2] = _mm_shuffle_ps(tmp2, tmp3, 0x88);
	dst[3] = _mm_shuffle_ps(tmp2, tmp3, 0xDD);
}

inline void matrix_mul_vector(const __m128 m[4], const __m128& v, __m128& dst) noexcept
{
	__m128 col1 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(0, 0, 0, 0));
	__m128 col2 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(1, 1, 1, 1));
	__m128 col3 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 2, 2, 2));
	__m128 col4 = _mm_shuffle_ps(v, v, _MM_SHUFFLE(3, 3, 3, 3));

	dst = _mm_add_ps(_mm_add_ps(_mm_mul_ps(m[0], col1), _mm_mul_ps(m[1], col2)),
	                 _mm_add_ps(_mm_mul_ps(m[2], col3), _mm_mul_ps(m[3], col4)));
}

inline void vector_mul_matrix(const __m128 v, const __m128 m[4], __m128 dst[4]) noexcept
{
	MATH_DEBUG_CHECK(false);
}

#endif

} // namespace simd
