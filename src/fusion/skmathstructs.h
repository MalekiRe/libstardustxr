//
// Created by malek on 4/25/22.
//
#pragma once
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif

typedef struct skmath_color {
    float r, g, b, a;
} skmath_color;
#ifdef __cplusplus
}
static SKMath::color stardust_convert_skmath_color(skmath_color color) {
    return {color.r, color.g, color.b, color.a};
}
#endif
