//
// Created by malek on 4/25/22.
//
#include "ctext.h"
#include "text.hpp"

text_t *text_create(spatial *parent, char *str) {
    text_t *t;
    StardustXRFusion::Text *obj;
    t = (text_t*)malloc(sizeof(*t));
    obj = new StardustXRFusion::Text(getSpatial(parent), std::string(str));
    t->obj = obj;
    return t;
}
