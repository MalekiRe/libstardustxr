//
// Created by malek on 4/26/22.
//
//#include "../../flexbuffers_c.h"
#include <cflexbuffers/cflexwrapper.h>
#include <types/fields/field.h>
#include <skmathstructs.h>

#pragma once
#ifdef __cplusplus
//C-Interface
extern "C" {
#endif
typedef struct stardust_pulse_receiver {
    void *obj;
}stardust_pulse_receiver;

    stardust_pulse_receiver* stardust_pulse_receiver_create(stardust_spatial *parent, stardust_field *field, skmath_vec3 origin, skmath_quat orientation);
    void stardust_pulse_receiver_destroy(stardust_pulse_receiver* r);
    void stardust_pulse_receiver_set_on_data_received(stardust_pulse_receiver *r, void (*fun)(char*, flex_buff_reference*, void*));

#ifdef __cplusplus
}
#endif
