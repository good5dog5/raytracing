#ifndef __RAY_MATH_TOOLKIT_H
#define __RAY_MATH_TOOLKIT_H

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <immintrin.h>

static inline __forceinline
void normalize(double *v)
{
    double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    assert(d != 0.0 && "Error calculating normal");

    v[0] /= d;
    v[1] /= d;
    v[2] /= d;
}

static inline __forceinline
double length(const double *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

static inline __forceinline
void add_vector(const double *a, const double *b, double *out)
{
    __m256i mask = _mm256_set_epi64x(0x0000000000000000, 0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff);
    __m256d c    = _mm256_loadu_pd(a);
    __m256d d    = _mm256_loadu_pd(b);
    __m256d dst  = _mm256_add_pd(c, d);
    _mm256_maskstore_pd(out, mask, dst);
}

static inline __forceinline
void subtract_vector(const double *a, const double *b, double *out)
{
        out[0] = a[0] - b[0];
        out[1] = a[1] - b[1];
        out[2] = a[2] - b[2];
}

static inline __forceinline
void multiply_vectors(const double *a, const double *b, double *out)
{
        out[0] = a[0] * b[0];
        out[1] = a[1] * b[1];
        out[2] = a[2] * b[2];
}

static inline __forceinline
void multiply_vector(const double *a, double b, double *out)
{
        out[0] = a[0] * b;
        out[1] = a[1] * b;
        out[2] = a[2] * b;
}

static inline __forceinline
void cross_product(const double *v1, const double *v2, double *out)
{
    out[0] = v1[1] * v2[2] - v1[2] * v2[1];
    out[1] = v1[2] * v2[0] - v1[0] * v2[2];
    out[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

static inline __forceinline
double dot_product(const double *v1, const double *v2)
{
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

static inline __forceinline
void scalar_triple_product(const double *u, const double *v, const double *w,
                           double *out)
{
    cross_product(v, w, out);
    multiply_vectors(u, out, out);
}

static inline __forceinline
double scalar_triple(const double *u, const double *v, const double *w)
{
    double tmp[3];
    cross_product(w, u, tmp);
    return dot_product(v, tmp);
}

#endif
