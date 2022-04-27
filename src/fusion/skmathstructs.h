//
// Created by malek on 4/25/22.
//
#pragma once
#ifdef __cplusplus

typedef SKMath::vec3 temp_skmath_vec3;
typedef SKMath::quat temp_skmath_quat;
using namespace SKMath;
//C-Interface
extern "C" {
#endif

typedef struct skmath_color {
    float r, g, b, a;
} skmath_color;
typedef struct skmath_vec3 {
    float x, y, z;
} skmath_vec3;
typedef struct skmath_quat {
    float x, y, z, w;
} skmath_quat;
typedef struct skmath_vec2 {
    float x, y;
} skmath_vec2;
#ifdef __cplusplus
}
static SKMath::color stardust_convert_skmath_color(skmath_color color) {
    return {color.r, color.g, color.b, color.a};
}
static SKMath::vec3 stardust_convert_skmath_vec3(skmath_vec3 vec) {
    return {vec.x, vec.y, vec.z};
}
static SKMath::quat stardust_convert_skmath_quat(skmath_quat quat) {
    return {quat.x, quat.y, quat.z, quat.w};
}
static SKMath::vec2 stardust_convert_skmath_vec2(skmath_vec2 vec) {
    return {vec.x, vec.y};
}
#endif
