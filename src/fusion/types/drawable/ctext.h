//
// Created by malek on 4/25/22.
//
#include <types/spatial/spatial.hpp>
#include "../spatial/spatial.h"
#ifndef BUILD_TEXT_H
#define BUILD_TEXT_H
#ifdef __cplusplus
extern "C" {
#endif
    typedef struct text {
        void *obj;
    }text_t;
    text_t *text_create(spatial *parent, char* str);
    void text_destroy(text *t);

    void text_set(text *t, char* str);
    void color_set(text *t, int color);

#ifdef __cplusplus
}
static StardustXRFusion::Spatial *getSpatial(spatial *s) {
    return static_cast<StardustXRFusion::Spatial *>(s->obj);
}
#endif
#endif //BUILD_TEXT_H
