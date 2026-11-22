/* bla.h -- https://github.com/takeiteasy/bla

 Copyright (C) 2026  George Watson

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#ifndef BLA_HEADER
#define BLA_HEADER

#include <stdio.h>
#include <tgmath.h>
#include <stdbool.h>

#define BLA_OVERLOAD __attribute__((overloadable))

#ifndef BLA_PREFIX
#define BLA_PREFIX bla_
#endif
#define _BLA_FN_CAT(P, N) P##N
#define _BLA_FN(P, N) _BLA_FN_CAT(P, N)
#define F(N) _BLA_FN(BLA_PREFIX, N)

#define __BLA_TYPES \
    X(2)            \
    X(3)            \
    X(4)

#define vector(N) __attribute__((ext_vector_type((N))))
#define X(SZ) \
    typedef float vec##SZ vector(SZ);
__BLA_TYPES
#undef X
#define X(SZ) \
    typedef int vec##SZ##i vector(SZ);
__BLA_TYPES
#undef X
#undef vector

typedef union {
    vec4 v;
    struct { float x, y, z, w; };
} quat;

#define _MATRIX(X, Y) __attribute__((matrix_type((X), (Y))))
#define X(N) \
    typedef float mat##N##N _MATRIX(N, N);
__BLA_TYPES
#undef X
#define X(N) \
    typedef mat##N##N mat##N;
__BLA_TYPES
#undef X
#undef _MATRIX

#define X(N)                                                    \
    BLA_OVERLOAD bool F(is_zero)(vec##N);                       \
    BLA_OVERLOAD float F(sum)(vec##N);                          \
    BLA_OVERLOAD bool F(cmp)(vec##N, vec##N);                   \
    BLA_OVERLOAD float F(length_sqr)(vec##N);                   \
    BLA_OVERLOAD float F(length)(vec##N);                       \
    BLA_OVERLOAD float F(dot)(vec##N, vec##N);                  \
    BLA_OVERLOAD vec##N F(normalize)(vec##N);                   \
    BLA_OVERLOAD float F(distance_sqr)(vec##N, vec##N);         \
    BLA_OVERLOAD float F(distance)(vec##N, vec##N);             \
    BLA_OVERLOAD vec##N F(clamp)(vec##N, vec##N, vec##N);       \
    BLA_OVERLOAD vec##N F(lerp)(vec##N, vec##N, float);         \
    BLA_OVERLOAD vec##N F(reflect)(vec##N, vec##N);             \
    BLA_OVERLOAD vec##N F(refract)(vec##N, vec##N, float);      \
    BLA_OVERLOAD vec##N F(move_towards)(vec##N, vec##N, float); \
    BLA_OVERLOAD void F(print)(vec##N);                         \
    mat##N F(mat##N##_identity)(void);                          \
    BLA_OVERLOAD bool F(is_identity)(mat##N);                   \
    BLA_OVERLOAD bool F(is_zero)(mat##N);                       \
    BLA_OVERLOAD bool F(cmp)(mat##N, mat##N);                   \
    BLA_OVERLOAD float F(trace)(mat##N);                        \
    BLA_OVERLOAD mat##N F(transpose)(mat##N);                   \
    BLA_OVERLOAD vec##N F(column)(mat##N, unsigned int);        \
    BLA_OVERLOAD vec##N F(row)(mat##N, unsigned int);           \
    BLA_OVERLOAD void F(print)(mat##N);
__BLA_TYPES
#undef X

#define Mat2() (mat2){}
#define Mat3() (mat3){}
#define Mat4() (mat4){}

#define _BLA_VEC_PICK(_1, _2, _3, _4, NAME, ...) NAME
#define Vec(...) _BLA_VEC_PICK(__VA_ARGS__, Vec4, Vec3, Vec2, _)(__VA_ARGS__)
#define Vec2(x, y) (vec2){x, y}
#define Vec3(x, y, z) (vec3){x, y, z}
#define Vec4(x, y, z, w) (vec4){x, y, z, w}
#define Quat(qx, qy, qz, qw) (quat){.v = {qx, qy, qz, qw}}

BLA_OVERLOAD float F(angle)(vec2 v1, vec2 v2);
BLA_OVERLOAD float F(angle)(vec3 v1, vec3 v2);
BLA_OVERLOAD float F(cross)(vec2 a, vec2 b);
BLA_OVERLOAD vec3 F(cross)(vec3 v1, vec3 v2);
BLA_OVERLOAD vec2 F(rotate)(vec2 v, float angle);
BLA_OVERLOAD vec3 F(rotate)(vec3 v, vec3 axis, float angle);
BLA_OVERLOAD vec3 F(perpendicular)(vec3 v);
BLA_OVERLOAD vec3 F(barycenter)(vec3 p, vec3 a, vec3 b, vec3 c);
BLA_OVERLOAD vec3 F(transform)(vec3 v, mat4 mat);
BLA_OVERLOAD vec3 F(unproject)(vec3 source, mat4 projection, mat4 view);
BLA_OVERLOAD float F(determinant)(mat2 mat);
BLA_OVERLOAD float F(determinant)(mat3 mat);
BLA_OVERLOAD float F(determinant)(mat4 mat);
BLA_OVERLOAD mat2 F(invert)(mat2 mat);
BLA_OVERLOAD mat3 F(invert)(mat3 mat);
BLA_OVERLOAD mat4 F(invert)(mat4 mat);

BLA_OVERLOAD float F(length_sqr)(quat);
BLA_OVERLOAD float F(length)(quat);
BLA_OVERLOAD float F(dot)(quat, quat);
BLA_OVERLOAD quat F(normalize)(quat);
BLA_OVERLOAD bool F(cmp)(quat, quat);
BLA_OVERLOAD quat F(mul)(quat q1, quat q2);
BLA_OVERLOAD quat F(invert)(quat q);
BLA_OVERLOAD quat F(nlerp)(quat a, quat b, float t);
BLA_OVERLOAD quat F(slerp)(quat a, quat b, float t);
BLA_OVERLOAD vec3 F(rotate)(vec3 v, quat q);
BLA_OVERLOAD vec4 F(transform)(vec4 v, mat4 mat);
quat F(quat_zero)(void);
quat F(quat_identity)(void);
quat F(quat_to_from_vec3)(vec3 from, vec3 to);
quat F(quat_from_axis_angle)(vec3 axis, float angle);
void F(quat_to_axis_angle)(quat q, vec3 *outAxis, float *outAngle);
quat F(quat_from_euler)(float pitch, float yaw, float roll);
vec3 F(quat_to_euler)(quat q);
quat F(quat_from_mat4)(mat4 mat);
mat4 F(mat4_from_quat)(quat q);

mat4 F(mat4_translate)(vec3 v);
mat4 F(mat4_rotate)(vec3 axis, float angle);
mat4 F(mat4_scale)(vec3 scale);
mat4 F(frustum)(float left, float right, float bottom, float top, float near, float far);
mat4 F(perspective)(float fovY, float aspect, float nearPlane, float farPlane);
mat4 F(ortho)(float left, float right, float bottom, float top, float nearPlane, float farPlane);
mat4 F(look_at)(vec3 center, vec3 target, vec3 up);

#undef F
#endif // BLA_HEADER

#if defined(BLA_IMPLEMENTATION)
#define F(N) _BLA_FN(BLA_PREFIX, N)
#ifndef BLA_FLOAT_EPSILON
#define BLA_FLOAT_EPSILON 0.000001f
#endif

#ifndef BLA_FLOAT_CMP_EXACT
#define FLT_CMP(A, B) \
    (fabs((A) - (B)) <= BLA_FLOAT_EPSILON * fmax(1.f, fmax(fabs(A), fabs(B))))
#define VEC_CMP(A, B)                                                                     \
    (__builtin_reduce_and(__builtin_elementwise_abs((A) - (B)) <=                         \
                          BLA_FLOAT_EPSILON *                                             \
                          __builtin_elementwise_maxnum(                                   \
                              __builtin_elementwise_maxnum(__builtin_elementwise_abs(A),  \
                                                           __builtin_elementwise_abs(B)), \
                              (__typeof__(A)){0} + 1.f)) != 0)
#define IS_SINGULAR(D) (fabs(D) <= BLA_FLOAT_EPSILON)
#else
#define FLT_CMP(A, B) \
    ((A) == (B))
#define VEC_CMP(A, B) \
    (__builtin_reduce_and((A) == (B)) != 0)
#define IS_SINGULAR(D) ((D) == 0.f)
#endif

#define X(N)                                                                            \
    bool BLA_OVERLOAD F(is_zero)(vec##N v)                                              \
    {                                                                                   \
        return F(cmp)(v, (vec##N){0});                                                  \
    }                                                                                   \
    float BLA_OVERLOAD F(sum)(vec##N v)                                                 \
    {                                                                                   \
        float result = 0.f;                                                             \
        for (int i = 0; i < N; i++)                                                     \
            result += v[i];                                                             \
        return result;                                                                  \
    }                                                                                   \
    bool BLA_OVERLOAD F(cmp)(vec##N a, vec##N b)                                        \
    {                                                                                   \
        return VEC_CMP(a, b);                                                           \
    }                                                                                   \
    float BLA_OVERLOAD F(length_sqr)(vec##N v)                                          \
    {                                                                                   \
        return F(dot)(v, v);                                                            \
    }                                                                                   \
    float BLA_OVERLOAD F(length)(vec##N v)                                              \
    {                                                                                   \
        return sqrt(F(length_sqr)(v));                                                  \
    }                                                                                   \
    float BLA_OVERLOAD F(dot)(vec##N a, vec##N b)                                       \
    {                                                                                   \
        return F(sum)(a * b);                                                           \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(normalize)(vec##N v)                                          \
    {                                                                                   \
        return v * (1.f / F(length)(v));                                                \
    }                                                                                   \
    float BLA_OVERLOAD F(distance_sqr)(vec##N a, vec##N b)                              \
    {                                                                                   \
        return F(length_sqr)(b - a);                                                    \
    }                                                                                   \
    float BLA_OVERLOAD F(distance)(vec##N a, vec##N b)                                  \
    {                                                                                   \
        return sqrt(F(distance_sqr)(a, b));                                             \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(clamp)(vec##N v, vec##N min, vec##N max)                      \
    {                                                                                   \
        return __builtin_elementwise_minnum(__builtin_elementwise_maxnum(v, min), max); \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(lerp)(vec##N a, vec##N b, float t)                            \
    {                                                                                   \
        return a + t * (b - a);                                                         \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(reflect)(vec##N v, vec##N normal)                             \
    {                                                                                   \
        return v - (2.f * normal) * F(dot)(v, normal);                                  \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(refract)(vec##N v, vec##N n, float r)                         \
    {                                                                                   \
        float d = F(dot)(v, n);                                                         \
        float k = 1.f - r * r * (1.f - d * d);                                          \
        return k < 0 ? (vec##N){0} : r * v - (r * d + sqrt(k)) * n;                     \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(move_towards)(vec##N v, vec##N target, float maxDistance)     \
    {                                                                                   \
        vec##N delta = target - v;                                                      \
        float dist = F(length_sqr)(delta);                                              \
        if (!dist || (maxDistance >= 0 && dist <= maxDistance * maxDistance))           \
            return target;                                                              \
        return v + (delta * (maxDistance / sqrt(dist)));                                \
    }                                                                                   \
    void BLA_OVERLOAD F(print)(vec##N v)                                                \
    {                                                                                   \
        printf("{ ");                                                                   \
        for (int i = 0; i < N; i++)                                                     \
            printf("%.6f ", v[i]);                                                      \
        puts("}");                                                                      \
    }                                                                                   \
    mat##N F(mat##N##_identity)(void)                                                   \
    {                                                                                   \
        mat##N mat = Mat##N();                                                          \
        for (int i = 0; i < N; i++)                                                     \
            mat[i][i] = 1.f;                                                            \
        return mat;                                                                     \
    }                                                                                   \
    bool BLA_OVERLOAD F(is_identity)(mat##N mat)                                        \
    {                                                                                   \
        return F(cmp)(mat, F(mat##N##_identity)());                                     \
    }                                                                                   \
    bool BLA_OVERLOAD F(is_zero)(mat##N mat)                                            \
    {                                                                                   \
        return F(cmp)(mat, Mat##N());                                                   \
    }                                                                                   \
    bool BLA_OVERLOAD F(cmp)(mat##N a, mat##N b)                                        \
    {                                                                                   \
        for (int y = 0; y < N; y++)                                                     \
            for (int x = 0; x < N; x++)                                                 \
                if (!FLT_CMP(a[y][x], b[y][x]))                                         \
                    return false;                                                       \
        return true;                                                                    \
    }                                                                                   \
    float BLA_OVERLOAD F(trace)(mat##N mat)                                             \
    {                                                                                   \
        float result = 0.f;                                                             \
        for (int i = 0; i < N; i++)                                                     \
            result += mat[i][i];                                                        \
        return result;                                                                  \
    }                                                                                   \
    mat##N BLA_OVERLOAD F(transpose)(mat##N mat)                                        \
    {                                                                                   \
        return __builtin_matrix_transpose(mat);                                         \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(column)(mat##N mat, unsigned int column)                      \
    {                                                                                   \
        vec##N result = {0};                                                            \
        if (column >= N)                                                                \
            return result;                                                              \
        for (int i = 0; i < N; i++)                                                     \
            result[i] = mat[column][i];                                                 \
        return result;                                                                  \
    }                                                                                   \
    vec##N BLA_OVERLOAD F(row)(mat##N mat, unsigned int row)                            \
    {                                                                                   \
        vec##N result = {0};                                                            \
        if (row >= N)                                                                   \
            return result;                                                              \
        for (int i = 0; i < N; i++)                                                     \
            result[i] = mat[i][row];                                                    \
        return result;                                                                  \
    }                                                                                   \
    void BLA_OVERLOAD F(print)(mat##N mat)                                              \
    {                                                                                   \
        for (int x = 0; x < N; x++) {                                                   \
            printf("| ");                                                               \
            for (int y = 0; y < N; y++)                                                 \
                printf("%.6f ", mat[x][y]);                                             \
            printf("|\n");                                                              \
        }                                                                               \
    }
__BLA_TYPES
#undef X

float BLA_OVERLOAD F(angle)(vec2 v1, vec2 v2) {
    return atan2(v2.y, v2.x) - atan2(v1.y, v1.x);
}

vec2 BLA_OVERLOAD F(rotate)(vec2 v, float angle) {
    float c = cos(angle);
    float s = sin(angle);
    return Vec2(v.x*c - v.y*s,  v.x*s + v.y*c);
}



float BLA_OVERLOAD F(cross)(vec2 a, vec2 b) {
    return a.x * b.y - a.y * b.x;
}


vec3 BLA_OVERLOAD F(cross)(vec3 v1, vec3 v2) {
    return Vec3(v1.y*v2.z - v1.z*v2.y,
                v1.z*v2.x - v1.x*v2.z,
                v1.x*v2.y - v1.y*v2.x);
}

vec3 BLA_OVERLOAD F(perpendicular)(vec3 v) {
    float min = (float) fabs(v.x);
    vec3 a = {1.f, 0.f, 0.f};
    if (fabs(v.y) < min) {
        min = (float) fabs(v.y);
        a = (vec3){0.f, 1.f, 0.f};
    }
    if (fabs(v.z) < min)
        a = (vec3){0};
    return Vec3(v.y * a.z - v.z * a.y,
                v.z * a.x - v.x * a.z,
                v.x * a.y - v.y * a.x);
}

float BLA_OVERLOAD F(angle)(vec3 v1, vec3 v2) {
    return atan2(F(length)(F(cross)(v1, v2)), F(dot)(v1, v2));
}

vec3 BLA_OVERLOAD F(rotate)(vec3 v, quat q) {
    return Vec3(v.x * (q.x * q.x + q.w * q.w - q.y * q.y - q.z * q.z) + v.y * (2 * q.x * q.y - 2 * q.w * q.z) + v.z * (2 * q.x * q.z + 2 * q.w * q.y),
                v.x * (2 * q.w * q.z + 2 * q.x * q.y) + v.y * (q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z) + v.z * (-2 * q.w * q.x + 2 * q.y * q.z),
                v.x * (-2 * q.w * q.y + 2 * q.x * q.z) + v.y * (2 * q.w * q.x + 2 * q.y * q.z) + v.z * (q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z));
}

vec3 BLA_OVERLOAD F(rotate)(vec3 v, vec3 axis, float angle) {
    // Using Euler-Rodrigues Formula
    // Ref.: https://en.wikipedia.org/w/index.php?title=Euler%E2%80%93Rodrigues_formula

    axis *= (1.f / fminf(fmaxf(F(length)(axis), 0.f), 1.f));

    angle /= 2.f;
    vec3 w = axis * sin(angle);
    vec3 wv = F(cross)(w, v);
    return v + (wv * (cos(angle) * 2.f)) + (F(cross)(w, wv) * 2.f);
}


vec3 BLA_OVERLOAD F(barycenter)(vec3 p, vec3 a, vec3 b, vec3 c) {
    vec3 v0 = b - a;
    vec3 v1 = c - a;
    vec3 v2 = p - a;
    float d00 = F(dot)(v0, v0);
    float d01 = F(dot)(v0, v1);
    float d11 = F(dot)(v1, v1);
    float d20 = F(dot)(v2, v0);
    float d21 = F(dot)(v2, v1);
    float denom = d00*d11 - d01*d01;
    float y = (d11*d20 - d01*d21)/denom;
    float z = (d00*d21 - d01*d20)/denom;
    return Vec3(1.f - (z + y), y, z);
}

float BLA_OVERLOAD F(length_sqr)(quat q) {
    return F(length_sqr)(q.v);
}

float BLA_OVERLOAD F(length)(quat q) {
    return F(length)(q.v);
}

float BLA_OVERLOAD F(dot)(quat a, quat b) {
    return F(dot)(a.v, b.v);
}

quat BLA_OVERLOAD F(normalize)(quat q) {
    return (quat){.v = F(normalize)(q.v)};
}

quat BLA_OVERLOAD F(nlerp)(quat a, quat b, float t) {
    if (F(dot)(a, b) < 0.f)
        b.v = -b.v;
    return F(normalize)((quat){.v = a.v + t * (b.v - a.v)});
}

quat BLA_OVERLOAD F(slerp)(quat a, quat b, float t) {
    float d = F(dot)(a, b);
    if (d < 0.f) {
        b.v = -b.v;
        d = -d;
    }
    if (d > 1.f - BLA_FLOAT_EPSILON)
        return F(nlerp)(a, b, t);
    float theta = acos(d);
    return (quat){.v = (a.v * sin((1.f - t) * theta) + b.v * sin(t * theta)) / sin(theta)};
}

bool BLA_OVERLOAD F(cmp)(quat a, quat b) {
    return F(cmp)(a.v, b.v);
}

quat F(quat_zero)(void) {
    return Quat(0.f, 0.f, 0.f, 0.f);
}

quat F(quat_identity)(void) {
    return Quat(0.f, 0.f, 0.f, 1.f);
}

quat BLA_OVERLOAD F(mul)(quat q1, quat q2) {
    float qax = q1.x, qay = q1.y, qaz = q1.z, qaw = q1.w;
    float qbx = q2.x, qby = q2.y, qbz = q2.z, qbw = q2.w;
    return Quat(qax * qbw + qaw * qbx + qay * qbz - qaz * qby,
                qay * qbw + qaw * qby + qaz * qbx - qax * qbz,
                qaz * qbw + qaw * qbz + qax * qby - qay * qbx,
                qaw * qbw - qax * qbx - qay * qby - qaz * qbz);
}

quat BLA_OVERLOAD F(invert)(quat q) {
    float lsqr = F(length_sqr)(q);
    if (lsqr == 0.f)
        return q;
    float inv = 1.f / lsqr;
    return Quat(-q.x * inv, -q.y * inv, -q.z * inv, q.w * inv);
}

quat F(quat_to_from_vec3)(vec3 from, vec3 to) {
    vec3 axis = F(cross)(from, to);
    return F(normalize)(Quat(axis.x, axis.y, axis.z, 1.f + F(dot)(from, to)));
}

quat F(quat_from_mat4)(mat4 mat) {
    float fourWSquaredMinus1 = mat[0][0] + mat[1][1] + mat[2][2];
    float fourXSquaredMinus1 = mat[0][0] - mat[1][1] - mat[2][2];
    float fourYSquaredMinus1 = mat[1][1] - mat[0][0] - mat[2][2];
    float fourZSquaredMinus1 = mat[2][2] - mat[0][0] - mat[1][1];

    int biggestIndex = 0;
    float fourBiggestSquaredMinus1 = fourWSquaredMinus1;
    if (fourXSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourXSquaredMinus1;
        biggestIndex = 1;
    }
    if (fourYSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourYSquaredMinus1;
        biggestIndex = 2;
    }
    if (fourZSquaredMinus1 > fourBiggestSquaredMinus1) {
        fourBiggestSquaredMinus1 = fourZSquaredMinus1;
        biggestIndex = 3;
    }

    float biggestVal = sqrt(fourBiggestSquaredMinus1 + 1.f) * .5f;
    float mult = .25f / biggestVal;
    switch (biggestIndex) {
        case 0:
            return Quat(
                (mat[2][1] - mat[1][2]) * mult,
                (mat[0][2] - mat[2][0]) * mult,
                (mat[1][0] - mat[0][1]) * mult,
                biggestVal
            );
        case 1: // X is biggest
            return Quat(
                biggestVal,
                (mat[1][0] + mat[0][1]) * mult,
                (mat[0][2] + mat[2][0]) * mult,
                (mat[2][1] - mat[1][2]) * mult
            );
        case 2: // Y is biggest
            return Quat(
                (mat[1][0] + mat[0][1]) * mult,
                biggestVal,
                (mat[2][1] + mat[1][2]) * mult,
                (mat[0][2] - mat[2][0]) * mult
            );
        case 3: // Z is biggest
            return Quat(
                (mat[0][2] + mat[2][0]) * mult,
                (mat[2][1] + mat[1][2]) * mult,
                biggestVal,
                (mat[1][0] - mat[0][1]) * mult
            );
        default:
            return F(quat_zero)();
    }
}

vec3 BLA_OVERLOAD F(unproject)(vec3 source, mat4 projection, mat4 view) {
    vec4 p = F(transform)(Vec4(source.x, source.y, source.z, 1.f), F(invert)(view * projection));
    return Vec3(p.x / p.w,
                p.y / p.w,
                p.z / p.w);
}

vec3 BLA_OVERLOAD F(transform)(vec3 v, mat4 mat) {
    return Vec3(mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z + mat[0][3],
                mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z + mat[1][3],
                mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z + mat[2][3]);
}

mat4 F(mat4_from_quat)(quat q) {
    float a2 = q.x*q.x;
    float b2 = q.y*q.y;
    float c2 = q.z*q.z;
    float ac = q.x*q.z;
    float ab = q.x*q.y;
    float bc = q.y*q.z;
    float ad = q.w*q.x;
    float bd = q.w*q.y;
    float cd = q.w*q.z;

    mat4 result = F(mat4_identity)();
    result[0][0] = 1 - 2 * (b2 + c2);
    result[1][0] = 2 * (ab + cd);
    result[2][0] = 2 * (ac - bd);

    result[0][1] = 2 * (ab - cd);
    result[1][1] = 1 - 2 * (a2 + c2);
    result[2][1] = 2 * (bc + ad);

    result[0][2] = 2 * (ac + bd);
    result[1][2] = 2 * (bc - ad);
    result[2][2] = 1 - 2 * (a2 + b2);
    return result;
}

quat F(quat_from_axis_angle)(vec3 axis, float angle) {
    float axisLength = F(length)(axis);
    if (axisLength == 0.f)
        return F(quat_identity)();

    axis = F(normalize)(axis);
    angle *= .5f;
    float sinres = sin(angle);
    float cosres = cos(angle);
    return Quat(axis.x * sinres,
                axis.y * sinres,
                axis.z * sinres,
                cosres);
}

void F(quat_to_axis_angle)(quat q, vec3 *outAxis, float *outAngle) {
    if (fabs(q.w) > 1.f)
        q = F(normalize)(q);
    float resAngle = 2.f * acos(q.w);
    float den = sqrt(1.f - q.w * q.w);
    vec3 qxyz = Vec3(q.x, q.y, q.z);
    vec3 resAxis = den > BLA_FLOAT_EPSILON ? qxyz / den : Vec3(1.f, 0.f, 0.f);
    *outAxis = resAxis;
    *outAngle = resAngle;
}

quat F(quat_from_euler)(float pitch, float yaw, float roll) {
    float x0 = cos(pitch * .5f);
    float x1 = sin(pitch * .5f);
    float y0 = cos(yaw   * .5f);
    float y1 = sin(yaw   * .5f);
    float z0 = cos(roll  * .5f);
    float z1 = sin(roll  * .5f);
    return Quat(x1 * y0 * z0 - x0 * y1 * z1,
                x0 * y1 * z0 + x1 * y0 * z1,
                x0 * y0 * z1 - x1 * y1 * z0,
                x0 * y0 * z0 + x1 * y1 * z1);
}

vec3 F(quat_to_euler)(quat q) {
    // Roll (x-axis rotation)
    float x0 = 2.f * (q.w * q.x + q.y * q.z);
    float x1 = 1.f - 2.f * (q.x * q.x + q.y * q.y);
    // Pitch (y-axis rotation)
    float y0 = 2.f * (q.w * q.y - q.z * q.x);
    y0 = y0 > 1.f ? 1.f : y0;
    y0 = y0 < -1.f ? -1.f : y0;
    // Yaw (z-axis rotation)
    float z0 = 2.f * (q.w * q.z + q.x * q.y);
    float z1 = 1.f - 2.f * (q.y * q.y + q.z * q.z);

    return Vec3(atan2(x0, x1),
                asin(y0),
                atan2(z0, z1));
}

vec4 BLA_OVERLOAD F(transform)(vec4 v, mat4 mat) {
    return Vec4(mat[0][0] * v.x + mat[0][1] * v.y + mat[0][2] * v.z + mat[0][3] * v.w,
                mat[1][0] * v.x + mat[1][1] * v.y + mat[1][2] * v.z + mat[1][3] * v.w,
                mat[2][0] * v.x + mat[2][1] * v.y + mat[2][2] * v.z + mat[2][3] * v.w,
                mat[3][0] * v.x + mat[3][1] * v.y + mat[3][2] * v.z + mat[3][3] * v.w);
}

float BLA_OVERLOAD F(determinant)(mat2 mat) {
    return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
}

float BLA_OVERLOAD F(determinant)(mat3 mat) {
    return mat[0][0] * (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) -
           mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) +
           mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]);
}

mat2 BLA_OVERLOAD F(invert)(mat2 mat) {
    float det = F(determinant)(mat);
    if (IS_SINGULAR(det))
        return Mat2();
    float invDet = 1.f / det;
    mat2 result = Mat2();
    result[0][0] = mat[1][1] * invDet;
    result[0][1] = -mat[0][1] * invDet;
    result[1][0] = -mat[1][0] * invDet;
    result[1][1] = mat[0][0] * invDet;
    return result;
}

mat3 BLA_OVERLOAD F(invert)(mat3 mat) {
    float det = F(determinant)(mat);
    if (IS_SINGULAR(det))
        return Mat3();
    float invDet = 1.f / det;
    mat3 result = Mat3();
    result[0][0] = (mat[1][1] * mat[2][2] - mat[1][2] * mat[2][1]) * invDet;
    result[0][1] = (mat[0][2] * mat[2][1] - mat[0][1] * mat[2][2]) * invDet;
    result[0][2] = (mat[0][1] * mat[1][2] - mat[0][2] * mat[1][1]) * invDet;
    result[1][0] = (mat[1][2] * mat[2][0] - mat[1][0] * mat[2][2]) * invDet;
    result[1][1] = (mat[0][0] * mat[2][2] - mat[0][2] * mat[2][0]) * invDet;
    result[1][2] = (mat[0][2] * mat[1][0] - mat[0][0] * mat[1][2]) * invDet;
    result[2][0] = (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]) * invDet;
    result[2][1] = (mat[0][1] * mat[2][0] - mat[0][0] * mat[2][1]) * invDet;
    result[2][2] = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) * invDet;
    return result;
}

float BLA_OVERLOAD F(determinant)(mat4 mat) {
    return mat[0][3] * mat[1][2] * mat[2][1] * mat[3][0] - mat[0][2] * mat[1][3] * mat[2][1] * mat[3][0] - mat[0][3] * mat[1][1] * mat[2][2] * mat[3][0] + mat[0][1] * mat[1][3] * mat[2][2] * mat[3][0] + mat[0][2] * mat[1][1] * mat[2][3] * mat[3][0] - mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0] - mat[0][3] * mat[1][2] * mat[2][0] * mat[3][1] + mat[0][2] * mat[1][3] * mat[2][0] * mat[3][1] + mat[0][3] * mat[1][0] * mat[2][2] * mat[3][1] - mat[0][0] * mat[1][3] * mat[2][2] * mat[3][1] - mat[0][2] * mat[1][0] * mat[2][3] * mat[3][1] + mat[0][0] * mat[1][2] * mat[2][3] * mat[3][1] + mat[0][3] * mat[1][1] * mat[2][0] * mat[3][2] - mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2] - mat[0][3] * mat[1][0] * mat[2][1] * mat[3][2] + mat[0][0] * mat[1][3] * mat[2][1] * mat[3][2] + mat[0][1] * mat[1][0] * mat[2][3] * mat[3][2] - mat[0][0] * mat[1][1] * mat[2][3] * mat[3][2] - mat[0][2] * mat[1][1] * mat[2][0] * mat[3][3] + mat[0][1] * mat[1][2] * mat[2][0] * mat[3][3] + mat[0][2] * mat[1][0] * mat[2][1] * mat[3][3] - mat[0][0] * mat[1][2] * mat[2][1] * mat[3][3] - mat[0][1] * mat[1][0] * mat[2][2] * mat[3][3] + mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3];
}

mat4 BLA_OVERLOAD F(invert)(mat4 mat) {
    float b00 = mat[0][0]*mat[1][1] - mat[1][0]*mat[0][1];
    float b01 = mat[0][0]*mat[2][1] - mat[2][0]*mat[0][1];
    float b02 = mat[0][0]*mat[3][1] - mat[3][0]*mat[0][1];
    float b03 = mat[1][0]*mat[2][1] - mat[2][0]*mat[1][1];
    float b04 = mat[1][0]*mat[3][1] - mat[3][0]*mat[1][1];
    float b05 = mat[2][0]*mat[3][1] - mat[3][0]*mat[2][1];
    float b06 = mat[0][2]*mat[1][3] - mat[1][2]*mat[0][3];
    float b07 = mat[0][2]*mat[2][3] - mat[2][2]*mat[0][3];
    float b08 = mat[0][2]*mat[3][3] - mat[3][2]*mat[0][3];
    float b09 = mat[1][2]*mat[2][3] - mat[2][2]*mat[1][3];
    float b10 = mat[1][2]*mat[3][3] - mat[3][2]*mat[1][3];
    float b11 = mat[2][2]*mat[3][3] - mat[3][2]*mat[2][3];
    float det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
    if (IS_SINGULAR(det))
        return Mat4();
    float invDet = 1.f / det;

    mat4 result = Mat4();
    result[0][0] = (mat[1][1]*b11 - mat[2][1]*b10 + mat[3][1]*b09)*invDet;
    result[1][0] = (-mat[1][0]*b11 + mat[2][0]*b10 - mat[3][0]*b09)*invDet;
    result[2][0] = (mat[1][3]*b05 - mat[2][3]*b04 + mat[3][3]*b03)*invDet;
    result[3][0] = (-mat[1][2]*b05 + mat[2][2]*b04 - mat[3][2]*b03)*invDet;
    result[0][1] = (-mat[0][1]*b11 + mat[2][1]*b08 - mat[3][1]*b07)*invDet;
    result[1][1] = (mat[0][0]*b11 - mat[2][0]*b08 + mat[3][0]*b07)*invDet;
    result[2][1] = (-mat[0][3]*b05 + mat[2][3]*b02 - mat[3][3]*b01)*invDet;
    result[3][1] = (mat[0][2]*b05 - mat[2][2]*b02 + mat[3][2]*b01)*invDet;
    result[0][2] = (mat[0][1]*b10 - mat[1][1]*b08 + mat[3][1]*b06)*invDet;
    result[1][2] = (-mat[0][0]*b10 + mat[1][0]*b08 - mat[3][0]*b06)*invDet;
    result[2][2] = (mat[0][3]*b04 - mat[1][3]*b02 + mat[3][3]*b00)*invDet;
    result[3][2] = (-mat[0][2]*b04 + mat[1][2]*b02 - mat[3][2]*b00)*invDet;
    result[0][3] = (-mat[0][1]*b09 + mat[1][1]*b07 - mat[2][1]*b06)*invDet;
    result[1][3] = (mat[0][0]*b09 - mat[1][0]*b07 + mat[2][0]*b06)*invDet;
    result[2][3] = (-mat[0][3]*b03 + mat[1][3]*b01 - mat[2][3]*b00)*invDet;
    result[3][3] = (mat[0][2]*b03 - mat[1][2]*b01 + mat[2][2]*b00)*invDet;
    return result;
}

mat4 F(mat4_translate)(vec3 v) {
    mat4 result = F(mat4_identity)();
    result[0][3] = v.x;
    result[1][3] = v.y;
    result[2][3] = v.z;
    return result;
}

mat4 F(mat4_rotate)(vec3 axis, float angle) {
    vec3 a = F(normalize)(axis);
    float s = sin(angle);
    float c = cos(angle);
    float t = 1.f - c;

    mat4 result = F(mat4_identity)();
    result[0][0] = a.x * a.x * t + c;
    result[1][0] = a.y * a.x * t + a.z * s;
    result[2][0] = a.z * a.x * t - a.y * s;
    result[0][1] = a.x * a.y * t - a.z * s;
    result[1][1] = a.y * a.y * t + c;
    result[2][1] = a.z * a.y * t + a.x * s;
    result[0][2] = a.x * a.z * t + a.y * s;
    result[1][2] = a.y * a.z * t - a.x * s;
    result[2][2] = a.z * a.z * t + c;
    return result;
}

mat4 F(mat4_scale)(vec3 scale) {
    mat4 result = Mat4();
    result[0][0] = scale.x;
    result[1][1] = scale.y;
    result[2][2] = scale.z;
    result[3][3] = 1.f;
    return result;
}

mat4 F(frustum)(float left, float right, float bottom, float top, float near, float far) {
    float rl = right - left;
    float tb = top - bottom;
    float fn = far - near;

    mat4 result = Mat4();
    result[0][0] = (near * 2.f)/rl;
    result[1][1] = (near * 2.f)/tb;
    result[0][2] = (right + left)/rl;
    result[1][2] = (top + bottom)/tb;
    result[2][2] = -(far + near)/fn;
    result[3][2] = -1.f;
    result[2][3] = -(far * near * 2.f)/fn;
    return result;
}

mat4 F(perspective)(float fovY, float aspect, float nearPlane, float farPlane) {
    float top = nearPlane * tan(fovY * 0.5f);
    float bottom = -top;
    float right = top * aspect;
    float left = -right;
    float rl = right - left;
    float tb = top - bottom;
    float fn = farPlane - nearPlane;

    mat4 result = Mat4();
    result[0][0] = (nearPlane * 2.0f) / rl;
    result[1][1] = (nearPlane * 2.0f) / tb;
    result[2][2] = -(farPlane + nearPlane) / fn;
    result[3][2] = -1.0f;
    result[2][3] = -(farPlane * nearPlane * 2.0f) / fn;
    result[3][3] = 0.0f;  // Explicit for clarity

    return result;
}

mat4 F(ortho)(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    float rl = right - left;
    float tb = top - bottom;
    float fn = farPlane - nearPlane;

    mat4 result = Mat4();
    result[0][0] = 2.0f / rl;
    result[1][1] = 2.0f / tb;
    result[2][2] = -2.0f / fn;
    result[0][3] = -(right + left) / rl;
    result[1][3] = -(top + bottom) / tb;
    result[2][3] = -(farPlane + nearPlane) / fn;
    result[3][3] = 1.0f;
    return result;
}

mat4 F(look_at)(vec3 eye, vec3 target, vec3 up) {
    vec3 vz = F(normalize)(eye - target);
    vec3 vx = F(normalize)(F(cross)(up, vz));
    vec3 vy = F(cross)(vz, vx);

    mat4 result = Mat4();
    result[0][0] = vx.x;
    result[1][0] = vy.x;
    result[2][0] = vz.x;
    result[0][1] = vx.y;
    result[1][1] = vy.y;
    result[2][1] = vz.y;
    result[0][2] = vx.z;
    result[1][2] = vy.z;
    result[2][2] = vz.z;
    result[0][3] = -F(dot)(vx, eye);
    result[1][3] = -F(dot)(vy, eye);
    result[2][3] = -F(dot)(vz, eye);
    result[3][3] = 1.f;
    return result;
}

#undef F
#endif // BLA_IMPLEMENTATION