#define BLA_IMPLEMENTATION
#include "bla.h"

int main(void) {
    vec3 a = Vec3(1.f, 2.f, 2.f), b = Vec3(0.f, 1.f, 0.f);
    vec2 c = Vec(3.f, 4.f);
    vec4 d = Vec(1.f, 2.f, 3.f, 4.f);
    vec3 e = a * b;
    vec3 f = a.xxx;
    float g = bla_length(f);
    float h = bla_length(d);
    bla_print(e); // { 0.000000 2.000000 0.000000 }
    return 0;
}
