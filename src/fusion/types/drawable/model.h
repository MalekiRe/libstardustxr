//
// Created by malek on 4/26/22.
//
#include "../spatial/spatial.h"
#include "../../skmathstructs.h"
#pragma once
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif
typedef struct stardust_model {
    void *obj;
}stardust_model;
stardust_model *stardust_model_create(stardust_spatial *parent, char *str);
void stardust_model_destroy(stardust_model *t);
void set_material_property_float(int submesh, char* propertyName, float value);
void set_material_property_color(int submesh, char* propertyName, skmath_color col);
void set_material_property_string(int submesh, char* propertyName, char* value);

#ifdef __cplusplus
}
#endif