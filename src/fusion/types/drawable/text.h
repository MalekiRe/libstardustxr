//
// Created by malek on 4/25/22.
//
#include "../../skmathstructs.h"
#pragma once
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif
typedef struct stardust_text {
    void *obj;
}stardust_text;
stardust_text *stardust_text_create(stardust_spatial *parent, char *str);
void stardust_text_destroy(stardust_text *t);
void stardust_text_set_text(stardust_text *t, char* str);
void stardust_text_set_color(stardust_text *t, skmath_color color) ;

#ifdef __cplusplus
}
#endif