# bla

**B**asic **L**inear **A**lgebra: a single-header C library for vectors, matrices and quaternions, using clang's vector/matrix extensions and overloadable functions.

```c
#define BLA_IMPLEMENTATION
#include "bla.h"

vec3 a = Vec3(1, 2, 2);
float l = bla_length(a);          // also vec2, vec4
mat4 m = bla_mat4_translate(a);
vec3 p = bla_transform(Vec3(0, 0, 0), m);
bla_print(m);                     // vec2/3/4 and mat2/3/4
```

Function names carry a `bla_` prefix by default. Tables below list names without it.[^2]

Build with `clang -fenable-matrix`. C only.[^1]

## Types

| Type | Meaning |
| --- | --- |
| `vec2` `vec3` `vec4` | float vectors (`vecNi` for int) |
| `mat2` `mat3` `mat4` | square float matrices |
| `quat` | union of `vec4 v` and `float x, y, z, w` |

Constructors: `Vec2`, `Vec3`, `Vec4`, `Vec(...)` (2-4 args), `Quat(x, y, z, w)`, `Mat2`/`Mat3`/`Mat4` (zero matrix).

Vector operators work on `vecN` and on `q.v`; `quat` itself has no operators.

## Overloaded functions

| Group | Functions |
| --- | --- |
| vec2/3/4 | `is_zero` `sum` `cmp` `length` `length_sqr` `dot` `normalize` `distance` `distance_sqr` `clamp` `lerp` `reflect` `refract` `move_towards` `print` |
| mat2/3/4 | `is_zero` `is_identity` `cmp` `trace` `transpose` `column` `row` `determinant` `invert` `print` |
| vec2, vec3 | `cross` `angle` |
| vec2 / vec3 | `rotate(vec2, angle)` / `rotate(vec3, axis, angle)` |
| vec3 | `perpendicular` `barycenter` `unproject` `transform(vec3, mat4)` |
| vec4 | `transform(vec4, mat4)` |
| quat | `length` `length_sqr` `dot` `normalize` `cmp` `mul` `invert` `rotate(vec3, quat)` `slerp` `nlerp` |

## Notes

| Function | Behaviour |
| --- | --- |
| `invert(matN)` | returns the zero matrix when `abs(determinant) <= BLA_FLOAT_EPSILON` (`== 0` with `BLA_FLOAT_CMP_EXACT`)[^3] |
| `slerp(a, b, t)` | shortest arc; falls back to `nlerp` when nearly parallel; unit quaternions |
| `nlerp(a, b, t)` | normalized linear interpolation along the shortest arc |

## Named functions

Functions that differ only by return type include the type in the name.

| Group | Functions |
| --- | --- |
| Matrices | `matN_identity` `mat4_translate` `mat4_rotate` `mat4_scale` `frustum` `perspective` `ortho` `look_at` |
| Quaternions | `quat_zero` `quat_identity` `quat_from_axis_angle` `quat_to_axis_angle` `quat_from_euler` `quat_to_euler` `quat_to_from_vec3` `quat_from_mat4` `mat4_from_quat` |

## Configuration

| Macro | Effect |
| --- | --- |
| `BLA_PREFIX` | function name prefix (default `bla_`) |
| `BLA_FLOAT_EPSILON` | tolerance for `cmp` and `is_zero` (default `0.000001f`) |
| `BLA_FLOAT_CMP_EXACT` | `cmp` uses `==` |

## Limitations

- `Mat2()`..`Mat4()` use an empty initializer, a C23 extension that clang accepts in C11 (warns under `-pedantic`).
- `invert` treats any matrix with `abs(determinant) <= BLA_FLOAT_EPSILON` as singular, including uniformly tiny ones.
- `sum` loops over components because clang has no float `__builtin_reduce_add`.

## License

```
bla
Copyright (C) 2026 George Watson

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.
```


[^1]: Overloadable functions use clang name mangling, so the header does not compile as C++ or with gcc.
[^2]: Types (`vec3`, `mat4`, `quat`) and the `Vec`, `Vec2`..`Vec4`, `Quat`, `Mat2`..`Mat4` macros are never prefixed.
[^3]: A uniformly tiny matrix (for example scale `1e-3` in a `mat4`, determinant `1e-12`) also counts as singular.