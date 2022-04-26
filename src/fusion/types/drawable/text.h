//
// Created by malek on 4/25/22.
//
#pragma once
#include "../../skmathstructs.h"
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif
typedef struct text {
    void *obj;
}text;
text *stardust_text_create(spatial *parent, char *str);
void stardust_text_destroy(text *t);
void stardust_text_set_text(text *t, char* str);
void stardust_text_set_color(text *t, color color) ;

#ifdef __cplusplus
}
#endif