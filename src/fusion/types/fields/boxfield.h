//
// Created by malek on 4/27/22.
//

#pragma once

#include "field.h"

#ifdef __cplusplus
extern "C" {
#include <skmathstructs.h>

#endif

typedef struct stardust_boxfield {
    void *obj;
} stardust_boxfield;

    stardust_boxfield *stardust_boxfield_create(stardust_spatial *s, skmath_vec3 origin, skmath_quat orientation, skmath_vec3 size);
    void stardust_boxfield_destroy(stardust_boxfield *b);

    stardust_field *stardust_boxfield_to_field_cast(stardust_boxfield *);
#ifdef __cplusplus
}
#endif
